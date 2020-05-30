// without struct hacking
#include "dyntable_impl.h"
#include <stdlib.h>

// 
typedef struct table{
	float capacity;
	float size;
	long *arr;
}table_t;

float grow_by = 2.0;
float shrink_by = 0.5;
float allocation_threshold = 1.0;
float deallocation_threshold = 0.25;


void* make_new_dynamic_table(int n){
	table_t *table = (table_t*)malloc(sizeof(table_t));
	table->arr = (long*)malloc(sizeof(int)*n);
	table->capacity = (float)n;
	table->size = 0.0;
	return table;
}

void push_back(void** addr, int value){
	table_t *table_ptr = *addr;
	if(table_ptr->capacity == 0){
		table_ptr->arr = (long*)malloc(sizeof(int));
		table_ptr->capacity = 1;
	}
	if(table_ptr->capacity == table_ptr->size*allocation_threshold){
		long *new_arr = (long*)malloc(sizeof(int)*table_ptr->size*grow_by);
		for (int i = 0; i < table_ptr->size; ++i)
		{
			new_arr[i] = table_ptr->arr[i];
		}
		free(table_ptr->arr);
		table_ptr->capacity = table_ptr->capacity*grow_by;
		table_ptr->arr = new_arr;
	}
	table_ptr->arr[((int)(table_ptr->size))+1] = value;
}

int pop_back(void **addr){
	table_t *table_ptr = *addr;
	if(table_ptr->size == 0)
		return -1;
	int opt = table_ptr->arr[(int)table_ptr->size-1];
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
	}
	return opt;
}