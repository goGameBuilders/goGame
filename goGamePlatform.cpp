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
    else if(myType == 3){
        game = new Reversi(8);
        if(vsWho == 1){
            gameAI = new ReversiAI(game);
        }
    }
    else if(myType == 2){
        game = new Go(8);
        if(vsWho == 1){
            gameAI = new GoAI(game);
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
    else if(type == 3)
    {
        int size = game->getsize();
        delete game;
        game = new Reversi(size);
        if(vsWho==1){
            delete gameAI;
            gameAI = new ReversiAI(game);
        }
    }
    else if(type == 2)
    {
        int size = game->getsize();
        delete game;
        game = new Go(size);
        if(vsWho==1){
            delete gameAI;
            gameAI = new GoAI(game);
        }
    }
}
