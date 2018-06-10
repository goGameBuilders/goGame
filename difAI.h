//不同游戏类的AI头文件
#include "goGameAIBase.h"
#include "goGameBase.h"
#include "difGame.h"
class FIRAI: public goGameAIBase{
public:
    FIRAI(goGameBase* _game):goGameAIBase(_game){}
}
