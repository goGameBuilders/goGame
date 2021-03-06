//主游戏文件
#include <iostream>
#include <stdlib.h>
#include "goGameBase.h"
#include "difGame.h"
//#include "difGame.h"

void PrintChessBoard(goGameBase & type);

int main() {
	goGameBase* FIR = new class FIR(20);
	PrintChessBoard(*FIR);
	while (!FIR->isEnd())
	{

		int x, y, choice;
		while (1) {
			cout << "1代表下子，2代表悔棋,请输入：" << endl;
			if (cin >> choice) {
				if (choice == 1)
				{
					while (1)
					{
						if (cin >> x >> y) {
							if (FIR->judge(x, y))
								break;
							else
							{
								cout << "这个地方已经有棋子或者越界了，请重新输入坐标：" << endl;
								continue;
							}
						}
						else//防止cin格式错误无限循环
						{
							cin.clear();
							cin.ignore();
						}
					}
					break;
				}
				else if (choice == 2)
				{
					if (FIR->regret())
					{
						PrintChessBoard(*FIR);
						cout << "regret successfully" << endl;
					}
					else
						cout << "you can't regret" << endl;
				}
			}
			else //防止cin格式错误无限循环
			{
				cin.clear();
				cin.ignore();
			}
		}
		FIR->changeMatrix(x, y);
		PrintChessBoard(*FIR);
	}
	if (FIR->isEnd() == 1)
	{
		cout << "The White win!";
	}
	else
		cout << "The Black win!";
	return 0;
}


void PrintChessBoard(goGameBase& type)    //打印棋盘，这个函数可以自己调整
{
	system("cls");                //系统调用，清空屏幕
								  //system("clear");			//mac or linux
	if (type.getWhoTurn()) {
		cout << "Black's Turn" << endl;
	}
	else
		cout << "White's Trun" << endl;
	for (int i = 0; i < type.getsize() + 1; ++i)
	{
		for (int j = 0; j < type.getsize() + 1; ++j)
		{
			if (i == 0)                               //打印行数字
			{
				if (j != 0)
					printf(" %2d ", j);
				else
					printf("    ");
			}
			else if (j == 0)                //打印列数字
				printf(" %2d ", i);
			else
			{
				if (i < type.getsize() + 1)
				{
					printf(" %c |", type.getMatrix(i, j));
				}
			}
		}
		cout << endl;
		cout << "    ";
		for (int m = 0; m < type.getsize(); m++)
		{
			printf("---|");
		}
		cout << endl;
	}
}
