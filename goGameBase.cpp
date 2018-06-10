//游戏基类，虚类
#include "goGameBase.h"

goGameBase::goGameBase() : size(19), step(0) {

		srand((unsigned)time(nullptr));//生成随机数种子
		firstPlayer = rand() % 2;//将先手赋随机初值
		Matrix = new int*[size + 1];
		for (int i = 0; i <= size; i++)
		{
			Matrix[i] = new int[size + 1];
			for (int j = 0; j <= size; j++)
			{
				Matrix[i][j] = -1;
			}
		}
	};

goGameBase::goGameBase(int mySize) : size(mySize), step(0) {

	srand((unsigned)time(nullptr));//生成随机数种子
	firstPlayer = rand() % 2;//将先手赋随机初值
	Matrix = new int*[size + 1];
	for (int i = 0; i <= size; i++)
	{
		Matrix[i] = new int[size + 1];
		for (int j = 0; j <= size; j++)
		{
			Matrix[i][j] = -1;
		}
	}
}

void goGameBase::changeMatrix(int x, int y) {
	xPath.push_back(x);
	yPath.push_back(y);
	step++;
	updateMatrix(step);
};
bool goGameBase::regret() {
		if (step >= 2)
		{
			step -= 2;
			xPath.pop_back();
			xPath.pop_back();
			yPath.pop_back();
			yPath.pop_back();
			updateMatrixTotal();
			return true;
		}
		else
			return false;
}

void goGameBase::updateMatrixTotal(){
	for (int i = 1; i <= size; i++)
	for (int j = 1; j <= size; j++)
		Matrix[i][j] = -1;
for (int i = 1; i <= step; i++)
{
	updateMatrix(i);
}
};
