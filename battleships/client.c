#include <stdio.h> // printf
#include <sys/ipc.h> // ipc
#include <sys/msg.h> // msg
#include <string.h> // strcpy
#include <stdlib.h> // exit
#include <string.h> // strcpy
#include <unistd.h> // sleep
#include <signal.h> //sigkill
#include <stdbool.h> //boolean
#include <errno.h> //ESRCH

typedef struct msgbuf {
  long mtype;
  char mtext[256];
} Msg;

void sndTxt(int where, char what[256], long type){
	Msg msg;
	msg.mtype=type;
 	strcpy(msg.mtext, what);
  msgsnd(where, &msg, sizeof(msg)-sizeof(long),0);
  //printf("Sent: %s\n", msg.mtext);
}
void sndInt(int where, int what, long type){
	Msg msg;
	msg.mtype=type;
 	sprintf(msg.mtext, "%d", what);
  msgsnd(where, &msg, sizeof(msg)-sizeof(long),0);
  //printf("Sent: %s\n", msg.mtext);
}

int main() {
	printf("Mini Battleships game.\n");
	int loginQueue = msgget(1337,IPC_CREAT|0600);	//PODLACZENIE DO GLOBALNEJ KOLEJKI SERWERA
	if (loginQueue == -1){
		perror("Error: Msgget: ");
		exit(1);
	}

	int privateQueue;	//TWORZENIE PRYWATNEJ KOLEJKI O ID=PID / EWENTUALNIE +i
	int i=0;
	while((privateQueue = msgget(getpid()+i,IPC_CREAT|IPC_EXCL|0666))<=0)
		i++;
		
	printf("Type in your name: ");		//POBRANIE NAZWY GRACZA, WYSLANIE NA GLOBALNA MTYPE=RUDY 102 ID KOLEJKI PRIV + PRZESLANIE PID I IMIENIA NA PRYWATNA
	char playerName[256];
	scanf("%255s",playerName);

	sndInt(loginQueue, getpid()+i, 102);
	sndInt(privateQueue, getpid(), 104);
	sndTxt(privateQueue, playerName, 6969); 
	Msg msg;	//ODEBRANIE PID SEREV 
	msgrcv(privateQueue, &msg, sizeof(msg)-sizeof(long),105,0);

	int serverPID = atoi(msg.mtext);
	//bool mainLoop = true;	//WYKRYWANIE CZY SERWER IS ALIVE;
    if(!fork()){
    	while((kill(serverPID, 0) != -1))
    		usleep(1000000);
   
   		//mainLoop = false;
    	printf("Server connection lost.\n");
    	kill(getppid(),SIGKILL);
    }

    if(!fork()) {
		while(1) {
			Msg msg;
			msg.mtype=1;
			msgrcv(privateQueue, &msg, sizeof(msg)-sizeof(long),2,0);
				printf("%s\n", msg.mtext);
			
		} 
		exit(0);
    }

    while(1){
		char buf[256];
		fgets(buf,255, stdin);
		sndTxt(privateQueue, buf, 1);
		usleep(100000);
    }
    return 0;   
}