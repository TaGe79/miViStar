#include <MicroView.h>				// include MicroView library
#include <stdlib.h>
#include <stdio.h>

#include "gameController.h"
#include "componist.h"
#include "ledController.h"

uint8_t controllerPos = 0;
int sensorPin         = A0;
int sensorValue       = 0;

int buzzerPin         = A1;

int ledPins[]         = {A2,A3,A4};


GameController *gameController;
void setup() {
  srand (9868136);
  
  uView.begin();					// start MicroView	
  uView.clear(PAGE);			        	// clear page
  pinMode(sensorPin, INPUT);				// set sensor pin as INPUT
  
  sensorValue=analogRead(sensorPin);
  controllerPos = floor(LEFT_MARGIN+min(RIGHT_MARGIN,(RIGHT_MARGIN/1000.0)*sensorValue));
  
  gameController = (new GameController())
    ->setComponist(new Componist(buzzerPin))
    ->setLEDController(new LEDController(ledPins,3));
}


void loop () {
  sensorValue = analogRead(sensorPin);		      // read and store sensor value
  //widget->setValue(sensorValue);		      // set sensor value to widget

  const int manPosX = floor(LEFT_MARGIN+min(RIGHT_MARGIN,(RIGHT_MARGIN/1000.0)*sensorValue));
  
  gameController->moveTheManTo(pos_t(manPosX,GROUND));
  gameController->executeInLoop();  
  
  uView.display();				      // display widget
  
  delay(DELAY);				              // delay 20 ms
}
