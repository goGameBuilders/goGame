#include "goGameBase.h"
#include "difGame.h"

// FIR函数实现
FIR::FIR() :goGameBase(){
}

FIR::FIR(int asize) :goGameBase(asize){
}

void FIR::updateMatrix(int step0) {
	touchMatrix(getPath(step0 - 1, 1), getPath(step0 - 1, 0), (getFirstPlayer() + step0) % 2);
}
int FIR::isEnd() {
    if(getstep() == getsize()*getsize())
        return 2;
    // 平局
	for (int i = 1; i <= getsize(); i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i, j) == 1 && getwhich(i, j + 1) == 1 && getwhich(i, j + 2) == 1 && getwhich(i, j + 3) == 1 && getwhich(i, j + 4) == 1)
				return 1;
	for (int i = 1; i <= getsize(); i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(j, i) == 1 && getwhich(j + 1, i) == 1 && getwhich(j + 2, i) == 1 && getwhich(j + 3, i) == 1 && getwhich(j + 4, i) == 1)
				return 1;
	for (int i = 1; i <= getsize() - 4; i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i, j) == 1 && getwhich(i + 1, j + 1) == 1 && getwhich(i + 2, j + 2) == 1 && getwhich(i + 3, j + 3) == 1 && getwhich(i + 4, j + 4) == 1)
				return 1;
	for (int i = 1; i <= getsize() - 4; i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i+4, j) == 1 && getwhich(i + 3, j + 1) == 1 && getwhich(i + 2, j + 2) == 1 && getwhich(i + 1, j + 3) == 1 && getwhich(i, j + 4) == 1)
				return 1;
	//白棋胜利
	for (int i = 1; i <= getsize(); i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i, j) == 0 && getwhich(i, j + 1) == 0 && getwhich(i, j + 2) == 0 && getwhich(i, j + 3) == 0 && getwhich(i, j + 4) == 0)
				return -1;
	for (int i = 1; i <= getsize(); i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(j, i) == 0 && getwhich(j + 1, i) == 0 && getwhich(j + 2, i) == 0 && getwhich(j + 3, i) == 0 && getwhich(j + 4, i) == 0)
				return -1;
	for (int i = 1; i <= getsize() - 4; i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i, j) == 0 && getwhich(i + 1, j + 1) == 0 && getwhich(i + 2, j + 2) == 0 && getwhich(i + 3, j + 3) == 0 && getwhich(i + 4, j + 4) == 0)
				return -1;
	for (int i = 1; i <= getsize() - 4; i++)
		for (int j = 1; j <= getsize() - 4; j++)
			if (getwhich(i + 4, j) == 0 && getwhich(i + 3, j + 1) == 0 && getwhich(i + 2, j + 2) == 0 && getwhich(i + 1, j + 3) == 0 && getwhich(i, j + 4) == 0)
				return -1;
	//黑棋胜利
	return 0;
}
// 黑白棋的函数实现
Reversi::Reversi():goGameBase(){
    InitMatrix();
}
Reversi::Reversi(int asize):goGameBase(asize){
    InitMatrix();
}
void Reversi::InitMatrix(){
    touchMatrix(4,4,1);
    touchMatrix(5,5,1);
    touchMatrix(4,5,0);
    touchMatrix(5,4,0);
}
void Reversi::updateMatrix(int step0){
    int x = getPath(step0 - 1, 1);
    int y = getPath(step0 - 1, 0);
    bool Me = (step0+1) % 2; //还需确定敌我双方问题
    int sum = 0;
    if(x!=0&&y!=0){
        touchMatrix(x, y, Me);
        for(int i = x+1; i <=getsize(); i++)
        {
            if(getMatrix(i, y)==(Me+1)%2)
                ++sum;
            else if(getMatrix(i, y)==Me&&sum == i-x-1&&sum > 0)
            {
                for(int j =x+1; j <i; j ++)
                    touchMatrix(j, y, Me);
                    sum=0;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = x-1; i>0; i--)
        {
            if(getMatrix(i, y)==(Me+1)%2)
                ++sum;
            else if(getMatrix(i, y)==Me&&sum == x-i-1&&sum > 0)
            {
                for(int j =x-1; j >i; j --)
                    touchMatrix(j, y, Me);
                sum=0;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = y+1; i <=getsize(); i++)
        {
            if(getMatrix(x, i)==(Me+1)%2)
                ++sum;
            else if(getMatrix(x, i)==Me&&sum == i-y-1&&sum > 0)
            {
                for(int j =y+1; j <i; j ++)
                    touchMatrix(x, j, Me);
                sum=0;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = y-1; i>0; i--)
        {
            if(getMatrix(x, i)==(Me+1)%2)
                ++sum;
            else if(getMatrix(x, i)==Me&&sum == y-i-1&&sum > 0)
            {
                for(int j =y-1; j >i; j --)
                    touchMatrix(x, j, Me);
                sum=0;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x+i)<=getsize()&&(y+i)<=getsize();i++)
        {
            if(getMatrix(x + i, y + i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x + i, y + i)== Me && sum == i-1 && sum> 0)
            {
                for(int j = 1; j < i; j ++)
                    touchMatrix(x+j, y+j, Me);
                sum=0;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x-i)>0&&(y-i)>0;i++)
        {
            if(getMatrix(x - i, y - i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x - i, y - i)== Me && sum == i-1 && sum> 0)
            {
                for(int j = 1; j < i; j ++)
                    touchMatrix(x-j, y-j, Me);
                sum=0;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x+i)<=getsize()&&(y-i)>0;i++)
        {
            if(getMatrix(x + i, y - i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x + i, y - i)== Me && sum == i-1 && sum> 0)
            {
                for(int j = 1; j < i; j ++)
                    touchMatrix(x+j, y-j, Me);
                sum=0;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x-i) > 0 && (y+i)<=getsize();i++)
        {
            if(getMatrix(x - i, y + i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x - i, y + i)== Me && sum == i-1 && sum> 0)
            {
                for(int j = 1; j < i; j ++)
                    touchMatrix(x-j, y+j, Me);
                sum=0;
                break;
            }
            else
            {   sum=0;
                break;
            }
        }
    }
}
bool Reversi::judge(int x, int y,bool swit = false){
    bool Me = (getWhoTurn()+1+swit)%2;
    if (x > 0 && x <= getsize() && y > 0 && y <= getsize() && getMatrix(x, y) == -1)
    {
        int sum=0;
        for(int i = x+1; i <=getsize(); i++)
        {

            if(getMatrix(i, y)==(Me+1)%2)
                ++sum;
            else if(getMatrix(i, y)==Me&&sum == i-x-1&&sum > 0)
                return true;
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = x-1; i>0; i--)
        {

            if(getMatrix(i, y)==(Me+1)%2)
                ++sum;
            else if(getMatrix(i, y)==Me&&sum == x-i-1&&sum > 0)
                return true;
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = y+1; i <=getsize(); i++)
        {

            if(getMatrix(x, i)==(Me+1)%2)
                ++sum;
            else if(getMatrix(x, i)==Me&&sum == i-y-1&&sum > 0)
                return true;
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = y-1; i>0; i--)
        {
            if(getMatrix(x, i)==(Me+1)%2)
                ++sum;
            else if(getMatrix(x, i)==Me&&sum == y-i-1&&sum > 0)
                return true;
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x+i)<=getsize()&&(y+i)<=getsize();i++)
        {
            if(getMatrix(x + i, y + i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x + i, y + i)== Me && sum == i-1 && sum> 0)
                return true;
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x-i)>0&&(y-i)>0;i++)
        {
            if(getMatrix(x - i, y - i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x - i, y - i)== Me && sum == i-1 && sum> 0)
                return true;
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x+i)<=getsize()&&(y-i)>0;i++)
        {
            if(getMatrix(x + i, y - i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x + i, y - i)== Me && sum == i-1 && sum> 0)
                return true;
            else
            {   sum=0;
                break;
            }
        }
         sum=0;
        for(int i = 1;(x-i) > 0 && (y+i)<=getsize();i++)
        {
            if(getMatrix(x - i, y + i)== (Me+1)%2)
                ++sum;
            else if(getMatrix(x - i, y + i)== Me && sum == i-1 && sum> 0)
                return true;
            else
            {   sum=0;
                break;
            }
        }
    }
    return false;
}
int Reversi::isEnd(){
//    if(getstep()==getsize()*getsize()-4)
//    {   if(getWhite()>getBlack())
//            return 1;
//        else if(getWhite()<getBlack())
//            return -1;
//        else
//            return 2;
//    }
    int sum = 0;
    for(int i = 1; i <=getsize(); i ++)
        for(int j = 1; j<=getsize();j++)
           {
            if(judge(i, j))
                ++sum;
            else if(judge(i, j, true))
                ++sum;
            }
    if(sum==0)
    {
        if(getWhite()>getBlack())
                    return 1;
                else if(getWhite()<getBlack())
                    return -1;
                else
                    return 2;
    }
    return 0;
}
// 围棋的函数实现

