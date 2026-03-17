#include "uart.h"

#define GPIOAEN (1U<<0)
#define UART2EN (1U<<17)

#define CR1_TE (1U<<3)
#define CR1_RE (1U<<2)
#define CR1_UE (1U<<13)

#define SR_TXE (1U<<7)
#define SR_RXNE (1U<<5)

#define SYS_FREQ 16000000
#define UART_BAUDRATE 115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

void uart2_rxtx_init(void)
{
    /* Enable clock GPIOA */
    RCC->AHB1ENR |= GPIOAEN;

    /* PA2 -> TX */
    GPIOA->MODER &= ~(3U << 4);
    GPIOA->MODER |=  (2U << 4);

    GPIOA->AFR[0] &= ~(0xF << 8);
    GPIOA->AFR[0] |=  (7 << 8);

    /* PA3 -> RX */
    GPIOA->MODER &= ~(3U << 6);
    GPIOA->MODER |=  (2U << 6);

    GPIOA->AFR[0] &= ~(0xF << 12);
    GPIOA->AFR[0] |=  (7 << 12);

    /* Enable USART2 clock */
    RCC->APB1ENR |= UART2EN;

    /* Baudrate */
    uart_set_baudrate(USART2, SYS_FREQ, UART_BAUDRATE);

    /* Enable TX RX */
    USART2->CR1 = CR1_TE | CR1_RE;

    /* Enable UART */
    USART2->CR1 |= CR1_UE;
}

void uart2_write(int ch)
{
    while(!(USART2->SR & SR_TXE)){}
    USART2->DR = (ch & 0xFF);
}

void uart2_write_str(char *str)
{
    while(*str)
    {
        uart2_write(*str++);
    }
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
    USARTx->BRR = (PeriphClk + (BaudRate/2U)) / BaudRate;
}
