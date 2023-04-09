// ����� �ִ����� �˰���
int euclidRecursive(int a, int b)
{
	if (b == 0) return a;

	else
		return euclidRecursive(b, a % b);
}

// �ݺ��� �ִ����� �˰���
int euclidRepeatitive(int a, int b)
{
	int result, c;
	if (a < b) //a�� b���� �۴ٸ� a�� b�� ���� �ٲ���
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