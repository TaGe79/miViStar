#include <MicroView.h>				// include MicroView library
#include <stdlib.h>
#include <stdio.h>

#include "gameController.h"
#include "componist.h"
#include "ledController.h"
#include "spmInputController.h"

uint8_t controllerPos = 0;
const int sensorPin         = A0;

const int buzzerPin         = A1;

const int ledPins[]         = {A2,A3,A4};


GameController       *gameController;
SpmInputController   *spmInputCtrl;

void setup() {
  gameController = (new GameController())
    ->setComponist(new Componist(buzzerPin))
    ->setLEDController(new LEDController(ledPins,3));
    
  spmInputCtrl = new SpmInputController(sensorPin, gameController);
  
  gameController->setUserInputController( spmInputCtrl );
  
  gameController->initialize();
}


void loop () {
  
  spmInputCtrl->processUserInputs();
  gameController->executeInLoop();  

}
