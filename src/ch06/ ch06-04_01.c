#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#define sbi(PORTX, BitX) (PORTX |= (1 << BitX))
#define cbi(PORTX, BitX) (PORTX &= ~(1 << BitX))

volatile uint8_t counter = 0;

void overflow_timer_init(void);

ISR(TIMER0_OVF_vect)
{
    if (counter >= 62){
        sbi(PORTD, 6);
        counter = 0;
    }
    else{
        cbi(PORTD, 6);
        counter++;
    }
}

int main(void){
    overflow_timer_init();

    while (1)
    {
       
    }
}

void overflow_timer_init(void)
{
    cli();
   
    DDRD |=(1 <<PD6);
    PORTD &= ~(1 << PD6);

    TCCR0A = 0x00;
    TCCR0B = (1 << CS02) | (1 << CS00); 

    TCNT0 = 0;
    TIMSK0 = (1 << TOIE0);
    
    sei();

}