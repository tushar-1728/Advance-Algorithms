#ifndef DYNTABLE_IMPLH
#define DYNTABLE_IMPLH

// Initialize a dynamic table.
void* make_new_dynamic_table(int);

// Inserts element at the end of dynamic table 
void push_back(void**, int);

// Pops element from the end of dynamic table. Return -1 if empty
int pop_back(void**);

#endif
