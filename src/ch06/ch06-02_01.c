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
        // 타이머 값이 5를 초과했는지 확인 (즉, falling edge 5번)
        if (TCNT0 >= 5)
        {
            sbi(PORTB, PB5);  // LED ON (예: 13번 핀)
        }
        else
        {
            cbi(PORTB, PB5);  // LED OFF
        }
    }
}

void EXT_falling_timer_Init(void)
{
    cli();  // 전역 인터럽트 비활성화

    // PD4를 입력으로 설정하고 내부 풀업 저항 활성화
    cbi(DDRD, PD4);   // 입력
    sbi(PORTD, PD4);  // 풀업

    // PB5를 출력으로 설정 (LED 연결)
    sbi(DDRB, PB5);

    // Timer0 설정 - 외부 클럭 소스 (T0 핀 = PD4) falling edge
    // CS02=1, CS01=1, CS00=1 => 0b111 = Falling Edge 외부 클럭
    TCCR0A = 0x00;
    TCCR0B = (1 << CS02) | (1 << CS01) | (1 << CS00);

    TCNT0 = 0x00;  // 초기화

    sei();  // 전역 인터럽트 활성화
}