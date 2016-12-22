/*******************************************************/
/* ��   �ƣ�NRF24L01+��������Գ���DS18B20�¶Ȳɼ�ʵ�飩*/
/* ��   �ܣ����ͽ��ղ��Գ���                           */
/* ˵   ����������ɼ��¶�ͨ�����ߴ��ڷ�������         */
/* ���ߣ�BQDZ     ����̳��http://bqdz.taobao.com��     */
/* ��ϵ��ʽ�� QQ :851968194     ������������2864       */
/*           �ֻ���15821472722���Ϻ���                 */
/*******************************************************/
#include "DS18B20.h"  	
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

void delay_main(uint t)
{
	uint k;
	while(t--)
	for(k=0;k<200;k++);
}
void main()
{
	uint num;
	uint temp;
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
		delay_main(10);
		num++;
		if(num>=100)
		{
			num=0;
			temp=ReadTemperature();
			rece_buf[1]=0xB5;					//��
			rece_buf[2]=0xB1;					//��
			rece_buf[3]=0xC7;					//ǰ
			rece_buf[4]=0xB0;					//ǰ
			rece_buf[5]=0xCE;					//��
			rece_buf[6]=0xC2;					//��
			rece_buf[7]=0xB6;					//��
			rece_buf[8]=0xC8;					//��
			rece_buf[9]=0xA3;					//��
			rece_buf[10]=0xBA;					//��
			rece_buf[11]=temp/1000+0x30;				
			rece_buf[12]=temp%1000/100+0x30;				
			rece_buf[13]=temp%100/10+0x30;				
			rece_buf[14]='.';					
			rece_buf[15]=temp%10+0x30;	
			rece_buf[16]=0x0D;		 //�س�
			rece_buf[17]=0x0A;		 //�س�
			rece_buf[0]=17;
			SEND_BUF(rece_buf);			
		}
	}
}



