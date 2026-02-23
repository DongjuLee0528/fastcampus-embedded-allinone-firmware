#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX, BitX) ( PORTX |= (1 << BitX) )

SIGNAL(INT1_vect)
{
    PORTB = 0x20;
    _delay_ms(200);
}

int main(void)
{
    sbi(SREG, 7); // SREG I 비트 1로 셋팅 (이 부분이 ?로 되어있었을 겁니다)

    sbi(EIMSK, INT1); // EIMSK INT1 1로 셋팅 = EIMSK = 0x02;
    EICRA = 0x08; // INT1 폴링 엣지 모드 셋팅 , sbi(EICRA , ISC11);

    DDRB = 0x20; // 출력 13번핀
    DDRD = 0x00; // 입력으로 사용 ( INT1 = 3번핀, INT0 = 2번핀 )
    PORTD = 0x08; // 풀업저항

    while (1)
    {
        PORTB = 0x00; //polling
    }
}