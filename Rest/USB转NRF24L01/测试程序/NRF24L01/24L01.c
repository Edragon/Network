#include"stm8s.h"
#include"stm8s903k.h"
#include"stm8s903k3.h"
#include"main.h"
#include"24L01.h"

const uchar TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ
const uchar RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //���͵�ַ

//��ʼ��SPI
void MY_SPI_Init(void)
{
	SPI_DeInit();
	
	SPI_Init(SPI_FIRSTBIT_MSB, 
					 SPI_BAUDRATEPRESCALER_2,
					 SPI_MODE_MASTER,
					 SPI_CLOCKPOLARITY_LOW, 
					 SPI_CLOCKPHASE_1EDGE, 													
					 SPI_DATADIRECTION_2LINES_FULLDUPLEX,
					 SPI_NSS_SOFT, 
					 0x07);
				 
	SPI_Cmd(ENABLE);//ʹ��SPI
	
	GPIO_Init(IOPORT_SPI_CS,PIN_SPI_CS,GPIO_MODE_OUT_PP_HIGH_FAST);//SPI_CS���ų�ʼ��Ϊ�������
	SPI_CS_HIGH;//ȡ��SPI����
}

//SPI��д����
//dat:׼�����͵�ֵ
//����ֵ����ȡ����ֵ
uchar SPI_ReadWriteByte(uchar dat)
{
	while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
	SPI_SendData(dat);
	
	while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
	return SPI_ReceiveData();
}

//NRF24L01��ʼ��
void NRF24L01_Init(void)
{
	GPIO_Init(IOPORT_24L01_CE,PIN_24L01_CE,GPIO_MODE_OUT_PP_HIGH_FAST);//NRF24L01_CE��ʼ��Ϊ�������
	GPIO_Init(IOPORT_24L01_IRQ,PIN_24L01_IRQ, GPIO_MODE_IN_PU_NO_IT);//IRQ��������
	
	MY_SPI_Init();
	
	NRF24L01_CE_LOW;//NRF24L01Ƭѡʹ��
	SPI_CS_HIGH;		//SPIƬѡȡ��
}

//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
uchar NRF24L01_Check(void)
{
	uchar buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	uchar i;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24L01����	
	return 0;		 //��⵽24L01
}	 	 

//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
uchar NRF24L01_Write_Reg(uchar reg,uchar value)
{
	uchar status;	
	
	SPI_CS_LOW;                 //ʹ��SPI����
	status =SPI_ReadWriteByte(reg);//���ͼĴ����� 
	SPI_ReadWriteByte(value);      //д��Ĵ�����ֵ
	SPI_CS_HIGH;                 //��ֹSPI����	
	
	return(status);       			//����״ֵ̬
}

//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
uchar NRF24L01_Read_Reg(uchar reg)
{
	uchar reg_val;	   
	
 	SPI_CS_LOW;          //ʹ��SPI����		
	SPI_ReadWriteByte(reg);   //���ͼĴ�����
	reg_val=SPI_ReadWriteByte(0XFF);//��ȡ�Ĵ�������
	SPI_CS_HIGH;          //��ֹSPI����		
	
	return(reg_val);           //����״ֵ̬
}	

//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
uchar NRF24L01_Read_Buf(uchar reg,uchar *pBuf,uchar len)
{
	uchar status,u8_ctr;
	
	SPI_CS_LOW;            //ʹ��SPI����
	status=SPI_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��), ����ȡ״ֵ̬   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI_ReadWriteByte(0XFF);//��������
	SPI_CS_HIGH;       //�ر�SPI����
		
	return status;        //���ض�����״ֵ̬	   
}
	//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
uchar NRF24L01_Write_Buf(uchar reg, uchar *pBuf, uchar len)
{
	uchar status,u8_ctr;
	
 	SPI_CS_LOW;         //ʹ��SPI����
	status = SPI_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��), ����ȡ״ֵ̬
	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI_ReadWriteByte(*pBuf++); //д������	 
	SPI_CS_HIGH;       //�ر�SPI����
	
	return status;          //���ض�����״ֵ̬
}	

//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
uchar NRF24L01_TxPacket(uchar *txbuf)
{
	uchar sta;
	
	NRF24L01_CE_LOW;
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//
 	NRF24L01_CE_HIGH;//��������	   
	while(NRF24L01_IRQ!=0);//�ȴ��������
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_OK)//�������
	{
		return TX_OK;
	}
	return 0xff;//����ԭ����ʧ��
}

//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:0��������ɣ��������������
uchar NRF24L01_RxPacket(uchar *rxbuf)
{
	uchar sta;		    							   
	
	sta=NRF24L01_Read_Reg(STATUS);  //��ȡ״̬�Ĵ�����ֵ    
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //
	if(sta&RX_OK)//���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//���RX FIFO�Ĵ��� 
		return 0; 
	}	   
	return 1;//û�յ��κ�����
}			

//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_CE_LOW;
	
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    	//ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);	//ʹ��ͨ��0�Ľ��յ�ַ  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	    	//����RFͨ��Ƶ��		  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);	//����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);		//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	
  NRF24L01_CE_HIGH; //CEΪ��,�������ģʽ 
}			

//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE_LOW;

	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ  
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //����TX�������,0db����,2Mbps,���������濪��   
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,
	
	NRF24L01_CE_HIGH;
	delay_10us(5);
}