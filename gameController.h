#ifndef GAME_CONTROLLER_H
#define GAME_CONTOLLER_H

#include "sprite.h"
#include "star.h"
#include "componist.h"
#include "energyIndicator.h"
#include "ledController.h"
#include "userInputReceiver.h"
#include "userInputController.h"
#include "lifeIndicator.h"

#define MAX_STARS_IN_GAME   20
#define MAX_LEVELS          10
#define BASE_GAME_SPEED     160
#define DELAY               20
#define LIVES               3
#define FALLING_PIXELS      1
#define GROUND              40
#define SKY                 6

#define START_ENERGY_VALUE  30
#define MAX_ENERGY          50

#define INTRO_SCREEN_DISP_TIME 4000

#define LEFT_MARGIN         4
#define RIGHT_MARGIN        52

typedef enum GameStates {
  GAME_INTRO,
  LEVEL_SELECTION,
  ACTIVE_GAME,
  LEVEL_FINISHED,
  LIFE_LOST,
  GAME_OVER  
} gameStates_t;

class GameController : public UserInputReceiver {
  private:
    Componist           *componist;
    LEDController       *ledController;
    
    EnergyIndicator     *energyIndicator;
    LifeIndicator       *lifeIndicator;
    
    UserInputController *inputController;
    

    uint8_t currentLevel;
    uint8_t currentGroundings;
    uint8_t currentCatches;
    
    uint8_t currentGameSpeed;
    uint8_t currentLives;
    uint8_t currentEnergyLevel;
    
    GameStates currentGameState;
    
    uint16_t  inStateTimeMs;
    Inputs lastInputDetected;
    
    static const uint8_t maxStarsInGame[MAX_LEVELS];
    
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
    
    void actualizeGameState();
    
    void finishAndStepToNextLevel();
    
  public:
    GameController();
    ~GameController();

    GameController* setComponist(Componist *componist);
    GameController* setLEDController(LEDController *ledController);
    GameController* setUserInputController(UserInputController *userInputController);
    
    void initialize();
    
    void executeInLoop();
    void moveTheManTo(pos_t pos);
    uint8_t getCurrentLevel();
    
    void userInputDetected(void* sender, Inputs userInput);
    void moveCarretTo(void* sender, int posX, int posY);    
};

#endif
