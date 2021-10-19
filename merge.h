#ifndef MERGE_H 

#define MERGE_H

typedef struct chunk {
	int* start;
	unsigned long size;
}chunk;

typedef struct chunk_list{
	chunk* chunks;
	unsigned long size;
	unsigned long capacity;
} chunk_list;

void print_chunk(chunk* printed_chunk);

void merge_thread(void* given_chunk);

void merge_sort(chunk*);

void final_merge_sort(chunk_list* sorted_chunks);

#endif
