#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t* semp;
int val;

void *wait_func(void *arg){
	
	printf("wait_fun thread starts...\n");

	while(1){
		sem_wait(semp);
		sem_getvalue(semp, &val);

		printf("wait_func thread : sem_value : %d\n", val);
	}

	return 0;
}

int main(void){

	pthread_t pthread_tid = 0;

	if((semp = sem_open("/semaphore", O_CREAT, 0644, 1)) == SEM_FAILED) {
		perror("sem_open failed\n");
		exit(EXIT_FAILURE);
	}

	sem_post(semp);
	sem_post(semp);
	sem_post(semp);
	sem_post(semp);

	sem_getvalue(semp, &val);
	printf("main : sem_value : %d\n", val);

	if(pthread_create(&pthread_tid, NULL, wait_func, NULL) != 0){
		perror("Thread create failed : i\n");
		exit(EXIT_FAILURE);
	}

	pthread_join(pthread_tid, NULL);

	exit(EXIT_SUCCESS);

	return 0;
}
