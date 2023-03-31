#include <stdio.h>

// 미로의 크기
#define SIZE 8

// 미로 배열 초기 설정
int maze[SIZE][SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};
//현재 위치
int point[SIZE][SIZE];

void find_way(int x, int y)
{
    // 도착점에 도달한 경우
    if (x == SIZE-2 && y == SIZE-2) {
        printf("goal!\n");
        maze[SIZE - 2][SIZE - 2] == 3;
        return;
    }
    else {
        // 현재 위치를 방문한 것으로 표시
        point[x][y] = 1;

        if (maze[x - 1][y] == 0 && point[x - 1][y] == 0) // 상
            find_way(x - 1, y);
        if (maze[x + 1][y] == 0 && point[x + 1][y] == 0) // 하
            find_way(x + 1, y);
        if (maze[x][y - 1] == 0 && point[x][y - 1] == 0) // 좌
            find_way(x, y - 1);
        if (maze[x][y + 1] == 0 && point[x][y + 1] == 0) // 우
            find_way(x, y + 1);
        
    }
}

int main()
{
    printf("start\n");
    //시작 포인트는 1.1
    find_way(1, 1);
    return 0;
}
