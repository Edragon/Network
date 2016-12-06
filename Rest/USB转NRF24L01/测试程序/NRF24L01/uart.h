#ifndef __UART_H
#define __UART_H

#define USART_REC_LEN     RX_PLOAD_WIDTH

void UART1_Configuration(void);
void UART1_SendByte(uchar data_8);
void UART1_SendString(uchar *p);

extern uchar USART_RX_STA;
extern uchar USART_RX_BUF[];

#endif