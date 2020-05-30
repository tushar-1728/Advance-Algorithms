#include <stdio.h>

void swap(int *a){
	int temp = a[0];
	a[0] = a[4];
	a[4] = temp;
}

int test(int *imp){
	int rv = *imp;
	*imp = 1;
	return rv;
}

int main(){
	int imp = 0;
	int a[] = {1,2,3,4,5};
	swap(a);
	for (int i = 0; i < 5; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	int tes = test(&imp);
	printf("%d %d\n", tes, imp);
	printf("%d\n", a[-2]);
	return 0;
}