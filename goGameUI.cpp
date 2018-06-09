//UI类的实现文件
#include "goGameUI.h"

#include <iostream>

using namespace std;


void goGameUI::freshScreen()
{
    if(isStarted == false)
    {
       while(1) 
        {
            cout << "请输入游戏类型 1:五子棋 2:围棋 3:黑白棋" << endl;
            int tmp;
            cin >> tmp;
            if(tmp == 1)
            {
                chessType =  1;
                return ;
            }
            if(tmp == 2)
            {
                chessType = 2;
                return ;
            }
            if(tmp == 3)
            {
                chessType = 3;
                return ;
            }
            else
            {
                cout << "输入指令错误， 请重新输入！" << endl;
                cin.clear();
				cin.ignore();
            }
        }           //只负责接收信息    不负责进行对游戏的真正初始化
    }

    if(isStarted == true)
    {
        
    }
}