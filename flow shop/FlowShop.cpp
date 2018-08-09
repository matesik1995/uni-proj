#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>


using namespace std;

struct Task {
	int id;
	int op1_t;
	int op2_t;
	int readyTime;
};

struct Task_t : public Task {
	int op_start_t;
	int punish = 0;
	bool interruptable = true;
};

struct Maintenance {
	int id;
	int duration;
	int start_t;
};

vector<Task> tasks;
vector<Maintenance> maintenances;

struct Machine {
	int id;
	int schedulingBegin;
	int schedulingEnd;
	vector<Task_t> machineTasks;
	int punishment(int taskId) {
		int ret = 0;
		ret = tasks[taskId].op1_t / 5;
		if (tasks[taskId].op1_t % 5 != 0)
			ret += 1;
		return ret;
	}

	Task_t getTask(int taskId) {
		for (int i = 0; i < machineTasks.size(); i++) {
			if (machineTasks[i].id == taskId) {
				return machineTasks[i];
			}
		}
	}

	bool addTask(int taskId) {
		if (id == 1) {
			bool maint = false;

			Task_t newTask;
			newTask.id = tasks[taskId].id;
			newTask.op1_t = tasks[taskId].op1_t;
			newTask.op2_t = tasks[taskId].op2_t;
			newTask.op_start_t = -1;
			newTask.readyTime = tasks[taskId].readyTime;
			newTask.punish = 0;

			for (int i = 0; i < maintenances.size(); i++) {
				if (schedulingEnd == maintenances[i].start_t) {
					schedulingEnd += maintenances[i].duration;
					newTask.op_start_t = schedulingEnd;
					machineTasks.push_back(newTask);
					return true;
				}
			}
			if (schedulingEnd < tasks[taskId].readyTime)
			{
				return false;
			}
			if (newTask.op_start_t == -1)
			for (int i = 0; i < maintenances.size(); i++) {
				if (schedulingEnd<maintenances[i].start_t && (schedulingEnd + tasks[taskId].op1_t)>maintenances[i].start_t) {
					//cout << (maintenances[i].start_t - schedulingEnd) + maintenances[i].duration + tasks[taskId].op1_t << " <= " << tasks[taskId].op1_t + maintenances[i].duration + punishment(taskId) << endl;
					if ((maintenances[i].start_t - schedulingEnd) + maintenances[i].duration + tasks[taskId].op1_t <= tasks[taskId].op1_t + maintenances[i].duration + punishment(taskId)) {
						schedulingEnd += (maintenances[i].start_t - schedulingEnd) + maintenances[i].duration;
						newTask.op_start_t = maintenances[i].start_t + maintenances[i].duration;
						//cout << "MAINT: "<< maintenances[i].duration << endl;
						break;
					}
					else {
						newTask.punish = punishment(taskId);
						newTask.op_start_t = schedulingEnd;
						schedulingEnd += maintenances[i].duration;
						//cout << "MAINT: " << maintenances[i].start_t << " - " << maintenances[i].duration << endl;
						break;
					}
				}
			}

			if (newTask.op_start_t == -1)
				newTask.op_start_t = schedulingEnd;

			machineTasks.push_back(newTask);

			schedulingEnd += tasks[taskId].op1_t + newTask.punish;

			//cout << newTask.op_start_t << " " << newTask.op1_t << " " << newTask.punish << " " << schedulingEnd << endl;
		}
		else { // machine 2
			Task_t newTask;
			newTask.id = tasks[taskId].id;
			newTask.op1_t = tasks[taskId].op1_t;
			newTask.op2_t = tasks[taskId].op2_t;
			newTask.op_start_t = -1;
			newTask.readyTime = tasks[taskId].readyTime;
			newTask.punish = 0;

			newTask.op_start_t = schedulingEnd;
			machineTasks.push_back(newTask);
			schedulingEnd += tasks[taskId].op2_t;
		}
		return true;
	}

	void addTaskByTime(int time, int taskId) {
		if (id == 2) {
			Task_t newTask;
			newTask.id = tasks[taskId].id;
			newTask.op1_t = tasks[taskId].op1_t;
			newTask.op2_t = tasks[taskId].op2_t;
			newTask.op_start_t = -1;
			newTask.readyTime = tasks[taskId].readyTime;
			newTask.punish = 0;

			newTask.op_start_t = time;
			machineTasks.push_back(newTask);
			schedulingEnd = time + tasks[taskId].op2_t;
		}
	}

};

