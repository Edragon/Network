/******************************************************************************/
/*                        -- 深圳安信可科技有限公司 --                        */
/*
//  文件名：GPIO.h                                                              
//  说明：与GPIO相关宏定义                                                                  
//  编写人员：Wu                                                                   
//  编写日期：2012年11月12日                                                              
//  程序维护：
//  维护记录：
//
//                                                          
*/ 
// 免责声明：该程序仅用于学习与交流 
// (c) Anxinke Corporation. All rights reserved.                                                               
/******************************************************************************/
#ifndef __GPIO_H
#define __GPIO_H

#define KEY                                  P30
#define KEY2                                 P31

#define led                                  P16
#define led2                                 P35

#define UART_TX_PIN                          P31
#define UART_TX_SET(n)                       UART_TX_PIN = n
#define UART_TX_HIGH()                       UART_TX_SET(1)
#define UART_TX_LOW()                        UART_TX_SET(0)
#define UART_TX_FLIP()                       UART_TX_PIN = !UART_TX_PIN

#define UART_RX_PIN                          P30
#define UART_RX_SET(n)                       UART_RX_PIN = n
#define UART_RX_HIGH()                       UART_RX_SET(1)
#define UART_RX_LOW()                        UART_RX_SET(0)
#define UART_RX_FLIP()                       UART_RX_PIN = !UART_RX_PIN









#endif 





