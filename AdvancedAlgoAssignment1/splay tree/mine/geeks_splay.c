// The code is adopted from http://goo.gl/SDH9hH 
#include<stdio.h> 
#include<stdlib.h> 

// An AVL tree node 
struct node 
{ 
	int key;
	int value;
	struct node *left, *right; 
};
typedef struct node node_t;

struct tree
{
	node_t *root;
};
typedef struct tree tree_t; 

/* Helper function that allocates a new node with the given key and 
	NULL left and right pointers. */
struct node* newNode(int key, int value) 
{ 
	struct node* node = (struct node*)malloc(sizeof(struct node)); 
	node->key = key;
	node->value = value;
	node->left = node->right = NULL; 
	return (node); 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct node *rightRotate(struct node *x) 
{ 
	struct node *y = x->left; 
	x->left = y->right; 
	y->right = x; 
	return y; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct node *leftRotate(struct node *x) 
{ 
	struct node *y = x->right; 
	x->right = y->left; 
	y->left = x; 
	return y; 
}

//Initialise the dictionary
void* make_new_dictionary();
void* make_new_dictionary()
{
	tree_t *tree = (tree_t*)malloc(sizeof(tree_t));
	tree->root = NULL;
	return tree;
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
}

// This function brings the key at root if key is present in tree. 
// If key is not present, then it brings the last accessed item at 
// root. This function modifies the tree and returns the new root 
struct node *splay(struct node *root, int key) 
{ 
	if(root == NULL || root->key == key)
		return root;

	if(key < root->key)
	{
		if(root->left == NULL)
			return root;

		if(root->left->key > key)
		{
			root->left->left = splay(root->left->left, key);
			root = rightRotate(root);
		}
		else if(root->left->key < key)
		{
			root->left->right = splay(root->left->right, key);
			if(root->left->right != NULL)
				root->left = leftRotate(root->left);
		}
		return (root->left == NULL)? root: rightRotate(root);
	}
	else
	{
		if(root->right == NULL) return root;
		if(root->right->key > key)
		{
			root->right->left = splay(root->right->left, key);
			if(root->right->left != NULL)
				root->right = rightRotate(root->right);
		} 
		else if(root->right->key < key)
		{
			root->right->right = splay(root->right->right, key);
			root = leftRotate(root);
		}
		return (root->right == NULL)? root: leftRotate(root); 
	} 
} 

// The search function for Splay tree. Note that this function 
// returns the new root of Splay Tree. If key is present in tree 
// then, it is moved to root. 
struct node *search(struct node *root, int key) 
{ 
	return splay(root, key); 
} 

// A utility function to print preorder traversal of the tree. 
// The function also prints height of every node 
void preOrder(struct node *root) 
{ 
	if (root != NULL) 
	{ 
		preOrder(root->left); 
		printf("(%d, %d) ", root->key, root->value); 
		preOrder(root->right); 
	} 
} 

/* Drier program to test above function*/
int main() 
{
	int key, value, code;
	void* dictionary = make_new_dictionary();
	printf("Codes and their value:\n");
	printf("1 k v - insert key value pair n into tree\n");
	printf("2 k - finds a key k in tree and splays the tree\n");
	printf("3 - preorder traversal of tree\n");
	// printf("4 - inorder traversal of tree\n");
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
				((tree_t*)dictionary)->root = search(((tree_t*)dictionary)->root, key);
				printf("%d\n", ((tree_t*)dictionary)->root->value);
			}
			break;
			case 3: preOrder(((tree_t*)dictionary)->root);
			break;
		}
		printf("Enter your code: ");
		scanf("%d", &code);
	}


	// ((tree_t*)dictionary)->root = search(((tree_t*)dictionary)->root, 20); 
	// printf("Preorder traversal of the modified Splay tree is \n"); 
	// preOrder(((tree_t*)dictionary)->root); 
	return 0; 
} 
