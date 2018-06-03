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
//其他自定义棋类游戏的实现