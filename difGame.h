#pragma once

#include "goGameBase.h"
#include <iostream>

//�̳к����ʵ��updateMatrix����غ����Լ�ʤ���ж�����غ�������

class FIR  :public goGameBase {
public:
	FIR();
	FIR(int size);
	virtual void updateMatrix(int step0);
	virtual int isEnd();
	~FIR() {};
};
//�����Զ���������Ϸ