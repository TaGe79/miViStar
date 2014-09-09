#include <MicroView.h>
#include <string.h>

#include "componist.h"

static int frequency(char note) 
{
	// This function takes a note character (a-g), and returns the
	// corresponding frequency in Hz for the tone() function.

	int i;
	const int numNotes = 8;  // number of notes we're storing

	// The following arrays hold the note characters and their
	// corresponding frequencies. The last "C" note is uppercase
	// to separate it from the first lowercase "c". If you want to
	// add more notes, you'll need to use unique characters.

	// For the "char" (character) type, we put single characters
	// in single quotes.

	char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
	int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

	// Now we'll search through the letters in the array, and if
	// we find it, we'll return the frequency for that note.

	for (i = 0; i < numNotes; i++)  // Step through the notes
	{
		if (names[i] == note)         // Is this the one?
		{
			return(frequencies[i]);     // Yes! Return the frequency
		}
	}
	return(0);  // We looked through everything and didn't find it,
	// but we still need to return a value, so return 0.
}

Componist::Componist(const int _buzzerPin) : buzzerPin(_buzzerPin) {
      pinMode(buzzerPin, OUTPUT);
}
    
void Componist::playMelody(const unsigned int tempo, const char *notes, const int *beats) {
  int songLength = strlen(notes);  
  int duration = 0;
  
  for ( int i=0; i< songLength; i++ ) {
    duration = beats[i] * tempo;  
    if (notes[i] == ' ') delay(duration);
    else tone(buzzerPin, frequency(notes[i]), duration);
    
    delay(tempo/10);
  }
}
