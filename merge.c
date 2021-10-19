#include "merge.h"
#include <string.h>
#include <stdlib.h>


void merge_thread(void* given_chunk){
	merge_sort((chunk*)given_chunk);
}

void merge(chunk* dest, chunk* lhs){

	chunk rhs;
	rhs.start = malloc(sizeof(int)*dest->size);
	memcpy(rhs.start, dest->start, dest->size);
	rhs.size = dest->size;

	unsigned long new_chunk_size = rhs.size + lhs->size;

	unsigned long rhs_index = 0;
	unsigned long lhs_index = 0;

	for(unsigned long i = 0 ; i < new_chunk_size ; i++){

		if (rhs.size < rhs_index){
			// If the right hand side runs out, then everything is sorted
			break;
		} else if (lhs->size >= lhs_index && lhs->start[lhs_index] < rhs.start[rhs_index]){
			dest->start[i] = lhs->start[lhs_index];
			lhs_index++;
		} else {
			dest->start[i] = rhs.start[rhs_index];
			rhs_index++;
		}
	}

	dest->size = new_chunk_size;

	free(rhs.start);
}

void get_sorted_chunks(chunk_list* sorted_chunks, chunk* unsorted_chunk ){

	// The first chunk starts at the start of the unsorted chunk
	sorted_chunks->chunks[0].start = unsorted_chunk->start;

	unsigned long chunk_count = 0;
	unsigned long chunk_size = 0;
	for (unsigned long i = 1 ; i < unsorted_chunk->size; i++){
		chunk_size++;
		if (unsorted_chunk->start[i-1] > unsorted_chunk->start[i]){
			sorted_chunks->chunks[chunk_count-1].size = chunk_size;
			sorted_chunks->chunks[chunk_count].start = &unsorted_chunk->start[i];
			chunk_size = 0;
			chunk_count++;
		}
	}

	sorted_chunks[chunk_count].size=chunk_size;
	sorted_chunks->size = chunk_count;
}

void merge_sort(chunk* given_chunk){

	chunk_list sorted_chunks;
	sorted_chunks.chunks = malloc(sizeof(chunk)*given_chunk->size);
	sorted_chunks.capacity = given_chunk->size;

	get_sorted_chunks(&sorted_chunks, given_chunk);

	for(unsigned long i = 1 ; i < sorted_chunks.size; i++){
		merge(&sorted_chunks.chunks[0], &sorted_chunks.chunks[i]);
	}

}