struct Schedule {
	int exec_time;
	vector<int> order;
	Machine machine1;
	Machine machine2;
	void init(vector<int> seed) {
		machine1.id = 1;
		machine2.id = 2;
		machine1.schedulingBegin = 0;
		machine1.schedulingEnd = 0;
		for (int i = 0; i < seed.size(); i++) {
			//Machine 1:
			int n = 1;
			while (!machine1.addTask(seed[i])) {
				//cout << "Blad uszeregowania, zamiana z " << i+n << " elementem\n";
				int tmp = seed[i];
				seed[i] = seed[i + n];
				seed[i + n] = tmp;
				n++;
			}
			order.push_back(seed[i]);
			//End Machine 1
			if (i == 0) {
				machine2.schedulingBegin = machine1.schedulingEnd;
				machine2.schedulingEnd = machine1.schedulingEnd;
			}
			if (machine1.schedulingEnd <= machine2.schedulingEnd)
				machine2.addTask(seed[i]);
			else
				machine2.addTaskByTime(machine1.schedulingEnd, seed[i]);
		}
		exec_time = machine2.schedulingEnd;
	}

	void printToFile(fstream &outputFile) {
		int idles1 = 0;
		int idles1_s = 0;
		cout << "M1: ";

		Task_t t0 = machine1.getTask(order[0]);
		if (t0.punish != 0 && t0.op_start_t == 0) {
			cout << "op1_" << t0.id << ", " << t0.op_start_t << ", " << t0.op1_t << ", " << t0.op1_t + t0.punish << ", ";
			for (int m = 0; m < maintenances.size(); m++) {
				if (maintenances[m].start_t > t0.op_start_t && maintenances[m].start_t <(t0.op_start_t + t0.op1_t + t0.punish)) {
					cout << "maint" << m << "_M1, " << maintenances[m].start_t << ", " << maintenances[m].duration << ", ";
					break;
				}
			}
		}
		else if (t0.op_start_t != 0) {
			for (int m = 0; m < maintenances.size(); m++) {
				if (maintenances[m].start_t >= 0 && maintenances[m].start_t <(t0.op_start_t)) {
					if (maintenances[m].start_t != 0) {
						cout << "idle" << idles1++ << "_M1, 0, " << maintenances[m].start_t << ", ";
						idles1_s += maintenances[m].start_t;
					}
					cout << "maint" << m << "_M1, " << maintenances[m].start_t << ", " << maintenances[m].duration << ", ";
					break;
				}
			}
			cout << "op1_" << t0.id << ", " << t0.op_start_t << ", " << t0.op1_t << ", " << t0.op1_t + t0.punish << ", ";
		}
		else {
			cout << "op1_" << t0.id << ", " << t0.op_start_t << ", " << t0.op1_t << ", " << t0.op1_t + t0.punish << ", ";
		}


		for (int i = 1; i < tasks.size(); i++) {
			Task_t t = machine1.getTask(order[i]);
			Task_t t1 = machine1.getTask(order[i - 1]);

			int prevmaint = 0;
			for (int m = 0; m < maintenances.size(); m++) {
				prevmaint = 0;
				if (maintenances[m].start_t > t1.op_start_t && maintenances[m].start_t <(t1.op_start_t + t1.op1_t + t1.punish)) {
					prevmaint = maintenances[m].duration;
					break;
				}
			}
			if (t1.punish == 0)
				prevmaint = 0;

			if (t.op_start_t != t1.op_start_t + t1.op1_t + t1.punish + prevmaint) {
				bool czy = true;
				for (int m = 0; m < maintenances.size(); m++) {
					if (maintenances[m].start_t >= (t1.op_start_t + t1.op1_t + t1.punish + prevmaint) && maintenances[m].start_t < t.op_start_t) {
						if (maintenances[m].start_t != t1.op_start_t + t1.op1_t + t1.punish + prevmaint) {
							cout << "idle" << idles1++ << "_M1, " << t1.op_start_t + t1.op1_t + t1.punish + prevmaint << ", " << maintenances[m].start_t - (t1.op_start_t + t1.op1_t + t1.punish + prevmaint) << ", ";
							idles1_s += maintenances[m].start_t - (t1.op_start_t + t1.op1_t + t1.punish + prevmaint);
						}
						cout << "maint" << m << "_M1, " << maintenances[m].start_t << ", " << maintenances[m].duration << ", ";
						czy = false;
						break;
					}
				}
				if (czy && t.op_start_t - (t1.op_start_t + t1.punish + prevmaint)>0) {
					cout << "idle" << idles1++ << "_M1, " << t1.op_start_t + t1.op1_t + t1.punish + prevmaint << ", " << t.op_start_t - (t1.op_start_t + t1.punish + prevmaint) << ", ";
					idles1_s += t.op_start_t - (t1.op_start_t + t1.op1_t);
				}
			}
			if (t.punish != 0) {
				cout << "op1_" << t.id << ", " << t.op_start_t << ", " << t.op1_t << ", " << t.op1_t + t.punish << ", ";
				for (int m = 0; m < maintenances.size(); m++) {
					if (maintenances[m].start_t > t.op_start_t && maintenances[m].start_t <(t.op_start_t + t.op1_t + t.punish)) {
						cout << "maint" << m << "_M1, " << maintenances[m].start_t << ", " << maintenances[m].duration << ", ";
						break;
					}
				}
			}
			else {
				cout << "op1_" << t.id << ", " << t.op_start_t << ", " << t.op1_t << ", " << t.op1_t + t.punish << ", ";
			}

		}
		int idles2 = 0;
		int idles2_s = 0;
		cout << "\nM2: ";
		t0 = machine2.getTask(order[0]);
		cout << "idle" << idles2++ << "_M2, " << 0 << ", " << t0.op_start_t << ", ";
		idles2_s += t0.op_start_t;
		cout << "op2_" << t0.id << ", " << t0.op_start_t << ", " << t0.op1_t << ", " << t0.op1_t + t0.punish << ", ";

		for (int i = 1; i < tasks.size(); i++) {
			Task_t t = machine2.getTask(order[i]);
			Task_t t1 = machine2.getTask(order[i - 1]);

			cout << "op2_" << t.id << ", " << t.op_start_t << ", " << t.op2_t << ", " << t.op2_t + t.punish << ", ";


			if (t1.op_start_t + t1.op2_t != t.op_start_t) {
				cout << "idle" << idles2++ << "_M2, " << t1.op_start_t + t1.op2_t << ", " << t.op_start_t - (t1.op_start_t + t1.op2_t) << ", ";
				idles2_s += t.op_start_t - (t1.op_start_t + t1.op2_t);
			}
		}

		cout << endl << maintenances.size() << ", ";
		int m_s = 0;
		for (int i = 0; i < maintenances.size(); i++) m_s += maintenances[i].duration;
		cout << m_s << "\n0, 0\n" << idles1 << ", " << idles1_s << endl << idles2 << ", " << idles2_s << endl;
	}
};

