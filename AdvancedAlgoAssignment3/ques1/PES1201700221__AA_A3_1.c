#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct trie_node{
	struct trie_node *children[128];
	int *indexes;
	int curr_of_indexes;
	bool end_of_word;
}trie_node;

trie_node* create_node(void){
	trie_node *node = (trie_node*)malloc(sizeof(trie_node));
	for (int i = 0; i < 128; i++)
		node->children[i] = NULL;
	node->indexes = (int*)calloc(4000, sizeof(int));
	node->curr_of_indexes = 0;
	node->end_of_word = false;
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
			temp->children[character]->indexes[temp->children[character]->curr_of_indexes] = i+index;
			++(temp->children[character]->curr_of_indexes);
		}

		temp = temp->children[character];
	}
	temp->end_of_word= true;
}

trie_node* create_tree(char **suffix_table, int text_len){
	trie_node *root = create_node();
	for(int i = 0; i < text_len - 1; ++i){
		insert_node(root, suffix_table[text_len - i -2], i);
	}
	return root;
}

bool search(trie_node *root, const char *key)
{
	int level;
	int length = strlen(key);
	int index;
	trie_node *pCrawl = root;

	for (level = 0; level < length; level++)
	{
		index = (key[level]);

		if (!pCrawl->children[index])
			return NULL;

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
		printf("%s\n", arr[end - i - 1]);
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
	char rev_text[4005];
	strcat(rev_text, strrev(text));
	for(int i = 0; i < text_len; ++i){
		suffix_table[i] = (char*)calloc((i + 5), sizeof(char));
		temp = (char*)calloc((i + 1 + 5), sizeof(char));
		strncat(temp, rev_text, i + 1);
		strcat(suffix_table[i], strrev(temp));
		free(temp);
	}
}

char* input(int *len){
	char *temp = (char*)malloc(4005);
	fgets(temp, 4005, stdin);
	fflush(stdin);
	fflush(stdout);
	*len = strlen(temp);
	char *str = (char*)calloc(*len, sizeof(char));
	strcat(str, temp);
	str[*len - 1] = '\0';
	fflush(stdin);
	fflush(stdout);
	return str;
}

int main(){
	char *text;
	char *patt;
	int text_len = 0;
	int patt_len = 0;
	int m = 0;
	text = input(&text_len);
	convert_to_lower(text);
	text_len = strlen(text);
	char **suffix_table = (char**)malloc(sizeof(char*)*text_len);
	find_all_suffix(suffix_table, text, text_len);
	trie_node *root = create_tree(suffix_table, text_len);
	fflush(stdin);
	fflush(stdout);
	scanf("%d", &m);
	m = m+1;
	for(int i = 0; i < m; ++i){
		fflush(stdin);
		fflush(stdout);
		patt = input(&patt_len);
		fflush(stdin);
		fflush(stdout);
		if(i > 0){
			bool res = search(root, patt);
			if(res){
				printf("The pattern exists.\n");
			}
			else{
				printf("The pattern does not exists.\n");
			}
		}
	}
}