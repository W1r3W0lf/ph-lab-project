#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "merge.h"

#define ARRAY_SIZE 100
#define THREAD_COUNT 1



int main(int arc, char** argv){

	int* number_array = malloc(ARRAY_SIZE);

	struct chunk chunk_array[THREAD_COUNT];
	pthread_t* thread_array[THREAD_COUNT];

	// Break the array into chunks
	int chunk_size = THREAD_COUNT / ARRAY_SIZE;
	

	// Create threads
	for(int t = 0 ; t < THREAD_COUNT ; t++){
		pthread_create(thread_array[t], NULL, (void*)merge_thread, (void *)&chunk_array[t]);
	}

	// Wait for threads
	for(int t = 0 ; t < THREAD_COUNT ; t++){
		pthread_join(*thread_array[t], NULL);
	}

	// Do the final merge
	merge(number_array, THREAD_COUNT);
	
}

