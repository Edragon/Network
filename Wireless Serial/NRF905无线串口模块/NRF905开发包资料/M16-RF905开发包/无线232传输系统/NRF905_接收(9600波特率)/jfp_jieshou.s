	.module jfp_jieshou.c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
_TxAddress::
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.dbsym e TxAddress _TxAddress A[4:4]c
_RFConf::
	.blkb 2
	.area idata
	.byte 0,'L
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.blkb 2
	.area idata
	.byte 12,'D
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.blkb 2
	.area idata
	.byte 32,32
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.blkb 1
	.area idata
	.byte 'X
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.dbsym e RFConf _RFConf A[11:11]c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	.dbfunc e Delay _Delay fV
;              i -> R20,R21
;              x -> R16,R17
	.even
_Delay::
	xcall push_gset1
	.dbline -1
	.dbline 86
; //ICC-AVR application builder : 2007-8-11 20:37:32
; // Target : M16
; // Crystal: 8.0000Mhz
; #include <iom16v.h>
; #include <macros.h>
; #define uint  unsigned int
; #define uchar unsigned char
; //---------------------------------ģʽ���ƶ���---------------------------------
; //#define  nrf905_TX_EN	  PB0	    //���1
; #define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
; #define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
; //#define  nrf905_TRX_CE  PD4 	    //���1
; #define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4);   
; #define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4); 
; //#define  nrf905_PWR     PB1 	    //���1
; #define   Hign_nrf905_PWR    PORTB |= (1 << PB1);   
; #define   Low_nrf905_PWR     PORTB &= ~(1 << PB1); 
; //--------------------------------NRF905-SPI�ڽӿڶ���--------------------------
; //#define  nrf905_MISO	  PB6   	//����0
; //#define  nrf905_MOSI    PB5	    //���1
; //#define  nrf905_SCK     PB7	    //���1
; #define   Low_nrf905_SCK     PORTB &= ~(1 << PB7); 
; //#define  nrf905_CSN     PB4		//���1		
; #define   Hign_nrf905_CSN    PORTB |= (1 << PB4);   
; #define   Low_nrf905_CSN     PORTB &= ~(1 << PB4); 						
; //-------------------------------״̬�����-------------------------------------
; //#define  nrf905_CD      PD3	    //����0
; #define   Hign_nrf905_CD    PORTD |= (1 << PD3);   
; #define   Low_nrf905_CD     PORTD &= ~(1 << PD3); 
; #define   Read_nrf905_CD    PINB & (1 << PD4);
; //#define  nrf905_AM      PB3	    //����0
; #define   Hign_nrf905_AM    PORTB |= (1 << PB3);   
; #define   Low_nrf905_AM     PORTB &= ~(1 << PB3); 
; #define   Read_nrf905_AM    PINB & (1 << PB3);
; //#define  nrf905_DR      PB2  		//����0
; #define   Hign_nrf905_DR     PORTB |= (1 << PB2);   
; #define   Low_nrf905_DR     PORTB &= ~(1 << PB2); 
; #define   Read_nrf905_DR    PINB & (1 << PB2);   
; //-------------------------------BELL������-------------------------------------
; #define   Hign_BELL  PORTD |= (1 << PD5);   
; #define   Low_BELL     PORTD &= ~(1 << PD5); 
; //-------------------------------JDQ�̵���--------------------------------------
; #define   Hign_JDQ  PORTD |= (1 << PD7)
; #define   Low_JDQ     PORTD &= ~(1 << PD7) 
; //----------------------------------NRF905-SPIָ��------------------------------
; #define WC	0x00
; #define RRC	0x10
; #define WTP	0x20
; #define RTP	0x21
; #define WTA	0x22
; #define RTA	0x23
; #define RRP	0x24
; //---------------------------------��������-------------------------------------
; uchar TxRxBuffer[32];
; //----------------------------------���յ�ַ------------------------------------
; uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
; //----------------------------------�Ĵ�������----------------------------------
; uchar RFConf[11]=
; {
;   0x00,                            //��������//
;   0x4c,                           //CH_NO,����Ƶ����430MHZ
;   0x0C,                          //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
;   0x44,                         //��ַ������ã�Ϊ4�ֽ�
;   0x20,0x20,                   //���շ�����Ч���ݳ���Ϊ32�ֽ�
;   0xCC,0xCC,0xCC,0xCC,        //���յ�ַ
;   0x58,                      //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
; };
; //----------------------------------��������------------------------------------
; void Delay(uint x);						       //��ʱ�ӳ���																							
; void Spi_initial();                            //SPI��ʼ��
; uchar SpiReadSpiWrite(unsigned char cData);    //SPI��д�ӳ���
; void system_Init(void);		   				   //ϵͳ��ʼ��
; void Config905(void);						   //NRF905��ʼ���ӳ���
; void TxPacket(void);						
; void SetTxMode(void);						   //���ݷ���
; void SetRxMode(void);						   //
; void TX(void);
; unsigned char CheckDR(void);
; void RxPacket(void);
; void  RX(void);
; //------------------------------------------------------------------------------
; void StartUART(void);
; void R_S_Byte(uchar R_Byte);
; //----------------------------------100us��ʱ�ӳ���-----------------------------
; void Delay(uint x)
; {
	xjmp L3
L2:
	.dbline 89
	clr R20
	clr R21
	xjmp L8
L5:
	.dbline 89
L6:
	.dbline 89
	subi R20,255  ; offset = 1
	sbci R21,255
L8:
	.dbline 89
	cpi R20,80
	ldi R30,0
	cpc R21,R30
	brlo L5
L3:
	.dbline 88
; 	uint i;
; 	while(x--)
	movw R2,R16
	subi R16,1
	sbci R17,0
	tst R2
	brne L2
	tst R3
	brne L2
X0:
	.dbline -2
L1:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbsym r x 16 i
	.dbend
	.dbfunc e Spi_initial _Spi_initial fV
	.even
_Spi_initial::
	.dbline -1
	.dbline 93
; 	for(i=0;i<80;i++);
; }
; //----------------------------------SPI��ʼ��-----------------------------------
; void Spi_initial()
; {
	.dbline 94
; 	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);// ����ģʽ��fck/16, SPI��ʽ0
	ldi R24,80
	out 0xd,R24
	.dbline -2
