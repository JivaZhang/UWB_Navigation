# Test Code II - Function & Algorithm
- JY61s - Get string data
- PID for encoder - turn a certain angle
					go at a specified speed
- Goto function - go to a select coordiante

## JY61s
- Enable the break of UART, find 0x55 header. Then disable UART-break, enable DMA to receive a 10 bits data. But this limit the efficiency of DMA.
- Set a receive circular buffer which has a maximum 1000 bits length. DMA receive 11 bits data at once and a ptr is set to get the data without stop DMA procession.
- Finally, my solution is to enable DMA's circular mode at all time. Change the length of readable data bit to find the header.

## Encoder


