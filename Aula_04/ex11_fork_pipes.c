#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	int vetor_pipe[2], TAM; // [0] para ler; [1] para escrita
	pid_t pid;
	TAM = strlen(argv[1]) + 1;
	char buffer[TAM];

	pipe(vetor_pipe); // cria o pipe
	pid = fork(); // cria um novo processo
	if(pid == 0) { // processo filho
		close(vetor_pipe[1]); // fecha o caminho de escrita
		while(read(vetor_pipe[0], &buffer, TAM) > 0) // leia enquanto não for o fim
		close(vetor_pipe[0]); // fecha o caminho de leitura
		printf("FILHO: O filho terminou e leu: %s\n", buffer);
		exit(EXIT_SUCCESS);
	}
	else { // processo pai
		close(vetor_pipe[0]); // fecha o caminho de leitura
		sleep(2);
		write(vetor_pipe[1], argv[1], strlen(argv[1]) + 1); // envia o conteúdo da entrada no endereço de escrita do vetor_pipe
		close(vetor_pipe[1]); // fecha o caminho de escrita
		printf("PAI: O pai terminou e escreveu: %s\n", argv[1]);
		wait(NULL);
		printf("PAI: O filho terminou\n");
		exit(EXIT_SUCCESS);
	}
}