#include "goGamePlatform.h"

void goGamePlatform::gameSelect(int myType, int myVsWho){
    type = myType;
    vsWho = myVsWho;
    if(myType == 1){
        game = new FIR(10);
        if(vsWho == 1){
            gameAI = new FIRAI(game);
        }
    }
}

void goGamePlatform::restartGame()
{
    if(type == 1)
    {
        int size = game->getsize();
        delete game;
        game = new FIR(size);
        if(vsWho==1){
            delete gameAI;
            gameAI = new FIRAI(game);
        }
    }
}
