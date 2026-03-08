#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#define sbi(PORTX, BitX) (PORTX |= (1 << BitX))
#define cbi(PORTX, BitX) (PORTX &= ~(1 << BitX))

volatile uint8_t counter = 0;

void overflow_timer_init(void);

ISR(TIMER0_OVF_vect) //timer0 overflow 인터럽트 서비스 루틴
{
    if (counter >= 62){ //62 * 256 = 15872, 약 1초
        sbi(PORTD, 6); // PD6 핀 HIGH
        counter = 0;
    }
    else{
        cbi(PORTD, 6); // PD6 핀 LOW
        counter++;
    }
}

int main(void){
    overflow_timer_init();

    while (1)
    {
       // 메인 루프에서는 아무것도 하지 않음
    }
}

void overflow_timer_init(void)
{
    cli(); //인터럽트 비활성화
   
    DDRD |=(1 <<PD6); //PD6 핀을 출력으로 설정
    PORTD &= ~(1 << PD6); //초기값 LOW

    TCCR0A = 0x00; //Normal mode
    TCCR0B = (1 << CS02) | (1 << CS00); //1024분주 (클럭 = 16MHZ / 1024 = 15625Hz)

    TCNT0 = 0;//타이머 카운터 초기화
    TIMSK0 = (1 << TOIE0);

    sei();

}