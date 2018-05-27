//主游戏文件
#include <iostream>
#include <stdlib.h>
#include "goGameBase.h"
#include "difGame.h"

void PrintChessBoard(goGameBase type);

int main(){
  goGameBase FIR;
    PrintChessBoard(FIR);
  while(1)
  {
      int x, y;
      cin >> x >> y;
      FIR.changeMatrix(x, y);
      PrintChessBoard(FIR);
      FIR.stepPlus();
  }
}


void PrintChessBoard(goGameBase type)    //打印棋盘，这个函数可以自己调整
    {
        system("clear");                //系统调用，清空屏幕
        //system("cls")     在mac上这句报错。。应该是win上用的？
        for (int i = 0; i < type.getsize()+1; ++i)
        {
            for (int j = 0; j < type.getsize()+1; ++j)
            {
                if (i == 0)                               //打印列数字
                {
                    if (j!=0)
                        printf("%d  ", j);
                    else
                        printf("   ");
                }
                else if (j == 0)                //打印行数字
                    printf("%2d ", i);
                else
                {
                    if (i < type.getsize()+1)
                    {
                        printf("%c |",type.getMatrix(i, j));
                    }
                }
            }
            cout << endl;
            cout << "   ";
            for (int m = 0; m < type.getsize(); m++)
            {
                printf("--|");
            }
            cout << endl;
        }
    }
