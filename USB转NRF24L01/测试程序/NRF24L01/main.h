#ifndef __MAIN_H
#define __MAIN_H

#define uint unsigned int
#define uchar unsigned char

#define  MODE_CTRL_PIN    GPIO_ReadInputPin(GPIOD, GPIO_PIN_1)
													//这个引脚如果要更改，需改动两处，还有一处在主函数中
#define MODE_TX 0
#define MODE_RX 1

void SysClkInit(void);
void delay_ms(uint z);
void delay_10us(uint z);
uchar PinLevel_Check(void);
void Mode_Config(uchar sta);
void NRF24L01_Status_RX(void);
void NRF24L01_Status_TX(void);

#endif