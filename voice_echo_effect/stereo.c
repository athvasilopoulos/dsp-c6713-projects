/*******************************************************************************
* FILENAME
*   stereo.c
*
* DESCRIPTION
*   Stereo and mono audio processing
*

*
*******************************************************************************/


/*-------------------------------------------------------------------------*/
/* stereo_to_mono()                                                        */
/*-------------------------------------------------------------------------*/
/*                                                                         */
/* Converts two stereo inputs to single mono output.                       */
/*                                                                         */
/* INPUT1 : First input signal from Audio Daughter Card.                   */
/* INPUT2 : Second input channel from Audio Daughter Card.                 */
/*                                                                         */
/* RETURNS: Average of two input signals from Audio Daughter Card.         */
/*                                                                         */
/*-------------------------------------------------------------------------*/

short int stereo_to_mono (short int input1, short int input2)
{
 int temp;

 /* Take average of two input signals */

 temp = ((int) input1 + (int) input2) ;

 temp /= 2;

 return( (short int) temp); 
}

/*-------------------------------------------------------------------------*/
/* End of stereo.c                                                         */
/*-------------------------------------------------------------------------*/





