#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define CMD_SIZE 100

const char msgWelcome[]="Bienvenue dans le shell ENSEA.\nPour quitter, tapez 'exit'.\n";
const char prompt[]="enseash % ";

int main(){
	
	write(STDOUT_FILENO,msgWelcome,sizeof(msgWelcome));
	char cmd[CMD_SIZE];
	
	while(1){
 //affichage du prompt et lecture de la commande
		write(STDOUT_FILENO,prompt,sizeof(prompt));
		int val=read(STDIN_FILENO,cmd,CMD_SIZE);
		cmd[val-1]='\0';
		
		int pid,status;
		pid = fork();
		
//Processus père
		if( pid != 0) {  
			wait(&status);
			}
			
//Processus fils 
		else{
			execlp(cmd,cmd,(char*)NULL);
			exit(-1);
		}
		
//Commande exit 
		if(strncmp(cmd,"exit",strlen("exit"))==0 || val == 0){	
			break;
		}
	}
	exit(EXIT_SUCCESS);
}
