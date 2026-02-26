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

 unsigned char UART_RECEIVE(void){
    while( !(UCSR0A & (1 << RXC0)) );
    return UDR0;
 }

 void UART_TRANSMIT(unsigned char data){
    while( !(UCSR0A & (1 << UDRE0)) );
    UDR0 = data;
 }

 void UART_string_transmit(char *string)
{
    while(*string != '\0')
    {
        UART_tranmit(*string);
        string++;
    }
}

uint16_t readADC(uint8_t channel)
{
    ADMUX &= 0xF0;
    ADMUX |= channel;

    sbi(ADCSRA, ADSC);
    while(ADCSRA & (1 << ADSC));

    return ADC;
}