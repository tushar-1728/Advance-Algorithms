#include <stdlib.h>
#include "dyntable_impl.h"

// structure for storing the dynamic table and its metadata
typedef struct table{
	int capacity; // stores the capacity of the table
	int size; // stores the current size of the table
	long arr[0]; // the dynamic array itself (struct hacking)
}table_t;


float grow_by = 2; // defines the factor by which table should grow
float shrink_by = 0.5; // defines the factor by which table should grow
float allocation_threshold = 1; // defines when the array should grow, 1 means when array is full
float deallocation_threshold = 0.25; // defines when the array should shrink, 0.25 means when array is one-fourth full

// initializes the dynamic table with the given size
void* make_new_dynamic_table(int n){
	table_t *table = (table_t*)malloc(sizeof(table_t) + sizeof(int)*n);
	table->capacity = n;
	table->size = 0;
	return table;
}

void push_back(void** addr, int value){
	table_t *table_ptr = *addr;
	// if the initial capacity of table is zero
	if(table_ptr->capacity == 0){
		table_ptr = (table_t*)malloc(sizeof(table_t) + sizeof(int));
		table_ptr->capacity = 1;
		table_ptr->size = 0;
	}
	// if the table has reached its allocation threshold
	if(table_ptr->size == table_ptr->capacity*allocation_threshold){
		// creating new table of bigger size
		table_t *new_table_ptr = (table_t*)malloc(sizeof(table_t)+ sizeof(int)*table_ptr->capacity*grow_by);
		// copying the elements
		for (int i = 0; i < table_ptr->size; ++i)
		{
			new_table_ptr->arr[i] = table_ptr->arr[i];
		}
		// updating the metadata
		new_table_ptr->capacity = table_ptr->capacity*grow_by;
		new_table_ptr->size = table_ptr->size;

		free(table_ptr);
		table_ptr = new_table_ptr;
	}
	// adding new element to the table
	table_ptr->arr[(table_ptr->size)++] = value;
	*addr = table_ptr;
}

int pop_back(void **addr){
	table_t *table_ptr = *addr;
	// if size of the table is zero
	if(table_ptr->size == 0)
		return -1;
	// opt contains the poppeed value, value to br returned
	int opt = table_ptr->arr[table_ptr->size-1];
	--(table_ptr->size);
	// if the table has reached its deallocation threshold
	if(table_ptr->size == table_ptr->capacity*deallocation_threshold){
		// creating new table of smaller size
		table_t *new_table_ptr = (table_t*)malloc(sizeof(table_t)+ sizeof(int)*table_ptr->capacity*shrink_by);
		// copying the elements
		for (int i = 0; i < table_ptr->size; ++i)
		{
			new_table_ptr->arr[i] = table_ptr->arr[i];
		}
		// updating the metadata
		new_table_ptr->capacity = table_ptr->capacity*shrink_by;
		new_table_ptr->size = table_ptr->size;

		free(table_ptr);
		table_ptr = new_table_ptr;
	}
	*addr = table_ptr;
	return opt;
}
