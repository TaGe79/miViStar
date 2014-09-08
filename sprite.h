#ifndef SPRITE_H
#define SPRITE_H

#include <MicroView.h>

typedef struct pos_t {
  pos_t(int _x, int _y) : x(_x), y(_y) { }
  
  uint8_t x;
  uint8_t y;  
} pos_t;

class Sprite {
private: 
  const uint8_t *sprite;

protected:
  uint8_t size;
  pos_t pos;

  void eraseCurrent();
  void draw(pos_t pos, uint8_t color);
  
public:
  Sprite(uint8_t size, const uint8_t *sprite);
  ~Sprite();
  
  pos_t whereAmI();
  
  void draw(pos_t newPos);
  bool isColliding(pos_t aPos);
  bool isColliding(Sprite *other);
  
  static const uint8_t star[];
  static const uint8_t man[];
  static const uint8_t SIZE;
};

#endif
