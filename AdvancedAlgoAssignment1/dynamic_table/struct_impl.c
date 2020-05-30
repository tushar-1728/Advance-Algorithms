#include <stdlib.h>
#include "dyntable_impl.h"

typedef struct table{
	int capacity;
	int size;
	int arr[0];
}table_t;


float grow_by = 2;
float shrink_by = 0.5;
float allocation_threshold = 1;
float deallocation_threshold = 0.25;

void* make_new_dynamic_table(int n){
	table_t *table = (table_t*)malloc(sizeof(table_t) + sizeof(int)*n);
	table->capacity = n;
	table->size = 0;
	return table;
}

void push_back(void** addr, int value){
	table_t *table_ptr = *addr;
	if(table_ptr->capacity == 0){
		table_ptr = (table_t*)malloc(sizeof(table_t) + sizeof(int));
		table_ptr->capacity = 1;
		table_ptr->size = 0;
	}
	if(table_ptr->size == table_ptr->capacity*allocation_threshold){
		table_t *new_table_ptr = (table_t*)malloc(sizeof(table_t)+ sizeof(int)*table_ptr->capacity*grow_by);
		for (int i = 0; i < table_ptr->size; ++i)
		{
			new_table_ptr->arr[i] = table_ptr->arr[i];
		}
		count = count+1;
		new_table_ptr->capacity = table_ptr->capacity*grow_by;
		new_table_ptr->size = table_ptr->size;
		free(table_ptr);
		table_ptr = new_table_ptr;
	}
	table_ptr->arr[(table_ptr->size)++] = value;
	*addr = table_ptr;
}

int pop_back(void **addr){
	table_t *table_ptr = *addr;
	if(table_ptr->size == 0)
		return -1;
	int opt = table_ptr->arr[table_ptr->size-1];
	--(table_ptr->size);
	if(table_ptr->size == table_ptr->capacity*deallocation_threshold){
		table_t *new_table_ptr = (table_t*)malloc(sizeof(table_t)+ sizeof(int)*table_ptr->capacity*shrink_by);
		for (int i = 0; i < table_ptr->size; ++i)
		{
			new_table_ptr->arr[i] = table_ptr->arr[i];
		}
		count = count+1;
		new_table_ptr->capacity = table_ptr->capacity*shrink_by;
		new_table_ptr->size = table_ptr->size;
		free(table_ptr);
		table_ptr = new_table_ptr;
	}
	*addr = table_ptr;
	return opt;
}
