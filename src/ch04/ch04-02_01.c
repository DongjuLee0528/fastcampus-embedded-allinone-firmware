#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX, BITX) (PORTX |= (1 << BITX))

SIGNAL(INT1_vect){ //ISR 인터럽트 루트
    //스위치가 눌렸을 때 인터럽트가 발생하여 이 루트로 들어오게 된다
    PORTB = 0x20;
    _delay_ms(200);
}

int main(void)
{
    sbi(SREG, 7); //매크로 함수 사용 SREG I 비트 1로 셋팅

    sbi(EIMSK, INT1); //EIMSK, INT1 1로 셋팅 = EIMSK = 0x02
    EICRA =0x08; //INT1 1 폴링 엣지모드 셋팅 , sbi(EICRA, ISC11); 

    DDRB = 0x20; // 출력 13번 핀
    DDRD = 0x00; // 입력으로 사용 ( INT1 = 3번핀, ㅑㅜ썌 = 2번핀 )
    PORTD = 0x08; // 풀업 저항

    while(1){
        PORTB = 0x00; //polling
    }
}