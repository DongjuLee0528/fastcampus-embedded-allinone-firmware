#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#define sbi(PORTX, BitX) (PORTX |= (1 << BitX))
#define cbi(PORTX, BitX) (PORTX &= ~(1 << BitX))

void EXT_falling_timer_Init(void);

int main(void)
{
    EXT_falling_timer_Init();

    while (1)
    {
        if (TCNT0 >= 5)
        {
            sbi(PORTB, PB5);
        }
        else
        {
            cbi(PORTB, PB5);
        }
    }
}

void EXT_falling_timer_Init(void)
{
    cli();

    cbi(DDRD, PD4);
    sbi(PORTD, PD4);

    sbi(DDRB, PB5);

    TCCR0A = 0x00;
    TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);

    TCNT0 = 0x00;

    sei();
}