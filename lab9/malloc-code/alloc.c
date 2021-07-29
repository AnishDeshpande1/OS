#include "alloc.h"
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

int init_alloc()
{
	size_t pgsz = PAGESIZE;
	int* begin = mmap(NULL, pgsz, PROT_READ, MAP_PRIVATE, 0, 0);
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