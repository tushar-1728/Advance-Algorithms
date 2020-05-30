// Implmentation of dynamic table with struct hacking
#include <stdlib.h>
#include "dyntable_impl.h"

// structure for storing the dynamic table and its metadata
typedef struct table{
	int capacity; // stores the capacity of the table
	int size; // stores the current size of the table
	long arr[0]; // the dynamic array itself (struct hacking)
}table_t;

// defines the factor by which table should grow
float grow_by = 2;
// defines the factor by which table should shrink
float shrink_by = 0.5;
// defines when the array should grow, 1 means the table will grow when it is full
float allocation_threshold = 1;
// defines when the array should shrink, 0.25 means the table will
// shrink when it is filled 25% of its full capacity
float deallocation_threshold = 0.25;

// Initializes the dynamic table with the given size n
void* make_new_dynamic_table(int n){
	table_t *table = (table_t*)malloc(sizeof(table_t) + sizeof(int)*n);
	table->capacity = n;
	table->size = 0;
	return table;
}

// Inserts a element into the table along with checking whether
// the table should grow
void push_back(void** table_addr, int element){
	table_t *table_ptr = *table_addr;
	// if the initial capacity of table is zero, inserting the first element
	if(table_ptr->capacity == 0){
		table_ptr = (table_t*)malloc(sizeof(table_t) + sizeof(int));
		table_ptr->capacity = 1;
		table_ptr->size = 0;
	}
	// if the table has reached its allocation threshold, the table
	// grows dynamically
	if(table_ptr->size == table_ptr->capacity*allocation_threshold){
		// creating new table of bigger size
		table_t *new_table_ptr = (table_t*)malloc(sizeof(table_t) + sizeof(int) * table_ptr->capacity * grow_by);
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
	table_ptr->arr[(table_ptr->size)++] = element;
	*table_addr = table_ptr;
}

// Pops an element from the table along with checking whether
// the table should shrink
int pop_back(void **table_addr){
	table_t *table_ptr = *table_addr;
	// if size of the table is zero, return -1
	if(table_ptr->size == 0)
		return -1;
	// opt contains the poppeed element, element to br returned
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
	*table_addr = table_ptr;
	return opt;
}
