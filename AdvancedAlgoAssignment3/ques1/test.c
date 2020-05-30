// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #define CHAR_LEN 128

// char* substr(char *str, int n){
// 	printf("%s\n", str);
// 	int i, j;
// 	int str_len = strlen(str);
// 	char *temp = (char*)malloc(sizeof(char) * (str_len - n + 1));
// 	for(i = n, j = 0; i <= str_len; ++i, ++j){
// 		temp[j] = str[i];
// 	}
// 	return temp;
// }

// int main(){
// 	int i = 0;
// 	char temp[] = "apple\0";
// 	substr(substr(substr(temp, 1),1),1);
// 	// printf("%s\n", substr(temp, 2));
// 	// int text[] = {1,2,3,4,5};
// 	// printf("size: %lu\n", sizeof(text)/sizeof(int));
// }

// A C program to implement Ukkonen's Suffix Tree Construction 
// And find all locations of a pattern in string 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#define MAX_CHAR 256 

struct SuffixTreeNode { 
	struct SuffixTreeNode *children[MAX_CHAR]; 

	//pointer to other node via suffix link 
	struct SuffixTreeNode *suffixLink; 

	/*(start, end) interval specifies the edge, by which the 
	node is connected to its parent node. Each edge will 
	connect two nodes, one parent and one child, and 
	(start, end) interval of a given edge will be stored 
	in the child node. Let's say there are two nods A and B 
	connected by an edge with indices (5, 8) then this 
	indices (5, 8) will be stored in node B. */
	int start; 
	int *end; 

	/*for leaf nodes, it stores the index of suffix for 
	the path from root to leaf*/
	int suffixIndex; 
}; 

typedef struct SuffixTreeNode Node; 

char text[100]; //Input string 
Node *root = NULL; //Pointer to root node 

/*lastNewNode will point to the newly created internal node, 
waiting for it's suffix link to be set, which might get 
a new suffix link (other than root) in next extension of 
same phase. lastNewNode will be set to NULL when last 
newly created internal node (if there is any) got it's 
suffix link reset to new internal node created in next 
extension of same phase. */
Node *lastNewNode = NULL; 
Node *activeNode = NULL; 

/*activeEdge is represented as an input string character 
index (not the character itself)*/
int activeEdge = -1; 
int activeLength = 0; 

// remainingSuffixCount tells how many suffixes yet to 
// be added in tree 
int remainingSuffixCount = 0; 
int leafEnd = -1; 
int *rootEnd = NULL; 
int *splitEnd = NULL; 
int size = -1; //Length of input string 

Node *newNode(int start, int *end) 
{ 
	Node *node =(Node*) malloc(sizeof(Node)); 
	int i; 
	for (i = 0; i < MAX_CHAR; i++) 
		node->children[i] = NULL; 

	/*For root node, suffixLink will be set to NULL 
	For internal nodes, suffixLink will be set to root 
	by default in current extension and may change in 
	next extension*/
	node->suffixLink = root; 
	node->start = start; 
	node->end = end; 

	/*suffixIndex will be set to -1 by default and 
	actual suffix index will be set later for leaves 
	at the end of all phases*/
	node->suffixIndex = -1; 
	return node; 
} 

int edgeLength(Node *n) { 
	if(n == root) 
		return 0; 
	return *(n->end) - (n->start) + 1; 
} 

int walkDown(Node *currNode) 
{ 
	/*activePoint change for walk down (APCFWD) using 
	Skip/Count Trick (Trick 1). If activeLength is greater 
	than current edge length, set next internal node as 
	activeNode and adjust activeEdge and activeLength 
	accordingly to represent same activePoint*/
	if (activeLength >= edgeLength(currNode)) 
	{ 
		activeEdge += edgeLength(currNode); 
		activeLength -= edgeLength(currNode); 
		activeNode = currNode; 
		return 1; 
	} 
	return 0; 
} 

