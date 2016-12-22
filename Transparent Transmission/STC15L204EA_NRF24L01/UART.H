#ifndef __UART_H
#define __UART_H

#define UART_BUAD                            115200

void uartInit(void);
void uartSendData(u8 ucData);
void uartSendString(char *s);

#endif