/****************POWSOS__430******************************
�����ܣ�24L01����ģ����1s����һ������
----------------------------------------------------------
*********************************************************/
#include  <msp430x14x.h>
#include "24l01.h"
extern unsigned char TestBuf;
/*******************************************
�������ƣ�Init_Clock
��    �ܣ�����ϵͳʱ��ѡ���ⲿ����8M
��    ������
����ֵ  ����
********************************************/
void Init_Clock(void)
{
    unsigned char i;
  /*------ѡ��ϵͳ��ʱ��Ϊ8MHz-------*/
    BCSCTL1 &= ~XT2OFF;                 //��XT2��Ƶ��������
    do
    {
        IFG1 &= ~OFIFG;                 //�������ʧ�ܱ�־
        for (i = 0xFF; i > 0; i--);     //�ȴ�8MHz��������
    }
    while ((IFG1 & OFIFG));             //����ʧЧ��־��Ȼ���ڣ�
    BCSCTL2 |= SELM_2 + SELS;           //MCLK��SMCLKѡ���Ƶ����
}

int main(void )
{

    WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT 
    Init_Clock();
    nRF24L01_IO_set();
    NRF_Check();
    nRF24L01_Init(nRF_TX_Mode);

    while(1)
    {  
      nRF24L01_Send();//ѭ�����͡��Ϻ���Ƕ���ӡ�
     delay_100ms(10); 
    }
    
}

