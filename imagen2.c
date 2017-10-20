#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <pthread.h>

void *saludo();

int main (){
	/*creamos los hilos */
	pthread_t id_hilos[3];
	int i=0;

	pthread_create(&id_hilos[0], NULL, (void*)saludo, NULL);
	pthread_create(&id_hilos[1], NULL, (void*)saludo, NULL);
	pthread_create(&id_hilos[2], NULL, (void*)saludo, NULL);

	for(i=0;i<3;i++){
		pthread_join(id_hilos[i],NULL);
	}

	return 0;
}

void *saludo(){
		printf("salidos\n");
}