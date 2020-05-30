#include "dyntable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int count = 0;

#define BENCHMARK_COUNT 10000

typedef struct table{
	int capacity;
	int size;
	long *arr;
	int count;
}table_t;

float grow_by = 2.0;
float shrink_by = 0.5;
float reallocation_threshold = 0.50;
float deallocation_threshold = 0.50;


void* make_new_dynamic_table(int n){
	table_t *table = (table_t*)malloc(sizeof(table_t));
	table->arr = (long*)malloc(sizeof(int)*n);
	table->capacity = n;
	table->size = 0;
	table->count = 0;
	return table;
}

void push_back(void** addr, int value){
	table_t *table_ptr = *addr;
	if(table_ptr->capacity == 0){
		table_ptr->arr = (long*)malloc(sizeof(int));
		table_ptr->capacity = 1;
	}
	if(table_ptr->capacity == (int)table_ptr->size/reallocation_threshold){
		long *new_arr = (long*)malloc(sizeof(int)*table_ptr->size*grow_by);
		for (int i = 0; i < table_ptr->size; ++i)
		{
			new_arr[i] = table_ptr->arr[i];
		}
		free(table_ptr->arr);
		table_ptr->capacity = table_ptr->capacity*grow_by;
		table_ptr->arr = new_arr;
		++(table_ptr->count);
		++(count);
	}
	table_ptr->arr[(table_ptr->size)++] = value;
}

int pop_back(void **addr){
	table_t *table_ptr = *addr;
	if(table_ptr->size == 0)
		return -1;
	int opt = table_ptr->arr[table_ptr->size-1];
	--table_ptr->size;
	if(table_ptr->size == table_ptr->capacity*deallocation_threshold){
		long *new_arr = (long*)malloc(sizeof(int)*table_ptr->capacity*shrink_by);
		for (int i = 0; i < table_ptr->size; ++i)
		{
			new_arr[i] = table_ptr->arr[i];
		}
		free(table_ptr->arr);
		table_ptr->arr = new_arr;
		table_ptr->capacity = table_ptr->capacity*shrink_by;
		++(table_ptr->count);
		++(count);
	}
	return opt;
}

// call this function to start a nanosecond-resolution timer
struct timespec timer_start(){
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}


int main() {
	void* dt = make_new_dynamic_table(10);
	long tot;
	for(int i=1; i<=BENCHMARK_COUNT; ++i) {
		struct timespec vartime = timer_start();
		if(i%10) {
			push_back(&dt, rand()%BENCHMARK_COUNT);
		}
		else {
			pop_back(&dt);
		}
		long time_elapsed_nanos = timer_end(vartime);
		printf("%ld\n", time_elapsed_nanos);
		tot += time_elapsed_nanos;
	}
	printf("total %ld\n", tot);
	printf("avg %ld\n", tot/BENCHMARK_COUNT);
	// printf("%d\n", ((table_t*)dt)->count);
	printf("%d\n", count);
}