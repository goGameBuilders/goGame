#include "goGamePlatform.h"
#include "difGame.h"
void goGamePlatform::gameSelect(int myType, int myVsWho){
    type = myType;
    vsWho = myVsWho;
    if(myType == 1){
        game = new FIR(10);
    }
}

void goGamePlatform::restartGame()
{
    if(type == 1)
    {
        int size = game->getsize();
        delete game;
        game = new FIR(size);
    }
}