// random generator function:
int myrandom(int i) { return rand() % i; }


struct Generation {
	int id;
	int elementsCount;
	int populationSize;
	vector<Schedule> schedules;
	void init(int elCount, int pSize) {
		elementsCount = elCount;
		populationSize = pSize;
		vector<int> seed;
		for (int i = 0; i < elementsCount; i++) {
			seed.push_back(i);
		}
		for (int i = 0; i < populationSize; i++) {
			random_shuffle(seed.begin(), seed.end(), myrandom);
			Schedule sched;
			sched.init(seed);
			schedules.push_back(sched);
		}
		sortSchedules();
	}

	void printOrder(int tmp) {
		cout << "Order of " << tmp << " population:\n";
		for (int i = 0; i < schedules[tmp].order.size(); i++) {
			cout << schedules[tmp].order[i] << ", ";
		}
		cout << endl;
	}

	void sortSchedules() {
		int i, j;
		for (i = 0; i < schedules.size(); i++) {
			for (j = i + 1; j < schedules.size(); j++) {
				if (schedules[j - 1].machine2.schedulingEnd > schedules[j].machine2.schedulingEnd) {
					swap(schedules[j], schedules[j - 1]);
				}
			}
		}
	}

	void weakOut() {
		srand(unsigned(time(0)));
		for (int i = 0; i < schedules.size(); i++) {
			int tmp;
			tmp = rand() % schedules.size();
			if (tmp < i) {
				schedules.erase(schedules.begin() + i);
				--i;
			}
		}
	}

