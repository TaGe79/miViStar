#ifndef SPM_INPUT_CONTROLLER_H
#define SPM_INPUT_CONTROLLER_H

#include "MicroView.h"

#include "userInputController.h"
#include "userInputReceiver.h"

#define SAMPLE_CNT         10
#define MAX_SENSOR_VALUE   1000.0
#define SENSOR_PRECISION   4

class SpmInputController : public UserInputController {
  private:
    uint8_t inputValues[SAMPLE_CNT];
    int pin;
    int lastSensorValue;
    
  public:
    void processUserInputs();  
    
  public:
    SpmInputController(int _pin, UserInputReceiver *inputReceiver);
    ~SpmInputController();
};
#endif
