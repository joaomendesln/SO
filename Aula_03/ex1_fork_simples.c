#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid;
	pid = fork();
	if (pid < 0){
		printf("Erro ao criar processo\n");
		return 1;
	}
	else if (pid == 0){
		printf("Esta é a execução do filho\n");
		for(;;)
			;
	}
	else{
		printf("O pai está esperando o filho\n");
		for (;;)
			;
    	printf("O processo filho finalizou\n");

	}
    return 0;
}