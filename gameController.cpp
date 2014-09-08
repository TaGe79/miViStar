#include "gameController.h"

static const int    catchTempo     = 150;
static const char   catchNotes[]   = "cahh";
static const int    catchBeats[]   = {1,2,1,1};

static const int    groundTempo    = 150;
static const char   groundNotes[]  = "hfdc";
static const int    groundBeats[]  = {2,2,2,2};


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
    } else if ( s->isGrounded() ) {
      currentGroundings++;
      if ( componist ) componist->playMelody(groundTempo, groundNotes, groundBeats);
    } else { continue; }

    // remove the stone any way
    delete s;
    stars[i] = NULL;
    starsInGame--;
    
    // and update the energy bar
    energyIndicator->setValue(START_ENERGY_VALUE+(currentCatches*2)-(currentGroundings*2));    
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
  currentGameSpeed(BASE_GAME_SPEED) {
  man = new Sprite(4,(uint8_t*)Sprite::man);
  memset(stars,0,MAX_STARS_IN_GAME*sizeof(Star*));  
  componist = NULL;
  //energyIndicator = new EnergyIndicator(HORIZONTAL,2,GROUND+3,100);
  energyIndicator = new EnergyIndicator(VERTICAL,LEFT_MARGIN+RIGHT_MARGIN+2,SKY+5,100);
  energyIndicator->setValue(START_ENERGY_VALUE);
}

GameController::~GameController() {
  delete man;
  delete energyIndicator;
  if ( componist ) delete componist;
}

void GameController::displayLevelNumber() {
  uView.setFontType(1); 
  uView.setCursor(0,0); 
  char lvl[30];
  sprintf(lvl,"LEVEL %d",currentLevel);
  uView.print(lvl);
}

void GameController::executeInLoop() {
  moveTheStars();
  generateAStar();  
  
  starsLastMoved += DELAY;
  starLastStarted += DELAY;
}

void GameController::moveTheManTo(pos_t pos) {
  man->draw(pos);
}

void GameController::setComponist(Componist *componist) {
   this->componist = componist; 
}
