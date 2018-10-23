// Welch, Wright, & Morrow, 
// Real-time Digital Signal Processing, 2011

///////////////////////////////////////////////////////////////////////
// Filename: ISRs.c
//
// Synopsis: Interrupt service routine for codec data transmit/receive
//
///////////////////////////////////////////////////////////////////////

#include "DSP_Config.h"

#define FILTER_TAP_NUM 16 // 17 taps but array size is going to be 16


  
// Data is received as 2 16-bit words (left/right) packed into one
// 32-bit word.  The union allows the data to be accessed as a single 
// entity when transferring to and from the serial port, but still be 
// able to manipulate the left and right channels independently.

#define LEFT  0
#define RIGHT 1

volatile union {
	Uint32 UINT;
	Int16 Channel[2];
} CodecDataIn, CodecDataOut;


/* add any global variables here */
int i;
float xLeft[FILTER_TAP_NUM + 1], *pLeft = xLeft;

float filter_taps[FILTER_TAP_NUM + 1] = {
 -0.0923694208024749,
 -0.03650640543188837,
 0.11875792315420561,
 0.0374948286074147,
 -0.08103564828339961,
 -0.042840979892957355,
 0.06320261016781677,
 -0.13370575066235044,
 1.2308691004305696,
 -0.13370575066235044,
 0.06320261016781677,
 -0.042840979892957355,
 -0.08103564828339961,
 0.0374948286074147,
 0.11875792315420561,
 -0.03650640543188837,
 -0.0923694208024749
};

interrupt void Codec_ISR()
///////////////////////////////////////////////////////////////////////
// Purpose:   Codec interface interrupt service routine  
//
// Input:     None
//
// Returns:   Nothing
//
// Calls:     CheckForOverrun, ReadCodecData, WriteCodecData
//
// Notes:     None
///////////////////////////////////////////////////////////////////////
{                    
	/* add any local variables here */
	float xRight, yRight;
	float output;

	float *pCurrentSampleCounter;



 	if(CheckForOverrun())					// overrun error occurred (i.e. halted DSP)
		return;								// so serial port is reset to recover

  	CodecDataIn.UINT = ReadCodecData();		// get input data samples
	
	/* add your code starting here */


	*pLeft  = CodecDataIn.Channel[ LEFT];
	xRight = CodecDataIn.Channel[ RIGHT];

	*pLeft += 0.05; // right output was too low

	output = 0;
	pCurrentSampleCounter = pLeft;

	if (++pLeft > &xLeft[FILTER_TAP_NUM])
		pLeft = xLeft;
	for (i = 0; i <= FILTER_TAP_NUM; i++)
	{
		output += (*pCurrentSampleCounter--) * filter_taps[i];
		if (pCurrentSampleCounter < &xLeft[0])
			pCurrentSampleCounter = &xLeft[FILTER_TAP_NUM];
	}

	yRight = xRight;


	CodecDataOut.Channel[ LEFT] = output;
	CodecDataOut.Channel[RIGHT] = yRight;

	/* end your code here */

	WriteCodecData(CodecDataOut.UINT);		// send output data to  port
}

