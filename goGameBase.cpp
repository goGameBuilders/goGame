//游戏基类，虚类
#include "goGameBase.h"

goGameBase::goGameBase() : size(19), step(0) {

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

goGameBase::goGameBase(int mySize) : size(mySize), step(0) {

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

void goGameBase::changeMatrix(int x, int y) {
	xPath.push_back(x);
	yPath.push_back(y);
	step++;
	updateMatrix(step);
}

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


void goGameBase::read(const QJsonObject &json)
{
    xPath.clear();
    yPath.clear();
    QJsonArray load_path = json["paths"].toArray();
    QJsonObject tmpData0 = load_path[0].toObject();
    firstPlayer = true;
    step = 0;
    InitMatrix();
    for(int i = 1;i < load_path.size(); i++)
    {
        QJsonObject tmpData = load_path[i].toObject();
        changeMatrix(tmpData["x"].toInt(),tmpData["y"].toInt());
    }
}      //从json中读取数据


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




