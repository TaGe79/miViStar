#include "lifeIndicator.h"

uint8_t LifeIndicator::reduceLife() {
  this->lifesLeft -= 1;
  
  drawFace();
  return this->lifesLeft;
}

uint8_t LifeIndicator::reset() {
  this->lifesLeft = this->maxLifes;
  
  drawFace();
  return this->maxLifes;  
}

uint8_t LifeIndicator::getLifesLeft() {
  return this->lifesLeft; 
}

void LifeIndicator::draw() {
   drawFace(); 
}
void LifeIndicator::drawFace() {
  uint8_t offsetX, offsetY;
  
  offsetX=getX();
  offsetY=getY(); 

  for ( uint8_t i=0;  i<this->maxLifes; i++ ) {
    if ( i < this->lifesLeft ) this->lifeSign->draw( pos_t(offsetX+(i*6)+3, offsetY+2) );  
    else this->deadSign->draw( pos_t(offsetX+(i*6)+3, offsetY+2) );
  }
}

void LifeIndicator::redraw() {
   draw(); 
}
