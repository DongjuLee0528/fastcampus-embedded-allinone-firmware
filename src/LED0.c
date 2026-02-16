#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // PB5(디지털 13번 핀)를 출력으로 설정
    DDRB |= (1 << PB5);

    while (1) {
        // LED ON: PB5를 HIGH로 설정
        PORTB |= (1 << PB5);
        _delay_ms(1000);  // 1초 대기

        // LED OFF: PB5를 LOW로 설정
        PORTB &= ~(1 << PB5);
        _delay_ms(1000);  // 1초 대기
    }

    return 0;
}