	void restitution() {
		int sch1, sch2, cut1, cut2, k;

		vector<int>seed;
		for (int i = 0; i < tasks.size(); i++) {
			seed.push_back(0);
		}
		vector<int>tmp;
		for (int i = 0; i < tasks.size(); i++) {
			tmp.push_back(1);
		}

		int let;
		double c;
		while (schedules.size() != populationSize) {

			for (int i = 0; i < tasks.size(); i++) {
				tmp[i] = 1;
			}
			c = schedules.size();
			let = rand() % 100;
			if (int(c*0.2) == 0)
				sch1 = 1;
			else if (let < 69) {
				sch1 = rand() % (int(c * 0.2)); // od 0 do 19
			}
			else if (let < 85) {
				sch1 = rand() % (int(c * 0.3)) + int(c * 0.2); // od 20 do 49
			}
			else if (let < 96) {
				sch1 = rand() % (int(c * 0.2)) + int(c * 0.5); // od 50 do 69
			}
			else {
				sch1 = rand() % (int(c *  0.3)) + int(c * 0.7); // od 70 do 99
			}

			let = rand() % 100;
			if (int(c*0.2) == 0)
				sch2 = 1;
			else if (let < 69) {
				sch2 = rand() % (int(c * 0.2)); // od 0 do 19
			}
			else if (let < 85) {
				sch2 = rand() % (int(c * 0.3)) + int(c * 0.2); // od 20 do 49
			}
			else if (let < 96) {
				sch2 = rand() % (int(c * 0.2)) + int(c * 0.5); // od 50 do 69
			}
			else {
				sch2 = rand() % (int(c *  0.3)) + int(c * 0.7); // od 70 do 99
			}

			if (sch1 == sch2)
				continue;

			cut1 = rand() % (tasks.size() - 2) + 1;
			int pom = cut1;
			for (int i = 0; i < cut1; i++) {
				seed[i] = schedules[sch1].order[i];
				tmp[schedules[sch1].order[i]] = 0;
			}

			for (int i = 0; i < tasks.size(); i++) {
				if (tmp[schedules[sch2].order[i]] == 1) {
					seed[cut1] = schedules[sch2].order[i];
					cut1++;
					tmp[schedules[sch2].order[i]] = 0;
				}
			}
			Schedule schedule2;
			schedule2.init(seed);
			schedules.push_back(schedule2);

			if (schedules.size() == populationSize)
				break;

			for (int i = 0; i < tasks.size(); i++) {
				tmp[i] = 1;
			}

			cut1 = pom;
			for (int i = 0; i < cut1; i++) {
				seed[i] = schedules[sch2].order[i];
				tmp[schedules[sch2].order[i]] = 0;
			}

			for (int i = 0; i < tasks.size(); i++) {
				if (tmp[schedules[sch1].order[i]] == 1) {
					seed[cut1] = schedules[sch1].order[i];
					cut1++;
					tmp[schedules[sch1].order[i]] = 0;
				}
			}

			//mutacja
			int l1, l2;
			let = rand() % 101;
			if (let >= 95) {
				l1 = rand() % tasks.size();
				l2 = rand() % tasks.size();
				swap(seed[l1], seed[l2]);
				l1 = rand() % tasks.size();
				l2 = rand() % tasks.size();
				swap(seed[l1], seed[l2]);
			}

			let = rand() % 101;
			if (let >= 95) {
				cut1 = rand() % tasks.size();
				cut2 = rand() % tasks.size();

				if (cut1 > cut2)
					swap(cut1, cut2);
				int r = cut1;
				for (int i = cut2; i >= cut1 + (cut2 - cut1) / 2; i--) {
					swap(seed[i], seed[r]);
					r++;
				}
			}

			Schedule schedules3;
			schedules3.init(seed);
			schedules.push_back(schedules3);
			let = rand() % 101;
			if (let >= 95 && schedules.size() != populationSize) {
				random_shuffle(seed.begin(), seed.end(), myrandom);
				schedules3.init(seed);
				schedules.push_back(schedules3);
			}
		}
	}

