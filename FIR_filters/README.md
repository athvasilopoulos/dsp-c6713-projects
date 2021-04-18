# FIR Filters
In this project, I use the AIC23 Codec peripheral to receive sound input and apply a variety of FIR filters. The filter is applied in real-time for every new sample and the result is sent to an output buffer.

## AIC23 Codec
This peripheral is connected with the McBSP serial port of the C6713 and after its initialization it continuously does A/D and D/A conversion. The communication is done using interrupts. To initialize the codec, the entry point of the program changes to the C file.