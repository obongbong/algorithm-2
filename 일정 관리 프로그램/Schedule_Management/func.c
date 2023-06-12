#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 최대 입력 버퍼 크기
#define STRING_SIZE 256

// -----------기본 데이터 구조체------------
typedef struct date
{
    int year;
    int month;
    int day;
} Date;

typedef struct _data
{
    Date date;
    char str[STRING_SIZE];
    int money;
    char money_reason[STRING_SIZE];
} data;
// -----------------------------------------

data d[100] = { 0 };
//data d top size
int size;

/* ------------------------------------------------파일 입출력 부분 */
int check_array_size_in_txt(const char* txt)
{
    int line = 0;
    int tmp;
    FILE* fp;
    fp = fopen(txt, "r");
    while ((tmp = fgetc(fp)) != EOF)
    {
        if (tmp == '\n')
        {
            line++;
        }
    }
    fclose(fp); // 파일 닫기
    return line;
}

void writeDataToFile(data d[], int size, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d-%02d-%02d|%d|%s|%s\n", d[i].date.year, d[i].date.month, d[i].date.day, d[i].money, d[i].money_reason, d[i].str);
    }

    fclose(fp);
}

void generate_random_data(data d[], int size)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < size; i++)
    {
        d[i].date.year = rand() % 100;
        d[i].date.month = rand() % 12 + 1;  // 1부터 12까지의 무작위 월
        d[i].date.day = rand() % 30 + 1;    // 1부터 30까지의 무작위 일

        d[i].money = rand() % 10000;  // 0부터 9999까지의 무작위 금액

        sprintf(d[i].money_reason, "Reason %d", i + 1);  // "Reason 1", "Reason 2", ... 형태의 문자열
        sprintf(d[i].str, "String %d", i + 1);  // "String 1", "String 2", ... 형태의 문자열
    }
}

void print_data(const data d[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Date: %d-%02d-%02d\n", d[i].date.year, d[i].date.month, d[i].date.day);
        printf("Money: %d\n", d[i].money);
        printf("Money Reason: %s\n", d[i].money_reason);
        printf("String: %s\n", d[i].str);
        printf("\n");
    }
}

data read_torken_struct(int n)
{
    data D;
    int i = 0, j = 0;
    char str[STRING_SIZE];
    char* tmp[4];

    FILE* fp = NULL;
    fp = fopen("ori.txt", "r");
    if (fp == NULL)
        exit(1);

    if (fp != NULL)
    {
        for (j = 0; j < n; j++)
            fgets(str, STRING_SIZE, fp);

        if (str[strlen(str) - 1] == '\n')
        {
            str[strlen(str) - 1] = '\0'; // 문자열의 끝을 널 문자로 대체
        }

        tmp[0] = strtok(str, "|");
        tmp[1] = strtok(NULL, "|");
        tmp[2] = strtok(NULL, "|");
        tmp[3] = strtok(NULL, "|");

        D.money = atoi(tmp[1]);
        strcpy(D.money_reason, tmp[2]);
        strcpy(D.str, tmp[3]);

        D.date.year = atoi(strtok(tmp[0], "-"));
        D.date.month = atoi(strtok(NULL, "-"));
        D.date.day = atoi(strtok(NULL, "-"));
    }

    fclose(fp);
    return D;
}
/*------------------------------------------------------------------*/

/*-----------------------------------------------------정렬 알고리즘*/
void swap(data* a, data* b) {
    data temp = *a;
    *a = *b;
    *b = temp;
}
//돈 나누기
int partition(data list[], int left, int right) {
    int pivot = list[left].money; // 맨 왼쪽을 피벗으로 설정
    int low = left + 1; // low = 피벗 다음 값
    int high = right;

    while (low <= high) {
        while (low <= right && list[low].money > pivot)
            low++;
        while (high >= left + 1 && list[high].money <= pivot)
            high--;
        if (low <= high) {
            swap(&list[low], &list[high]);
        }
    }
    swap(&list[left], &list[high]);
    return high;
}
//돈 정렬
void money_quick_sort(data list[], int left, int right) {
    if (left < right) {
        int pivot = partition(list, left, right);
        money_quick_sort(list, left, pivot - 1);
        money_quick_sort(list, pivot + 1, right);
    }
}
// 날짜 비교 함수
int compare_dates(struct date date1, struct date date2) {
    if (date1.year < date2.year)
        return -1;
    else if (date1.year > date2.year)
        return 1;
    else {
        if (date1.month < date2.month)
            return -1;
        else if (date1.month > date2.month)
            return 1;
        else {
            if (date1.day < date2.day)
                return -1;
            else if (date1.day > date2.day)
                return 1;
            else
                return 0; // 날짜가 동일한 경우
        }
    }
}
// 날짜 나누기
int date_partition(data list[], int left, int right) {
    struct date pivot = list[left].date;
    int low = left + 1;
    int high = right;

    while (1) {
        while (low <= high && compare_dates(list[low].date, pivot) <= 0)
            low++;

        while (low <= high && compare_dates(list[high].date, pivot) > 0)
            high--;

        if (low < high) {
            swap(&list[low], &list[high]);
        }
        else {
            break;
        }
    }

    swap(&list[left], &list[high]);
    return high;
}
// 날짜 정렬
void date_quick_sort(data list[], int left, int right) {
    if (left < right) {
        int pivot = date_partition(list, left, right);
        date_quick_sort(list, left, pivot - 1);
        date_quick_sort(list, pivot + 1, right);
    }
}

/*------------------------------------------------------------------*/

