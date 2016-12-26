#include "sprintf.h"

void uart_putc(unsigned char);

void sprintf(const unsigned char *str)
{
 while (*str) uart_putc(*str++);
}

void dprintf(unsigned char n)
{
 unsigned char cnt=0,num=100;
 while (n>=num) {n-=num;cnt++;}
 if (cnt) uart_putc('0'+cnt);

 num=10;cnt=0;
 while (n>=num) {n-=num;cnt++;}
 if (cnt) uart_putc('0'+cnt);

 uart_putc('0'+n);
}

void hprintf(unsigned char n)
{
 unsigned char c=n>>4;

 if (c<10) uart_putc('0'+c); else uart_putc('A'-10+c);
 c=n&0xF;
 if (c<10) uart_putc('0'+c); else uart_putc('A'-10+c);
}

