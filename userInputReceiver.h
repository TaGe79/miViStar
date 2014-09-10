#ifndef USER_INPUT_PROCESSOR_H
#define USER_INPUT_PROCESSOR_H

#include "userInputTypes.h"

class UserInputReceiver {
  public:
    virtual void userInputDetected(void* sender, Inputs userInput);
    virtual void moveCarretTo(void* sender, int posX, int posY);
};

#endif
