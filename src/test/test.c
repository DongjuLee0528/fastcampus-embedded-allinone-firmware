#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600UL
#define UBRR_VALUE ((F_CPU / 16UL / BAUD) - 1)

static void USART_Init(void) {
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)(UBRR_VALUE);
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

static void USART_Tx(uint8_t c) {
    while (!(UCSR0A & (1 << UDRE0))) {}
    UDR0 = c;
}

static void USART_Print(const char *s) {
    while (*s) USART_Tx((uint8_t)*s++);
}

int main(void) {
    USART_Init();
    while (1) {
        USART_Print("PING\r\n");
        _delay_ms(1000);
    }
}
