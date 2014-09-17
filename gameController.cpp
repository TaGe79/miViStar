#include "gameController.h"

static const int      catchTempo          = 150;
static const char     catchNotes[]        = "cahh";
static const int      catchBeats[]        = {1,2,1,1};

static const int      groundTempo         = 150;
static const char     groundNotes[]       = "hfdc";
static const int      groundBeats[]       = {2,2,2,2};

static const uint8_t  catchLightsTempo    = 50;
static const int8_t   catchLights[]       = {1, 2, 3,-3,-2,-1,-99};
static const uint8_t  catchLightsBeats[]  = {1, 1, 2, 0, 0, 0, 0};

static const uint8_t  groundLightsTempo   = 50;
static const int8_t   groundLights[]      = {1, 2, 3, 0, -3,-2,-1,-99};
static const uint8_t  groundLightsBeats[] = {0, 0, 0, 3, 0,  0, 0, 0};

const uint8_t GameController::maxStarsInGame[MAX_LEVELS] = {4,4,5,6,7,8,10,12,12,15};

pos_t GameController::generateNonCollidingX() {
  bool collisionDetected;
  pos_t starPos(0,0);
  
  do {
    collisionDetected = false;
    uint8_t x = LEFT_MARGIN + rand()%RIGHT_MARGIN; 
    starPos = pos_t(x,SKY);  
    for ( int i = 0; i < MAX_STARS_IN_GAME; i++ ) {
      Star *s = stars[i];
      if ( s == NULL ) continue;
      
      if ( s->isColliding(starPos) ) { 
        collisionDetected = true; 
        break; 
      }
    }
  } while ( collisionDetected );

  return starPos;  
}

void GameController::generateAStar() {
  if ( starsInGame >= maxStarsInGame[currentLevel] || rand() % 10 < 5 || starLastStarted < starGenSpeed ) return;
  
  Star *s = new Star(Sprite::SIZE,Sprite::star,GROUND);
  s->draw(generateNonCollidingX());
  
  for ( int i=0; i < MAX_STARS_IN_GAME; i++ ) {
    if ( stars[i] ) continue;
    
    stars[i] = s;
    break;
  }
  
  starsInGame++;
  starLastStarted = 0;
  starGenSpeed = rand()%(12*currentGameSpeed) + 3*BASE_GAME_SPEED;  
}

void GameController::moveTheStars() {
  if ( starsInGame <= 0 || starsLastMoved < currentGameSpeed ) return;

  for ( int i = 0; i < MAX_STARS_IN_GAME; i++ ) {
    Star *s = stars[i];
    if ( s == NULL ) continue;
    
    const pos_t pos = s->whereAmI();
    s->draw(pos_t(pos.x,pos.y+FALLING_PIXELS));  
    
    if ( man->isColliding(s) ) { 
      currentCatches++; 
      if ( componist ) componist->playMelody(catchTempo, catchNotes, catchBeats); 
      if ( ledController ) ledController->play(catchLightsTempo,catchLights,catchLightsBeats);
      
    } else if ( s->isGrounded() ) {
      currentGroundings++;
      if ( componist ) componist->playMelody(groundTempo, groundNotes, groundBeats);
      if ( ledController ) ledController->play(groundLightsTempo,groundLights,groundLightsBeats);
    } else { continue; }

    // remove the stone any way
    delete s;
    stars[i] = NULL;
    starsInGame--;
    
    // and update the energy bar
    int energyLevel = max(0, min( MAX_ENERGY, START_ENERGY_VALUE+(currentCatches*2)-(currentGroundings*2) ) );
    
    if ( energyLevel == MAX_ENERGY ) {
      // TODO step a level higher
      // TODO reset energy level
      
    } else if ( energyLevel == 0 ) {
      // TODO decrease lives by one
      // TODO test lives and finish game if the 0
      // TODO reset energy level  
    }
    
    energyIndicator->setValue(energyLevel);           
  }
  
  starsLastMoved = 0;  
}

