#include "ledController.h"

LEDController::LEDController(int *ledPins, uint8_t numberOfLeds) {
  this->ledPins = ledPins;
  this->numberOfLeds = numberOfLeds;
  
  for ( int i=0; i<this->numberOfLeds; i++ ) {
    pinMode(this->ledPins[i], OUTPUT);  
    digitalWrite(this->ledPins[i], LOW);  // turn all the LEDs off
  }
}
    
void LEDController::turnLEDOn(uint8_t idx) {
 if ( idx >= numberOfLeds ) return;
 
 digitalWrite(ledPins[idx], HIGH);
}

void LEDController::turnLEDOff(uint8_t idx) {
 if ( idx >= numberOfLeds ) return;
 
 digitalWrite(ledPins[idx], LOW);  
}

void LEDController::turnLED(uint8_t idx, boolean onOff) {
 if ( idx >= numberOfLeds ) return;
 
 digitalWrite(ledPins[idx], onOff?HIGH:LOW);  
}

void LEDController::play(const uint8_t tempo, const int8_t *leds, const uint8_t *beats) {
  int8_t l;
  int i = 0;  
  while( (l = leds[i++]) != -99 ) {
    const uint8_t _delay = beats[i]*tempo;
    if ( l ) turnLED((uint8_t)abs(l-1), l>0);
    if ( _delay ) delay(_delay);
  }
}

