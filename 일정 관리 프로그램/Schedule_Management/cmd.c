#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void gotoxy(int x, int y);
void print_subMenu();
void print_mainMenu();
void draw_todo();
void draw_insert();
void draw_modify();
void draw_delete();



// 함수 돌아갈때 필요한 변수 추가하겠습니다.
data d[100];
int D_SIZE = 0;

// 해당 좌표에 출력 함수(UI)
void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 서브 메뉴(날짜순/금액순) 출력 함수
void print_subMenu()
{
    int subNum;
    while (1)
    {
        printf("\n1. 날짜순 2. 금액순 3. 보기 >> ");
        scanf("%d", &subNum);

        switch (subNum)
        {
            /*
                case 1 :
                날짜순으로 일정 나열
                함수 적용 후 UI에 적용
                메인 메뉴로 이동
            */
        case 1:
            printf("\n날짜순 on\n");
            date_quick_sort(d, 0, D_SIZE-1);
            // print_data(d, D_SIZE);
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            print_mainMenu();
            break;
            /*
                case 2 :
                금액순으로 일정 나열
                함수 적용 후 UI에 적용
                메인 메뉴로 이동
            */
        case 2:
            printf("\n금액순 on\n");
            money_quick_sort(d, 0, D_SIZE - 1);
            // print_data(d, D_SIZE);
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            print_mainMenu();
            break;
            /*
                case 3 :
                화면 초기화 후
                메인 메뉴로 이동 하면서
                일정표 화면에 띄움
            */
        case 3:
            printf("\n보기로 이동\n");
            system("cls");
            draw_todo();

            gotoxy(20, D_SIZE + 7);
            print_mainMenu();
            break;

        default:
            printf("\n잘못된 입력입니다.\n");
            break;
        }
    }
}

// 메인메뉴 출력 함수
void print_mainMenu()
{
    int index = 0;

    int mainNum;
    while (1)
    {
        printf("\n1.보기 변환 2. 내용 추가 3. 내용 수정 4. 내용 삭제 5. 종료 >> ");
        scanf("%d", &mainNum);

        switch (mainNum)
        {
        case 1:
            system("cls");
            print_subMenu();
            break;
        case 2:
            printf("\n내용 추가 메뉴 선택\n");
            system("cls");
            insert_and_modify_2(d, &D_SIZE, "ori.txt");
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            break;
        case 3:
            printf("\n내용 수정 메뉴 선택\n");
            system("cls");
            modify_3(d, D_SIZE, "ori.txt");
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            break;
        case 4:
            printf("\n내용 삭제 메뉴 선택\n");
            system("cls");
            delete_4(d, &D_SIZE, "ori.txt");
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            break;
        case 5:
            printf("\n종료 선택\n");
            exit(1);
            break;
        default:
            printf("\n잘못된 입력입니다.\n");
            break;
        }
    }
}

// 일정표 UI
void draw_todo()
{
    int i, j;

    gotoxy(2, 0);
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");
    gotoxy(2, D_SIZE + 5);
    printf("□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n");

    gotoxy(10, 2);
    printf("날짜");
    gotoxy(19, 2);
    printf("|");
    gotoxy(26, 2);
    printf("지출 지급");
    gotoxy(41, 2);
    printf("|");
    gotoxy(65, 2);
    printf("지출급 내용");
    gotoxy(100, 2);
    printf("|");
    gotoxy(130, 2);
    printf("일정 내용");

    for (i = 1; i <= D_SIZE + 5; i++)
    {
        gotoxy(2, i);
        printf("□");
        gotoxy(168, i);
        printf("□");
    }
    gotoxy(5, 3);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < D_SIZE; i++)
    {
        gotoxy(8, i + 4);
        printf("%d-%d-%d", d[i].date.year, d[i].date.month, d[i].date.day);
        gotoxy(19, i + 4);
        printf("|");
        gotoxy(28, i + 4);
        printf("%d", d[i].money);
        gotoxy(41, i + 4);
        printf("|");
        gotoxy(46, i + 4);
        printf("%s", d[i].money_reason);
        gotoxy(100, i + 4);
        printf("|");
        gotoxy(102, i + 4);
        printf("%s", d[i].str);
    }
}

// 내용추가 UI
void draw_insert()
{
    
}

// 내용수정 UI
void draw_modify()
{

}

// 내용 삭제 UI
void draw_delete()
{
    //몇번쨰 요소 (index)를 삭제할지 사용자에게 입력 받아야합니다.
    
}

// 데이터 파일 불러오기
void load_file_data()
{
    D_SIZE = check_array_size_in_txt("ori.txt");
    read_torken_struct(D_SIZE);
    for (int i = 0; i < D_SIZE; i++)
    {
        d[i] = read_torken_struct(i + 1);
    }
}


int main()
{
    load_file_data();

    system("cls");
    system("mode con cols=180 lines=180");

    FILE* fp = fopen("ori.txt", "r");
    if (fp == NULL) {
        printf("파일 열기 오류\n");
        return 1;
    }

    fclose(fp);

    draw_todo();

    gotoxy(20, D_SIZE + 7);
    print_mainMenu();

    return 0;
}
