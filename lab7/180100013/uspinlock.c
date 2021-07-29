/*----------xv6 sync lab----------*/
#include "types.h"
#include "x86.h"
#include "uspinlock.h"

//TODO: define an array of NLOCK uspinlocks
struct uspinlock{
	uint locked;
};

struct uspinlock arr[NLOCK];

int
uspinlock_init(void)
{
  // Initialize all locks to unlocked state
  // To be done.
	for(int i = 0; i< NLOCK; i++){
		arr[i].locked = 0;
	}
  return 0;
}

int
uspinlock_acquire(int index)
{
  // To be done.
	while(xchg(&(arr[index].locked),1)!=0){
		continue;
	}
  return 0;
}

int
uspinlock_release(int index)
{
  // To be done.
	arr[index].locked = 0;
  return 0;
}

int
uspinlock_holding(int index)
{
  // To be done.
  //Return 0 if lock is free, 1 if lock is held
  
  return arr[index].locked;
}
/*----------xv6 sync lock end----------*/
