//퀵 정렬 알고리즘
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
        int p = medians(A, left, right); // 피봇 선택

        // 피봇을 A[left]와 교환
        swap(&A[left], &A[p]);
        p = left;

        int L = left+1; //피봇의 다음위치
        int R = right; // 맨 오른쪽 위치

        //분할
        while (L <= R) { //left + 1 <= right
            while (A[L] < A[p]) {  //L이 p보다 큰 값을 만나거나 p를 만날 때까지 반복
                L++;
            }
            while (A[R] > A[p]) { //R이 p보다 작은 값을 만날때 까지 반복
                R--;
            }
            if (L <= R) { //L이 R보다 왼쪽에 있으면 서로 교환
                swap(&A[L], &A[R]);
            }
        }
        swap(&A[p], &A[R]); // 피봇의 위치 변경

        Quicksort(A, left, R - 1); // 왼쪽 부분집합에 대해 QuickSort 재귀호출
        Quicksort(A, R + 1, right); // 오른쪽 부분집합에 대해 QuickSort 재귀호출
    }
}

int main()
{
    int a[MAX_SIZE];
    int n = 0;

    FILE* fp = fopen("test.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
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
        printf("파일 열기 실패\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    printf("정렬 결과를 result.txt 파일에 저장하였습니다.\n");

    return 0;
}
