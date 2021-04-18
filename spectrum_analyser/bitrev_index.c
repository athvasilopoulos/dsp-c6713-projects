/* ======================================================================== */
/*                                                                          */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      bitrev_index                                                        */
/*                                                                          */
/*  USAGE                                                                   */
/*      This function has the prototype:                                    */
/*                                                                          */
/*      void bitrev_index(short *index, int n);                             */
/*                                                                          */
/*      index[sqrt(n)] : Pointer to index table that is returned by the     */
/*                       routine.                                           */
/*      n              : Number of complex array elements to bit-reverse.   */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This routine calculates the index table for the DSPLIB function     */
/*      bitrev_cplx which performs a complex bit reversal of an array of    */
/*      length n. The length of the index table is 2^(2*ceil(k/2)) where    */
/*      n = 2^k. In other words, the length of the index table is sqrt(n)   */
/*      for even powers of radix.                                           */
/*                                                                          */
/* ======================================================================== */
                                                                          
void bitrev_index(short *index, int n)                 
{                                                                   
    int   i, j, k, radix = 2;                                                  
    short nbits, nbot, ntop, ndiff, n2, raddiv2;                    
                                                                    
    nbits = 0;                                                      
    i = n;                                                          
    while (i > 1)                                                   
    {                                                               
        i = i >> 1;                                                 
        nbits++;                                                    
    }                                                               
                                                                    
    raddiv2 = radix >> 1;                                           
    nbot    = nbits >> raddiv2;                                     
    nbot    = nbot << raddiv2 - 1;                                  
    ndiff   = nbits & raddiv2;                                      
    ntop    = nbot + ndiff;                                         
    n2      = 1 << ntop;                                            
                                                                    
    index[0] = 0;                                                   
    for ( i = 1, j = n2/radix + 1; i < n2 - 1; i++)                 
    {                                                               
        index[i] = j - 1;                                           
                                                                    
        for (k = n2/radix; k*(radix-1) < j; k /= radix)             
            j -= k*(radix-1);                                       
                                                                    
        j += k;                                                     
    }                                                               
    index[n2 - 1] = n2 - 1;                                         
}                                                                 

