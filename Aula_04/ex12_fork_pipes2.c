#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define MAX_SIZE 4

int main(int argc, char * argv[]){
	int vetor_pipe_ida[2], vetor_pipe_volta[2];
	pid_t pid;
	char buffer[MAX_SIZE];
	int num, resposta;

	pipe(vetor_pipe_ida); // cria o pipe
	pipe(vetor_pipe_volta); // cria o pipe
	pid = fork(); // cria um novo processo
	if(pid == 0) { // processo filho
		close(vetor_pipe_ida[1]); // fecha o caminho de escrita do pipe de ida
		while(read(vetor_pipe_ida[0], buffer, MAX_SIZE) > 0) // leia enquanto não for o fim
		sscanf(buffer, "%d", &num);

		close(vetor_pipe_ida[0]); // fecha o caminho de leitura do pipe de ida
		printf("FILHO: O filho leu: %d\n", num);

		num = num + 1;
		sprintf(buffer, "%d", num);

		// resposta ao pai

		close(vetor_pipe_volta[0]); // fecha o caminho de leitura do pipe de volta
		write(vetor_pipe_volta[1], buffer, MAX_SIZE); // envia o conteúdo do buffer no endereço de escrita do pipe de volta
		close(vetor_pipe_volta[1]); // fecha o caminho de escrita do pipe de volta

		printf("FILHO: O filho escreveu: %d\n", num);
		printf("FILHO: O filho terminou\n");
		exit(0); // termina o procesoo filho
	}
	else { // processo pai
		num = atoi(argv[1]);
		sprintf(buffer, "%d", num);
		close(vetor_pipe_ida[0]); // fecha o caminho de leitura do pipe de ida 
		write(vetor_pipe_ida[1], buffer, MAX_SIZE); // envia o conteúdo do buffer no endereço de escrita do pipe de ida
		close(vetor_pipe_ida[1]); // fecha o caminho de escrita do pipe de ida
		printf("PAI: O pai escreveu: %s\n", buffer);


		// resposta do filho

		close(vetor_pipe_volta[1]); // fecha o caminho de escrita do pipe de volta
		while(read(vetor_pipe_volta[0], buffer, MAX_SIZE) > 0);
		close(vetor_pipe_volta[0]); // fecha o caminho de leitura do pipe de volta
		sscanf(buffer, "%d", &num);
		printf("PAI: O pai leu: %d\n", num);

		wait(NULL);
		printf("PAI: O filho terminou\n");
		printf("PAI: O pai terminou\n");
		exit(0);
	}
}