/*
* quciksort(a, left, right)
* 1. if (left < right)
* 2. p = dividepivot(a, left, right)
* 3. quicksort(a, left, p - 1)
* 4. quicksort(a, p+1, right)
*/

#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#define MAX_SIZE 100

void swap(int* a, int* b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int medians(int a[], int left, int right) {
    /* select middle size pibit in left, mid, right */
    int mid = (left + right) / 2;
    if (((a[left] > a[mid]) && (a[left] < a[right])) || ((a[left] > a[right]) && (a[left] < a[mid]))) return left;
    if (((a[mid] > a[right]) && (a[mid] < a[left])) || ((a[mid] > a[left]) && (a[mid] < a[right]))) return mid;
    if (((a[right] > a[left]) && (a[right] < a[mid])) || ((a[right] > a[mid]) && (a[right] < a[left]))) return right;
    return left;
}

int dividepivot(int a[], int left, int right) {
    int p = medians(a, left, right);
    swap(&a[left], &a[p]);
    // pivot position left side
    p = left;
    // check array without pivot ==> start check to a[pivot + 1]
    left++;

    while (left <= right) {
        while (a[p] >= a[left] && left <= right)
            left++;
        while (a[p] <= a[right] && left <= right)
            right--;
        if (left <= right)
            swap(&a[left], &a[right]);
    }
    // move pivot to its final position
    swap(&a[p], &a[right]);

    // return pivot
    return right;
}

void quicksort(int a[], int left, int right) {
    if (left < right) {
        int p = dividepivot(a, left, right);
        quicksort(a, left, p - 1);
        quicksort(a, p + 1, right);
    }
}

int main() {

    int a[MAX_SIZE];
    int n = 0;

    FILE* fp = fopen("data.txt", "r");
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
    /*---------------------------------------------------------*/
    quicksort(a, 0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    /*---------------------------------------------------------*/
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

}