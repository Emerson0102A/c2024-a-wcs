#include "AI.h"
#include <algorithm>

using namespace std;

int X, Y;

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	scoreMap.resize(size, vector<int>(size, 0));
	//初始化scoreMap的权重值

}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000); //假装思考
	chess->chessDown(&pos, CHESS_WHITE);
}



void AI::calculateFrame(chess_kind_t kind1, chess_kind_t kind2) 
{
	int personNum;
	int aiNum;
	int emptyNum;

	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {

			if (chess->getChessData(row, col) == 0) {
				for (int y = -1; y <= 0; y++) {
					for (int x = -1; x <= 1; x++) {
						personNum = 0;
						aiNum = 0;
						emptyNum = 0;

						if (x == 0 && y == 0) continue;
						if (x == 1 && y == 0) continue;

						//假设kind1在此落子
						for (int i = 1; i <= 4; ++i) {

							int curRow = row + i * x;
							int curCol = col + i * y;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) {
								if (chess->getChessData(curRow, curCol) == kind1) {
									personNum++;
								}
								else if (chess->getChessData(curRow, curCol) == kind2) {
									break;
								}
								else {
									emptyNum++;
									break;
								}
							}
						}

						for (int i = 1; i <= 4; i++) {
							int curRow = row - i * x;
							int curCol = col - i * y;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) {
								if (chess->getChessData(curRow, curCol) == kind1) {
									personNum++;
								}
								else if (chess->getChessData(curRow, curCol) == kind2) {
									break;
								}
								else {
									emptyNum++;
									break;
								}
							}
						}
						//计算kind1得分
						if (personNum == 1) {//活二
							scoreMap[row][col] += 10;
						}
						else if (personNum == 2) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 30;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 40;
							}
						}
						else if (personNum == 3) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 60;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 200;
							}
						}
						else if (personNum == 4) {
							scoreMap[row][col] += 20000;
						}
						//假设kind2落子，计算得分
						emptyNum = 0;
						for (int i = 1; i <= 4; ++i) {
							int curRow = row + i * x;
							int curCol = col + i * y;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) {
								if (chess->getChessData(curRow, curCol) == kind2) {
									aiNum++;
								}
								else if (chess->getChessData(curRow, curCol) == kind1) {
									break;
								}
								else {
									emptyNum++;
									break;
								}
							}
						}

						//反向计算
						for (int i = 1; i <= 4; ++i) {
							int curRow = row - i * x;
							int curCol = col - i * y;
							if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) {
								if (chess->getChessData(curRow, curCol) == kind2) {
									aiNum++;
								}
								else if (chess->getChessData(curRow, curCol) == kind1) {
									break;
								}
								else {
									emptyNum++;
									break;
								}
							}
						}

						//计算kind2得分
						if (aiNum == 0) {
							scoreMap[row][col] += 5;
						}
						else if (aiNum == 1) {
							scoreMap[row][col] += 10;
						}
						else if (aiNum == 2) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 25;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 50;
							}
						}
						else if (aiNum == 3) {
							if (emptyNum == 1) {
								scoreMap[row][col] += 55;
							}
							else if (emptyNum == 2) {
								scoreMap[row][col] += 1000;
							}
						}
						else if (aiNum == 4) {
							scoreMap[row][col] += 30000;
						}

					}
				}
			}
		}
	}




	


}



void AI::calculateScoreOfAI()
{
	calculateFrame(CHESS_BLACK, CHESS_WHITE);
}

void AI::calculateScoreOfMan()
{
	calculateFrame(CHESS_WHITE, CHESS_BLACK);
}

int AI::evaluate(int flag, int n)
{
	if (flag == 1) {
		//此时是max层
		calculateScoreOfAI();
	}
	else {
		//此时是min层
		calculateScoreOfMan();
	}

	int FinalScore = 0;
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
				FinalScore += scoreMap[i][j];
		}
	}
	if (n == 1 && flag == 1) {
		//max层
		return FinalScore - evaluate(-1, 2);
	}
	else if (n == 1 && flag == -1) {
		//min层
		return FinalScore - evaluate(1, 2);
	}
	else {
		return FinalScore;
	}
}

int AI::judge(int co[sizee][sizee], int x, int y, int n)
{
	int i, j;
	int sum = 0;
	if (n == 1)//3*3
	{
		for (i = x - 1; i < x + 2; i++)
			for (j = y - 1; j < y + 2; j++)
				if ((i > 0 && j > 0 && i < sizee && j < sizee) && (co[i][j] == 1 || co[i][j] == -1))
					sum = 1;
	}
	else//5*5
	{
		for (i = x - 2; i < x + 3; i += 2)
			for (j = y - 2; j < y + 3; j += 2)
				if ((i > 0 && j > 0 && i < sizee && j < sizee) && (co[i][j] == 1 || co[i][j] == -1))
					sum = 1;
	}
	return sum;
}

int AI::minMax(int co[sizee][sizee], int deep, int alpha, int beta, int flag)
//flag为1表示白棋，为-1表示黑棋，alpha初始值NGIF,beta初始值PTIF
{
	int i, j;
	int c[sizee][sizee];
	int minmax;
	int n = 1;
	Tree tree;
	tree.data = NGIF;
	tree.Alpha = alpha;
	tree.Beta = beta;
	tree.X = 0;
	tree.Y = 0;

	flag = -flag;
	if (deep > 0) {
		for (i = 0; i < sizee; i++) {
			for (j = 0; j < sizee; j++) {
				if (co[i][j] == 0 && judge(co, i, j, 1) && tree.Alpha < tree.Beta) {
					memcpy(c, co, sizeof(int) * sizee * sizee);
					c[i][j] = flag;
					minmax = minMax(c, deep - 1, tree.Alpha, tree.Beta, flag);
					if (deep % 2 == 0) {//max层
						if (n == 1) {
							tree.data = minmax;
							n++;//n == 2时结束
						}
						if (minmax > tree.data) {
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}


					}
					else//min层
					{
						if (n == 1)
						{
							tree.data = minmax;
							n++;
						}
						if (tree.Beta > minmax) {
							tree.Beta = minmax;
							tree.data = minmax;
							tree.X = i;
							tree.Y = j;
						}
					}
				}
			}
		}

	}
	else {
		return evaluate(flag, 1);
	}
}


ChessPos AI::think()
{
	calculateScoreOfAI();
	int size = chess->getGradeSize();
	int maxScore = 0;
	int co[sizee][sizee] = {};
	for (int i = 0; i < sizee; i++) {
		for (int j = 0; j < sizee; j++) {
			co[i][j] = chess->getChessData(i, j);
		}
	}
	vector<ChessPos> maxScorePos;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (maxScore < scoreMap[row][col]) {
				maxScore = scoreMap[row][col];
				maxScorePos.clear();
				maxScorePos.push_back(ChessPos(row, col));
			}
			else if (maxScore == scoreMap[row][col]) {
				maxScorePos.push_back(ChessPos(row, col));
			}
			else {
				continue;
			}
		}
	}
	int random = rand() % maxScorePos.size();
	
	int deep = 4;
	ChessPos maxScorePos2;
	static int n = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			minMax(co, deep, -1, NGIF, PTIF);
			maxScorePos2.row = X;
			maxScorePos2.col = Y;
			return maxScorePos[random];

		}
	}
}																			