/*---------------------------------------------------cmd쪽 최종 함수*/
void insert_and_modify_2(data d[], int* size) {
    int i, index;
    Date date = { 0 };

    /* cmd part ----------------------------------------*/
    gotoxy(64, 0);
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    for (i = 1; i <= 20; i++)
    {
        gotoxy(64, i);
        printf("□");
        gotoxy(130, i);
        printf("□");
    }
    gotoxy(64, 20);
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");

    gotoxy(74, 3);
    printf("날짜 입력 (ex: yyyy-mm-dd): ");
    scanf("%d-%d-%d", &date.year, &date.month, &date.day);
    /*------------------------------------------------*/

    // 중복 확인 후 있으면 해당 데이터 수정
    for (index = 0; index < *size; index++) {
        if (d[index].date.year == date.year && d[index].date.month == date.month && d[index].date.day == date.day) {
            /* cmd part */
            system("cls");
            gotoxy(64, 0);
            printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
            for (i = 1; i <= 20; i++)
            {
                gotoxy(64, i);
                printf("□");
                gotoxy(130, i);
                printf("□");
            }
            gotoxy(64, 20);
            printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");

            gotoxy(74, 3);
            printf("중복된 날짜. 해당 날짜를 수정하겠습니다.\n");

            gotoxy(74, 5);
            printf("날짜 입력 (ex: yyyy-mm-dd): ");
            scanf("%d-%d-%d", &d[index].date.year, &d[index].date.month, &d[index].date.day);

            gotoxy(74, 7);
            printf("지급 지출된 돈 입력: ");
            scanf("%d", &d[index].money);

            gotoxy(74, 9);
            printf("지급 지출내역 입력 : ");
            scanf(" %[^\n]", d[index].money_reason);

            gotoxy(74, 11);
            printf("일정 입력: ");
            scanf(" %[^\n]", d[index].str);

            writeDataToFile(d, *size, "ori.txt"); // 파일에 데이터 삽입

            return;
        }
    }

    // 중복되는 데이터가 없는 경우 새 데이터 삽입
    data temp;
    temp.date = date;

    /* cmd part */
    gotoxy(74, 5);
    printf("지급 지출된 돈 입력: ");
    scanf("%d", &temp.money);

    gotoxy(74, 7);
    printf("지급 지출 내역 입력: ");
    scanf(" %[^\n]", temp.money_reason);

    gotoxy(74, 9);
    printf("일정 입력: ");
    scanf(" %[^\n]", temp.str);

    // 배열 d 맨 뒤에 데이터 삽입
    d[*size] = temp;
    (*size)++;

    writeDataToFile(d, *size, "ori.txt"); // 파일에 데이터 삽입
}

// 데이터 수정 함수
void modify_3(data d[], int size, const char* filename) {
    char searchDate[STRING_SIZE];

    gotoxy(64, 0);
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    for (int i = 1; i <= 20; i++)
    {
        gotoxy(64, i);
        printf("□");
        gotoxy(130, i);
        printf("□");
    }
    gotoxy(64, 20);
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");

    gotoxy(74, 3);
    printf("일정을 수정할 날짜 입력 (ex: yyyy-mm-dd): ");
    scanf("%s", searchDate);

    int found = 0;

    for (int i = 0; i < size; i++) {
        char tempDate[STRING_SIZE];
        sprintf(tempDate, "%d-%02d-%02d", d[i].date.year, d[i].date.month, d[i].date.day);

        if (strcmp(tempDate, searchDate) == 0) {

            gotoxy(74, 5);
            printf("날짜 입력 (ex: yyyy-mm-dd): ");
            scanf("%d-%d-%d", &d[i].date.year, &d[i].date.month, &d[i].date.day);

            gotoxy(74, 7);
            printf("지급 지출 입력: ");
            scanf("%d", &d[i].money);

            gotoxy(74, 9);
            printf("지급 지출 내역 입력: ");
            scanf(" %[^\n]", d[i].money_reason);

            gotoxy(74, 11);
            printf("일정 입력: ");
            scanf(" %[^\n]", d[i].str);

            found = 1;
            break;
        }
    }

    if (found) {
        writeDataToFile(d, size, "ori.txt");
        printf("데이터 수정 후 파일에 저장 완료.\n");
    }
    else {
        gotoxy(74, 8);
        printf("입력한 데이터는 존재하지 않습니다.\n");
    }
}

// 데이터 삭제 함수
void delete_4(data d[], int* size, const char* filename) {
    char deleteDate[STRING_SIZE];

    gotoxy(64, 0);
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    for (int i = 1; i <= 20; i++)
    {
        gotoxy(64, i);
        printf("□");
        gotoxy(130, i);
        printf("□");
    }
    gotoxy(64, 20);
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");

    gotoxy(74, 3);
    printf("일정을 삭제할 날짜 입력 (ex: yyyy-mm-dd): ");
    scanf("%s", deleteDate);

    int found = 0;

    for (int i = 0; i < *size; i++) {
        char tempDate[STRING_SIZE];
        sprintf(tempDate, "%d-%02d-%02d", d[i].date.year, d[i].date.month, d[i].date.day);

        if (strcmp(tempDate, deleteDate) == 0) {
            for (int j = i; j < *size - 1; j++) {
                d[j] = d[j + 1];
            }
            (*size)--;
            found = 1;
            break;
        }
    }

    if (found) {
        writeDataToFile(d, *size, filename);
        printf("데이터 삭제 후 파일에 저장 완료\n");
    }
    else {
        printf("입력한 데이터는 존재하지 않습니다.\n");
    }
}

/*------------------------------------------------------------------*/

/*------------------------------------------------------------------*/

