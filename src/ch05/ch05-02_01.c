#define F_UCPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define sbi(PORTX, BitX) ( (PORTX) |= (1 << BitX) )
#define cbi(PORTX, BitX) ( (PORTX) &= ~(1 << BitX) )

uint16_t adcValue = 0;

void adcInit (void){
    sbi(ADMUX, REFS0);
    sbi(ADCSRA, ADPS0);
    sbi(ADCSRA, ADPS1);
    sbi(ADCSRA, ADPS2);
    sbi(ADCSRA, ADEN);
}
 void UART_INIT(void){
    sbi(UCSR0A, U2X0);

    UBRR0H = 0x00;
    UBRR0L = 207;
    UCSR0C |= 0x06;
    
    sbi(UCSR0B, RXEN0);
    sbi(UCSR0B, TXEN0);
 }