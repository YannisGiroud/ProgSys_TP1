#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD_SIZE 100

const char msgWelcome[]="Bienvenue dans le shell ENSEA.\nPour quitter, tapez 'exit'.\n";
const char prompt[]="enseash %";

int main(){
	
	write(STDOUT_FILENO,msgWelcome,sizeof(msgWelcome));
	write(STDOUT_FILENO,prompt,sizeof(prompt));
	
	exit(EXIT_SUCCESS);
}
