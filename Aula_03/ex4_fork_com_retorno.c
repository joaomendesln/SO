#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid;
	int retorno;
	pid = fork();
	if (pid < 0){
		fprintf(stderr, "Erro ao criar processo\n");
		return 1;
	}
	else if (pid == 0){
		printf("Esta é a execução do filho (PID=%d), cujo pai tem PID=%d\n", getpid(), getppid());
	}
	else{
		retorno = wait(NULL);
    	printf("O processo filho finalizou e seu PID era %d\n", retorno);
	}
    return 0;
}