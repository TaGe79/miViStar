#include "energyIndicator.h"

static const uint8_t width = 2;
static const uint8_t height = 30;

void EnergyIndicator::drawFace() {
  uint8_t offsetX, offsetY, dw = width, dh = height;
  offsetX=getX();
  offsetY=getY(); 
 
  if ( direction == VERTICAL ) { 
    dw = width;
    dh = height;
  } else if ( direction == HORIZONTAL ) {
    dh = width;
    dw = height;  
  }

  uView.lineH(offsetX,offsetY,dw);
  uView.lineH(offsetX,offsetY+dh,dw);

  uView.lineV(offsetX+dw,offsetY,dh+1);
  uView.lineV(offsetX,offsetY,dh);
  
}

void EnergyIndicator::draw() {
  uint8_t normedVal = max( min( floor((height*getValue())/getMaxValue() +0.5), getMaxValue() ), getMinValue() );
  uint8_t ox = getX(), oy = getY();
  uint8_t dw =0, dh = height - normedVal, sx = ox+1, sy = oy;
  
  if ( direction == VERTICAL ) { 
    dw = 0;
    dh = normedVal;
    sx = ox + 1;
    sy = oy + height - normedVal;
  } else if ( direction == HORIZONTAL ) {
    dw = normedVal;
    dh = 0;  
    sx = ox + height - normedVal;
    sy = oy + 1;
  }       
  uView.line(sx,sy,sx+dw,sy+dh, WHITE, NORM); 
  
    if ( direction == VERTICAL ) { 
    dw = 0;
    dh = height - normedVal-1;
    sx= ox+1;
    sy = oy+1;
  } else if ( direction == HORIZONTAL ) {
    dw = height - normedVal -1;
    dh = 0;  
    sx = ox+1;
    sy = oy+1;
  } 
  uView.line(sx,sy,sx+dw,sy+dh, BLACK, NORM);
}
