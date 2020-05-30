#include <stdio.h>

void test(char *str){
	str[0] = 'k';
}

int main(){
	char t[10];
	scanf("%s", t);
	t[0] = 'z';
	test(t);
	printf("%s\n", t);
	printf("%d\n", sizeof(t)*sizeof(char));
}