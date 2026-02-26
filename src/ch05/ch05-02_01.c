#define F_UCPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define sbi(PORTX, BitX) ( (PORTX) |= (1 << BitX) )
#define cbi(PORTX, BitX) ( (PORTX) &= ~(1 << BitX) )