void extendSuffixTree(int pos) 
{ 
	/*Extension Rule 1, this takes care of extending all 
	leaves created so far in tree*/
	leafEnd = pos; 

	/*Increment remainingSuffixCount indicating that a 
	new suffix added to the list of suffixes yet to be 
	added in tree*/
	remainingSuffixCount++; 

	/*set lastNewNode to NULL while starting a new phase, 
	indicating there is no internal node waiting for 
	it's suffix link reset in current phase*/
	lastNewNode = NULL; 

	//Add all suffixes (yet to be added) one by one in tree 
	while(remainingSuffixCount > 0) { 

		if (activeLength == 0) 
			activeEdge = pos; //APCFALZ 

		// There is no outgoing edge starting with 
		// activeEdge from activeNode 
		if (activeNode->children] == NULL) 
		{ 
			//Extension Rule 2 (A new leaf edge gets created) 
			activeNode->children] = 
										newNode(pos, &leafEnd); 

			/*A new leaf edge is created in above line starting 
			from an existing node (the current activeNode), and 
			if there is any internal node waiting for its suffix 
			link get reset, point the suffix link from that last 
			internal node to current activeNode. Then set lastNewNode 
			to NULL indicating no more node waiting for suffix link 
			reset.*/
			if (lastNewNode != NULL) 
			{ 
				lastNewNode->suffixLink = activeNode; 
				lastNewNode = NULL; 
			} 
		} 
		// There is an outgoing edge starting with activeEdge 
		// from activeNode 
		else
		{ 
			// Get the next node at the end of edge starting 
			// with activeEdge 
			Node *next = activeNode->children]; 
			if (walkDown(next))//Do walkdown 
			{ 
				//Start from next node (the new activeNode) 
				continue; 
			} 
			/*Extension Rule 3 (current character being processed 
			is already on the edge)*/
			if (text[next->start + activeLength] == text[pos]) 
			{ 
				//If a newly created node waiting for it's 
				//suffix link to be set, then set suffix link 
				//of that waiting node to current active node 
				if(lastNewNode != NULL && activeNode != root) 
				{ 
					lastNewNode->suffixLink = activeNode; 
					lastNewNode = NULL; 
				} 

				//APCFER3 
				activeLength++; 
				/*STOP all further processing in this phase 
				and move on to next phase*/
				break; 
			} 

			/*We will be here when activePoint is in middle of 
			the edge being traversed and current character 
			being processed is not on the edge (we fall off 
			the tree). In this case, we add a new internal node 
			and a new leaf edge going out of that new node. This 
			is Extension Rule 2, where a new leaf edge and a new 
			internal node get created*/
			splitEnd = (int*) malloc(sizeof(int)); 
			*splitEnd = next->start + activeLength - 1; 

			//New internal node 
			Node *split = newNode(next->start, splitEnd); 
			activeNode->children] = split; 

			//New leaf coming out of new internal node 
			split->children = newNode(pos, &leafEnd); 
			next->start += activeLength; 
			split->children = next; 

			/*We got a new internal node here. If there is any 
			internal node created in last extensions of same 
			phase which is still waiting for it's suffix link 
			reset, do it now.*/
			if (lastNewNode != NULL) 
			{ 
			/*suffixLink of lastNewNode points to current newly 
			created internal node*/
				lastNewNode->suffixLink = split; 
			} 

			/*Make the current newly created internal node waiting 
			for it's suffix link reset (which is pointing to root 
			at present). If we come across any other internal node 
			(existing or newly created) in next extension of same 
			phase, when a new leaf edge gets added (i.e. when 
			Extension Rule 2 applies is any of the next extension 
			of same phase) at that point, suffixLink of this node 
			will point to that internal node.*/
			lastNewNode = split; 
		} 

		/* One suffix got added in tree, decrement the count of 
		suffixes yet to be added.*/
		remainingSuffixCount--; 
		if (activeNode == root && activeLength > 0) //APCFER2C1 
		{ 
			activeLength--; 
			activeEdge = pos - remainingSuffixCount + 1; 
		} 
		else if (activeNode != root) //APCFER2C2 
		{ 
			activeNode = activeNode->suffixLink; 
		} 
	} 
} 

void print(int i, int j) 
{ 
	int k; 
	for (k=i; k<=j; k++) 
		printf("%c", text[k]); 
} 

//Print the suffix tree as well along with setting suffix index 
//So tree will be printed in DFS manner 
//Each edge along with it's suffix index will be printed 
void setSuffixIndexByDFS(Node *n, int labelHeight) 
{ 
	if (n == NULL) return; 

	if (n->start != -1) //A non-root node 
	{ 
		//Print the label on edge from parent to current node 
		//Uncomment below line to print suffix tree 
	// print(n->start, *(n->end)); 
	} 
	int leaf = 1; 
	int i; 
	for (i = 0; i < MAX_CHAR; i++) 
	{ 
		if (n->children[i] != NULL) 
		{ 
			//Uncomment below two lines to print suffix index 
		// if (leaf == 1 && n->start != -1) 
			// printf(" [%d]\n", n->suffixIndex); 

			//Current node is not a leaf as it has outgoing 
			//edges from it. 
			leaf = 0; 
			setSuffixIndexByDFS(n->children[i], labelHeight + 
								edgeLength(n->children[i])); 
		} 
	} 
	if (leaf == 1) 
	{ 
		n->suffixIndex = size - labelHeight; 
		//Uncomment below line to print suffix index 
		//printf(" [%d]\n", n->suffixIndex); 
	} 
} 

void freeSuffixTreeByPostOrder(Node *n) 
{ 
	if (n == NULL) 
		return; 
	int i; 
	for (i = 0; i < MAX_CHAR; i++) 
	{ 
		if (n->children[i] != NULL) 
		{ 
			freeSuffixTreeByPostOrder(n->children[i]); 
		} 
	} 
	if (n->suffixIndex == -1) 
		free(n->end); 
	free(n); 
} 

