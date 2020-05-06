#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t tid[2];
static int counter;
pthread_mutex_t lock;

void *doSomething(void *arg){
	
	pthread_mutex_lock(&lock);

	counter++;

	printf("Job %d Started\n", counter);
	// insert sleep or some long dummy codes to delay this thread
	// It is takes long time, times up and the other thread will run

	for(unsigned long i=0; i<(0xFFFFFFFF); i++);
	
	printf("Job %d Finished\n", counter);

	pthread_mutex_unlock(&lock);

	return NULL;
}

int main(void){

	int i = 0;
	int err;

	pthread_mutex_init(&lock, NULL);

	while(i<2){
		err = pthread_create(&(tid[i]), NULL, &doSomething, NULL);
		if(err != 0){
			perror("thread creation failed\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
