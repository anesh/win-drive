#include "memory.h"

void zeroMemory(char* loc, unsigned long size)
{
	unsigned long i = 0;
	for(i = 0; i < size; i++)
		loc[i] = 0;
}