#include <stdio.h>
#include <time.h>

int testeuclid();

int main(void)
{
	double st, et;

	st = (double)clock() / CLOCKS_PER_SEC; //시작
	int ret = 0;
	int ret1 = 0;
	ret = testeuclid();

	et = (((double)clock()) / CLOCKS_PER_SEC); //종료
	printf("수행 시간은: %lf초 입니다.\n", (et-st));
	return 0;
}