int Max(int x, int y, int z, int w){
    if(x<y)
        x = y;
    if(x<z)
        x = z;
    if(x<w)
        x = w;
    return x;
}
Go::Go():goGameBase(){
    InitQiMatrix();
    InitFlagMatrix();
}
Go::Go(int asize):goGameBase(asize){
    InitQiMatrix();
    InitFlagMatrix();
}
void Go::updateMatrix(int step0){
    touchMatrix(getPath(step0 - 1, 1), getPath(step0 - 1, 0), (getFirstPlayer() + step0) % 2);
    calculateQi(1);
    bool theOpp = step0 % 2; //还需确定敌我双方问题
    for(int i = 1; i <= getsize();++i)
        for(int j = 1; j <= getsize(); ++j)
            if(getMatrix(i, j)==theOpp&&QiMatrix[i][j]==0)
                touchMatrix(i, j, -1);
}
int Go::calculateSingleQiXY(int x, int y, bool swit = true){
    bool theColor = (getWhoTurn()+1+swit)%2;
    if(getMatrix(x, y)==theColor)
    {
        if(x+1<=getsize()&&getMatrix(x+1, y)==-1)
            return 1;
        if(x-1>0&&getMatrix(x-1, y)==-1)
            return 1;
        if(y+1<=getsize()&&getMatrix(x, y+1)==-1)
            return 1;
        if(y-1>0&&getMatrix(x, y-1)==-1)
            return 1;
    }
    return 0;
}
int Go::calculateQiXY(int x, int y, bool swit= true){
    bool theColor = (getWhoTurn()+1+swit)%2;
    if(x<=0||y<=0||x>getsize()||y>getsize())
        return 0;
    FlagMatrix[x][y] = 1;
    if(getMatrix(x, y)==theColor){
       if(QiMatrix[x][y]==1)
           return 1;
       else
           return Max(calculateQiXY(x+1, y), calculateQiXY(x-1, y),calculateQiXY(x, y+1),calculateQiXY(x, y-1));
    }
    return 0;
}
void Go::calculateQi(bool swit = true){
        bool theColor = (getWhoTurn()+1+swit)%2;
        for(int i = 1; i <=getsize(); ++i)
            for(int j = 1; j <=getsize(); ++j)
                QiMatrix[i][j]=calculateSingleQiXY(i, j);
        for(int i = 1; i <=getsize(); ++i)
            for(int j = 1; j <=getsize(); ++j)
            {
                QiMatrix[i][j]=calculateQiXY(i, j);
                InitFlagMatrix();
            }
}
void Go::InitQiMatrix(){
    for(int i = 0; i < 20; ++i)
        for(int j = 0; j < 20;++j)
            QiMatrix[i][j]=0;
}
void Go::InitFlagMatrix(){
    for(int i = 0; i < 20; ++i)
        for(int j = 0; j < 20;++j)
            FlagMatrix[i][j]=0;
}
int Go::isEnd(){

}
//其他自定义棋类游戏的实现
