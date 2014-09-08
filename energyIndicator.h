#ifndef ENERGY_INDICATOR_H
#define ENERGY_INDICATOR_H

#include <MicroView.h>

typedef enum _direction {
  HORIZONTAL,
  VERTICAL  
} direction_t;

class EnergyIndicator : public MicroViewWidget {
  private:
    direction_t direction;
    
  public:  
    EnergyIndicator(direction_t dir, uint8_t newx, uint8_t newy, int16_t max ) : MicroViewWidget(newx, newy, 0, max), direction(dir) {
      drawFace();
      draw();
    };
    
    void draw();
    void drawFace();
};

#endif
