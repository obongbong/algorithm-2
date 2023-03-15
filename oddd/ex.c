/*배열을 입력받아 더 큰 값을 출력해주는 프로그램*/
#include<stdio.h>
#define MAX_ELEMENTS 50000
int find_max_score(int score[], int n)
{
	int i, tmp;
	tmp = score[0];
	for (i = 0; i < n; i++)
		if (score[i] > tmp)
			tmp = score[i];
	return tmp;
}
int main(void)
{
	int A[5], B[5];
	int i, maxA, maxB;

	for (i = 0; i < 5; i++)
	{
		printf("Please enter two number >> ");
		scanf_s("%d %d", &A[i], &B[i]);
	}
	maxA = find_max_score(A, 5);
	maxB = find_max_score(B, 5);

	if (maxA > maxB)
		printf("Array A");
	else if (maxA < maxB)
		printf("Array B");
	else
		printf("Array A and Array B have same maxinum number ");

	return 0;
}