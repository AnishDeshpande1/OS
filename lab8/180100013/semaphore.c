/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "defs.h"
#include "semaphore.h"

struct spinlock arr[NSEM];
char* name1 = "lock";
int
sem_init(int index, int val)
{
	if(0<=index && index<NSEM){
		sems[index].count = val;
		initlock(&arr[index],name1);
	}
	
  //to be done
  return 0;
}

int
sem_up(int index)
{
  //to be done
	acquire(&arr[index]);
	sems[index].count = sems[index].count + 1;
	wakeup((void*)index);
	release(&arr[index]);
  return 0;
}

int
sem_down(int index)
{
  //to be done
	acquire(&arr[index]);
	while(sems[index].count<=0)
		sleep((void*)index, &arr[index]);
	sems[index].count = sems[index].count - 1;
	release(&arr[index]);
  return 0;
}

/*----------xv6 sync lab end----------*/
