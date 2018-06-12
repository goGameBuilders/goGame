#include "goGamePlatform.h"
#include "difGame.h"
void goGamePlatform::gameSelect(int myType, int myVsWho){
    type = myType;
    vsWho=myVsWho;
    if(myType == 1){
        game = new FIR(10);
    }
}
