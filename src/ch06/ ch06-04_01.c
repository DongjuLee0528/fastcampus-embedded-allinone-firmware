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