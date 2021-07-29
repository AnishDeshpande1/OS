#include "alloc.h"
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

int init_alloc()
{
	size_t pgsz = PAGESIZE;
	void* ptr;
	ptr = mmap(0, pgsz, PROT_READ, MAP_PRIVATE, 0, 0);
	if(ptr == MAP_FAILED){
        cout<<"Mapping Failed\n";
        return 1;
    }
}

int cleanup()
{

}
char *alloc(int)
{

}
void dealloc(char *)
{

}