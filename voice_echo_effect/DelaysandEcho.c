#include <stdio.h>
#include "bargraph.h"
#include "stereo.h"
#include "switches.h"
#include "c6713dsk.h"
#include "dsk6713_aic23.h"
#include "stdlib.h"
#include "math.h"

#define N (48000 * 4)

// Codec configuration settings
DSK6713_AIC23_Config config = { \
	0x0017,  /* 0 DSK6713_AIC23_LEFTINVOL  Left line input channel volume */ \
	0x0017,  /* 1 DSK6713_AIC23_RIGHTINVOL Right line input channel volume */\
	0x01f9,  /* 2 DSK6713_AIC23_LEFTHPVOL  Left channel headphone volume */  \
	0x01f9,  /* 3 DSK6713_AIC23_RIGHTHPVOL Right channel headphone volume */ \
	0x0011,  /* 4 DSK6713_AIC23_ANAPATH    Analog audio path control */      \
	0x0000,  /* 5 DSK6713_AIC23_DIGPATH    Digital audio path control */     \
	0x0000,  /* 6 DSK6713_AIC23_POWERDOWN  Power down control */             \
	0x0043,  /* 7 DSK6713_AIC23_DIGIF      Digital audio interface format */ \
	0x0001,  /* 8 DSK6713_AIC23_SAMPLERATE Sample rate control */            \
	0x0001   /* 9 DSK6713_AIC23_DIGACT     Digital interface activation */   \
};

far signed int delay_array[N]; /* Buffer for maximum delay of 4 seconds */

// Uses DIP switches to control the delay time between 0 s and
// 4 seconds. 48000 samples represent 1 second.
float get_delay_time(int delay){
	float time;
	time = delay * (4.0 / 7.0);
	return time;
}

// Take oldest sample from the array and replace it with the newest
// Uses a circular buffer because a straight buffer would be too slow.
Uint32 delayed_input(float time, int position, int *delay_array){
	Uint32 echo;
	int shift, i;
	shift = time * 48000;
	if (!shift){
		echo = delay_array[position];
	}
	else{
		if(shift > position){
			i = N - (shift - position);
			echo = delay_array[i];
		}
		else{
			i = position - shift;
			echo = delay_array[i];
		}
	}
	echo = (short)(echo >> 16);
	return echo;
}

// Fill delay array with zeroes to prevent noise / clicks.
void delay_array_clear(int *delay_array){
	int i;
	for(i = 0; i < N; i++)
		delay_array[i] = 0;
}

// Show status on console window.
void switch_status_display(int status){
	printf("The current status is: %d\n", status);
}

int main(void)
{
	DSK6713_AIC23_CodecHandle hCodec;

	// Initialize BSL
	DSK6713_init();

	//Start codec
	hCodec = DSK6713_AIC23_openCodec(0, &config);

	// Set  frequency to 48KHz
	DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_48KHZ);


	Uint32 val,normal,echo,echo2;
	int i=0;
	short int status,prev,temp;
	float time;
	* (unsigned volatile int*)McBSP1_RCR = 0x000000A0;
	* (unsigned volatile int*)McBSP1_XCR = 0x000000A0;

	delay_array_clear(delay_array);

	// Read and write to the aic23 using the polling method
	while(1){
		while(!DSK6713_AIC23_read(hCodec,&val));
		delay_array[i] = val;

		// Read the delay from the switches
		status = user_switches_read();
		status = 7 - status;

		temp = prev - status;
		if(temp)
			switch_status_display(status);
		prev = status;

		time = get_delay_time(status);

		// Keep the original input to push it to the output
		normal = val & 0xffff0000;

		// Find the delayed echo
		echo = delayed_input(time, i, delay_array);

		// Merge the two signals
		val = normal + echo;
		i++;
		i = i % N;
		
		// Amplify the echo signal for the bargraph
		echo2 = 2 * echo;
		bargraph(echo2);

		while(!DSK6713_AIC23_write(hCodec,val));
	}

	return (0);
}
