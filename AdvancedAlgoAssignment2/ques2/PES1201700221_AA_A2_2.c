#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void print_arr_1d(int n, int arr[]){
	for(int i = 0; i < n; ++i){
		printf("%2d ", arr[i]);
	}
	printf("\n");
}

void print_arr_2d(int n, int m, unsigned long int arr[][m]){
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("%20lu ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void init_operator_operand(int n, int opert[], int operd[], char *expr){
	int temp1 = 0;
	int temp2 = 0;
	for(int j = 0; j < n; ++j){
			if(isdigit(expr[j])){
				operd[temp1++] = expr[j]-48;
			}
			else{
				opert[temp2++] = expr[j];
			}
		}
}

void init_cost_table(int size, unsigned long int max[][size], unsigned long int min[][size], int operand[]){
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			if(i == j){
				max[i][j] = min[i][j] = operand[i];
			}
			else{
				max[i][j] = 0;
				min[i][j] = ULONG_MAX;
			}
		}
	}
}

unsigned long int op(unsigned long int a, unsigned long int b, char c){
	if(c == '+')
		return a+b;
	return a*b;
}

void fill_cost_table(int size, unsigned long int max_cost[][size], unsigned long int min_cost[][size], int operator[], int operand[]){
	for(int l = 1; l <= size; ++l){
		for(int i = 0; i < size-l+1; ++i){
			int j = i+l-1;
			for(int k = i; k < j; ++k){
				unsigned long int min = op(min_cost[i][k], min_cost[k+1][j], operator[k]);
				unsigned long int max = op(max_cost[i][k], max_cost[k+1][j], operator[k]);
				if(min < min_cost[i][j])
					min_cost[i][j] = min;
				if(max > max_cost[i][j])
					max_cost[i][j] = max;
			}
		}
	}
}

int main(){
	int t;
	scanf("%d", &t);
	for(int i = 0; i < t; ++i){
		char expr[105];
		scanf("%s", expr);
		int expr_len = strlen(expr);
		int opert_len = expr_len/2;
		int operd_len = expr_len/2+1;
		int operator[opert_len];
		int operand[operd_len];
		init_operator_operand(expr_len, operator, operand, expr);
		unsigned long int max_cost[operd_len][operd_len];
		unsigned long int min_cost[operd_len][operd_len];
		init_cost_table(operd_len, max_cost, min_cost, operand);
		fill_cost_table(operd_len, max_cost, min_cost, operator, operand);


		// print_arr_1d(operd_len, operand);
		// print_arr_1d(opert_len, operator);
		// print_arr_2d(operd_len, operd_len, max_cost);
		// print_arr_2d(operd_len, operd_len, min_cost);

		printf("%lu %lu\n", max_cost[0][operd_len-1], min_cost[0][operd_len-1]);
	}
}