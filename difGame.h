#pragma once

#include "goGameBase.h"
#include <iostream>

//继承后仅需实现updateMatrix的相关函数以及胜利判定的相关函数即可
//五子棋的游戏实现
class FIR  :public goGameBase {
public:
	FIR();
	FIR(int size);
	virtual void updateMatrix(int step0);
	virtual int isEnd();
    ~FIR() {}
};
//黑白棋的游戏实现
class Reversi :public goGameBase {
public:
      Reversi();
      Reversi(int size);
      virtual void updateMatrix(int step0);
      virtual int isEnd();
      virtual bool judge(int x, int y, bool swit );
      virtual void InitMatrix();
      ~Reversi(){}
};
//围棋的游戏实现
class Go :public goGameBase {
private :
    int _size = 8;
    int QiMatrix[20][20];
    int FlagMatrix[20][20];
public:
    Go();
    Go(int size);
    int getsize(){return _size;}
    virtual void updateMatrix(int step0);
    virtual int isEnd();
    void InitQiMatrix();
    void InitFlagMatrix();
    int calculateSingleQiXY(int x, int y, int step0, bool swit);
    int calculateQiXY(int x, int y,int step0, bool swit);
    void calculateQi(int step0, bool swit);
};
//其他自定义棋类游戏