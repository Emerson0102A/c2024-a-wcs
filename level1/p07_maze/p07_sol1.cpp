//
// Created by Emerson on 2024/9/27.
//
#include <iostream>
#include <fstream>
using namespace std;
//��ͼ
// int maze[5][5] = {
//     {0,1,0,0,0},
//     {0,1,0,1,0},
//     {0,1,0,1,0},
//     {0,1,0,1,0},
//     {0,0,0,1,0}
// };

const int ROWS = 5;
const int COLS = 5;
int maze[ROWS][COLS];

//���
int x, y;
//Ŀ�ĵ�
int targetX,targetY;

bool loadMap(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "û����" << endl;
        return false;
    }
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            file >> maze[i][j];
        }
    }
    file.close();

    //ÿ�γ�ʼ��ʱ����������������
    x = 0;
    y = 0;
    //Ŀ���
    targetX = ROWS - 1;
    targetY = COLS - 1;


    return true;
}
//��ͼ����
void printMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == x && j == y) {
                cout << "P ";
            }
            else if(i == targetX && j == targetY) {
                cout << "T";
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
    if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS) {
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
                x--;
            }
        break;
        case'S':
            if (isValid(x + 1, y)) {
                x++;
            }
        break;
        case'A':
            if (isValid(x, y - 1)) {
                y--;
            }
        break;
        case'D':
            if (isValid(x, y + 1)) {
                y++;
            }
        break;
        default:
            cout << "ָ����Ч " << endl;
    }
}

int main() {
    int level = 1;

    while (true) {
        //��̬�����ļ���
        string filename = "map" + to_string(level) + ".txt";
        if (!loadMap(filename)) {
            cout << "���һ��Ҳû����" << endl;
            break;
        }

        cout << "���عؿ�"  << level << "�ɹ�" << endl;

        char command;
        while (true) {
            printMaze(); // ��ʾ��ͼ
            cout << "����ָ�� (W/A/S/D ������������): ";
            cin >> command;
            Move(command); // �ƶ����

            // �ж��Ƿ񵽴�Ŀ�ĵ�
            if (x == targetX && y == targetY) {
                cout << "�ؿ� " << level << " ��ɣ�" << endl;
                level++; // ������һ��
                break;
            }
        }
    }
    return 0;
}