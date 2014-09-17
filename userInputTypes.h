#ifndef USER_INPUT_TYPES_H
#define USER_INPUT_TYPES_H
typedef enum Inputs {
  NONE,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  ENTER,
  POSITION  
} Inputs;

typedef enum InptuModes {
  IM_GESTURE,
  IM_POSITION  
} InputModes;
#endif
