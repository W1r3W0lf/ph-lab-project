#ifndef MERGE_H 

#define MERGE_H

typedef struct chunk {
	int* start;
	int size;
}chunk;

void merge_thread(void* given_chunk);

void merge_sort(int* memory, int size);

#endif
