#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <getopt.h>

/* Based on OSTEP.
*/

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit1() { 
	pthread_mutex_lock(&m); 
	done = 1; 
	pthread_cond_signal(&c); 
	pthread_mutex_unlock(&m);
}

void thr_exit2() { 
	pthread_mutex_lock(&m); 
	pthread_cond_signal(&c); 
	pthread_mutex_unlock(&m);
}

void * child1(void *arg) { 
	printf("child1\n"); 
	thr_exit1();
	return NULL;
}

void * child2(void *arg) { 
	printf("child2\n"); 
	thr_exit2();
	return NULL;
}

void thr_join1() 
{
	pthread_mutex_lock(&m); 
	while (done == 0)
		pthread_cond_wait(&c, &m); 
	pthread_mutex_unlock(&m);
}

void thr_join2() 
{
	pthread_mutex_lock(&m); 
	pthread_cond_wait(&c, &m); 
	pthread_mutex_unlock(&m);
}

int main(int argc, char *argv[]) { 
	int c;
	int mode = 0;

	while ((c = getopt(argc, argv, "m:")) != -1) {
		switch (c) {
			case 'm':
				mode = atoi(optarg);
				break;

			default:
				printf("Bad option -  usage: prog -m MODENUM\n");
				exit(1);
		}
	}

	printf("parent: begin\n");
	pthread_t p;

	switch (mode) {
		case 0:
			pthread_create(&p, NULL, child1, NULL);
			thr_join1();
			break;

		case 1:
			pthread_create(&p, NULL, child2, NULL);
			pthread_yield_np();
			thr_join2();
			break;
	}

	printf("parent: end\n");
	return 0;
}
