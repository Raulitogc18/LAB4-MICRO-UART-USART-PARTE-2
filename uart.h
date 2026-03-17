#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

/* Inicialización */
void uart2_tx_init(void);
void uart2_rxtx_init(void);

/* Transmisión */
void uart2_write(int ch);
void uart2_write_str(char *str);

/* Recepción */
char uart2_read(void);

#endif /* UART_H_ */
