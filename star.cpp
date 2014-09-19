#include "star.h"

Star::Star(uint8_t size, const uint8_t* sprite, uint8_t ground)  : Sprite(size,sprite, COMPRESSED) {
      this->ground = ground;
}
    
bool Star::isGrounded() {
  return ( pos.y+floor(width/2+0.5) >= ground );
}


