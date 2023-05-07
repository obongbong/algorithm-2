//�� ���� �˰���
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int medians(int a[], int left, int right) {
	int mid = (left + right) / 2;
	if (((a[left] > a[mid]) && (a[left] < a[right])) || ((a[left] > a[right]) && (a[left] < a[mid]))) return left;
	if (((a[mid] > a[right]) && (a[mid] < a[left])) || ((a[mid] > a[left]) && (a[mid] < a[right]))) return a[mid];
	if (((a[right] > a[left]) && (a[right] < a[mid])) || ((a[right] > a[mid]) && (a[right] < a[left]))) return right;
}

void Quicksort(int A[], int left, int right) {
    if (left < right) {
        int p = medians(A, left, right); // �Ǻ� ����

        // �Ǻ��� A[left]�� ��ȯ
        swap(&A[left], &A[p]);
        p = left;

        int L = left+1; //�Ǻ��� ������ġ
        int R = right; // �� ������ ��ġ

        //����
        while (L <= R) { //left + 1 <= right
            while (A[L] < A[p]) {  //L�� p���� ū ���� �����ų� p�� ���� ������ �ݺ�
                L++;
            }
            while (A[R] > A[p]) { //R�� p���� ���� ���� ������ ���� �ݺ�
                R--;
            }
            if (L <= R) { //L�� R���� ���ʿ� ������ ���� ��ȯ
                swap(&A[L], &A[R]);
            }
        }
        swap(&A[p], &A[R]); // �Ǻ��� ��ġ ����

        Quicksort(A, left, R - 1); // ���� �κ����տ� ���� QuickSort ���ȣ��
        Quicksort(A, R + 1, right); // ������ �κ����տ� ���� QuickSort ���ȣ��
    }
}

int main()
{
    int a[MAX_SIZE];
    int n = 0;

    FILE* fp = fopen("test.txt", "r");
    if (fp == NULL) {
        printf("���� ���� ����\n");
        return -1;
    }

    while (1) {
        int num;
        if (fscanf(fp, "%d", &num) == EOF) break;
        a[n++] = num;
    }

    fclose(fp);

    Quicksort(a, 0, n - 1);

    fp = fopen("result.txt", "w");
    if (fp == NULL) {
        printf("���� ���� ����\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    printf("���� ����� result.txt ���Ͽ� �����Ͽ����ϴ�.\n");

    return 0;
}
