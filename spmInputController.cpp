#include "spmInputController.h"

SpmInputController::SpmInputController(int _pin, UserInputReceiver *inputReceiver) : UserInputController(inputReceiver) {
  pin = _pin;
  lastSensorValue = 0;
  
  pinMode(pin, INPUT);				// set sensor pin as INPUT  
}

SpmInputController::~SpmInputController() {
  
}

void SpmInputController::processUserInputs() {
  const int sensorValue = analogRead(pin);
  if ( abs(lastSensorValue -sensorValue ) < SENSOR_PRECISION ) return;
  
  const int posX = floor(minPosX+min(maxPosX,(minPosX/MAX_SENSOR_VALUE)*sensorValue));
 
  inputReceiver->moveCarretTo(this, posX,fixPosY);    
}
