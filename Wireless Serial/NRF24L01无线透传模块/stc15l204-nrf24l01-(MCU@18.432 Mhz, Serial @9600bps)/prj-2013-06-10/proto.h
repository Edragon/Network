void UART_INIT(void);
void tm0() __interrupt 1 __using 1;
void uart_putc(unsigned char);
#define uart_put_char uart_putc
