#ifndef STAR_H
#define STAR_H

#include "sprite.h"

class Star : public Sprite {
  private:
    uint8_t ground;
    
  public:
    Star(uint8_t size, const uint8_t* sprite, uint8_t ground);
    
    bool isGrounded();
};

#endif
