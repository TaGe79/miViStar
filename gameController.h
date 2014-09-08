#ifndef GAME_CONTROLLER_H
#define GAME_CONTOLLER_H

#include "sprite.h"
#include "star.h"
#include "componist.h"
#include "energyIndicator.h"

#define MAX_STARS_IN_GAME   20
#define MAX_LEVELS          10
#define BASE_GAME_SPEED     160
#define DELAY               20
#define LIVES               3
#define FALLING_PIXELS      1
#define GROUND              40
#define SKY                 6
#define START_ENERGY_VALUE  30

#define LEFT_MARGIN         4
#define RIGHT_MARGIN        52

typedef enum GAME_STATES {
  LEVEL_SELECTION,
  ACTIVE_GAME,
  GAME_OVER  
} gameStates_t;

class GameController {
  private:
    Componist *componist;
    EnergyIndicator *energyIndicator;
    
    uint8_t currentLevel;
    uint8_t currentGroundings;
    uint8_t currentCatches;
    
    uint8_t currentGameSpeed;
    uint8_t currentLives;
    
    uint8_t maxStarsInGame[MAX_LEVELS] = {4,4,5,6,7,8,10,12,12,15};
    
    Sprite *man;
    Star *stars[MAX_STARS_IN_GAME];

    int starsInGame;
    int starsLastMoved;
    int starLastStarted;
    int starGenSpeed;
    
    void displayLevelNumber(); 
    pos_t generateNonCollidingX();
    void generateAStar();
    void moveTheStars();
    
  public:
    GameController();
    ~GameController();

    void setComponist(Componist *componist);
    void executeInLoop();
    void moveTheManTo(pos_t pos);
    uint8_t getCurrentLevel();
};

#endif
