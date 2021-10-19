#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "merge.h"

//#define ARRAY_SIZE 1000
//#define THREAD_COUNT 1


int main(int argc, char** argv){


	int array_size = 10000;
	int thread_count = 1;

	if (argc == 3){
		array_size = atoi(argv[1]);
		thread_count = atoi(argv[2]);
	}


	pthread_t* thread_array = malloc(sizeof(pthread_t)*thread_count);

	chunk unsorted_chunk;
	unsorted_chunk.start = malloc(sizeof(int)*array_size);
	unsorted_chunk.size = array_size;

	for (int i = 0; i < array_size ; i++){
		unsorted_chunk.start[i] = random();
	}

	//print_chunk(&unsorted_chunk);

	chunk_list unsorted_chunk_list;
	unsorted_chunk_list.size = thread_count;
	unsorted_chunk_list.capacity = thread_count;
	unsorted_chunk_list.chunks = malloc(sizeof(chunk)*thread_count);
	
	unsorted_chunk_list.chunks[0].start = unsorted_chunk.start;

	// Break the array into chunks
	int chunk_size = array_size / thread_count;

	for(int i = 0 ; i < thread_count; i++){
		unsorted_chunk_list.chunks[i].start = &unsorted_chunk.start[chunk_size * i];
		unsorted_chunk_list.chunks[i].size = chunk_size;
	}
	unsorted_chunk_list.chunks[thread_count - 1].size = array_size - chunk_size * (thread_count - 1);

	chunk* temp_chunk;
	// Create threads
	for(int t = 0 ; t < thread_count ; t++){
		temp_chunk = &unsorted_chunk_list.chunks[t];
		pthread_create(&thread_array[t], NULL, (void*)merge_thread, (void *)temp_chunk);
	}

	// Wait for threads
	for(int t = 0 ; t < thread_count ; t++){
		pthread_join(thread_array[t], NULL);
	}

	// Do the final merge
	//merge_thread(&unsorted_chunk_list);
	
	merge_sort(&unsorted_chunk);
	//print_chunk(&unsorted_chunk);
	printf("DONE\n");

	free(unsorted_chunk.start);
	free(unsorted_chunk_list.chunks);
	free(thread_array);
	
}

