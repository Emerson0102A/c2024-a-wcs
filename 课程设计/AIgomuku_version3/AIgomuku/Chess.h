#pragma once
#include<graphics.h>//easyXͼ�ο��ͷ�ļ�
#include<vector>
using namespace std;

//����λ��
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0,int c = 0) : row(r),col(c){}

	bool operator==(const ChessPos& pos) {
		return row == pos.row && col == pos.col;
	}

};

typedef enum {
	CHESS_WHITE = -1, //����
	CHESS_BLACK = 1, //����
	CHESS_EMPTY = 0 //�հ�
}chess_kind_t;

class Chess
{	
public:
	vector<vector<int>> chessMap;
	vector<ChessPos> availableMoves;
	
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void FindAvailableMoves();
	//���̵ĳ�ʼ�����������̵�ͼƬ��Դ����ʼ�����̵��������
	void init();

	bool isValid(int x, int y);
	//�ж���ָ������(x,y)λ�ã��Ƿ�����Ч���
	bool clickBoard(int x, int y, ChessPos* pos);

	//��ָ��λ������
	void chessDown(ChessPos *pos, chess_kind_t kind);
	
	//��ȡ���̴�С
	int getGradeSize();


	//��ȡָ��λ���Ǻ��壬���ǰ��壬���ǿհ�
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//�������Ƿ����
	bool checkOver();
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;//���̵Ĵ�С
	int margin_x;//���̵����߽�
	int margin_y;//���̵Ķ����߽�
	float chessSize;//���ӵĴ�С(����С����Ĵ�С)
	
	//�洢��ǰ��ֵ����ӷֲ����� 0:�հ� 1:���� -1:����
	//chessMap[3][5] ��ʾ���̵ĵ�3�е�5��
	

	//��ʾ���ڸ�˭����
	bool playerFlag;//true:������  false:������

	void updateGameMap(ChessPos* pos);

	bool checkWin();//���ʤ���ѷ֣�����true,���򷵻�false

	ChessPos lastPos;//������ӵ��λ��
};

