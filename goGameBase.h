//游戏基类头文件
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class goGameBase{
private:
int size;
int** Matrix;// 矩阵状态，支持未知大小
int step;// 下过的步数
bool firstPlayer;
vector <int> xPath;
vector <int> yPath;
public:
goGameBase(): size(19), step(0){
    
    srand((unsigned)time(nullptr));//生成随机数种子
    firstPlayer = rand() % 2;//将先手赋随机初值
    Matrix = new int*[size];
    for(int i = 0; i < size;i ++)
    {
        Matrix[i]= new int[size];//如果不行把初始化分开写  （好像确实不行。。。)
        for(int j = 0;j < size;j++)
        {
            Matrix[i][j] = -1;
        }
    }
};
goGameBase(int mySize): size(mySize), step(0){
    
    srand((unsigned)time(nullptr));//生成随机数种子
    firstPlayer = rand() % 2;//将先手赋随机初值
    Matrix = new int*[size];
    for(int i = 0; i < size;i ++)
    {
        Matrix[i]= new int[size];//如果不行把初始化分开写    (好像确实不行。。。)
        for(int j = 0;j < size;j++)
        {
            Matrix[i][j] = -1;
        }
    }
}
// virtual void changeMarix(int x, int y)=0;
// virtual bool judge(int x, int y)=0;
// virtual bool isEnd()=0;
// for test----------------------------
int getsize(){return size;};
char getMatrix(int x, int y)
{
    if(Matrix[x][y] == -1)
        return ' ';
    else if(Matrix[x][y] == 0)
        return 'o';
    else if(Matrix[x][y] == 1)
        return 'x';
};//绘制矩阵时将数字转换为符号
void changeMatrix(int x, int y)
{
    Matrix[x][y] = (step + firstPlayer) % 2 + 1;
    xPath.push_back(x);
    yPath.push_back(y);
}; //每一次落子后改变矩阵的状态 （同时记录当前步骤？？）
void stepPlus(){ step++; }
bool judge(int x, int y);
bool isEnd();
//-------------------------------------
virtual ~goGameBase(){
    delete[] Matrix;//防止内存泄漏
}
};