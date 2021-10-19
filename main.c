#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "merge.h"

#define ARRAY_SIZE 1000
#define THREAD_COUNT 1


void print_chunk(chunk* printed_chunk){
	for (unsigned long i = 0 ;  i < printed_chunk->size ; i++){
		printf("%d", printed_chunk->start[i]);
	}
}


int main(int arc, char** argv){

	struct chunk chunk_array[THREAD_COUNT];
	pthread_t* thread_array[THREAD_COUNT];



	chunk unsorted_chunk;
	unsorted_chunk.start = malloc(sizeof(int)*ARRAY_SIZE);
	unsorted_chunk.size = ARRAY_SIZE;

	for (int i = 0; i < ARRAY_SIZE ; i++){
		unsorted_chunk.start[i] = random();
	}


	chunk_list unsorted_chunk_list;
	unsorted_chunk_list.size = THREAD_COUNT;
	unsorted_chunk_list.capacity = THREAD_COUNT;
	
	unsorted_chunk_list.chunks[0].start = unsorted_chunk.start;

	// Break the array into chunks
	int chunk_size = ARRAY_SIZE / THREAD_COUNT;

	for(int i = 0 ; i < THREAD_COUNT; i++){
		unsorted_chunk_list.chunks[i].start = &unsorted_chunk.start[chunk_size * i];
		unsorted_chunk_list.chunks[i].size = chunk_size;
	}
	unsorted_chunk_list.chunks[THREAD_COUNT].size = ARRAY_SIZE - chunk_size * (THREAD_COUNT - 1);


	// Create threads
	for(int t = 0 ; t < THREAD_COUNT ; t++){
		pthread_create(thread_array[t], NULL, (void*)merge_thread, (void *)&chunk_array[t]);
	}

	// Wait for threads
	for(int t = 0 ; t < THREAD_COUNT ; t++){
		pthread_join(*thread_array[t], NULL);
	}

	// Do the final merge
	merge_thread(&unsorted_chunk_list);
	
}

