#pragma once
//游戏基类头文件
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class goGameBase {
private:
	int size;
	int** Matrix;// 矩阵状态，支持未知大小
	int step;// 下过的步数
	bool firstPlayer;
	vector <int> xPath;
	vector <int> yPath;
public:
	goGameBase() : size(19), step(0) {

		srand((unsigned)time(nullptr));//生成随机数种子
		firstPlayer = rand() % 2;//将先手赋随机初值
		Matrix = new int*[size + 1];
		for (int i = 0; i <= size; i++)
		{
			Matrix[i] = new int[size + 1];//如果不行把初始化分开写  （好像确实不行。。。)
			for (int j = 0; j <= size; j++)
			{
				Matrix[i][j] = -1;
			}
		}
	};
	goGameBase(int mySize) : size(mySize), step(0) {

		srand((unsigned)time(nullptr));//生成随机数种子
		firstPlayer = rand() % 2;//将先手赋随机初值
		Matrix = new int*[size + 1];
		for (int i = 0; i <= size; i++)
		{
			Matrix[i] = new int[size + 1];//如果不行把初始化分开写    (好像确实不行。。。)
			for (int j = 0; j <= size; j++)
			{
				Matrix[i][j] = -1;
			}
		}
	}
	void changeMatrix(int x, int y)
	{
		xPath.push_back(x);
		yPath.push_back(y);
		step++;
		updateMarix(x, y);
	}; //每一次落子后改变矩阵的状态 （同时记录当前步骤？？）
	  // 把update分开来，记录是通用的
	bool regret() {
		if (step >= 2)
		{
			step -= 2;
			xPath.pop_back();
			xPath.pop_back();
			yPath.pop_back();
			yPath.pop_back();
			updateMarixTotal();
			return true;
		}
		else
			return false;
	}
	// virtual bool judge(int x, int y)=0;
	// virtual bool isEnd()=0;
	// for test----------------------------
	void updateMarixTotal(){ 
		for (int i = 1; i <= size; i++)
			for (int j = 1; j <= size; j++)
				Matrix[i][j] = -1;
		for (int i = 0; i < step; i++)
		{
			updateMarix(xPath[i], yPath[i]);
		}
	};
	void updateMarix(int x, int y) {//最后应当是虚函数
		Matrix[x][y] = (step + firstPlayer) % 2;
	};
	const int getsize() { return size; };
	const bool getWhoTurn() { return (firstPlayer + step) % 2; };
	char getMatrix(int x, int y)
	{
		if (Matrix[x][y] == -1)
			return ' ';
		else if (Matrix[x][y] == 0)
			return 'o';
		else if (Matrix[x][y] == 1)
			return 'x';
	};//绘制矩阵时将数字转换为符号


	bool judge(int x, int y)
	{
		if (x > 0 && x <= size && y > 0 && y <= size && Matrix[x][y] == -1)
		return true;
		else
			return false;
	};
	bool isEnd();
	//-------------------------------------
	virtual ~goGameBase() {
		for (int i = 0; i <= size; i++) {
			delete[] Matrix[i];
		}
		delete[] Matrix;
	}
};