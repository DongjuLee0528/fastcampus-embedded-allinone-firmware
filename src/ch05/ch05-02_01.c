#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define sbi(PORTX, BitX)  ((PORTX) |= (1 << BitX))   // 비트 SET
#define cbi(PORTX, BitX)  ((PORTX) &= ~(1 << BitX))  // 비트 CLEAR

uint16_t adcValue = 0;

void adcInit(void){
    sbi(ADMUX, REFS0);      // AVCC(5V)
    sbi(ADCSRA, ADPS0);     // 16Mhz / 128 = 125Khz
    sbi(ADCSRA, ADPS1);
    sbi(ADCSRA, ADPS2);
    sbi(ADCSRA, ADEN);      // ADC 활성화
}

void UART_INIT(void){
    sbi(UCSR0A, U2X0);      // U2X0 = 1 --> Baudrate 9600 = 207

    UBRR0H = 0x00;
    UBRR0L = 207;           // Baudrate 9600
    UCSR0C |= 0x06;         // 1stop bit, 8bit data

    sbi(UCSR0B, RXEN0);     // enable receiver and transmitter
    sbi(UCSR0B, TXEN0);
}

unsigned char UART_receive(void){
    while(!(UCSR0A & (1 << RXC0)));   // wait for data to be received
    return UDR0;                     // get and return received data from buffer
}

void UART_tranmit(unsigned char data){
    while(!(UCSR0A & (1 << UDRE0)));  // wait for empty transmit buffer
    UDR0 = data;                     // put data into buffer, sends the data
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
    ADMUX &= 0xF0;                   // 핀 초기화
    ADMUX |= channel;                // 사용할 ADC 채널 설정

    sbi(ADCSRA, ADSC);               // ADC Start Conversion ADC 변환 시작
    while(ADCSRA & (1 << ADSC));     // ADC 변환 완료까지 대기

    return ADC;
}

int main(void)
{
    char buffer[10] = {0};
    uint16_t adcValue = 0;

    adcInit();
    UART_INIT();

    /* Replace with your application code */
    while (1)
    {
        adcValue = readADC(0);
        itoa(adcValue, buffer, 10);
        UART_string_transmit(buffer);
        UART_tranmit('\n');
        _delay_ms(500);
    }
}