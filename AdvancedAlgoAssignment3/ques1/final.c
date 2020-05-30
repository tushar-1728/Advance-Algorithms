#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAR_LEN 128

typedef struct node{
	struct node *children[CHAR_LEN];
	int *indexes;
	int cur_of_index;
}node_t;

node_t* create_node(){
	node_t *node = (node_t*)malloc(sizeof(node));
	node->indexes = (int*)malloc(sizeof(int)*4005);
	node->cur_of_index = 0;
	for(int i = 0; i < CHAR_LEN; ++i){
		node->children[i] = NULL;
	}
	return node;
}

// char* substr(char *str, int n){
// 	printf("%s\n", str);
// 	int i, j;
// 	int str_len = strlen(str);
// 	char *temp = (char*)calloc((str_len - n + 5), sizeof(char));
// 	// char temp[str_len - n + 5];
// 	printf("allocation done\n");
// 	for(i = n, j = 0; i <= str_len; ++i, ++j){
// 		printf("value of i and j: %d %d\n", i, j);
// 		printf("%c %c\n", str[i], temp[j]);
// 		temp[j] = str[i];
// 	}
// 	printf("copying done\n");
// 	// str = temp;
// 	return temp;
// }
char* substr(const char *src, int m)
{
	// get length of the destination string
	int n = strlen(src);
	int len = n - m;

	// allocate (len + 1) chars for destination (+1 for extra null character)
	char *dest = (char*)malloc(sizeof(char) * (len + 1));

	// extracts characters between m'th and n'th index from source string
	// and copy them into the destination string
	for (int i = m; i < n && (*src != '\0'); i++)
	{
		*dest = *(src + i);
		dest++;
	}

	// null-terminate the destination string
	*dest = '\0';

	// return the destination string
	return dest - len;
}

// void insert_suffix(node_t *node, char *pattern, int index){
// 	printf("printing pattern: %s\n", pattern);
// 	node->indexes[(node->cur_of_index)++] = index;
// 	if(strlen(pattern) > 0){
// 		printf("entered 1st if\n");
// 		char cindex = pattern[0];
// 		if(node->children[(int)cindex] == NULL)
// 			node->children[(int)cindex] = create_node();
// 		printf("done with 2nd if\n");
// 		printf("substring: %s\n", substr(pattern, 1));
// 		insert_suffix(node->children[(int)cindex], substr(pattern, 1), index+1);
// 	}
// }

void insert_suffix(node_t* root, char* str, int i){
	int len = strlen(str);
	int character;
	node_t* temp = root;

	for (int index = 0; index < len; index++){
		character = str[index];
		if (temp->children[character] == NULL){
			temp->children[character] = create_node();
			// temp->indexes[temp->cur_of_index] = i+index;
			// temp->cur_of_index += 1;
		}

		temp = temp->children[character];
	}
	// temp->end_of_word= true;
}

void create_suffix_trie(node_t *root, char **suffix_table, int text_len){
	for(int i = 0; i < text_len; ++i){
		// printf("%s\n", suffix_table[i]);
		insert_suffix(root, suffix_table[i], i);
	}
}

int* find_pattern(node_t *node, char *pattern){
	if(strlen(pattern) == 0)
		return node->indexes;
	if(node->children[(int)pattern[0]] != NULL)
		return find_pattern(node->children[(int)pattern[0]], substr(pattern, 1));
	else
		return NULL;
}

char* input(int *len){
	char *temp = (char*)malloc(4005);
	fflush(stdin);
	scanf("%[^\n]s",temp);
	// fflush(stdin);
	*len = strlen(temp);
	char *str = (char*)calloc(*len, sizeof(char));
	strcat(str, temp);
	// printf("printing str: %s\n", str);
	return str;
}

void convert_to_lower(char str[]){
	int n = strlen(str);
	for(int i = 0; i < n; ++i){
		if(str[i] > 64 && str[i] < 91)
			str[i] += 32;
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
		suffix_table[text_len-1-i] = (char*)calloc((i + 5), sizeof(char));
		temp = (char*)calloc((i + 1 + 5), sizeof(char));
		strncat(temp, rev_text, i + 1);
		strcat(suffix_table[text_len-1-i], strrev(temp));
		free(temp);
	}
}

void print_arr(int start, int end, char **arr){
	for(int i = start; i < end; ++i){
		printf("%s\n", arr[i]);
	}
}

int main(){
	char *text;
	int text_len;
	// int patt_len;
	int m;
	text = input(&text_len);
	// char text[] = "apple\0";
	// text_len = 5;
	convert_to_lower(text);
	char **suffix_table = (char**)malloc(sizeof(char*)*text_len);
	find_all_suffix(suffix_table, text, text_len);
	print_arr(0 ,text_len, suffix_table);
	node_t *root = create_node();
	// printf("app1\n");
	create_suffix_trie(root, suffix_table, text_len);
	printf("print test\n");
	// scanf("%d", &m);
	// for(int i = 0; i < m; ++i){
	// 	printf("enter for loop\n");
	// 	char *patt = (char*)malloc(sizeof(char) * 1005);
	// 	fflush(stdin);
	// 	scanf("%[^\n]s",patt);
	// 	int *index = find_pattern(root, patt);
	// 	printf("%d ", index[0]);
	// }
	return 0;
}