//Example.c

#include <math.h>
#include "dsk6713_aic23.h"  			//support file for codec,DSK
#include "dsk6713_led.h"
#include "dsk6713_dip.h"


#define FS          48000
Uint32 fs = DSK6713_AIC23_FREQ_48KHZ;//set sampling rate
void comm_poll();
void output_sample(int);
Uint32 input_sample();

Int16 sineWave[] = { 2588, 5000, 7071, 8660, 9659, 10000, 9659, 8660, 7071,
		5000, 2588, 0, -2588, -5000, -7071, -8660, -9659, -10000, -9659, -8660,
		-7071, -5000, -2588, 0 };

void main()
{
	Uint32 sw, sample_data;
	Uint8 idx = 0, increment;


	comm_poll();               			//init DSK,codec,McBSP
	DSK6713_LED_init();						//init LED from BSL
	DSK6713_DIP_init();						//init DIP from BSL

	while(1) 				 					//infinite loop
	{
		//poll the switches to set fc
		sw = DSK6713_DIP_get(0);
		if (sw) {
			DSK6713_LED_on(0);
			increment = 1;
		}
		else {
			DSK6713_LED_off(0);
			increment = 2;
		}

	    output_sample( sineWave[idx] << 16 | sineWave[idx] );   //output sample
	    idx = idx + increment >= sizeof(sineWave)/2 ? 0 : idx + increment;
    }
}
