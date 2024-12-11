//
// Created by Emerson on 2024/9/27.
//
#include <iostream>
#include <fstream>
using namespace std;
//��ͼ
// int maze[5][5] = {
//     {0,0,0,0,0},
//     {0,0,0,0,0},
//     {0,0,1,0,0},
//     {0,0,0,0,0},
//     {0,0,0,0,0}
// };

int x, y, boxX, boxY, targetX, targetY;
const int ROWS = 5;
const int COLS = 5;
int maze[ROWS][COLS];

bool loadMap(const string& filename) {
    ifstream file(filename);
    if(!file) {
        cout << "û����" << endl;
        return false;
    }
    for(int i = 0;i < ROWS;i++) {
        for(int j = 0;j < COLS;j++) {
            file >> maze[i][j];
        }
    }
    file.close();
    x = 0;
    y = 0;
    boxX = 1;
    boxY = 1;
    targetX = ROWS - 1;
    targetY = COLS - 1;
    return true;
}


void printMaze() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == x && j == y) {
                cout << "P ";
            }
            else if(i == boxX && j == boxY) {
                cout << "B ";
            }
            else if(i == targetX && j == targetY) {
                cout << "T ";
            }
            else if (maze[i][j] == 0) {
                cout << ". ";
            }
            else if (maze[i][j] == 1) {
                cout << "# ";
            }
        }
        cout << endl;
    }
}

//�ж��Ƿ���Ч
bool isValid(int newX, int newY) {
    if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5) {
        if (maze[newX][newY] == 0) {
            return true;
        }
    }
    return false;
}
//�ж�
void Move(char& command) {
    switch (command) {
        case 'W':
            if (isValid(x - 1, y)) {
                if(x-1 == boxX && y == boxY && isValid(boxX-1,boxY)) {
                    x--,boxX--;
                }else {
                    x--;
                }
            }
            break;
        case'S':
            if (isValid(x + 1, y)) {
                if(x+1 == boxX && y == boxY && isValid(boxX+1,boxY)) {
                    x++,boxX++;
                }else {
                    x++;
                }
            }
            break;
        case'A':
            if (isValid(x, y - 1)) {
                if(x == boxX && y-1 == boxY && isValid(boxX,boxY-1)) {
                    y--,boxY--;
                }else {
                    y--;
                }
            }
            break;
        case'D':
            if (isValid(x, y + 1)) {
                if(x == boxX&& y+1 == boxY && isValid(boxX,boxY+1)) {
                    y++,boxY++;
                }else {
                    y++;
                }
            }
            break;
        default:
            cout << "ָ����Ч " << endl;
    }
}

int main() {
    int level = 1;

    while (true) {
        string filename = "boxmap" + to_string(level) + ".txt";
        if (!loadMap(filename)) {
            cout << "���û����" << endl;
            break;
        }
        char command;
        while(true) {
            printMaze();
            cout << "����ָ��" << endl;
            cin >> command;
            Move(command);
            if (boxX == targetX && boxY == targetY) {
                cout << "WIN" << endl;
                level++;
                break;
            }
        }
    }


    return 0;
}