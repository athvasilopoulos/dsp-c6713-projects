//C6xdskinit_pcm.h Function prototypes for routines in C6xdskinit_pcm.c

void mcbsp0_init();
void mcbsp1_activate();
void mcbsp1_write(int);
int mcbsp1_read();
void c6x11_dsk_init();  
void comm_poll();
void comm_intr();
int input_sample();      
short input_left_sample();
short input_right_sample();
void output_sample(int);
void output_left_sample(short);
void output_right_sample(short);