/*Build the suffix tree and print the edge labels along with 
suffixIndex. suffixIndex for leaf edges will be >= 0 and 
for non-leaf edges will be -1*/
void buildSuffixTree() 
{ 
	size = strlen(text); 
	int i; 
	rootEnd = (int*) malloc(sizeof(int)); 
	*rootEnd = - 1; 

	/*Root is a special node with start and end indices as -1, 
	as it has no parent from where an edge comes to root*/
	root = newNode(-1, rootEnd); 

	activeNode = root; //First activeNode will be root 
	for (i=0; i<size; i++) 
		extendSuffixTree(i); 
	int labelHeight = 0; 
	setSuffixIndexByDFS(root, labelHeight); 
} 

int traverseEdge(char *str, int idx, int start, int end) 
{ 
	int k = 0; 
	//Traverse the edge with character by character matching 
	for(k=start; k<=end && str[idx] != '\0'; k++, idx++) 
	{ 
		if(text[k] != str[idx]) 
			return -1; // mo match 
	} 
	if(str[idx] == '\0') 
		return 1; // match 
	return 0; // more characters yet to match 
} 

int doTraversalToCountLeaf(Node *n) 
{ 
	if(n == NULL) 
		return 0; 
	if(n->suffixIndex > -1) 
	{ 
		printf("\nFound at position: %d", n->suffixIndex); 
		return 1; 
	} 
	int count = 0; 
	int i = 0; 
	for (i = 0; i < MAX_CHAR; i++) 
	{ 
		if(n->children[i] != NULL) 
		{ 
			count += doTraversalToCountLeaf(n->children[i]); 
		} 
	} 
	return count; 
} 

int countLeaf(Node *n) 
{ 
	if(n == NULL) 
		return 0; 
	return doTraversalToCountLeaf(n); 
} 

int doTraversal(Node *n, char* str, int idx) 
{ 
	if(n == NULL) 
	{ 
		return -1; // no match 
	} 
	int res = -1; 
	//If node n is not root node, then traverse edge 
	//from node n's parent to node n. 
	if(n->start != -1) 
	{ 
		res = traverseEdge(str, idx, n->start, *(n->end)); 
		if(res == -1) //no match 
			return -1; 
		if(res == 1) //match 
		{ 
			if(n->suffixIndex > -1) 
				printf("\nsubstring count: 1 and position: %d", 
							n->suffixIndex); 
			else
				printf("\nsubstring count: %d", countLeaf(n)); 
			return 1; 
		} 
	} 
	//Get the character index to search 
	idx = idx + edgeLength(n); 
	//If there is an edge from node n going out 
	//with current character str[idx], traverse that edge 
	if(n->children[str[idx]] != NULL) 
		return doTraversal(n->children[str[idx]], str, idx); 
	else
		return -1; // no match 
} 

void checkForSubString(char* str) 
{ 
	int res = doTraversal(root, str, 0); 
	if(res == 1) 
		printf("\nPattern <%s> is a Substring\n", str); 
	else
		printf("\nPattern <%s> is NOT a Substring\n", str); 
} 

// driver program to test above functions 
int main(int argc, char *argv[]) 
{ 
	strcpy(text, "GEEKSFORGEEKS$"); 
	buildSuffixTree();	 
	printf("Text: GEEKSFORGEEKS, Pattern to search: GEEKS"); 
	checkForSubString("GEEKS"); 
	printf("\n\nText: GEEKSFORGEEKS, Pattern to search: GEEK1"); 
	checkForSubString("GEEK1"); 
	printf("\n\nText: GEEKSFORGEEKS, Pattern to search: FOR"); 
	checkForSubString("FOR"); 
	//Free the dynamically allocated memory 
	freeSuffixTreeByPostOrder(root); 

	strcpy(text, "AABAACAADAABAAABAA$"); 
	buildSuffixTree();	 
	printf("\n\nText: AABAACAADAABAAABAA, Pattern to search: AABA"); 
	checkForSubString("AABA"); 
	printf("\n\nText: AABAACAADAABAAABAA, Pattern to search: AA"); 
	checkForSubString("AA"); 
	printf("\n\nText: AABAACAADAABAAABAA, Pattern to search: AAE"); 
	checkForSubString("AAE"); 
	//Free the dynamically allocated memory 
	freeSuffixTreeByPostOrder(root); 

	strcpy(text, "AAAAAAAAA$"); 
	buildSuffixTree();	 
	printf("\n\nText: AAAAAAAAA, Pattern to search: AAAA"); 
	checkForSubString("AAAA"); 
	printf("\n\nText: AAAAAAAAA, Pattern to search: AA"); 
	checkForSubString("AA"); 
	printf("\n\nText: AAAAAAAAA, Pattern to search: A"); 
	checkForSubString("A"); 
	printf("\n\nText: AAAAAAAAA, Pattern to search: AB"); 
	checkForSubString("AB"); 
	//Free the dynamically allocated memory 
	freeSuffixTreeByPostOrder(root); 

	return 0; 
}