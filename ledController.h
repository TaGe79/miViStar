#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <MicroView.h>

class LEDController {
  private:
    int *ledPins; 
    int numberOfLeds;
    
  public:
    LEDController(int *ledPins, uint8_t numberOfLeds);
    
    void turnLEDOn(uint8_t idx);  
    void turnLEDOff(uint8_t idx);
    void turnLED(uint8_t idx, boolean onOff);
    
    void play(const uint8_t tempo, const int8_t *leds, const uint8_t *beats);    // terminate the leds array with -99; positive index = on; negative index = off
};

#endif
