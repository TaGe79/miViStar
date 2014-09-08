#include <MicroView.h>				// include MicroView library
#include <stdlib.h>
#include <stdio.h>

#include "gameController.h"
#include "componist.h"

uint8_t controllerPos = 0;
int sensorPin         = A0;
int sensorValue       = 0;

int buzzerPin         = A1;

GameController *gameController;
void setup() {
  srand (98732168136);
  
  uView.begin();					// start MicroView	
  uView.clear(PAGE);			        	// clear page
  pinMode(sensorPin, INPUT);				// set sensor pin as INPUT
  pinMode(buzzerPin, OUTPUT);
  
  sensorValue=analogRead(sensorPin);
  controllerPos = floor(LEFT_MARGIN+min(RIGHT_MARGIN,(RIGHT_MARGIN/1000.0)*sensorValue));
  
  gameController = new GameController();
  gameController->setComponist(new Componist(buzzerPin));
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
