#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
	int ret;
	int i;
	ucounter_init();
	uspinlock_init();
	ret = fork();
	if(ret == 0)
	{
	  for(i=0; i < 10; i++) {
	  	while(ucounter_get(0)!=0){
	  		uspinlock_acquire(0);
	  		ucv_sleep(0,0);
	  		uspinlock_release(0);
	  	}
	    	printf(1, "I am child\n");
	    	ucounter_set(0,ucounter_get(0)+1);
	    	ucv_wakeup(1);   
	    
	  }
	  ucv_wakeup(1);
          exit();
	}
	else
	{
	  for(i=0; i < 10; i++) {
	    while(ucounter_get(0)!=1){
	    	uspinlock_acquire(0);
	  		ucv_sleep(1,0);
	  		uspinlock_release(0);
	    }
	    	printf(1, "I am parent\n");
	    	ucounter_set(0,ucounter_get(0)-1);
	    	ucv_wakeup(0);
	  }
	  ucv_wakeup(0);
	  wait();
          exit();
	}
}

