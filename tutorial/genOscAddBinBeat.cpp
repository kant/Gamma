/*	Gamma - Generic processing library
	See COPYRIGHT file for authors and license information
	
	Tutorial:		Generator / Oscillator / Additive
	Description:	Two-oscillator binaural beating
*/

#include "tutorial.h"

float ff = 220;
float freqBeat = 1;

Sine<> osc1(ff);					// fundamental oscillator
Sine<> osc2(ff + freqBeat, 0.5);	// beat oscillator starting 180 out-of-phase
									// from fundamental

void audioCB(AudioIOData& io){

	for(int i=0; i<io.framesPerBuffer(); ++i){

		io.out(0)[i] = osc1() * 0.1;
		io.out(1)[i] = osc2() * 0.1;
	}
}


RUN(audioCB);