L9:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e SpiReadSpiWrite _SpiReadSpiWrite fc
;          cData -> R16
	.even
_SpiReadSpiWrite::
	.dbline -1
	.dbline 98
; }
; //---------------------------------SPI��д����----------------------------------	
; uchar SpiReadSpiWrite(unsigned char cData)
; {
	.dbline 99
; 	SPDR = cData;
	out 0xf,R16
L11:
	.dbline 101
	.dbline 101
L12:
	.dbline 100
; 	while(!(SPSR & (1<<SPIF) ))  // �ȴ�SPI�������
	sbis 0xe,7
	rjmp L11
	.dbline 101
; 	{};			
	.dbline 102
; 	return SPDR;
	in R16,0xf
	.dbline -2
L10:
	.dbline 0 ; func end
	ret
	.dbsym r cData 16 c
	.dbend
	.dbfunc e system_Init _system_Init fV
	.even
_system_Init::
	.dbline -1
	.dbline 106
; }
; //--------------------------------ϵͳ״̬��ʼ��--------------------------------
; void system_Init(void)			
; {
	.dbline 108
; 
;    	Hign_nrf905_CSN;			// SPIʹ��
	sbi 0x18,4
	.dbline 108
	.dbline 109
; 	Low_nrf905_SCK;				
	cbi 0x18,7
	.dbline 109
	.dbline 110
; 	Low_nrf905_DR;				// DR=0
	cbi 0x18,2
	.dbline 110
	.dbline 111
; 	Low_nrf905_AM;				// AM=0
	cbi 0x18,3
	.dbline 111
	.dbline 112
; 	Low_nrf905_CD;				// CD=0
	cbi 0x12,3
	.dbline 112
	.dbline 113
; 	Hign_nrf905_PWR;		    // PWR=1
	sbi 0x18,1
	.dbline 113
	.dbline 114
; 	Low_nrf905_TRX_CE;			// nrf905_TRX_CE=0
	cbi 0x12,4
	.dbline 114
	.dbline 115
; 	Low_nrf905_TX_EN ;			// nrf905_TX_EN=0
	cbi 0x18,0
	.dbline 115
	.dbline -2
L14:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Config905 _Config905 fV
;              i -> R20
	.even
_Config905::
	xcall push_gset1
	.dbline -1
	.dbline 119
; }
; //--------------------------------NRF905�Ĵ�����ʼ������------------------------
; void Config905(void)
; {
	.dbline 121
; 	uchar i;
; 	Low_nrf905_CSN;				//SPIʹ��											
	cbi 0x18,4
	.dbline 121
	.dbline 122
; 	Delay(1);				   
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 123
; 	for (i=0;i<11;i++)			//�NRF905������
	clr R20
	xjmp L19
L16:
	.dbline 124
	.dbline 125
	ldi R24,<_RFConf
	ldi R25,>_RFConf
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 126
L17:
	.dbline 123
	inc R20
L19:
	.dbline 123
	cpi R20,11
	brlo L16
	.dbline 127
; 	{
; 	 SpiReadSpiWrite(RFConf[i]);
; 	}
; 	Hign_nrf905_CSN;					// Disable Spi
	sbi 0x18,4
	.dbline 127
	.dbline -2
L15:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbend
	.dbfunc e TxPacket _TxPacket fV
;              i -> R20
	.even
_TxPacket::
	xcall push_gset1
	.dbline -1
	.dbline 131
; }
; //--------------------------------NRF905�������ݴ��----------------------------
; void TxPacket(void)
; {
	.dbline 133
; 	uchar i;
; 	Low_nrf905_CSN;		   				// ʹ��Spi�������nrf905���ж�д����
	cbi 0x18,4
	.dbline 133
	.dbline 134
; 	Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 135
; 	SpiReadSpiWrite(WTP);				// д����ǰ��дд��������
	ldi R16,32
	xcall _SpiReadSpiWrite
	.dbline 136
; 	for (i=0;i<32;i++)
	clr R20
	xjmp L24
L21:
	.dbline 137
	.dbline 138
	ldi R24,<_TxRxBuffer
	ldi R25,>_TxRxBuffer
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 139
L22:
	.dbline 136
	inc R20
L24:
	.dbline 136
	cpi R20,32
	brlo L21
	.dbline 140
; 	{
; 	SpiReadSpiWrite(TxRxBuffer[i]);		// �����͵�32�ֽ�����
; 	}						
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 140
	.dbline 141
; 	Delay(1);							// �ر�Spi���������nrf905���ж�д����
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 142
; 	Low_nrf905_CSN;						// ʹ��Spi
	cbi 0x18,4
	.dbline 142
	.dbline 143
; 	SpiReadSpiWrite(WTA);				// д��ַǰ������д��ַ����
	ldi R16,34
	xcall _SpiReadSpiWrite
	.dbline 144
; 	for (i=0;i<4;i++)					// д��4 bytes ���յ�ַ
	clr R20
	xjmp L28
L25:
	.dbline 145
	.dbline 146
	ldi R24,<_TxAddress
	ldi R25,>_TxAddress
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 147
L26:
	.dbline 144
	inc R20
L28:
	.dbline 144
	cpi R20,4
	brlo L25
	.dbline 148
; 	{
; 	SpiReadSpiWrite(TxAddress[i]);
; 	}
; 	Hign_nrf905_CSN;					// �ر�Spi
	sbi 0x18,4
	.dbline 148
	.dbline 149
; 	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	sbi 0x12,4
	.dbline 149
	.dbline 150
; 	Delay(1);							// �ȴ�DR���
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 151
; 	Low_nrf905_TRX_CE;					// ����TRX_CE=0
	cbi 0x12,4
	.dbline 151
	.dbline -2
L20:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbend
	.dbfunc e SetTxMode _SetTxMode fV
	.even
_SetTxMode::
	.dbline -1
	.dbline 155
; }
; //------------------------------���÷���ģʽ------------------------------------
; void SetTxMode(void)
; {
	.dbline 156
; 	Low_nrf905_TRX_CE;				//
	cbi 0x12,4
	.dbline 156
	.dbline 157
; 	Hign_nrf905_TX_EN;				//����ʹ��
	sbi 0x18,0
	.dbline 157
	.dbline 158
; 	Delay(2); 				// delay for mode change(>=650us)
	ldi R16,2
	ldi R17,0
	xcall _Delay
	.dbline -2
L29:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e SetRxMode _SetRxMode fV
	.even
_SetRxMode::
	.dbline -1
	.dbline 162
; }
; //------------------------------���ý���ģʽ����--------------------------------
; void SetRxMode(void)
; {
	.dbline 163
; 	Low_nrf905_TX_EN;
	cbi 0x18,0
	.dbline 163
	.dbline 164
; 	Hign_nrf905_TRX_CE;
	sbi 0x12,4
	.dbline 164
	.dbline 165
; 	Delay(10); 					// delay for mode change(>=650us)
	ldi R16,10
	ldi R17,0
	xcall _Delay
	.dbline -2
L30:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e TX _TX fV
	.even
_TX::
	.dbline -1
	.dbline 169
; }
; //------------------------------��������----------------------------------------
; void TX(void)
; {
	.dbline 170
;      SetTxMode();	   // Set nRF905 in Tx mode
	xcall _SetTxMode
	.dbline 171
; 	 TxPacket();			   // Send data by nRF905
	xcall _TxPacket
	.dbline -2
L31:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e CheckDR _CheckDR fc
	.even
_CheckDR::
	.dbline -1
	.dbline 175
; }
; //-----------------------------�ж��Ƿ��յ�����---------------------------------
; unsigned char CheckDR(void)		//����Ƿ��������ݴ��� 
; {
	.dbline 176
; 	if (PINB & (1 << PB2))
	sbis 0x16,2
	rjmp L33
	.dbline 177
; 	{
	.dbline 178
; 		return 1; 	 	  		//�յ�����
	ldi R16,1
	xjmp L32
L33:
	.dbline 181
; 	}
; 	else
; 	{
	.dbline 182
; 		return 0;
	clr R16
	.dbline -2
L32:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e RxPacket _RxPacket fV
;              i -> R20
	.even
_RxPacket::
	xcall push_gset1
	.dbline -1
	.dbline 187
; 	}
; }
; //-----------------------------------���������ݰ�-------------------------------
; void RxPacket(void)							//������
; {
	.dbline 189
; 	uchar i;
;     Low_nrf905_TRX_CE;
	cbi 0x12,4
	.dbline 189
	.dbline 190
; 	Low_nrf905_CSN;						    // ʹ��SPI
	cbi 0x18,4
	.dbline 190
	.dbline 191
;     Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 192
; 	SpiReadSpiWrite(RRP);				   // д�����ݽ��ջ�������������
	ldi R16,36
	xcall _SpiReadSpiWrite
	.dbline 193
; 	for (i = 0 ;i < 32 ;i++)
	clr R20
	xjmp L39
L36:
	.dbline 194
	.dbline 195
	clr R16
	xcall _SpiReadSpiWrite
	ldi R24,<_TxRxBuffer
	ldi R25,>_TxRxBuffer
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	std z+0,R16
	.dbline 196
L37:
	.dbline 193
	inc R20
L39:
	.dbline 193
	cpi R20,32
	brlo L36
	.dbline 197
; 	{   
; 	TxRxBuffer[i]=SpiReadSpiWrite(0);	  // ��ȡ���ݽ��ջ���������       
; 	}
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 197
	.dbline 198
;     Delay(2);                            //
	ldi R16,2
	ldi R17,0
	xcall _Delay
	.dbline 199
; 	Hign_nrf905_TRX_CE;							
	sbi 0x12,4
	.dbline 199
	.dbline -2
L35:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbend
	.dbfunc e RX _RX fV
	.even
_RX::
	.dbline -1
	.dbline 203
; }
; //--------------------------------���ý���ģʽ----------------------------------
; void  RX(void)
; {
	.dbline 204
;     SetRxMode();			          //����NRF905����ģʽ
	xcall _SetRxMode
L41:
	.dbline 205
L42:
	.dbline 205
;     while (CheckDR()==0);	         //�ȴ��������
	xcall _CheckDR
	tst R16
	breq L41
	.dbline 206
; 	RxPacket();                     //��ȡ�������ݻ�����
	xcall _RxPacket
	.dbline 207
; 	Delay(10);
	ldi R16,10
	ldi R17,0
	xcall _Delay
	.dbline -2
L40:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e StartUART _StartUART fV
	.even
_StartUART::
	.dbline -1
	.dbline 211
; }
; //-------------------------------���ڳ�ʼ��-------------------------------------
; void StartUART(void)
; {
	.dbline 212
;  	 UCSRA=0x00;	
	clr R2
	out 0xb,R2
	.dbline 213
; 	 UCSRB=0x18;	
	ldi R24,24
	out 0xa,R24
	.dbline 214
; 	 UCSRC=0x06;	
	ldi R24,6
	out 0x20,R24
	.dbline 215
; 	 UBRRL=0x33;
	ldi R24,51
	out 0x9,R24
	.dbline 216
; 	 UBRRH=0x00;
	out 0x20,R2
	.dbline 217
; 	 UCSRA=UCSRA|0x08;	
	sbi 0xb,3
	.dbline -2
L44:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e R_S_Byte _R_S_Byte fV
;         R_Byte -> R16
	.even
_R_S_Byte::
	.dbline -1
	.dbline 221
; }
; //------------------------------���ڷ���----------------------------------------
; void R_S_Byte(uchar R_Byte)
; {	
	.dbline 222
;      UDR= R_Byte;  
	out 0xc,R16
	.dbline -2
L45:
	.dbline 0 ; func end
	ret
	.dbsym r R_Byte 16 c
	.dbend
	.dbfunc e main _main fV
;              i -> R20,R21
	.even
_main::
	.dbline -1
	.dbline 226
; }
; //------------------------------������------------------------------------------
; void main(void)
; {  
	.dbline 228
; 	uint i;
; 	DDRD=0xF2;						 //�˿�D����											  
	ldi R24,242
	out 0x11,R24
	.dbline 229
; 	DDRB=0xB3;					    //�˿�B����		
	ldi R24,179
	out 0x17,R24
	.dbline 231
; //------------------------------------------------------------------------------
; 	Hign_BELL;		
	sbi 0x12,5
	.dbline 231
	.dbline 232
; 	Hign_JDQ;								  			 				
	sbi 0x12,7
	.dbline 234
; //------------------------------------------------------------------------------
; 	Spi_initial();	               //SPI��ʼ��															  
	xcall _Spi_initial
	.dbline 235
; 	system_Init();				  //ϵͳ״̬��ʼ��												
	xcall _system_Init
	.dbline 236
; 	Config905();  				 //NRF905��ʼ��									
	xcall _Config905
	.dbline 238
; //------------------------------------------------------------------------------		  
; 	StartUART();				//���ڳ�ʼ��9600������
	xcall _StartUART
	.dbline 239
; 	Delay(500);
	ldi R16,500
	ldi R17,1
	xcall _Delay
	xjmp L48
L47:
	.dbline 241
; 	while(1)
; 	{
	.dbline 242
; 		RX();  					//��������
	xcall _RX
	.dbline 243
; 		for(i=0;i<32;i++)
	clr R20
	clr R21
	xjmp L53
L50:
	.dbline 244
	.dbline 245
	ldi R24,<_TxRxBuffer
	ldi R25,>_TxRxBuffer
	movw R30,R20
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _R_S_Byte
	.dbline 246
	ldi R16,20
	ldi R17,0
	xcall _Delay
	.dbline 247
L51:
	.dbline 243
	subi R20,255  ; offset = 1
	sbci R21,255
L53:
	.dbline 243
	cpi R20,32
	ldi R30,0
	cpc R21,R30
	brlo L50
	.dbline 248
L48:
	.dbline 240
	xjmp L47
X1:
	.dbline -2
L46:
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbend
	.area bss(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
_TxRxBuffer::
	.blkb 32
	.dbsym e TxRxBuffer _TxRxBuffer A[32:32]c
