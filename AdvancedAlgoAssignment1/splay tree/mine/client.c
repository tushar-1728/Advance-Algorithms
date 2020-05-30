#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BENCHMARK_COUNT 100
struct node
{
	int key;
	int value;
	struct node *left;
	struct node *right;
};
typedef struct node node_t;

struct tree
{
	node_t *root;
};
typedef struct tree tree_t;

//Initialise the dictionary
void* make_new_dictionary();
void* make_new_dictionary()
{
	tree_t *tree = (tree_t*)malloc(sizeof(tree_t));
	tree->root = NULL;
	return tree;
}

node_t* right_rotate(node_t *node);
node_t* right_rotate(node_t *node)
{
	node_t *temp = node->left;
	node->left = temp->right;
	temp->right = node;
	return temp;
}

node_t* left_rotate(node_t *node);
node_t* left_rotate(node_t *node)
{
	node_t *temp = node->right;
	node->right = temp->left;
	temp->left = node;
	return temp;
}

node_t* splay(node_t *node, int key);
node_t* splay(node_t *node, int key)
{
	if(node == NULL || node->key == key)
		return node;

	if(key < node->key)
	{
		if(node->left == NULL)
			return node;

		if(node->left->key > key)
		{
			node->left->left = splay(node->left->left, key);
			node = right_rotate(node);
		}
		else if(node->left->key < key)
		{
			node->left->right = splay(node->left->right, key);
			if(node->left->right != NULL)
				node->left = left_rotate(node->left);
		}
		if(node->left == NULL)
			return node;
		else
			return right_rotate(node);
	}
	else
	{
		if(node->right == NULL) return node;
		if(node->right->key > key)
		{
			node->right->left = splay(node->right->left, key);
			if(node->right->left != NULL)
				node->right = right_rotate(node->right);
		}
		else if(node->right->key < key)
		{
			node->right->right = splay(node->right->right, key);
			node = left_rotate(node);
		}
		if(node->right == NULL)
			return node;
		else
			return left_rotate(node);
	}
}

//Inserts new key-value pair into the dictionary. Update the value in case of duplicate keys
void insert(void*, int, int);
void insert(void* dictionary, int key, int value)
{
	tree_t *ptr_tree = (tree_t*)dictionary;
	node_t *newnode = (node_t*)malloc(sizeof(node_t));
	newnode->key = key;
	newnode->value = value;
	newnode->left = newnode->right = NULL;
	if(ptr_tree->root == NULL)
	{
		ptr_tree->root = newnode;
	}
	else
	{
		int flag = 1;
		node_t *parent = ptr_tree->root;
		node_t *grandparent;
		while(parent && flag)
		{
			if(key > parent->key)
			{
				grandparent = parent;
				parent = parent->right;
			}
			else if(key < parent->key)
			{
				grandparent = parent;
				parent = parent->left;
			}
			else
				flag = 0;
		}
		if(flag == 0)
			parent->value = value;
		else
		{
			if(key > grandparent->key)
				grandparent->right = newnode;
			else
				grandparent->left = newnode;
		}
	}
	ptr_tree->root = splay(ptr_tree->root, key);
}

void disp_preorder(node_t *ptr_node);
void disp_preorder(node_t *ptr_node)
{
	if(ptr_node)
	{
		printf("(%d, %d) ", ptr_node->key, ptr_node->value);
		disp_preorder(ptr_node->left);
		disp_preorder(ptr_node->right);
	}
}

void display_preorder(const void *dictionary);
void display_preorder(const void *dictionary)
{
	tree_t *ptr_tree = (tree_t*)dictionary;
	if(ptr_tree->root)
	{
		disp_preorder(ptr_tree->root);
		puts("");
	}
	else
		puts("empty tree");
}


void disp_inorder(const node_t *ptr_node)
{
	if(ptr_node)
	{
		disp_inorder(ptr_node->left);
		printf("(%d, %d) ", ptr_node->key, ptr_node->value);
		disp_inorder(ptr_node->right);
	}
}

void display_inorder(const void *dictionary)
{
	tree_t *ptr_tree = (tree_t*)dictionary;
	if(ptr_tree->root)
	{
		disp_inorder(ptr_tree->root);
		puts("");
	}
	else
		puts("empty tree");
}

//Returns value if found else returns -1 
int find(void*, int);
int find(void* dictionary, int key)
{
	tree_t *ptr_tree = (tree_t*)dictionary;
	ptr_tree->root = splay(ptr_tree->root, key);
	if(ptr_tree->root->key == key)
		return ptr_tree->root->value;
	else
		return -1;
}

// function to start a nanosecond-resolution timer
struct timespec timer_start(){
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}


int main() {
	int key, value, code;
	void* dictionary = make_new_dictionary();
	printf("Codes and their value:\n");
	printf("1 k v - insert key value pair n into tree\n");
	printf("2 k - finds a key k in tree\n");
	printf("3 - preorder traversal of tree\n");
	printf("4 - inorder traversal of tree\n");
	printf("0 - exit\n");
	printf("Enter your code: ");
	scanf("%d", &code);
	while(code){
		switch(code){
			case 1:{
				scanf("%d %d", &key, &value);
				insert(dictionary, key, value);
			}
			break;
			case 2:{
				scanf("%d", &key);
				printf("%d\n", find(dictionary, key));
			}
			break;
			case 3: display_preorder(dictionary);
			break;
			case 4: display_inorder(dictionary);
			break;
		}
		printf("Enter your code: ");
		scanf("%d", &code);
	}
}