GameController::GameController() : 
  currentLevel(0), 
  currentGroundings(0),
  currentCatches(0),
  currentLives(LIVES),
  starsInGame(0),
  starsLastMoved(0),
  starLastStarted(0),
  starGenSpeed(BASE_GAME_SPEED),
  currentGameSpeed(BASE_GAME_SPEED),
  currentGameState(GAME_INTRO),
  lastInputDetected(NONE) {
  man = new Sprite(4,(uint8_t*)Sprite::man);
  memset(stars,0,MAX_STARS_IN_GAME*sizeof(Star*));  

  componist = NULL;
  ledController = NULL;
  
  energyIndicator = new EnergyIndicator(VERTICAL,LEFT_MARGIN+RIGHT_MARGIN+2,SKY+5,MAX_ENERGY);  
}

GameController::~GameController() {
  delete man;
  delete energyIndicator;
  
  if ( componist ) delete componist;
  if ( ledController ) delete ledController;
  
  delete inputController;
}

void GameController::initialize() {
  srand (9868136);
    
  inputController->setFixPositionY(GROUND);
  inputController->setMinPositionX(LEFT_MARGIN);
  inputController->setMaxPositionX(RIGHT_MARGIN);
  
  uView.begin();					// start MicroView	
  uView.clear(PAGE);  			        	// clear page  
}

void GameController::displayLevelNumber() {
  uView.setFontType(1); 
  uView.setCursor(0,0); 
  char lvl[30];
  sprintf(lvl,"LEVEL %d",currentLevel);
  uView.print(lvl);
}

void GameController::executeInLoop() {
  
  switch ( currentGameState ) {
    case GAME_INTRO:
      uView.setCursor(0,0); 
      uView.print('I');
      break;
    
    case LEVEL_SELECTION:
      uView.setCursor(0,0);
      uView.print('L');
      break;
    
    case ACTIVE_GAME:
  
      moveTheStars();
      generateAStar();  
  
      break;

    case LEVEL_FINISHED:
      uView.setCursor(0,0); 
      uView.print('F');    
      break;
      
    case GAME_OVER:
      uView.setCursor(0,0); 
      uView.print('G');        
      break;
      
    default:
      uView.setCursor(0,0); 
      uView.print((char)('A'+currentGameState));        
      break;
  }
  
  actualizeGameState();
  
  starsLastMoved += DELAY;
  starLastStarted += DELAY;
  
  uView.display();
  
  delay(DELAY);
}

void GameController::actualizeGameState() {
  const GameStates lastState = currentGameState;
  
  // TODO evaluate and advance game state
  switch ( currentGameState ) {
    case GAME_INTRO:
      if ( inStateTimeMs < INTRO_SCREEN_DISP_TIME ) break;
      
      uView.clear(PAGE);
      currentGameState = LEVEL_SELECTION;
      break;
    case LEVEL_SELECTION:
      //if (lastInputDetected == ENTER ) 
        uView.clear(PAGE);
        currentGameState = ACTIVE_GAME;
        energyIndicator->redraw();
      break;
    case ACTIVE_GAME:
      break;
    case LEVEL_FINISHED:
      currentGameState = ACTIVE_GAME;
      break;
      
    case GAME_OVER:
      break;
    default:
      currentGameState = GAME_INTRO;
      break;    
  }
  
  if ( lastState != currentGameState ) inStateTimeMs = 0;
  else inStateTimeMs += DELAY;
}

void GameController::moveTheManTo(pos_t pos) {
  man->draw(pos);
}

GameController* GameController::setComponist(Componist *componist) {
   this->componist = componist; 
   
   return this;
}

GameController* GameController::setLEDController(LEDController *ledController) {
  this->ledController = ledController;  
  
  return this;
}

GameController* GameController::setUserInputController(UserInputController *userInputController) {
   this->inputController = userInputController;
  
  return this; 
}

void GameController::userInputDetected(void* sender, Inputs userInput) {
  
}

void GameController::moveCarretTo(void* sender, int posX, int posY) {
  moveTheManTo(pos_t(posX,posY));
}

