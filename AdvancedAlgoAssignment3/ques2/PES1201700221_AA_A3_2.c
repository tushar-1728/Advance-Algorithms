#include <stdio.h>
#include <string.h>

void print_arr(int n, int arr[]){
	for(int i = 0; i < n; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void convert_to_lower(char str[]){
	int n = strlen(str);
	for(int i = 0; i < n; ++i){
		if(str[i] > 64 && str[i] < 91)
			str[i] += 32;
	}
}

void compute_prefix_table(int *pi, char *patt){
	int m = strlen(patt);
	int k = 0;
	pi[0] = 0;
	for(int q = 1; q < m; ++q){
		while(k > 0 && patt[k] != patt[q])
			k = pi[k];
		if(patt[k] == patt[q])
			k += 1;
		pi[q] = k;
	}
}

void kmp_match(char *text, char *patt){
	int n = strlen(text);
	int m = strlen(patt);
	int pi[m];
	int q = 0;
	int flag = 0;
	compute_prefix_table(pi, patt);
	// print_arr(m, pi);
	for(int i = 0; i < n; ++i){
		while(q > 0 && patt[q] != text[i])
			q = pi[q];
		if(patt[q] == text[i])
			q += 1;
		if(q == m){
			printf("%d ", i-m+1);
			q = pi[q-1];
			flag = 1;
		}
	}
	if(flag == 0)
		printf("-1");
}

int main(){
	int t;
	char text[4005];
	char patt[1005];
	gets(text);
	scanf("%d", &t);
	fflush(stdin);
	for(int i = 0; i < t; ++i){
		gets(patt);
		fflush(stdin);
		kmp_match(text, patt);
		printf("\n");
	}
}