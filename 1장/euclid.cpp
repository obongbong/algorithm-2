// 재귀적 최대공약수 알고리즘
int euclidRecursive(int a, int b)
{
	if (b == 0) return a;

	else
		return euclidRecursive(b, a % b);
}

// 반복적 최대공약수 알고리즘
int euclidRepeatitive(int a, int b)
{
	int result, c;
	if (a < b) //a가 b보다 작다면 a와 b의 값을 바꿔줌
	{
		c = a;
		a = b;
		b = c;
	}
	while (b != 0)
	{
		result = a% b;
		a = b;
		b = result;
	}
	return a;
}