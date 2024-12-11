#pragma once
#include "Chess.h"
#define sizee 13
#define PTIF 2147483647
#define NGIF -2147483647

class AI
{
public:
	void init(Chess *chess);
	void go();
	void calculateFrame(chess_kind_t kind1,chess_kind_t kind2);
	void calculateScoreOfAI();
	void calculateScoreOfMan();
	int evaluate(int flag, int n);//flag:1��ʾAI(max��)��-1��ʾ��(min��)
	int judge(int co[sizee][sizee], int x, int y, int n);//�ж���Χ�Ƿ�������
	int minMax(int co[sizee][sizee], int deep, int alpha, int beta, int flag);
	

	
	
	
	
	

	ChessPos think();

	

private:
	Chess* chess;
	vector<vector<int>> scoreMap;

	struct Tree {
		int data;
		int Alpha;
		int Beta;
		int X;
		int Y;
	};
	
	

	
	





};

