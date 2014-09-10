#ifndef USER_INPUT_CONTROLLER_H
#define USER_INPUT_CONTROLLER_H

#include "userInputTypes.h"
#include "userInputReceiver.h"

class UserInputController {
  protected:
    InptuModes inputMode;
    UserInputReceiver *inputReceiver;

    uint8_t fixPosY;    // 0 means not set
    uint8_t fixPosX;    // 0 means not set
    uint8_t minPosX;
    uint8_t maxPosX;
    uint8_t minPosY;
    uint8_t maxPosY;

  public:
    virtual void processUserInputs();

  public:
    UserInputController(UserInputReceiver *inputReceiver) { 
      this->inputReceiver = inputReceiver; 
      fixPosX = 0;
      fixPosY = 0;
      minPosX = 0;
      maxPosX = 0;      
      minPosY = 0;
      maxPosX = 0;      
    }
    void setInputMode(InputModes inputMode) { this->inputMode = inputMode; }

    void setFixPositionY(uint8_t posY) {this->fixPosY = posY; }
    void setFixPositionX(uint8_t posX) { this->fixPosX = posX; }
    
    void setMinPositionX(uint8_t minPosX) { this->minPosX = minPosX; }
    void setMaxPositionX(uint8_t maxPosX) { this->maxPosX = maxPosX; }
    void setMinPositionY(uint8_t minPosY) { this->minPosY = minPosY; }
    void setMaxPositionY(uint8_t maxPosY) { this->maxPosY = maxPosY; }

};

#endif
