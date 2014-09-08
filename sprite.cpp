#include "sprite.h"

const uint8_t Sprite::SIZE     = 4;

const uint8_t Sprite::man []= {
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0
};

const uint8_t Sprite::star [] = {
  1,0,0,1,
  0,1,1,0,
  0,1,1,0,
  1,0,0,1
};
    
Sprite::Sprite(uint8_t size, const uint8_t *sprite) : pos(0,0) {
  this->size = size;
  this->sprite = sprite;
}

Sprite::~Sprite() {
  eraseCurrent();  
}

pos_t Sprite::whereAmI() {
  return pos;
}

void Sprite::draw(pos_t pos, uint8_t color) {
  const uint8_t sizeHalf = floor(size/2 +0.5);
  for ( uint8_t x=0; x<size; x++ ) {
    for ( uint8_t y =0; y<size; y++ ) {
      if ( !sprite[x+(size*y)] ) continue;
      uView.pixel(pos.x-sizeHalf+x, pos.y-sizeHalf+y,color, NORM);  
    }
  }    
}

void Sprite::eraseCurrent() {
  draw(pos,BLACK);  
}
 
void Sprite::draw(pos_t newPos) {
  eraseCurrent();
  draw(newPos,WHITE);
  pos = newPos;  
}

bool Sprite::isColliding(pos_t aPos) {
return ( aPos.x >= pos.x-size
       && aPos.x <= pos.x+size
       && aPos.y >= pos.y-size );  
}

bool Sprite::isColliding(Sprite *other) {
  pos_t whereIsHe = other->whereAmI();

  return isColliding(whereIsHe);  
}
