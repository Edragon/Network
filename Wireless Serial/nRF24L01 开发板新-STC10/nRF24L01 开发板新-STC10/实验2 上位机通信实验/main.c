/*******************************************************/
/* ��   �ƣ�NRF24L01+��������Գ�����λ��ͨѶ������̣�*/
/* ��   �ܣ������巢�͵��Խ��գ����Է��Ϳ��������     */
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
sbit     P14 = P1^4;    
sbit     P15 = P1^5;    
sbit     P16 = P1^6;    
sbit     P17 = P1^7;    
uchar GetKeyChar()
{
	
	P1=0xfe;
	if(!P14){return '1';}  
	if(!P15){return '2';}   
	if(!P16){return '3';}  
	if(!P17){return 'A';} 

	P1=0xfd;
	if(!P14){return '4';}    
	if(!P15){return '5';}   
	if(!P16){return '6';}   
	if(!P17){return 'B';} 


	P1=0xfb;
	if(!P14){return '7';}   
	if(!P15){return '8';}    
	if(!P16){return '9';}    
	if(!P17){return 'C';} 

	P1=0xf7;
	if(!P14){return '*';}   
	if(!P15){return '0';}   
	if(!P16){return '#';}    
	if(!P17){return 'D';}   
	
	return 99;          //û�а���������
}
void main()
{
	uchar strKeyCode;
	while(NRF24L01_Check()); // �ȴ���⵽NRF24L01������Ż�����ִ��
	NRF24L01_RT_Init(TX_PLOAD_WIDTH,TX_ADDRESS,TX_ADR_WIDTH,RX_ADDRESS,RX_ADR_WIDTH,rate);			
	while(1)
	{
		strKeyCode=GetKeyChar();
		if(strKeyCode!=99)
		{
			rece_buf[1]=0xC4;					//��
			rece_buf[2]=0xFA;					//��
			rece_buf[3]=0xB0;					//��
			rece_buf[4]=0xB4;					//��
			rece_buf[5]=0xCF;					//��
			rece_buf[6]=0xC2;					//��
			rece_buf[7]=0xB5;					//��
			rece_buf[8]=0xC4;					//��
			rece_buf[9]=0xCA;					//��
			rece_buf[10]=0xC7;					//��
			rece_buf[11]=0xA3;					//��
			rece_buf[12]=0xBA;					//��
			
			rece_buf[13]=strKeyCode;

			rece_buf[14]=0x0D;					//��
			rece_buf[15]=0x0A;					//��

			rece_buf[0]=15;	   					//һ��Ҫ����15���ֽڣ�rece_buf[0]=15   ���Ǻͱ���USBתnRF24L01ģ��ͨ��Э��
			SEND_BUF(rece_buf);
			delay_us(20000); 		
		}
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
			rece_buf[0]=1;	   					//һ��Ҫ����1���ֽڣ�rece_buf[0]=1	 ���Ǻͱ���USBתnRF24L01ģ��ͨ��Э��
			SEND_BUF(rece_buf);
			delay_us(10000);
			while(!S1);	
		}
		if(S2==0)			  					//����S2���� ���Ϻ���Ƕ���ӡ�
		{ 			
			rece_buf[1]=0xc9;					//��
			rece_buf[2]=0xcf;					//��
			rece_buf[3]=0xba;					//��
			rece_buf[4]=0xa3;					//��
			rece_buf[5]=0xb1;					//��
			rece_buf[6]=0xa6;					//��
			rece_buf[7]=0xc7;					//Ƕ
			rece_buf[8]=0xb6;					//Ƕ
			rece_buf[9]=0xb5;					//��
			rece_buf[10]=0xe7;					//��
			rece_buf[11]=0xd7;					//��
			rece_buf[12]=0xd3;					//��
			rece_buf[0]=12;						//һ��Ҫ����12���ֽڣ�rece_buf[0]������12 ���Ǻͱ���USBתnRF24L01ģ��ͨ��Э��
			SEND_BUF(rece_buf);
			delay_us(20000);
			while(!S2);	
		}
	}
}



