#include <stdio.h>
#include <time.h>

int testeuclid();

int main(void)
{
	double st, et;

	st = (double)clock() / CLOCKS_PER_SEC; //����
	int ret = 0;
	int ret1 = 0;
	ret = testeuclid();

	et = (((double)clock()) / CLOCKS_PER_SEC); //����
	printf("���� �ð���: %lf�� �Դϴ�.\n", (et-st));
	return 0;
}