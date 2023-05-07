#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 10
typedef struct Point {
    int x;
    int y;
} Point;

double distance(Point p1, Point p2)
{
    double result;
    double a, b, c;

    if (p1.x == p2.x) //x���� ��ġ�� ������� 
    {
        result = p2.y - p1.y;
        fabs(result); //���� �Լ�fabs�� �̿��� �����ϰ�� ��� 
    }
    else if (p1.y == p2.y) //y���� ��ġ�� ������� 
    {
        result = p2.x - p1.x;
        fabs(result);
    }
    else //���Ͱ���� ������ Ȱ���ؾ� �ϴ°�� 
    {
        a = p1.x - p2.x;
        b = p1.y - p2.y;
        c = (pow(a, 2)) + (pow(b, 2));
        result = sqrt(c);
        return result;
    }
}
void Read_File(Point a[], int size)
{
    int i, count;
    FILE* fp = fopen("data.txt", "r"); // �б�� ���� ����

    if (fp == NULL) // ���� ���� ���н�
    {
        printf("���Ͽ��� ����\n");
        return;
    }
    printf("�����б� ����!\n");

    for (i = 0; i < size; i++)
    {
        if (fscanf(fp, "%d", &count) == 1)
        {
            a[i].x = count;

            if (fscanf(fp, "%d", &count) == 1)
                a[i].y = count;
            else
                printf("������ �ʰ��߽��ϴ�.\n");
        }
        else
        {
            printf("������ �ʰ��߽��ϴ�.\n");
            return;
        }
    }
    for (i = 0;i < size;i++)
        printf("(%d, %d)\n", a[i].x, a[i].y);
    fclose(fp);
}


double Closest_Pair(Point P[], int left, int right, Point* Pair[])
{
    int i, j;

    if (right - left <= 2) //���� ������ 3�� �̸��� ���
    {
        double minDistance = 99999999;
        for (i = left; i < right; i++)
        {
            for (j = i + 1; j < right; j++)
            {
                double dist = distance(P[i], P[j]);
                if (dist < minDistance)
                {
                    minDistance = dist;
                    Pair[0] = &P[i];
                    Pair[1] = &P[j];
                }
            }
        }
        return minDistance;
    }
    // �߾��� �ε��� ���
    int mid = (left + right) / 2;

    // ���� �κа� ���� �κп� ���� ��������� �ֱ��� ���� �ְ� �Ÿ� ã��
    Point* leftClosestPair[2];
    double minDistanceLeft = Closest_Pair(P, left, mid, leftClosestPair);
    Point* rightClosestPair[2];
    double minDistanceRight = Closest_Pair(P, mid + 1, right, rightClosestPair);

    // ���� �κа� ���� �κп��� ã�� �ֱ��� ���� �� �߿��� �ּ� �Ÿ� ����
    double minDistance = (minDistanceLeft < minDistanceRight) ? minDistanceLeft : minDistanceRight;
    Point** minDistancePair = (minDistanceLeft < minDistanceRight) ? leftClosestPair : rightClosestPair;

    // ���������� �������� �� ����� ���� ���� �ִ��� Ȯ��
    double minDistanceStrip = 99999999;
    Point* stripPair[2];
    int stripPairCount = 0;

    for (i = left; i <= right; i++) {
        if (abs(P[i].x - P[mid].x) < minDistance) {
            for (j = i + 1; j <= right; j++) {
                if (abs(P[j].x - P[mid].x) < minDistance) {
                    double dist = distance(P[i], P[j]);
                    if (dist < minDistance) {
                        minDistance = dist;
                        stripPair[0] = &P[i];
                        stripPair[1] = &P[j];
                        stripPairCount = 1;
                    }
                    else if (dist == minDistance) {
                        if (stripPairCount < 2) {
                            stripPair[stripPairCount++] = &P[i];
                            stripPair[stripPairCount++] = &P[j];
                        }
                    }
                }
                else {
                    break;
                }
            }
        }
    }

    // ���������� ���������� �ֱ��� ���� �ְ� �Ÿ� �� �ּҰ� ����
    if (stripPairCount > 0) {
        minDistancePair = stripPair;
    }

    Pair[0] = minDistancePair[0];
    Pair[1] = minDistancePair[1];
    return minDistance;
}

int main()
{
    Point P[SIZE];
    Read_File(P, SIZE);
    Point* Pair[2];
    Closest_Pair(P, 0, SIZE, Pair);

    int i;
    FILE* fp = fopen("result.txt", "w");// ����� ���� ����
    if (fp == NULL) 					// ���� ���� ���н�
    {
        printf("���Ͽ��� ����\n");
        return;
    }

    fprintf(fp, "�ֱ��� ���� ���� ");
    for (i = 0; i < 2; i++)
    {
        fprintf(fp, "(");
        fprintf(fp, "%d ", Pair[i]->x);
        fprintf(fp, "%d", Pair[i]->y);
        fprintf(fp, ") ");
    }
    fclose(fp);
    return 0;
}
