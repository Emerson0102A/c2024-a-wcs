#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;

	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row(size, 0);
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos = think();
	Sleep(1000); //假装思考
	chess->chessDown(&pos, CHESS_WHITE);
}

void AI::calculateScore()
{	
	int personNum = 0; //棋手方有多少个连续棋子
	int aiNum = 0; //AI有多少个连续棋子
	int emptyNum = 1;//该方向上空白位的个数         ////////////////////////////////////



	//评分向量数组清零
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;

		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			
			//对每个点进行计算
			if (chess->getChessData(row, col)) continue;
			//只对空白点评分

			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					//清零计数器
					personNum = 0;
					aiNum = 0;
					emptyNum = 1;/////////////////////////////////////////////////////////
					if (y == 0 && x == 0) continue;

					//假设黑棋在该位置落子
					for (int i = 1; i <= 4; i++) {//i不能从0开始判断，因为0处是空白，然后就直接break了，丸辣！！！
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
							//连棋被打断则不再判断
						}
						else {//如果是白棋直接break
							break;
						}
					}

					if (personNum == 1) {//连2
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2) {
						if (emptyNum == 1) {//死三
						//空
						//  黑
						//    黑
						//      判断点
						//
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

					// 假设白棋在该位置落子
					emptyNum = 1;                        ////////////////////////////////////
					for (int i = 1; i <= 4; ++i) {        ////////////////////////////////////
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == -1) {
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol == 0)) {
							emptyNum++;
							break;
						}
						else {
							break;
						}
					}
					
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
							scoreMap[row][col] += 10000;
						}
					}
					else if (aiNum >= 4) {
						scoreMap[row][col] += 30000;
					}


				}
			}
		}
	}
}

ChessPos AI::think()
{	
	calculateScore();

	int maxScore = 0;

	vector<ChessPos> maxPoints;

	int size = chess->getGradeSize();
	//size = scoreMap.size();
	for(int row = 0; row < size; row++){
		for (int col = 0; col < size; col++) {
			if (chess->getChessData(row, col) == 0) {
				if (scoreMap[row][col] > maxScore) {
					maxScore = scoreMap[row][col];
					maxPoints.clear();
					maxPoints.push_back(ChessPos(row, col));
				}
				else if (scoreMap[row][col] == maxScore) {
					maxPoints.push_back(ChessPos(row,col));
				}
			}
		}
	}
	
	int index = rand() % maxPoints.size();//都一样，那就随机挑一个吧
	return maxPoints[index];
}
