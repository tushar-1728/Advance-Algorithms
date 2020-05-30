#ifndef SPLAY_TREE_IMPLH
#define SPLAY_TREE_IMPLH
//Initialise the dictionary
void* make_new_dictionary();

//Inserts new key-value pair into the dictionary. Update the value in case of duplicate keys
void insert(void*, int, int);

//Returns value if found else returns -1 
int find(void*, int);
#endif
