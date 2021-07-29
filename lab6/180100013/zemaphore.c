#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include "zemaphore.h"

void zem_init(zem_t *s, int value) {
  s->counter = value;
  s->m = PTHREAD_MUTEX_INITIALIZER;
  s->block = PTHREAD_COND_INITIALIZER;
}

void zem_down(zem_t *s) {
	pthread_mutex_lock(&s->m);
	while(s->counter < 0){
		pthread_cond_wait(&s->block,&s->m);
	}
	s->counter = s->counter - 1;
	while(s->counter < 0){
		pthread_cond_wait(&s->block,&s->m);
	}
	pthread_mutex_unlock(&s->m);
}

void zem_up(zem_t *s) {
	pthread_mutex_lock(&s->m);
	s->counter = s->counter + 1;
	if(s->counter>=0)
		pthread_cond_signal(&s->block);
	pthread_mutex_unlock(&s->m);
}
