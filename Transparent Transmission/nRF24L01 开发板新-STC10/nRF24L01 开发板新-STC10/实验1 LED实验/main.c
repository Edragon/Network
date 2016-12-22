/*******************************************************/
/* ��   �ƣ�NRF24L01+��������Գ���LEDʵ�飩         */
/* ��   �ܣ����ͽ��ղ��Գ���                           */
/* ˵   �������¿�����1�İ�����KEY1��       		   */ 
/*          ����������2��LED1��LED3    				   */
/*          ���¿�����1�İ�����KEY2��          		   */
/*          ����������2��LED2��LED4    			       */     
/* ���ߣ�BQDZ     ����̳��http://bqdz.taobao.com��     */
/* ��ϵ��ʽ�� QQ :851968194     ������������2864       */
/*           �ֻ���15821472722���Ϻ���                 */
/*******************************************************/
#include "API.h"  	
uchar TX_ADDRESS[TX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //���͵�ַ
uchar RX_ADDRESS[RX_ADR_WIDTH]={0xFF,0xFF,0xFF,0xFF,0xFF}; //���յ�ַ
uchar   rate = 0x0F;    				    //2Mbs, 0dB  ���������濪��
sbit 	S1   = P3^2;						//������KEY1��
sbit 	S2	 = P3^3;						//������KEY2��
sbit 	LED1 = P0^3;						//LED1
sbit 	LED2 = P0^2;						//LED2
sbit 	LED3 = P0^1;						//LED3
sbit 	LED4 = P0^0;						//LED4
uchar rece_buf[32];							//���ռĴ���

void delay()
{
	uchar i,j;
	for(i=0;i<50;i++)
		for(j=0;j<200;j++);
}
void main()
{
	while(NRF24L01_Check()); // �ȴ���⵽NRF24L01������Ż�����ִ��
	NRF24L01_RT_Init(TX_PLOAD_WIDTH,TX_ADDRESS,TX_ADR_WIDTH,RX_ADDRESS,RX_ADR_WIDTH,rate);			
	while(1)
	{
		if(NRF_IRQ==0)	 	// �������ģ����յ�����
		{		
			if(NRF24L01_RxPacket(rece_buf)==0)
			{			   
				if(	rece_buf[1]=='1')		   	//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
					LED1=LED3=~LED1;
				if(	rece_buf[1]=='2')	 		//��1λ�Ժ����յ����������ݣ�rece_buf[0]������λ������
					LED2=LED4=~LED2;		
			}
		}
		if(S1==0)								//����S1����ASCII�� ��1��
		{
			rece_buf[1]='1';
			rece_buf[0]=1;	   					//һ��Ҫ����1���ֽڣ�rece_buf[0]=1
			SEND_BUF(rece_buf);			
			while(!S1);	
			delay();
		}
		if(S2==0)			  					//����S2���� ASCII�롰2��
		{
			rece_buf[1]='2';
			rece_buf[0]=1;	   					//һ��Ҫ����1���ֽڣ�rece_buf[0]=1
			SEND_BUF(rece_buf);			
			while(!S2);	
			delay();	
		}
	}
}



