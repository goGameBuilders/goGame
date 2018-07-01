//游戏基类，虚类
#include "goGameBase.h"

goGameBase::goGameBase() : gg(false), size(19), step(0) {

        firstPlayer = 1;
		Matrix = new int*[size + 1];
		for (int i = 0; i <= size; i++)
		{
			Matrix[i] = new int[size + 1];
			for (int j = 0; j <= size; j++)
			{
				Matrix[i][j] = -1;
			}
		}
    }

goGameBase::goGameBase(int mySize) :gg(false), size(mySize), step(0) {
//默认先手为黑，由于刚开始对规则不是很了解才提供的变量
    firstPlayer = 1;
	Matrix = new int*[size + 1];
	for (int i = 0; i <= size; i++)
	{
		Matrix[i] = new int[size + 1];
		for (int j = 0; j <= size; j++)
		{
			Matrix[i][j] = -1;
		}
    }
}
//对矩阵的改变，是打包的一系列功能，
//和每个类的具体实现解耦和，只需要提供依次落子的位置即可（（0，0）代表弃子或者黑白棋无子可下时的情况））
void goGameBase::changeMatrix(int x, int y) {
    static int sum = 0;
	xPath.push_back(x);
	yPath.push_back(y);
	step++;
	updateMatrix(step);
    int sum1 = 0,sum2=0;
    for(int i = 1; i <=size; i ++)
        for(int j = 1; j<=size;j++)
           {
            if(judge(i, j))
                ++sum1;
            if(Matrix[i][j]==-1)
                ++sum2;
            }
    if(sum1==0&&sum2>0&&sum==0){
        sum++;
        changeMatrix(0,0);
    }
    sum = 0;
}
//悔棋功能的实现
bool goGameBase::regret() {
		if (step >= 2)
		{
			step -= 2;
			xPath.pop_back();
			xPath.pop_back();
			yPath.pop_back();
			yPath.pop_back();
			updateMatrixTotal();
			return true;
		}
		else
			return false;
}
//把矩阵初始化，之后按照规则一步一步落子，也是悔棋的实现方式
void goGameBase::updateMatrixTotal(){
	for (int i = 1; i <= size; i++)
	for (int j = 1; j <= size; j++)
		Matrix[i][j] = -1;
    InitMatrix();
    for (int i = 1; i <= step; i++)
    {
        updateMatrix(i);
    }
}
//存档功能，所存数据有首落子者（由于之前对规则不是很了解所致）总步数，以及每步的位置
void goGameBase::write(QJsonObject &json) const
{
    QJsonArray save_Path;
    QJsonObject tmpData0;
    tmpData0.insert("firstPlayer", firstPlayer);
    tmpData0.insert("totalStep", step);
    save_Path.append(tmpData0);
    for(int i = 0; i < xPath.size(); i++)
    {
        QJsonObject tmpData;
        tmpData.insert("x", xPath[i]);
        tmpData.insert("y", yPath[i]);
        save_Path.append(tmpData);
    }
    json["paths"] = save_Path;
}       //向json中写入数据

//读档功能
void goGameBase::read(const QJsonObject &json)
{
    xPath.clear();
    yPath.clear();
    QJsonArray load_path = json["paths"].toArray();
    QJsonObject tmpData0 = load_path[0].toObject();
    firstPlayer = true;
    step = tmpData0["totalStep"].toInt();
    for(int i = 1;i < load_path.size(); i++)
    {
        QJsonObject tmpData = load_path[i].toObject();
        //changeMatrix(tmpData["x"].toInt(),tmpData["y"].toInt());
        xPath.push_back(tmpData["x"].toInt());
        yPath.push_back(tmpData["y"].toInt());
    }
}      //从json中读取数据

//保存游戏
bool goGameBase::saveGame(goGameBase::SaveFormat saveFormat, QString path) const
{
    QString fileName;
    if(saveFormat == Json)
        fileName = "save.json";
    else
        fileName = "save.dat";


    QFile saveFile(path + "/" + fileName);

          if (!saveFile.open(QIODevice::WriteOnly)) {
              qWarning("Couldn't open save file.");
              return false;
          }

          QJsonObject gameObject;
          write(gameObject);
          QJsonDocument saveDoc(gameObject);
          saveFile.write(saveFormat == Json
              ? saveDoc.toJson()
              : saveDoc.toBinaryData());
          saveFile.flush();
          saveFile.close();
          return true;


}       //存储游戏存档文件至游戏目录下
//导入游戏
bool goGameBase::loadGame(goGameBase::SaveFormat saveFormat, QString Path)
{
    QString fileName;
    if(saveFormat == Json)
        fileName = "save.json";
    else
        fileName = "save.dat";

    QFile loadFile(Path);

    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file");
        return false;
    }

     QByteArray saveData = loadFile.readAll();

     QJsonDocument loadDoc(saveFormat == Json
               ? QJsonDocument::fromJson(saveData)
               : QJsonDocument::fromBinaryData(saveData));

    read(loadDoc.object());
    loadFile.close();
    return true;
}       //读取已存在的存档文件




