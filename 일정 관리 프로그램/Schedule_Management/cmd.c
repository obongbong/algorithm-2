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



// �Լ� ���ư��� �ʿ��� ���� �߰��ϰڽ��ϴ�.
data d[100];
int D_SIZE = 0;

// �ش� ��ǥ�� ��� �Լ�(UI)
void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���� �޴�(��¥��/�ݾ׼�) ��� �Լ�
void print_subMenu()
{
    int subNum;
    while (1)
    {
        printf("\n1. ��¥�� 2. �ݾ׼� 3. ���� >> ");
        scanf("%d", &subNum);

        switch (subNum)
        {
            /*
                case 1 :
                ��¥������ ���� ����
                �Լ� ���� �� UI�� ����
                ���� �޴��� �̵�
            */
        case 1:
            printf("\n��¥�� on\n");
            date_quick_sort(d, 0, D_SIZE-1);
            // print_data(d, D_SIZE);
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            print_mainMenu();
            break;
            /*
                case 2 :
                �ݾ׼����� ���� ����
                �Լ� ���� �� UI�� ����
                ���� �޴��� �̵�
            */
        case 2:
            printf("\n�ݾ׼� on\n");
            money_quick_sort(d, 0, D_SIZE - 1);
            // print_data(d, D_SIZE);
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            print_mainMenu();
            break;
            /*
                case 3 :
                ȭ�� �ʱ�ȭ ��
                ���� �޴��� �̵� �ϸ鼭
                ����ǥ ȭ�鿡 ���
            */
        case 3:
            printf("\n����� �̵�\n");
            system("cls");
            draw_todo();

            gotoxy(20, D_SIZE + 7);
            print_mainMenu();
            break;

        default:
            printf("\n�߸��� �Է��Դϴ�.\n");
            break;
        }
    }
}

// ���θ޴� ��� �Լ�
void print_mainMenu()
{
    int index = 0;

    int mainNum;
    while (1)
    {
        printf("\n1.���� ��ȯ 2. ���� �߰� 3. ���� ���� 4. ���� ���� 5. ���� >> ");
        scanf("%d", &mainNum);

        switch (mainNum)
        {
        case 1:
            system("cls");
            print_subMenu();
            break;
        case 2:
            printf("\n���� �߰� �޴� ����\n");
            system("cls");
            insert_and_modify_2(d, &D_SIZE, "ori.txt");
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            break;
        case 3:
            printf("\n���� ���� �޴� ����\n");
            system("cls");
            modify_3(d, D_SIZE, "ori.txt");
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            break;
        case 4:
            printf("\n���� ���� �޴� ����\n");
            system("cls");
            delete_4(d, &D_SIZE, "ori.txt");
            system("cls");
            draw_todo();
            gotoxy(20, D_SIZE + 7);
            break;
        case 5:
            printf("\n���� ����\n");
            exit(1);
            break;
        default:
            printf("\n�߸��� �Է��Դϴ�.\n");
            break;
        }
    }
}

// ����ǥ UI
void draw_todo()
{
    int i, j;

    gotoxy(2, 0);
    printf("�������������������������������������������������������������������������������������\n");
    gotoxy(2, D_SIZE + 5);
    printf("�������������������������������������������������������������������������������������\n");

    gotoxy(10, 2);
    printf("��¥");
    gotoxy(19, 2);
    printf("|");
    gotoxy(26, 2);
    printf("���� ����");
    gotoxy(41, 2);
    printf("|");
    gotoxy(65, 2);
    printf("����� ����");
    gotoxy(100, 2);
    printf("|");
    gotoxy(130, 2);
    printf("���� ����");

    for (i = 1; i <= D_SIZE + 5; i++)
    {
        gotoxy(2, i);
        printf("��");
        gotoxy(168, i);
        printf("��");
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

// �����߰� UI
void draw_insert()
{
    
}

// ������� UI
void draw_modify()
{

}

// ���� ���� UI
void draw_delete()
{
    //����� ��� (index)�� �������� ����ڿ��� �Է� �޾ƾ��մϴ�.
    
}

// ������ ���� �ҷ�����
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
        printf("���� ���� ����\n");
        return 1;
    }

    fclose(fp);

    draw_todo();

    gotoxy(20, D_SIZE + 7);
    print_mainMenu();

    return 0;
}
