#pragma once

#include "goGameBase.h"
#include <iostream>

//继承后仅需实现updateMatrix的相关函数以及胜利判定的相关函数即可

class FIR  :public goGameBase {
public:
	FIR();
	FIR(int size);
	virtual void updateMatrix(int step0);
	virtual int isEnd();
    ~FIR() {}
};
//其他自定义棋类游戏
class Reversi :public goGameBase {
private:
    int skipnumber=0;
public:
      Reversi();
      Reversi(int size);
      virtual void updateMatrix(int step0);
      virtual int isEnd();
      virtual bool judge(int x, int y, bool swit );
      virtual void InitMatrix();
      ~Reversi(){}
};
