#include <stdlib.h>
#include <stdio.h>

void testSearchK();
int searchK(int K);

int main(void)
{
	testSearchK();
}

void testSearchK()
{
	int fval = 15;
	int xret = 2;

	xret = searchK(fval);
	if (xret == fval)
	{
		printf("ã�ҽ��ϴ�. %d \n",fval, xret);
	}
	else
	{
		printf("%d ���� ã�� ���߽��ϴ�. %d \n", xret);
	}
}
//Funtion: find K from array A[]
//return:
//	-1: if K is not found
//	K: if K is found
int searchK(int K)
{
	//1. �迭�� ������ ���ڷ� �ʱ�ȭ�Ѵ�.
	int A[10] = { 5,7,3,0,80,95,42,31,23,15 };
	int ret = -1;
	int i; 
	//2. K���� ���������� ã�´�.
	for (i = 0; i < 10; i++) 
	{
		if (A[i] == K)
		{
			ret = K;
			break;
		}
	}

	return ret;
}
