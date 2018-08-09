#include <stdio.h> // printf
#include <sys/ipc.h> // ipc
#include <sys/msg.h> // msg
#include <stdlib.h> // atoi
#include <string.h> //strcpy;
#include <unistd.h> // sleep
#include <signal.h> //sigkill
#include <stdbool.h> //boolean
#include <errno.h> //ESRCH
#include <sys/shm.h> //shm
#include <math.h> // rand
#include <time.h> // time()
#include <sys/sem.h> // sem

typedef struct msgbuf {
  long mtype;
  char mtext[256];
} Msg;

typedef struct player {
	int id;
	int qid;
	int privateQueue;
	int PID;
	char name[256];
	int state;
	int opponent;
} Player;

void sndTxt(int where, char what[256], long type){
	Msg msg;
	msg.mtype=type;
 	strcpy(msg.mtext, what);
  msgsnd(where, &msg, sizeof(msg)-sizeof(long),0);
//  printf("Sent: %s\n", msg.mtext);
}

void sndInt(int where, int what, long type){
	Msg msg;
	msg.mtype=type;
 	sprintf(msg.mtext, "%d", what);
  msgsnd(where, &msg, sizeof(msg)-sizeof(long),0);
//  printf("Sent: %s\n", msg.mtext);
}

char itoa ( int i ) {
	return '0'+i;
}

void P(int sem){
	struct sembuf s[1];
	s->sem_num=0;
	s->sem_flg=0;
	s->sem_op=-1;
	semop(sem,s,1);
}
void V(int sem){
	struct sembuf s[1];
	s->sem_num=0;
	s->sem_flg=0;
	s->sem_op=1;
	semop(sem, s,1);
}

int shipsLeft(int * pb) {
	int ships=0;
	for(int i = 0;i<100; i++)
		if (pb[i]==1) ships++;	
	return ships;
}

void dispBoard(Player * p, int * pb, int * qb) {
	char buf[256];
	sndTxt(p->privateQueue, " Your board:\tOpponent board:", 2);
	sndTxt(p->privateQueue, "  a b c d e f g h i j \t  a b c d e f g h i j", 2);
	for(int i=0;i<10;i++){
		buf[0]=itoa(i);
		buf[1]=' ';
		for(int j=0;j<10;j++){
			buf[2*(j+1)] = (pb[i*10+j]==1 ? '@' : (pb[i*10+j]==2 ? 'x' : (pb[i*10+j]== 3 ? 'o' : '~')));
			buf[2*(j+1)+1] = ' ';
		}
		buf[22]='\t';
		buf[23]=itoa(i);
		buf[24]=' ';
		for(int j=0;j<10;j++){
			buf[23+2*(j+1)] = (qb[i*10+j]==2 ? '+' : (qb[i*10+j]== 3 ? 'o' : '~'));
			buf[23+2*(j+1)+1] = ' ';
		}
		buf[45]='\0';
		sndTxt(p->privateQueue, buf, 2);
	}			  				
}

