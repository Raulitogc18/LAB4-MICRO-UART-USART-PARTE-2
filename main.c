#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include "uart.h"

#define STX 0x02
#define ETX 0x03

void send_frame(char *payload);

int main(void)
{
    int counter = 0;
    char msg[32];

    uart2_rxtx_init();

    while(1)
    {
        sprintf(msg,"CNT=%06d",counter++);

        send_frame(msg);

        for(volatile int i=0;i<2000000;i++);
    }
}

void send_frame(char *payload)
{
    uint8_t len = strlen(payload);
    uint8_t chk = len;

    uart2_write(STX);
    uart2_write(len);

    for(int i=0;i<len;i++)
    {
        uart2_write(payload[i]);
        chk ^= payload[i];
    }

    uart2_write(chk);
    uart2_write(ETX);
}
