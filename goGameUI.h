#include <string>

using namespace std;

//UI类的头文件
class goGameUI{
private:
    bool isStarted;
    int chessType;  //1-五子棋   2-围棋   3-黑白棋
                    //只负责信息接收

public:
    void freshScreen();

};