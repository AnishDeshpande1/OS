/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "spinlock.h"
#include "defs.h"
#include "barrier.h"
//define any variables needed here
int barrier_count;
struct spinlock lk;
char* name = "mybarrier";
int
barrier_init(int n)
{
  //to be done
	initlock(&lk,name);
	barrier_count = n;
  	return 0;
}

int
barrier_check(void)
{
  //to be done
	acquire(&lk);
	// cprintf("im hereere\n");
	barrier_count = barrier_count - 1;
	while(barrier_count>0){
		sleep(0,&lk);
	}
	wakeup(0); 
	release(&lk);
		 
    return 0;
}

/*----------xv6 sync lock end----------*/
