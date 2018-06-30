#pragma once
//游戏基类头文件
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>

#include <QtCore>
#include <QWidget>
#include <QtWidgets>
#include <QJsonDocument>

using namespace std;

class goGameBase {
private:
	int size;
	int** Matrix;// 矩阵状态，支持未知大小
	int step;// 下过的步数
    bool firstPlayer;//先手是哪方,由于最初对棋类规则不了解设定为随机先手，现默认黑棋先手
	vector <int> xPath;
	vector <int> yPath;
    bool isYourTurn;                //联机对战时能否下子的判断条件
protected:
    inline void touchMatrix(int x, int y, bool state) {
        Matrix[x][y] = state;
    }//提供子函数对矩阵的访问接口(仅用于改变)
public:
    enum SaveFormat{
        Json, Binary
    };                  //保存游戏的所有格式

    goGameBase();
	goGameBase(int mySize);
    void changeMatrix(int x, int y);

    bool regret();          //悔棋函数

    bool saveGame(goGameBase::SaveFormat saveFormat, QString path)  const;
    bool loadGame(goGameBase::SaveFormat saveFormat, QString path);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

	void updateMatrixTotal() ;
    virtual void updateMatrix(int) {//最后应当是虚函数，输入值应当可变动，防止悔棋重新跑时step是常量导致的黑棋白旗全变成同一种颜色
	//	Matrix[xPath[step0-1]][yPath[step0-1]] = (step0 + firstPlayer) % 2;
    }
    inline  int getsize() { return size; }
    inline  int getstep() { return step; }
    inline  int getPath(int x, bool which)//提供路径的访问接口（只读）which 为1时返回x
	{
		if (which)
			return xPath[x];
		return yPath[x];
	}
    inline  int getwhich(int x, int y) { return Matrix[x][y]; } //获得（x，y）处的棋子状态
    inline  bool getFirstPlayer() {
        return firstPlayer;
    }//
    bool getIsYourTurn(){return isYourTurn;}
    void changeYourTurn(){
        if(isYourTurn)
            isYourTurn = false;
        else
            isYourTurn = true;
    }
    void initYourTurn(bool tmp)
    {
        isYourTurn = tmp;
    }
    inline int getBlack(){
        int black = 0;
        for(int i = 1; i <=size; i ++)
            for(int j = 1; j <=size; j ++)
                if(Matrix[i][j]==0)
                    black++;
        return black;
    }
    inline int getWhite(){
        int white = 0;
        for(int i = 1; i <=size; i ++)
            for(int j = 1; j <=size; j ++)
                if(Matrix[i][j]==1)
                    white++;
        return white;
    }
    inline  bool getWhoTurn() { return (firstPlayer + step) % 2; }
    inline int getMatrix(int x, int y)
	{
        return Matrix[x][y];
    } //获得坐标x，y处的状态。

    inline const std::string getinfo(){
        std::string info;
        info += "Total steps: \n";
        info += to_string(getstep());
        info += "\n";
        if(!isEnd()){
            if(getWhoTurn()==0)
               info+="The white's turn\n";
            else
                info+="The black's turn\n";
        }
        else if(isEnd()==-1)
            info+="The black win!\n";
        else if(isEnd()== 1)
            info+="The white win! \n";
        else if(isEnd()== 2)
            info += "Tie!\n";
        return info;
    }
    virtual bool judge(int x, int y, bool swit = false)
	{
		if (x > 0 && x <= size && y > 0 && y <= size && Matrix[x][y] == -1)
			return true;
		else
			return false;
    }//默认凡是有空的地方就能下，对于黑白棋和别的棋类需要重载
	virtual int isEnd()= 0;
    virtual void InitMatrix(){}
	virtual ~goGameBase() {
		for (int i = 0; i <= size; i++) {
			delete[] Matrix[i];
		}
		delete[] Matrix;
	}
};
