/*	Gamma - Generic processing library
	See COPYRIGHT file for authors and license information
	
	Tutorial:		Generator / Envelope
	Description:	Using an exponential AD (attack/decay) envelope to control
					the amplitude of an oscillator.
*/

#include "tutorial.h"

Accum<> tmr(1/1.2);			// Timer for resetting envelope
NoiseWhite<> src;			// Noise source
AD<> env(0, 1);				// Attack/decay envelope
double tilt = 0;			// Tilt of envelope; 0=percussive, 1=reversive

void audioCB(AudioIOData& io){

	for(int i=0; i<io.framesPerBuffer(); ++i){
	
		if(tmr()){
			tilt += 0.1; if(tilt > 1) tilt=0;	// increment tilt amount
			env.set(tilt, 1-tilt);				// set new attack/decay times
			env.reset();						// reset amplitude of envelope
		}

		float s = src() * env() * 0.2;

		io.out(0)[i] = io.out(1)[i] = s;
	}
}

RUN(audioCB);
