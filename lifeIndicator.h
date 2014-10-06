#ifndef LIFE_INDICATOR_H
#define LIFE_INDICATOR_H

#include <MicroView.h>
#include <stdlib.h>

#include "sprite.h"

static const uint8_t emptyHeart[] = {
0x50,
0xa8,
0x88,
0x50,
0x20
};

static const uint8_t filledHeart[] = {
0x50,
0xf8,
0xf8,
0x70,
0x20
};


class LifeIndicator : public MicroViewWidget {
  private:
    uint8_t maxLifes;
    uint8_t lifesLeft;

    Sprite **lifeSigns;
    Sprite **deadSigns;

    const uint8_t width;
    const uint8_t height;
    
  public:  
    LifeIndicator(uint8_t maxLifes, uint8_t newx, uint8_t newy) : MicroViewWidget(newx, newy, 0, maxLifes), width(maxLifes*6), height(5) {
      this->maxLifes = maxLifes;
      this->lifesLeft = maxLifes;
      
      this->deadSigns = (Sprite**)malloc(maxLifes * sizeof(Sprite*));
      this->lifeSigns = (Sprite**)malloc(maxLifes * sizeof(Sprite*));
      
      for ( int i =0; i<maxLifes; i++ ) {
        this->lifeSigns[i] = new Sprite(5,5,filledHeart,COMPRESSED);
        this->deadSigns[i] = new Sprite(5,5,emptyHeart,COMPRESSED);        
      }
      
      drawFace();
      draw();
    };
    
    ~LifeIndicator() {
      for ( int i=0; i< maxLifes; i++ ) {
        delete deadSigns[i];
        delete lifeSigns[i];  
      }
      
        delete deadSigns;
        delete lifeSigns;      
    }
    
    uint8_t reduceLife();
    uint8_t reset();

    uint8_t getLifesLeft();    
    uint8_t getMaxLifes();
    
    void draw();
    void drawFace();
    
    void redraw();
};


#endif
