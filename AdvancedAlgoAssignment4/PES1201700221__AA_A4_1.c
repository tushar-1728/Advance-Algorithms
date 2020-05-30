#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sieve_of_eratosthenes(int *prime_arr, long long int end_point){
	int arr_no, bit_no;
	for(long long int i = 2; i*i < end_point; ++i){
		arr_no = i / 32;
		bit_no = i % 32;
		if(!(prime_arr[arr_no] & (1 << bit_no))){
			for(long long int j = i*i; j < end_point; j += i){
				arr_no = j / 32;
				bit_no = j % 32;
				prime_arr[arr_no] |= (1 << bit_no);
			}
		}
	}
}

int main(){
	int t, num, arr_no_start, arr_no_end, flag;
	int prime_arr_limit = ceil(9999999999 / 32.0);
	int *prime_arr = (int*)calloc(prime_arr_limit, sizeof(int));
	scanf("%d", &t);
	long long int end_point = 0;
	for(int i = 0; i < t; ++i){
		flag = 0;
		scanf("%d", &num);
		if(num < 2){
			printf("2\n");
		}
		else{
			if(end_point < 2*num -1){
				end_point = 2*num - 1;
				sieve_of_eratosthenes(prime_arr, end_point);
			}
			arr_no_start = num / 32;
			arr_no_end = (2* num) / 32;
			for(int j = arr_no_start; j <= arr_no_end; ++j){
				for(int k = 0; k < 32; ++k){
					if(!(prime_arr[j] & (1 << k)) && 32*j+k > num){
						printf("%d\n", 32*j+k);
						flag = 1;
						break;
					}
				}
				if(flag == 1)
					break;
			}
		}
	}
}