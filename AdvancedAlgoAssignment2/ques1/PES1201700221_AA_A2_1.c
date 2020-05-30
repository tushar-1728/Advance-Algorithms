#include <stdio.h>

void print_arr(int n, int m, int arr[][m]){
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
}

void init_assembly_line(int n, int m, int assmbl_line[][m+2]){
	for (int i = 0; i < 3*n - 2; i = i+3){
		int j = 0;
		int flag = 1;
		while(j < m+1){
			if(j == 1 && flag){
				scanf("%d", &assmbl_line[i][m+1]);
				flag = 0;
			}
			else{
				scanf("%d", &assmbl_line[i][j]);
				++j;
			}
		}
	}
	for (int i = 1; i < 3*n - 2; ++i){
		if(i % 3 != 0){
			assmbl_line[i][0] = assmbl_line[i][m] = assmbl_line[i][m+1] = 0;
			int j = 1;
			while(j < m){
				scanf("%d", &assmbl_line[i][j]);
				++j;
			}
		}
	}
}

int min_2(int a, int b, int *flag){
	if(a <= b){
		*flag = 0;
		return a;
	}
	*flag = 1;
	return b;
}

int min_3(int a, int b, int c, int *flag){
	int temp = a;
	*flag = -1;
	if(temp > b){
		temp = b;
		*flag = 0;
	}
	if(temp > c){
		temp = c;
		*flag = 1;
	}
	return temp;
}

void init_cost_table(int n, int m, int table[][m+1], int assmbl_line[][m+2]){
	for (int i = 0; i < n; ++i){
		table[i][0] = assmbl_line[i*3][0] + assmbl_line[i*3][1];
	}
}

int fill_cost_and_path_table(int n, int m, int table[][m+1], int assmbl_line[][m+2], int path[][m-1]){
	int min = 0;
	int flag;
	for(int j = 1; j < m; ++j){
		for(int i = 0; i < n; ++i){
			if(i == 0){
				table[i][j] = min_2(table[i][j-1]+assmbl_line[i*3][j+1], table[i+1][j-1]+assmbl_line[i*3][j+1]+assmbl_line[(i+1)*3-1][j], &flag);
				path[i][j-1] = i+flag;
			}
			else if(i == n-1){
				table[i][j] = min_2(table[i][j-1]+assmbl_line[i*3][j+1], table[i-1][j-1]+assmbl_line[i*3][j+1]+assmbl_line[(i-1)*3+1][j], &flag);
				path[i][j-1] = i-flag;
			}
			else{
				table[i][j] = min_3(table[i-1][j-1]+assmbl_line[i*3][j+1]+assmbl_line[(i-1)*3+1][j], table[i][j-1]+assmbl_line[i*3][j+1], table[i+1][j-1]+assmbl_line[i*3][j+1]+assmbl_line[(i+1)*3-1][j], &flag);
				path[i][j-1] = i+flag;
			}
		}
	}
	for(int i = 0; i < n; ++i){
		table[i][m] = table[i][m-1]+assmbl_line[i*3][m+1];
		if(table[i][m] < table[min][m])
			min = i;
	}
	return min;
}

int main()
{
	int n,m;
	scanf("%d %d", &n, &m);
	int cost_table[n][m+1];
	int path_table[n][m-1];
	int path[m];
	int assmbl_line[3*n - 2][m+2];
	init_assembly_line(n, m, assmbl_line);
	init_cost_table(n, m, cost_table, assmbl_line);
	path[m-1] = fill_cost_and_path_table(n, m, cost_table, assmbl_line, path_table);
	for(int i = m-2; i >= 0; --i){
		path[i] = path_table[path[i+1]][i];
	}
	// printf("\n");
	// print_arr(3*n-2, m+2, assmbl_line);
	// printf("\n");
	// print_arr(n, m+1, cost_table);
	// printf("\n");
	// print_arr(n, m-1, path_table);
	// printf("\n");
	printf("%d\n", cost_table[path[m-1]][m]);
	for(int i = 0; i < m; ++i){
		printf("%d\n", path[i]+1);
	}
	return 0;
}
