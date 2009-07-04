/*	Gamma - Generic processing library
	See COPYRIGHT file for authors and license information
	
	Tutorial:		Generator / Oscillator / Osc
	Description:	Using a general-purpose table-based oscillator.
*/

#include "tutorial.h"

float ff = 110;						// fundamental frequency
Accum<> tmr(0.2, 2);				// timer for modifying wavetable contents
Osc<> osc1(ff       , 0, 512);		// oscillator owning a 512-element wavetable
Osc<> osc2(ff + 0.17, 0, osc1);		// detuned oscillator sharing osc1's table
Osc<> osc3(ff + 0.03, 0, osc1);		// detuned oscillator sharing osc1's table

void audioCB(AudioIOData& io){

	for(uint32_t i=0; i<io.framesPerBuffer(); i++){
	
		if(tmr()){
			osc1.zero();			// zero wavetable
			osc1 << tup(1, 1, 0);	// add the fundamental
		
			// add some 1/f overtones
			int skip = rnd::uni(5, 1);
			for(int i=1+skip; i<=rnd::uni(65, 16); i+=skip){
				if(rnd::prob()) osc1 << tup(i, 1./i, 0);
			}
		}

		float s = (osc1() + osc2()/2 + osc3()/4) * 0.1;
		
		io.out(0)[i] = io.out(1)[i] = s;
	}
}


int main(int argc, char* argv[]){
	AudioIO io(256, 44100., audioCB, NULL, 2);
	Sync::master().spu(io.framesPerSecond());

	io.start();
	printf("\nPress 'enter' to quit...\n"); getchar();
	return 0;
}
