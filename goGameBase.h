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
	goGameBase();
	goGameBase(int mySize);
	void changeMatrix(int x, int y);
	//每一次落子后改变矩阵的状态 （同时记录当前步骤）
	// 把update分开来，记录是通用的
	bool regret();
	// virtual bool judge(int x, int y)=0;
	// virtual bool isEnd()=0;
	// for test----------------------------
	void updateMatrixTotal() ;
	virtual void updateMatrix(int step0) {//最后应当是虚函数，输入值应当可变动，防止悔棋重新跑时step是常量导致的黑棋白旗全变成同一种颜色
	//	Matrix[xPath[step0-1]][yPath[step0-1]] = (step0 + firstPlayer) % 2;
	};
	inline const int getsize() { return size; };
	inline void touchMatrix(int x, int y, bool state) {
		Matrix[x][y] = state;
	}//提供子函数对矩阵的访问接口（可改变）
	inline const int getPath(int x, bool which)//提供路径的访问接口（只读）which 为1时返回x 
	{
		if (which)
			return xPath[x];
		return yPath[x];
	}
	inline const int getwhich(int x, int y) { return Matrix[x][y]; };//获得（x，y）处的棋子状态
	inline const bool getFirstPlayer() { return firstPlayer; }//
	inline const bool getWhoTurn() { return (firstPlayer + step) % 2; };
	inline char getMatrix(int x, int y)
	{
		if (Matrix[x][y] == -1)
			return ' ';
		else if (Matrix[x][y] == 0)
			return 'o';
		else if (Matrix[x][y] == 1)
			return 'x';
		return ' ';
	};//绘制矩阵时将数字转换为符号


	inline bool judge(int x, int y)
	{
		if (x > 0 && x <= size && y > 0 && y <= size && Matrix[x][y] == -1)
			return true;
		else
			return false;
	};
	virtual int isEnd()= 0;
	//-------------------------------------
	virtual ~goGameBase() {
		for (int i = 0; i <= size; i++) {
			delete[] Matrix[i];
		}
		delete[] Matrix;
	}
};