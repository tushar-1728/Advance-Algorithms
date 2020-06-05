#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct trie_node{
	char character;
	struct trie_node *children[128];
}trie_node;

trie_node* create_node(void){
	trie_node *node = (trie_node*)malloc(sizeof(trie_node));
	for (int i = 0; i < 128; i++)
		node->children[i] = NULL;
	return node;
}

void insert_node(trie_node* root, char* str, int i){
	int len = strlen(str);
	int character;
	trie_node* temp = root;

	for (int index = 0; index < len; index++){
		character = str[index];
		if (temp->children[character] == NULL){
			temp->children[character] = create_node();
		}

		temp = temp->children[character];
	}
}

trie_node* create_tree(char **suffix_table, int text_len){
	trie_node *root = create_node();
	for(int i = 0; i < text_len; ++i){
		insert_node(root, suffix_table[i], i);
	}
	return root;
}

bool search(trie_node *root, const char *key)
{
	int length = strlen(key);
	int index;
	trie_node *pCrawl = root;

	for (int level = 0; level < length; level++)
	{
		index = (key[level]);

		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}
	return true;
}

void convert_to_lower(char str[]){
	int n = strlen(str);
	for(int i = 0; i < n; ++i){
		if(str[i] > 64 && str[i] < 91)
			str[i] += 32;
	}
}

void print_arr(int start, int end, char **arr){
	for(int i = start; i < end; ++i){
		printf("%s\n", arr[i]);
	}
}

char *strrev(char *text)
{
	char *p1, *p2;
	if(!text || ! *text)
		return text;
	for(p1 = text, p2 = text + strlen(text) - 1; p2 > p1; ++p1, --p2){
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return text;
}

void find_all_suffix(char **suffix_table, char text[], int text_len){
	char *temp;
	char *rev_text = (char*)calloc(4005, sizeof(char));
	strrev(text);
	strcpy(rev_text, text);
	for(int i = 0; i < text_len; ++i){
		suffix_table[i] = (char*)calloc((i + 5), sizeof(char));
		temp = (char*)calloc((i + 1 + 5), sizeof(char));
		strncat(temp, rev_text, i + 1);
		strcat(suffix_table[i], strrev(temp));
		free(temp);
	}
	free(rev_text);
}

char* input(int *len){
	char *temp = (char*)malloc(4005);
	fgets(temp, 4005, stdin);
	*len = strlen(temp);
	char *str = (char*)calloc(*len + 1, sizeof(char));
	strcat(str, temp);
	if(str[*len - 1] == '\n')
		str[--(*len)] = '\0';
	free(temp);
	return str;
}

int main(){
	char *text;
	int text_len = 0;
	char *patt;
	int patt_len = 0;
	int m = 0;
	text = input(&text_len);
	text[text_len++] = '$';
	convert_to_lower(text);
	char **suffix_table = (char**)malloc(sizeof(char*)*text_len);
	find_all_suffix(suffix_table, text, text_len);
	trie_node *root = create_tree(suffix_table, text_len);
	scanf("%d\n", &m);
	for(int i = 0; i < m; ++i){
		patt = input(&patt_len);
		convert_to_lower(patt);
		bool res = search(root, patt);
		if(res){
			printf("The pattern exists.\n");
		}
		else{
			printf("The pattern does not exists.\n");
		}
		// printf("%d\n", patt_len);
		// printf("%s\n", patt);
		free(patt);
	}
	// print_arr(0, text_len, suffix_table);
	for (int i = 0; i < text_len; ++i) {
		free(suffix_table[i]);
	}
	free(suffix_table);
	free(text);
}