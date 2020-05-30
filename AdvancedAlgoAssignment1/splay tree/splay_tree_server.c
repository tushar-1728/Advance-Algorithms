#include <stdlib.h>
#include "splay_tree_imp.h"


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

node_t* right_rotate(node_t *node);
node_t* left_rotate(node_t *node);
node_t* splay(node_t *node, int key);

void* make_new_dictionary()
{
	tree_t *tree = (tree_t*)malloc(sizeof(tree_t));
	tree->root = NULL;
	return tree;
}

node_t* right_rotate(node_t *node)
{
	node_t *temp = node->left;
	node->left = temp->right;
	temp->right = node;
	return temp;
}

node_t* left_rotate(node_t *node)
{
	node_t *temp = node->right;
	node->right = temp->left;
	temp->left = node;
	return temp;
}

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

int find(void* dictionary, int key)
{
	tree_t *ptr_tree = (tree_t*)dictionary;
	ptr_tree->root = splay(ptr_tree->root, key);
	if(ptr_tree->root->key == key)
		return ptr_tree->root->value;
	else
		return -1;
}