int main() {
	//Create shm for players tab
	int shPl=shmget(IPC_PRIVATE, sizeof(Player[32]), IPC_CREAT | 0666);
	if(shPl == -1) perror("shmget: ");
	Player * players = shmat(shPl, NULL, 0);


	int smPl=semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
	if(smPl == -1) perror("semget: ");
	union semun {
		int val;
		struct semid_ds *buf;
		ushort * array;
	} argument;
	argument.val=1;
	if(semctl(smPl, 0, SETVAL, argument)<0) perror("semctl: ");
	//delete 1337q if exist
	int q = msgget(1337,IPC_CREAT|0600);
	msgctl(q,IPC_RMID,0);
	
	//mark all players slots free
	for (int i =0; i<32;i++) players[i].id=-1;

	int loginQueue = msgget(1337,IPC_CREAT|0600);
	if(loginQueue == -1) perror("msgget: ");

	Msg msg;
	while(1) { // main loop
	    if(msgrcv(loginQueue, &msg, sizeof(msg)-sizeof(long),102,0)!=-1){ // New client connected to server
	    	if(!fork()) {	//Create new thread for client service
	    		Player * p;	//player
	    		Player * q;	//opponent

				P(smPl);
		    	for (int i = 0;i<32;i++){
					if(players[i].id==-1){	
		    			p = &players[i];
		    			p->id=i;
				  		p->qid = atoi(msg.mtext);
				  		p->privateQueue = msgget(p->qid,IPC_CREAT|0666);
				  		
				  		if(p->privateQueue == -1) perror("privateQueue open failed: ");
				  		
				  		msgrcv(p->privateQueue, &msg, sizeof(msg)-sizeof(long),104,0);
				  		
				  			p->PID = atoi(msg.mtext);
				  			if(!fork()){
				  				//printf("kill check \n");
						    	while((kill(p->PID, 0) != -1))
						    		usleep(100000);
								P(smPl);
									if(p->opponent!=-1) {
										q=&players[p->opponent];
										sndTxt(q->privateQueue, "Your opponent has disconnected!",2);
										sndInt(q->privateQueue, 1, 2137);
									}
							    	p->id=-1;
							    	p->qid=-1;
							    	p->privateQueue=-1;
							    	p->PID=-1;
							    	p->state=0;
							    	p->opponent=-1;
							    	strcpy(p->name, "");
						    	V(smPl);
						    	printf("Client lost connection. ppid:%d pid: %d\n",getppid(),getpid());
						    	kill(getppid(), SIGTERM);
						    	exit(0);
						    }
				  		

				  		sndInt(p->privateQueue,getppid(),105);
				  		msgrcv(p->privateQueue, &msg, sizeof(msg)-sizeof(long),6969,0);
				  			strcpy(p->name, msg.mtext);
				  		p->state=0;
						p->opponent=-1;
				  		printf("Player %s (%d) connected. PID=%d\n", p->name, p->id, p->PID);
				  		sndTxt(p->privateQueue, "Connected to server succesfuly. To list avaliable commands type: /help",2);
				  		break;
		      		}
		    	}
		    	V(smPl);

		    	while(1)	
			    	if (p->state==0) { // LOBBY 
			    		if(msgrcv(p->privateQueue, &msg, sizeof(msg)-sizeof(long),1,IPC_NOWAIT)!=-1){
			    			printf("Recived %s from %s(%d)\n",msg.mtext,p->name,p->id);
							if(!strncmp("/help",msg.mtext,5)) {
								sndTxt(p->privateQueue, "List of avaliable commands:",2);
								sndTxt(p->privateQueue, "\t/accept [id]\t\t - accept invitation from player [id]",2);
								sndTxt(p->privateQueue, "\t/invite [id]\t\t - send invitation to player [id]",2);
								sndTxt(p->privateQueue, "\t/players\t\t - list all connected players",2);
								sndTxt(p->privateQueue, "\t/help\t\t - show this page",2);
								printf("%s(%d) /help\n",p->name, p->id);							
							}
							else if(!strncmp("/players",msg.mtext,8)) {
								sndTxt(p->privateQueue, "List of players:\n\tID:\tName:\t\tState:",2);
								for(int j=0;j<32;j++) {
									//printf("%d\t%s\t%d\n",players[j].id,players[j].name,players[j].state);
									if(players[j].id>=0) {
										char buf[255];
										sprintf(buf, "\t%d \t%s \t\t%d", j,players[j].name,players[j].state);
										sndTxt(p->privateQueue, buf,2);
									}
								}
								printf("%s(%d) /plyers\n",p->name, p->id);
							}
							else if(!strncmp("/invite",msg.mtext,7)) {
								int opponentId = atoi(&msg.mtext[8]);
								P(smPl);
									if(players[opponentId].state == 0 && opponentId!=p->id) {
										char buf[256];
										p->opponent=opponentId;
										q = &players[opponentId];
										sprintf(buf, "Player %s(%d) sent you a game invitation? To accept type: /accept [id]", p->name,p->id);
										sndTxt(q->privateQueue, buf, 2);
										sprintf(buf, "You send invitation to %s. Wait for his reply.", players[opponentId].name);
										sndTxt(p->privateQueue, buf, 2);
									} else {
										sndTxt(p->privateQueue, "Incorrect opponent ID!",2);
									}
								V(smPl);
								printf("%s(%d) /invite %d\n",p->name, p->id, opponentId);
							}
							else if(!strncmp("/accept",msg.mtext,7)) {
								int opponentId = atoi(&msg.mtext[8]);							
								printf("%s(%d) /accept %d\n",p->name, p->id, opponentId);	
								P(smPl);
									if(players[opponentId].opponent == p->id ) {
										p->opponent=opponentId;
										q = &players[opponentId];
										p->state=1;
										q->state=1;
										sndTxt(p->privateQueue, "Game begins!", 2);
										sndTxt(q->privateQueue, "Game begins!", 2);
										printf("Game between %s:%s starts\n",p->name,q->name);

										printf("p: %s(%d), op: %d, state: %d\n",p->name,p->id,p->opponent,p->state);
									
										printf("q: %s(%d), op: %d, state: %d\n",q->name,q->id,q->opponent,q->state);
									} else {
										sndTxt(p->privateQueue,"That player doesn\'t want to play with you!",2);
									}
								V(smPl);					
							}
			    		} else usleep(100000);
					
			    	} else {	//IN GAME
			    		printf("%s(%d) in game\n",p->name,p->id);
						srand(time(NULL) ^ getpid());
			    		int shmBoard = shmget(IPC_PRIVATE, sizeof(int [100]), IPC_CREAT |IPC_EXCL | 0666);	//STWÓRZ PLANSZE I UDOSTEPNIJ JA PRZYECIWNIKOWI
			    		int * pb = shmat(shmBoard, NULL, 0);
			    		for(int i=0; i<100; i++) pb[i%10+i/10] = 0; // CZYSZCZENIE	

			    		int ships = 0;		//LOSOWE USTAWIANIE STATKOW
			    		while(ships!=2){
			    			int pos = rand()%100;
			    			bool add = true;	//SPRAWDZENIE CZY NIE SASIADUJE Z INNYM STATKIEM
			    			if (((pos > 9) && (pb[pos-10]!=0)) ||
			    				((pos < 90) && (pb[pos+10]!=0)) ||
			    				((pos%9!=0) && (pb[pos+1]!=0)) ||
			    				((pos%9!=1) && (pb[pos-1]!=0)) ||
			    				((pos > 9) && (pos%9!=0) && (pb[pos-9]!=0)) ||
			    				((pos > 9) && (pos%9!=1) && (pb[pos-11]!=0)) ||
			    				((pos < 90) && (pos%9!=0) && (pb[pos+11]!=0)) ||
			    				((pos < 90) && (pos%9!=1) && (pb[pos+9]!=0))) add=false;
			    				
			    			if(add) {
			    				pb[pos]=1;
			    				ships++;
			    			}
			    		}

			    		printf("%s(%d) ships placed\n",p->name,p->id);
			    		sndInt(q->privateQueue, shmBoard, 666);				//WYSLANIE ID SHM Z BOARDEM I ODEBRANIE PRZECIWNEJ
			    		msgrcv(p->privateQueue, &msg, sizeof(msg)-sizeof(long),666,0);
			    		int * qb = shmat(atoi(msg.mtext), NULL, 0);
			    		
			    		printf("%s(%d) recived boards\n",p->name,p->id);
						int *turn;				//TWORZENIE ZMIENNEJ TURN, ZACZYNA GRACZ O NIZSZYM ID.
						if(p->id>q->id){
							int shmTurn = shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT | 0666);
							turn=shmat(shmTurn,NULL,0);
							*turn=p->id;
							sndInt(q->privateQueue, shmTurn, 667);
						} else {
							msgrcv(p->privateQueue, &msg, sizeof(msg)-sizeof(long),667,0);
			    			turn = shmat(atoi(msg.mtext), NULL, 0);
						}
				  		char buf[256];
				  		sprintf(buf, "You play against %s(%d)", q->name,q->id);
						sndTxt(p->privateQueue, buf, 2);
						printf("%s(%d) init done\n",p->name,p->id);

			    		while(1) {
							if(msgrcv(p->privateQueue, &msg, sizeof(msg)-sizeof(long),2137,IPC_NOWAIT)!=-1) { //check for win
								P(smPl);
									if(atoi(msg.mtext) == 1) { // win!
										sndTxt(p->privateQueue,"You won! Congratulations!\n",2);
										p->opponent = -1;
										p->state = 0;
									} else { // lose;
										sndTxt(p->privateQueue,"You loose!\n",2);
										p->opponent = -1;
										p->state = 0;
									}
								V(smPl);
								break;
							}
			    			if(*turn==p->id) {
			    				dispBoard(p,pb,qb);
				    			sndTxt(p->privateQueue,"It\'s your move!", 2);
			    				bool correct = false;
			    				while(!correct){
				    				sndTxt(p->privateQueue,"Type position: ", 2);
									msgrcv(p->privateQueue, &msg, sizeof(msg)-sizeof(long),1,0);
				  					if(msg.mtext[0]>='a' && msg.mtext[0]<='j' && msg.mtext[1]>='0' && msg.mtext[1]<='9'){
				  						int pos = ((int)msg.mtext[0]-97)+((int)msg.mtext[1]-48)*10;
				  						if(qb[pos]==1) {
				  							qb[pos]=2;
				  							dispBoard(p,pb,qb);														
				  							sndTxt(p->privateQueue, "You hit a ship!", 2);	
				  							printf("%s hit. %s left: %d\n", p->name, q->name, shipsLeft(qb));
				  							if(!shipsLeft(qb)) {
				  								printf("end!\n");
				  								sndInt(p->privateQueue,1,2137);
				  								sndInt(q->privateQueue,2,2137);
				  								correct=true;
				  							}
				  						} else if (qb[pos]==0) {
				  							correct=true;
				  							qb[pos]=3;
				  							sndTxt(p->privateQueue, "You missed, opponents move! ", 2);
			    							*turn=q->id;
				  						} else {
				  							sndTxt(p->privateQueue, "Wrong format of input or you already shot that place! [a-j0-9] ", 2);
				  						}
									}
			    				}
			    			} else {

								if(msgrcv(p->privateQueue, &msg, sizeof(msg)-sizeof(long),1,IPC_NOWAIT)!=-1)
									sndTxt(p->privateQueue, "It\'s not your move!",2);
								else 
			    					usleep(100000);
			    			}
			    		}
			    	}
			    exit(0);
		    } // end of fork
		}
	}
	return 0;
}