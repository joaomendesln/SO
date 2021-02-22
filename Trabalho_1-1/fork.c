#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void formato_dia(struct tm *hora){
	// printa o dia no formato dd/mm/aaaa

	if (hora->tm_mday < 10){
		printf("0%d/", hora->tm_mday);
	}
	else {
		printf("%d/", hora->tm_mday);
	}
	if (hora->tm_mon < 9){
		printf("0%d/", hora->tm_mon + 1);
	}
	else {
		printf("%d/", hora->tm_mon + 1);
	}
	printf("%d", hora->tm_year + 1900);
}

void formato_hora(struct tm *hora){
	// printa o horário no formato XX h : XX min : XX seg

	if (hora->tm_hour < 10){
		printf("0%d h : ", hora->tm_hour);
	}
	else {
		printf("%d h : ", hora->tm_hour);
	}
	if (hora->tm_min < 10){
		printf("0%d min : ", hora->tm_min);
	}
	else {
		printf("%d min : ", hora->tm_min);
	}
	if (hora->tm_sec < 10){
		printf("0%d seg\n", hora->tm_sec);
	}
	else {
		printf("%d seg\n", hora->tm_sec);
	}
}

time_t nascimento(char nome[]){
	// printa as informações do nascimento do processo, retornando o horário do seu nascimento

	struct tm *dia_horario_nascimento;
	time_t seg_nasc;
	time(&seg_nasc);
	dia_horario_nascimento = localtime(&seg_nasc);
	printf("Nascimento do processo %s\nDia: ", nome);
	formato_dia(dia_horario_nascimento);
	printf(" Horário: ");
	formato_hora(dia_horario_nascimento);
	printf("------------------------------------------------------------------\n");
	return seg_nasc;
}

void morte(char nome[], time_t seg_nasc){
	// printa as informações da morte do processo

	struct tm *dia_horario_morte;
	time_t seg_morte;
	time(&seg_morte);
	dia_horario_morte = localtime(&seg_morte);
	printf("Morte do processo %s\nDia: ", nome);
	formato_dia(dia_horario_morte);
	printf(" Horário: ");
	formato_hora(dia_horario_morte);

	struct tm *dia_horario_nascimento;
	dia_horario_nascimento = localtime(&seg_nasc);

	printf("Este processo nasceu no dia ");
	formato_dia(dia_horario_nascimento);
	printf(" às ");
	formato_hora(dia_horario_nascimento);

	printf("Isso totaliza %.0f anos de vida\n", difftime(seg_morte, seg_nasc));
	printf("------------------------------------------------------------------\n");
}

int main()
{
	pid_t pid[4] = {-1, -1, -1, -1};

	time_t horario_nascimento[5] = {-1, -1, -1, -1, -1};

	horario_nascimento[0] = nascimento("PAI");

	sleep(14);
	horario_nascimento[1] = nascimento("FILHO 1");
	pid[0] = fork();

	if(pid[0] < 0){
		printf("Erro ao criar o processo FILHO 1\n");
		exit(-1);
	}

	if (pid[0] > 0){ // execução do pai
		sleep(2);
		horario_nascimento[2] = nascimento("FILHO 2");
		pid[1] = fork();

		if(pid[1] < 0){
			printf("Erro ao criar o processo FILHO 2\n");
			exit(-1);
		}

		if (pid[1] == 0){ // execução do filho 2
			sleep(14);
			horario_nascimento[4] = nascimento("NETO 2");
			pid[3] = fork();

			if(pid[3] < 0){
				printf("Erro ao criar o processo NETO 2\n");
				exit(-1);
			}

			if(pid[3] == 0){ // execução do neto 2
				sleep(18);
				morte("NETO 2", horario_nascimento[4]);
				exit(0);
			}
			
			if(pid[3] > 0){ // execução do filho 2
				sleep(16);
				morte("FILHO 2", horario_nascimento[2]);
				exit(0);
			}
			
		}

		if (pid[1] > 0){ // execução do pai
			sleep(44);
			morte("PAI", horario_nascimento[0]);
			exit(0);
		}

	}

	if (pid[0] == 0){ // execução do filho 1
		sleep(12);
		horario_nascimento[3] = nascimento("NETO 1");
		pid[2] = fork();

		if (pid[2] < 0){
			printf("Erro ao criar o processo NETO 1\n");
			exit(-1);
		}

		if (pid[2] == 0){ // execução do neto 1
			sleep(12);
			morte("NETO 1", horario_nascimento[3]);
			exit(0);
		}

		if (pid[2] > 0){ // execução do filho 1
			sleep(18);
			morte("FILHO 1", horario_nascimento[1]);
			exit(0);
		}

	}
	return 0;
}