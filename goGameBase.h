#pragma once
//��Ϸ����ͷ�ļ�
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class goGameBase {
private:
	int size;
	int** Matrix;// ����״̬��֧��δ֪��С
	int step;// �¹��Ĳ���
	bool firstPlayer;
	vector <int> xPath;
	vector <int> yPath;
public:
	goGameBase();
	goGameBase(int mySize);
	void changeMatrix(int x, int y);
	//ÿһ�����Ӻ�ı�����״̬ ��ͬʱ��¼��ǰ���裩
	// ��update�ֿ�������¼��ͨ�õ�
	bool regret();
	// virtual bool judge(int x, int y)=0;
	// virtual bool isEnd()=0;
	// for test----------------------------
	void updateMatrixTotal() ;
	virtual void updateMatrix(int step0) {//���Ӧ�����麯��������ֵӦ���ɱ䶯����ֹ����������ʱstep�ǳ������µĺ������ȫ���ͬһ����ɫ
	//	Matrix[xPath[step0-1]][yPath[step0-1]] = (step0 + firstPlayer) % 2;
	};
	inline const int getsize() { return size; };
	inline void touchMatrix(int x, int y, bool state) {
		Matrix[x][y] = state;
	}//�ṩ�Ӻ����Ծ���ķ��ʽӿڣ��ɸı䣩
	inline const int getPath(int x, bool which)//�ṩ·���ķ��ʽӿڣ�ֻ����which Ϊ1ʱ����x 
	{
		if (which)
			return xPath[x];
		return yPath[x];
	}
	inline const int getwhich(int x, int y) { return Matrix[x][y]; };//��ã�x��y����������״̬
	inline const bool getFirstPlayer() { return firstPlayer; }//
	inline const bool getWhoTurn() { return (firstPlayer + step) % 2; };
	inline char getMatrix(int x, int y)
	{
		if (Matrix[x][y] == -1)
			return ' ';
		else if (Matrix[x][y] == 0)
			return 'o';
		else if (Matrix[x][y] == 1)
			return 'x';
		return ' ';
	};//���ƾ���ʱ������ת��Ϊ����


	inline bool judge(int x, int y)
	{
		if (x > 0 && x <= size && y > 0 && y <= size && Matrix[x][y] == -1)
			return true;
		else
			return false;
	};
	virtual int isEnd()= 0;
	//-------------------------------------
	virtual ~goGameBase() {
		for (int i = 0; i <= size; i++) {
			delete[] Matrix[i];
		}
		delete[] Matrix;
	}
};