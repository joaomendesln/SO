#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(){
	struct tm *hora_atual;
	time_t segundos;

	time(&segundos);
	hora_atual = localtime(&segundos);
	printf("%d : %d : %d\n", hora_atual->tm_hour, hora_atual->tm_min, hora_atual->tm_sec);

	sleep(2);

	time(&segundos);
	hora_atual = localtime(&segundos);
	printf("%d : %d : %d\n", hora_atual->tm_hour, hora_atual->tm_min, hora_atual->tm_sec);


}