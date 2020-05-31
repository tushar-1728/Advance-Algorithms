#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

// Prints 1D array of dimension n
void print_arr_1d(int n, int arr[]){
	for(int i = 0; i < n; ++i){
		printf("%2d ", arr[i]);
	}
	printf("\n");
}

// Prints 2D array of dimension n * m
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

// Extracts operator and operands from expr and fills them in their respective arrays
void init_operator_operand(int n, int operator[], int operand[], char *expr){
	int temp1 = 0;
	int temp2 = 0;
	int digit = 0;
	for(int j = 0; j < n; ++j){
		if(expr[j] == '+' || expr[j] == '*'){
			operator[temp1++] = expr[j];
			operand[temp2++] = digit;
			digit = 0;
		}
		else{
			digit = digit * 10 + expr[j] - 48;
		}
	}
	operand[temp2] = digit;
}

// Initializes the cost table with the start-up values and dummy values as required
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

// Performs operation between two operands based on operator
unsigned long int op (unsigned long int a, unsigned long int b, char c){
	if(c == '+')
		return a+b;
	else
		return a*b;
}

// fills the remaining cost table using dynamic programming technique
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
		int count = 0;
		char expr[100];
		scanf("%s", expr);
		int expr_len = strlen(expr);
		for (int i = 0; i < expr_len; ++i) {
			if(expr[i] == '+' || expr[i] == '*')
				++count;
		}
		int operator_len = count;
		int operand_len = count + 1;
		int operator[operator_len];
		int operand[operand_len];
		unsigned long int max_cost[operand_len][operand_len];
		unsigned long int min_cost[operand_len][operand_len];
		init_operator_operand(expr_len, operator, operand, expr);
		init_cost_table(operand_len, max_cost, min_cost, operand);
		fill_cost_table(operand_len, max_cost, min_cost, operator, operand);


		// printf("%d %d\n", operator_len, operand_len);
		// print_arr_1d(operand_len, operand);
		// print_arr_1d(operator_len, operator);
		// print_arr_2d(operand_len, operand_len, max_cost);
		// print_arr_2d(operand_len, operand_len, min_cost);

		printf("%lu %lu\n", max_cost[0][operand_len-1], min_cost[0][operand_len-1]);
	}
}