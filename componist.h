#ifndef COMPONIST_H
#define COMPONIST_H

class Componist {
  private:
    const int buzzerPin;
    
  public:
    Componist(const int _buzzerPin) : buzzerPin(_buzzerPin) {};
    void playMelody(const unsigned int tempo, const char *notes, const int *beats);
};

#endif

