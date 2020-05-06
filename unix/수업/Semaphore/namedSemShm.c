#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

#define LOOP 100

// Global
/*
sem_t 	*semP;
sem_t 	*semC;
*/

int shmRemove(int shmid, int *data){
	shmdt(data);

	if (shmctl(shmid, IPC_RMID, 0) < 0){
		printf("Failed to delete shared memory\n");
		return -1;
	}
	else{
		printf("Successfully delete shared memory\n");
	}

}

int main() {

	// fork
	pid_t childpid;

	// shared memory
	key_t 	key;
	int 	shmid;
	int 	*data;
	int 	prev = 1000;

	// semaphore
	

	// Heap
	sem_t 	*semP = (sem_t *)malloc(sizeof(sem_t));
	sem_t 	*semC = (sem_t *)malloc(sizeof(sem_t));

	/* Stack
	sem_t 	*semP;
	sem_t 	*semC;
	*/

	int 		pShared = 1;
	unsigned int 	valueP = 1;
	unsigned int 	valueC = 0;

	key = ftok("namedSemShm.c", 'R');
	shmid = shmget(key, sizeof(int), 0644 | IPC_CREAT | IPC_EXCL);

	if (shmid < 0) {
		shmid = shmget(key, sizeof(int), 0644);
		data = shmat(shmid, (void *)0, 0666);
		if (data <(int *)0) {
			perror("shmat attch is failed : ");
			exit(-1);
		}
	}
	else {
		data = shmat(shmid, (void *)0, 0644);
	}

	data = shmat(shmid, (void *)0, 0);
	if (data==(int *)(-1)) perror("shmat : ");

	*data = prev;

	sem_unlink("pSem");
	sem_unlink("cSem");

	// named Semaphore
	semP = sem_open("pSem", O_CREAT | O_EXCL, 0644, valueP);

	if (semP == SEM_FAILED){
		shmRemove(shmid, data);
		perror("sem_open [pSem] : ");
		exit(-1);
	}

	semC = sem_open("cSem", O_CREAT | O_EXCL, 0644, valueC);

	if (semC == SEM_FAILED){
		shmRemove(shmid, data);
		perror("sem_open [cSem] : ");
		exit(-1);
	}

	if ((childpid = fork()) < 0) {
		perror("fork failed");
		exit(-1);
	}

	if (childpid == 0) { // Child Process
		int i = 0;
		for(i=0; i<LOOP; i++){
			sem_wait(semP);
			*data = *data + 1;
			printf("Child data : %d\n", *data);
			sleep(2);
			sem_post(semC);
		}
	}
	else { // Parent Process
		
		int i = 0;
		for(i=0; i<LOOP; i++){
			sem_wait(semC);
			*data = *data - 1;
			printf("Parent data : %d\n", *data);
			sem_post(semP);
		}
	}

	shmRemove(shmid, data);
	sem_unlink("pSem");
	sem_unlink("CSem");

	return 0;
}
