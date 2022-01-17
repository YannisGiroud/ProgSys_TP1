#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#define CMD_SIZE 100

const char msgWelcome[]="Bienvenue dans le shell ENSEA.\nPour quitter, tapez 'exit'.\n";
const char prompt[]="enseash % ";

int main(){

	write(STDOUT_FILENO,msgWelcome,sizeof(msgWelcome));
	write(STDOUT_FILENO,prompt,sizeof(prompt));
	char cmd[CMD_SIZE];
	char newprompt[CMD_SIZE];
	
//Définition de l'horloge
	struct timespec tp1;
	struct timespec tp2;
	clockid_t clk_id = CLOCK_REALTIME;
	
	while(1){
 // lecture de la commande
		int val=read(STDIN_FILENO,cmd,CMD_SIZE);
		cmd[val-1]='\0';
		
		int pid,status;
		pid = fork();
		
//Processus père
		if( pid != 0) {  
			wait(&status);
			clock_gettime(clk_id, &tp2);	//Deuxième mesure
			}
			
//Processus fils 
		else{
			clock_gettime(clk_id, &tp1);    //Première mesure 
			execlp(cmd,cmd,(char*)NULL);
			exit(-1);
		}
		
//Commande exit 
		if(strncmp(cmd,"exit",strlen("exit"))==0 || val == 0){	
			break;
		}
		
//Affichage du prompt et de l'état de la commande 
		
		if(WIFEXITED(status)){
			int time = (tp2.tv_nsec-tp1.tv_nsec)/1000000;    //On calcule le temps d'execution pour l'afficher 
			sprintf(newprompt,"enseash [exit:%d|%d ms] %%",WEXITSTATUS(status),time);
			write(STDOUT_FILENO,newprompt,strlen(newprompt));					//On affiche le nouveau prompt
		} 
		else if (WIFSIGNALED(status)){
			int time = (tp2.tv_nsec-tp1.tv_nsec)/1000000;
			sprintf(newprompt,"enseash [sign:%d|%d ms] %%",WTERMSIG(status),time);
			write(STDOUT_FILENO,newprompt,strlen(newprompt));					//On affiche le nouveau prompt
		}
	}
	exit(EXIT_SUCCESS);
}

