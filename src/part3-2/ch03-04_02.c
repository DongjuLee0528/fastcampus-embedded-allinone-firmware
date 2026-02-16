#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define PORTB_REG 0x23 // #difined 통하면 PORTB_REG이름을 0x23 상수값으로 치환 가능

struct io_port{
    unsigned char pin; // 8bit
    uint8_t ddr;  //0x24
    uint8_t port; //0x25
    /* data */
};
int main(void){
    struct io_port *portB = (void *)PORTB_REG; //(void *) 포인터를 사용해서 상수값을 주소 값으로 변경 한 후 매칭 진행
    portB->ddr = 0x20;

    while (1)
    {
        portB->port = 0x20;
        _delay_ms(1000);
        portB->port = 0x00;
        _delay_ms(1000);
    }

    
}
