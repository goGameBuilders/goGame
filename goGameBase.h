//游戏基类头文件
#include <iostream>
#include <ctime>
#include <stdlib>
class goGameBase{
private:
int size;
int** Marix;// 矩阵状态，支持未知大小
int step;// 下过的步数
bool firstPlayer;
vector <int> x;
vector <int> y;
public：
goGameBase(): size(19), step(0),firstPlayer(srand((unsigned)time(nullptr)%2)) {
    Marix = new int*[size];
    for(int i = 0; i < size;i ++)
    {
        Marix[i]= new int[size](0);//如果不行把初始化分开写
    }
}；
goGameBase(int mySize): size(mySize), step(0),firstPlayer(srand((unsigned)time(nullptr)%2)) {
    Marix = new int*[size];
    for(int i = 0; i < size;i ++)
    {
        Marix[i]= new int[size](0);//如果不行把初始化分开写
    }
// virtual void changeMarix(int x, int y)=0;
// virtual bool judge(int x, int y)=0;
// virtual bool isEnd()=0;
// for test----------------------------
int getsize(){return size;}; 
void changeMarix(int x, int y);
bool judge(int x, int y);
bool isEnd();
//-------------------------------------
virtual ~goGameBase(){
    delete[] Marix;//防止内存泄漏
}
};