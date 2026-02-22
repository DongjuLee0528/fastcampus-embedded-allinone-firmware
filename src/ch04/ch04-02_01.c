#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX, BITX) (PORTX |= (1 << BITX))

SIGNAL(INT1_vect){
    PORTB = 0x20;
    _delay_ms(200);
}

int main(void)
{
    sbi(SREG, 7);

    sbi(EIMSK, INT1);
    EICRA =0x08;

    DDRB = 0x20;
    DDRD = 0x00;
    PORTD = 0x08;

    while(1){
        PORTB = 0x00;
    }
}