	void removeDuplicates() {
		int c = 0;
		while (c < schedules.size() - 1) {
			c++;
			while (schedules[c].machine2.schedulingEnd == schedules[c - 1].machine2.schedulingEnd) {
				if (c == schedules.size() - 1)
					break;
				schedules.erase(schedules.begin() + c);
			}
		}

		vector<int> seed;
		for (int i = 0; i < tasks.size(); i++)
			seed.push_back(i);
		while (schedules.size() <= populationSize) {
			random_shuffle(seed.begin(), seed.end(), myrandom);
			Schedule sched;
			sched.init(seed);
			schedules.push_back(sched);
		}
	}

	void printStats() {
		int average = 0;
		for (int i = 0; i < schedules.size(); i++) {
			average += schedules[i].exec_time;
		}
		int median = schedules[schedules.size() / 2].exec_time;
		average /= schedules.size();
		cout << id << "\t" << schedules[0].exec_time << "\t" << average << "\t" << median << "\t" << schedules[schedules.size() - 1].exec_time << endl;
	}

	void printAllTimes() {
		for (int i = 0; i < schedules.size(); i++) {
			cout << "schedules[" << i << "].exec_time=" << schedules[i].exec_time << endl;
		}
	}
};





int main(int argc, char * argv[]) {
	srand(unsigned(time(0)));

	int generationsNumber = 100;
	int populationSize = 100;
	string inputFileName, outputFileName;

	if (argc > 3) {
		inputFileName = argv[1];
		generationsNumber = atoi(argv[2]);
		populationSize = atoi(argv[3]);
	}
	else {
		cout << "inputFileName: ";
		cin >> inputFileName;
	}

	int elementsCount;
	fstream inputFile, outputFile;
	inputFile.open(inputFileName);  // LOADING DATA FROM FILE
	if (inputFile.is_open()) {
		inputFile >> elementsCount;
		string temp;
		for (int i = 0; i < elementsCount; i++) {
			Task task;

			task.id = i;
			inputFile >> temp;
			temp = temp.substr(0, temp.length() - 1);
			task.op1_t = atoi(temp.c_str());

			inputFile >> temp;
			temp = temp.substr(0, temp.length() - 1);
			task.op2_t = atoi(temp.c_str());

			inputFile >> temp >> temp >> temp;
			temp = temp.substr(0, temp.length() - 1);
			task.readyTime = atoi(temp.c_str());

			tasks.push_back(task);
		}
		while (inputFile >> temp) {
			Maintenance main;

			temp = temp.substr(0, temp.length() - 1);
			main.id = atoi(temp.c_str());

			inputFile >> temp >> temp;
			temp = temp.substr(0, temp.length() - 1);
			main.duration = atoi(temp.c_str());

			inputFile >> temp;
			temp = temp.substr(0, temp.length() - 1);
			main.start_t = atoi(temp.c_str());

			maintenances.push_back(main);
		}
		inputFile.close();
	}
	else cout << "Error opening inputFile\n";

	vector<Generation> generations;
	Generation tempGen;
	generations.push_back(tempGen);
	generations[0].id = 0;
	generations[0].init(elementsCount, populationSize);
	//cout << "Generataion " << 0 << "[0]:\t" << generations[0].schedules[0].exec_time << endl;
	generations[0].printStats();
	//CROSSING
	
	for (int g = 1; g < generationsNumber; g++) {

		generations.push_back(generations[g - 1]);
		generations[g].id = g;
	//	generations[g].removeDuplicates();
		generations[g].sortSchedules();
		generations[g].weakOut();
		generations[g].restitution();
		generations[g].sortSchedules();
		//cout << "Generataion " << g << "[0]:\t" << generations[g].schedules[0].exec_time << endl;
		generations[g].printStats();
		//generations[g].printAllTimes();
		//generations[g].printOrder(0);
		//generations[g].printOrder(1);
		//generations[g].printOrder(2);
		//getchar();
	}

	//Print best order to file:
	
	outputFileName = inputFileName + ".out";
	outputFile.open(outputFileName, fstream::out);  // LOADING DATA FROM FILE
	if (outputFile.is_open()) {
		cout << generations[generationsNumber - 1].schedules[0].exec_time << ", " << generations[0].schedules[0].exec_time << endl;
		generations[generationsNumber - 1].schedules[0].printToFile(outputFile);
		outputFile.close();
	}
//	else cout << "Error opening outputFile\n";
	
	if (argc <= 3)
		system("PAUSE");
	return 0;
}