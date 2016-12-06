	.module jifeng_jieshou.c
	.area text(rom, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
_TxAddress::
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.dbsym e TxAddress _TxAddress A[4:4]c
_RFConf::
	.blkb 2
	.area idata
	.byte 0,'L
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 12,'D
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 4,4
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.blkb 1
	.area idata
	.byte 'X
	.area data(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.dbsym e RFConf _RFConf A[11:11]c
	.area text(rom, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	.dbfunc e Delay _Delay fV
;              i -> R20,R21
;              x -> R16,R17
	.even
_Delay::
	st -y,R20
	st -y,R21
	.dbline -1
	.dbline 89
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
; //#define  nrf905_TRX_CE  PD4	    //���1
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
; //-------------------------------NRF905״̬�����-------------------------------
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
; 
; //----------------------------------NRF905-SPIָ��------------------------------
; #define WC	0x00
; #define RRC	0x10
; #define WTP	0x20
; #define RTP	0x21
; #define WTA	0x22
; #define RTA	0x23
; #define RRP	0x24
; //---------------------------------��������-------------------------------------
; uchar TxRxBuffer[4];
; //----------------------------------���յ�ַ------------------------------------
; uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
; //------------------------------------------------------------------------------
; uchar count1 ,count2;
; //----------------------------------�Ĵ�������----------------------------------
; uchar RFConf[11]=
; {
;   0x00,                            //��������//
;   0x4c,                           //CH_NO,����Ƶ����430MHZ
;   0x0C,                          //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
;   0x44,                         //��ַ������ã�Ϊ4�ֽ�
;   0x04,0x04,                   //���շ�����Ч���ݳ���Ϊ4�ֽ�
;   0xCC,0xCC,0xCC,0xCC,        //���յ�ַ
;   0x58,                      //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
; };
; //----------------------------------NRF905��������------------------------------
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
; //-------------------------------���ں�������-----------------------------------
; void StartUART(void);
; void R_S_Byte(uchar R_Byte);
; //----------------------------------100us��ʱ�ӳ���-----------------------------
; void Delay(uint x)
; {
	xjmp L3
L2:
	.dbline 92
; 	uint i;
; 	while(x--)
; 	for(i=0;i<80;i++);
	clr R20
	clr R21
	xjmp L8
L5:
	.dbline 92
L6:
	.dbline 92
	subi R20,255  ; offset = 1
	sbci R21,255
L8:
	.dbline 92
	cpi R20,80
	ldi R30,0
	cpc R21,R30
	brlo L5
X0:
L3:
	.dbline 91
	movw R2,R16
	subi R16,1
	sbci R17,0
	tst R2
	brne L2
	tst R3
	brne L2
X1:
	.dbline -2
L1:
	.dbline 0 ; func end
	ld R21,y+
	ld R20,y+
	ret
	.dbsym r i 20 i
	.dbsym r x 16 i
	.dbend
	.dbfunc e Spi_initial _Spi_initial fV
	.even
_Spi_initial::
	.dbline -1
	.dbline 96
; }
; //----------------------------------SPI��ʼ��-----------------------------------
; void Spi_initial()
; {
	.dbline 97
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
	.dbline 101
; }
; //---------------------------------SPI��д����----------------------------------	
; uchar SpiReadSpiWrite(unsigned char cData)
; {
	.dbline 102
; 	SPDR = cData;
	out 0xf,R16
L11:
	.dbline 104
; 	while(!(SPSR & (1<<SPIF) ))  // �ȴ�SPI�������
; 	{};			
	.dbline 104
L12:
	.dbline 103
	sbis 0xe,7
	rjmp L11
X2:
	.dbline 104
	.dbline 105
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
	.dbline 109
; }
; //--------------------------------ϵͳ״̬��ʼ��--------------------------------
; void system_Init(void)			
; {
	.dbline 111
; 
;    	Hign_nrf905_CSN;			// SPIʹ��
	sbi 0x18,4
	.dbline 111
	.dbline 112
; 	Low_nrf905_SCK;				
	cbi 0x18,7
	.dbline 112
	.dbline 113
; 	Low_nrf905_DR;				// DR=0
	cbi 0x18,2
	.dbline 113
	.dbline 114
; 	Low_nrf905_AM;				// AM=0
	cbi 0x18,3
	.dbline 114
	.dbline 115
; 	Low_nrf905_CD;				// CD=0
	cbi 0x12,3
	.dbline 115
	.dbline 116
; 	Hign_nrf905_PWR;		    // PWR=1
	sbi 0x18,1
	.dbline 116
	.dbline 117
; 	Low_nrf905_TRX_CE;			// nrf905_TRX_CE=0
	cbi 0x12,4
	.dbline 117
	.dbline 118
; 	Low_nrf905_TX_EN ;			// nrf905_TX_EN=0
	cbi 0x18,0
	.dbline 118
	.dbline -2
L14:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Config905 _Config905 fV
;              i -> R20
	.even
_Config905::
	st -y,R20
	st -y,R21
	.dbline -1
	.dbline 122
; }
; //--------------------------------NRF905�Ĵ�����ʼ������------------------------
; void Config905(void)
; {
	.dbline 124
; 	uchar i;
; 	Low_nrf905_CSN;				//SPIʹ��											
	cbi 0x18,4
	.dbline 124
	.dbline 125
; 	Delay(1);				   
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 126
; 	for (i=0;i<11;i++)			//�NRF905������
	clr R20
	xjmp L19
L16:
	.dbline 127
; 	{
	.dbline 128
; 	 SpiReadSpiWrite(RFConf[i]);
	ldi R24,<_RFConf
	ldi R25,>_RFConf
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 129
; 	}
L17:
	.dbline 126
	inc R20
L19:
	.dbline 126
	cpi R20,11
	brlo L16
X3:
	.dbline 130
; 	Hign_nrf905_CSN;					// Disable Spi
	sbi 0x18,4
	.dbline 130
	.dbline -2
L15:
	.dbline 0 ; func end
	ld R21,y+
	ld R20,y+
	ret
	.dbsym r i 20 c
	.dbend
	.dbfunc e TxPacket _TxPacket fV
;              i -> R20
	.even
_TxPacket::
	st -y,R20
	st -y,R21
	.dbline -1
	.dbline 134
; }
; //--------------------------------NRF905�������ݴ��----------------------------
; void TxPacket(void)
; {
	.dbline 136
; 	uchar i;
; 	Low_nrf905_CSN;		   				// ʹ��Spi�������nrf905���ж�д����
	cbi 0x18,4
	.dbline 136
	.dbline 137
; 	Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 138
; 	SpiReadSpiWrite(WTP);				// д����ǰ��дд��������
	ldi R16,32
	xcall _SpiReadSpiWrite
	.dbline 139
; 	for (i=0;i<32;i++)
	clr R20
	xjmp L24
L21:
	.dbline 140
; 	{
	.dbline 141
; 	SpiReadSpiWrite(TxRxBuffer[i]);		// �����͵�32�ֽ�����
	ldi R24,<_TxRxBuffer
	ldi R25,>_TxRxBuffer
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 142
; 	}						
L22:
	.dbline 139
	inc R20
L24:
	.dbline 139
	cpi R20,32
	brlo L21
X4:
	.dbline 143
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 143
	.dbline 144
; 	Delay(1);							// �ر�Spi���������nrf905���ж�д����
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 145
; 	Low_nrf905_CSN;						// ʹ��Spi
	cbi 0x18,4
	.dbline 145
	.dbline 146
; 	SpiReadSpiWrite(WTA);				// д��ַǰ������д��ַ����
	ldi R16,34
	xcall _SpiReadSpiWrite
	.dbline 147
; 	for (i=0;i<4;i++)					// д��4 bytes ���յ�ַ
	clr R20
	xjmp L28
L25:
	.dbline 148
; 	{
	.dbline 149
; 	SpiReadSpiWrite(TxAddress[i]);
	ldi R24,<_TxAddress
	ldi R25,>_TxAddress
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 150
; 	}
L26:
	.dbline 147
	inc R20
L28:
	.dbline 147
	cpi R20,4
	brlo L25
X5:
	.dbline 151
; 	Hign_nrf905_CSN;					// �ر�Spi
	sbi 0x18,4
	.dbline 151
	.dbline 152
; 	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	sbi 0x12,4
	.dbline 152
	.dbline 153
; 	Delay(1);							// �ȴ�DR���
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 154
; 	Low_nrf905_TRX_CE;					// ����TRX_CE=0
	cbi 0x12,4
	.dbline 154
	.dbline -2
L20:
	.dbline 0 ; func end
	ld R21,y+
	ld R20,y+
	ret
	.dbsym r i 20 c
	.dbend
	.dbfunc e SetTxMode _SetTxMode fV
	.even
_SetTxMode::
	.dbline -1
	.dbline 158
; }
; //------------------------------���÷���ģʽ------------------------------------
; void SetTxMode(void)
; {
	.dbline 159
; 	Low_nrf905_TRX_CE;				//
	cbi 0x12,4
	.dbline 159
	.dbline 160
; 	Hign_nrf905_TX_EN;				//����ʹ��
	sbi 0x18,0
	.dbline 160
	.dbline 161
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
	.dbline 165
; }
; //------------------------------���ý���ģʽ����--------------------------------
; void SetRxMode(void)
; {
	.dbline 166
; 	Low_nrf905_TX_EN;
	cbi 0x18,0
	.dbline 166
	.dbline 167
; 	Hign_nrf905_TRX_CE;
	sbi 0x12,4
	.dbline 167
	.dbline 168
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
	.dbline 172
; }
; //------------------------------��������----------------------------------------
; void TX(void)
; {
	.dbline 173
;      SetTxMode();	   // Set nRF905 in Tx mode
	xcall _SetTxMode
	.dbline 174
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
	.dbline 178
; }
; //-----------------------------�ж��Ƿ��յ�����---------------------------------
; unsigned char CheckDR(void)		//����Ƿ��������ݴ��� 
; {
	.dbline 179
; 	if (PINB & (1 << PB2))
	sbis 0x16,2
	rjmp L33
X6:
	.dbline 180
; 	{
	.dbline 181
; 		return 1; 	 	  		//�յ�����
	ldi R16,1
	xjmp L32
L33:
	.dbline 184
; 	}
; 	else
; 	{
	.dbline 185
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
	st -y,R20
	st -y,R21
	.dbline -1
	.dbline 190
; 	}
; }
; //-----------------------------------���������ݰ�-------------------------------
; void RxPacket(void)							//������
; {
	.dbline 192
; 	uchar i;
;     Low_nrf905_TRX_CE;
	cbi 0x12,4
	.dbline 192
	.dbline 193
; 	Low_nrf905_CSN;						    // ʹ��SPI
	cbi 0x18,4
	.dbline 193
	.dbline 194
;     Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 195
; 	SpiReadSpiWrite(RRP);				   // д�����ݽ��ջ�������������
	ldi R16,36
	xcall _SpiReadSpiWrite
	.dbline 196
; 	for (i = 0 ;i < 4 ;i++)
	clr R20
	xjmp L39
L36:
	.dbline 197
; 	{   
	.dbline 198
; 	TxRxBuffer[i]=SpiReadSpiWrite(0);	  // ��ȡ���ݽ��ջ���������       
	clr R16
	xcall _SpiReadSpiWrite
	ldi R24,<_TxRxBuffer
	ldi R25,>_TxRxBuffer
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	std z+0,R16
	.dbline 199
; 	}
L37:
	.dbline 196
	inc R20
L39:
	.dbline 196
	cpi R20,4
	brlo L36
X7:
	.dbline 200
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 200
	.dbline 201
;     Delay(2);                            //
	ldi R16,2
	ldi R17,0
	xcall _Delay
	.dbline 202
; 	Hign_nrf905_TRX_CE;							
	sbi 0x12,4
	.dbline 202
	.dbline -2
L35:
	.dbline 0 ; func end
	ld R21,y+
	ld R20,y+
	ret
	.dbsym r i 20 c
	.dbend
	.dbfunc e RX _RX fV
	.even
_RX::
	.dbline -1
	.dbline 206
; }
; //--------------------------------���ý���ģʽ----------------------------------
; void  RX(void)
; {
	.dbline 207
;     SetRxMode();			          //����NRF905����ģʽ
	xcall _SetRxMode
L41:
	.dbline 208
;     while (CheckDR()==0);	         //�ȴ��������
L42:
	.dbline 208
	xcall _CheckDR
	tst R16
	breq L41
X8:
	.dbline 209
; 	RxPacket();                     //��ȡ�������ݻ�����
	xcall _RxPacket
	.dbline 210
; 	Delay(10);
	ldi R16,10
	ldi R17,0
	xcall _Delay
	.dbline -2
L40:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
;              i -> <dead>
	.even
_main::
	.dbline -1
	.dbline 214
; }
; //------------------------------������------------------------------------------
; void main(void)
; {  
	.dbline 216
; 	uint i;
; 	DDRD=0xF2;						  //�˿�D����											  
	ldi R24,242
	out 0x11,R24
	.dbline 217
; 	DDRB=0xB3;					     //�˿�B����	
	ldi R24,179
	out 0x17,R24
	.dbline 218
; 	PORTA=0x00;
	clr R2
	out 0x1b,R2
	.dbline 219
; 	PORTC=0xbf;
	ldi R24,191
	out 0x15,R24
	.dbline 221
; //------------------------------------------------------------------------------	
; 	Hign_JDQ;			  //�رռ̵���				
	sbi 0x12,7
	.dbline 222
; 	Hign_BELL;							
	sbi 0x12,5
	.dbline 222
	.dbline 224
; //------------------------------------------------------------------------------				  			 				
; 	Spi_initial();	                //SPI��ʼ��															  
	xcall _Spi_initial
	.dbline 225
; 	system_Init();				   //ϵͳ״̬��ʼ��												
	xcall _system_Init
	.dbline 226
; 	Config905();  				  //NRF905��ʼ��	
	xcall _Config905
	xjmp L46
L45:
	.dbline 230
; 	
; //------------------------------------------------------------------------------
; 	while(1)
; 	{
	.dbline 231
; 	RX();  					//��������
	xcall _RX
	.dbline 232
; 	if(TxRxBuffer[0])
	lds R2,_TxRxBuffer
	tst R2
	breq L48
X9:
	.dbline 233
; 	{
	.dbline 234
; 	if(TxRxBuffer[0]==0x29)
	mov R24,R2
	cpi R24,41
	brne L50
X10:
	.dbline 235
; 	{
	.dbline 236
; 	Low_JDQ;			   //�򿪼̵���
	cbi 0x12,7
	.dbline 237
; 	}
L50:
	.dbline 238
; 	if(TxRxBuffer[0]==0x30)
	lds R24,_TxRxBuffer
	cpi R24,48
	brne L52
X11:
	.dbline 239
; 	{
	.dbline 240
; 	Low_BELL;			   //�򿪷�����
	cbi 0x12,5
	.dbline 240
	.dbline 242
; 
; 	}
L52:
	.dbline 243
; 	}
L48:
	.dbline 244
; 	Delay(200);
	ldi R16,200
	ldi R17,0
	xcall _Delay
	.dbline 245
; 	Hign_JDQ;			  //�رռ̵���				
	sbi 0x12,7
	.dbline 246
; 	Hign_BELL;			  //�رշ�����		
	sbi 0x12,5
	.dbline 246
	.dbline 247
; 	}
L46:
	.dbline 229
	xjmp L45
X12:
	.dbline -2
L44:
	.dbline 0 ; func end
	ret
	.dbsym l i 1 i
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
_count2::
	.blkb 1
	.dbsym e count2 _count2 c
_count1::
	.blkb 1
	.dbsym e count1 _count1 c
_TxRxBuffer::
	.blkb 4
	.dbsym e TxRxBuffer _TxRxBuffer A[4:4]c
; }
