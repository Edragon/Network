	.module JASK_PCfasong.C
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
_TxAddress::
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.dbsym e TxAddress _TxAddress A[4:4]c
_seg::
	.blkb 2
	.area idata
	.byte 192,207
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 164,176
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 153,146
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 130,248
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 128,144
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.dbsym e seg _seg A[10:10]c
_RFConf::
	.blkb 2
	.area idata
	.byte 0,'L
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 12,'D
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 4,4
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.blkb 1
	.area idata
	.byte 'X
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.dbsym e RFConf _RFConf A[11:11]c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.dbfunc e Delay _Delay fV
;              i -> R20,R21
;              x -> R16,R17
	.even
_Delay::
	xcall push_gset1
	.dbline -1
	.dbline 121
; //ICC-AVR application builder : 2007-8-11 20:37:32
; // Target : M16
; // Crystal: 8.0000Mhz
; #include <iom16v.h>
; #include <macros.h>
; #define uint  unsigned int
; #define uchar unsigned char
; char KEY0,tf,TxBuf[4];
; //---------------------------------ģʽ���ƶ���---------------------------------
; //#define  nrf905_TX_EN	  PB0	    //���1   
; #define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0)
; #define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0)
; //#define  nrf905_TRX_CE  PD4 	    //���1
; #define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4)  
; #define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4) 
; //#define  nrf905_PWR     PB1 	    //���1
; #define   Hign_nrf905_PWR    PORTB |= (1 << PB1) 
; #define   Low_nrf905_PWR     PORTB &= ~(1 << PB1)
; //--------------------------------SPI�ڶ���-------------------------------------
; //#define  nrf905_MISO	  PB6   	//����0
; //#define  nrf905_MOSI    PB5	    //���1
; //#define  nrf905_SCK     PB7	    //���1
; #define   Low_nrf905_SCK     PORTB &= ~(1 << PB7)
; //------------------------------------------------------------------------------
; //#define  nrf905_CSN     PB4		//���1		
; #define   Hign_nrf905_CSN    PORTB |= (1 << PB4)  
; #define   Low_nrf905_CSN     PORTB &= ~(1 << PB4)				
; //-------------------------------״̬�����-------------------------------------
; //#define  nrf905_CD      PD3    //����0
; #define   Hign_nrf905_CD    PORTD |= (1 << PD3) 
; #define   Low_nrf905_CD     PORTD &= ~(1 << PD3) 
; #define   Read_nrf905_CD    PINB & (1 << PD4)
; //#define  nrf905_AM      PB3	    //����0
; #define   Hign_nrf905_AM    PORTB |= (1 << PB3) 
; #define   Low_nrf905_AM     PORTB &= ~(1 << PB3)
; #define   Read_nrf905_AM    PINB & (1 << PB3)
; //#define  nrf905_DR      PB2  		//����0
; #define   Hign_nrf905_DR    PORTB |= (1 << PB2)
; #define   Low_nrf905_DR     PORTB &= ~(1 << PB2)
; #define   Read_nrf905_DR    PINB & (1 << PB2)
; //------------------------------LCD״̬�����-----------------------------------
; //#define LCD_CS           PC7  	//1-out
; //#define   Out_LCD_CS       DDRC |= (1 << PC7);
; #define   Hign_LCD_CS      PORTC |= (1 << PC7);   
; #define   Low_LCD_CS       PORTC &= ~(1 << PC7); 
; //#define LCD_RESET         PC6 	//1-out
; //#define   Out_CD_RESET      DDRC |= (1 << PC6);
; #define   Hign_LCD_RESET    PORTC |= (1 << PC6);   
; #define   Low_LCD_RESET     PORTC &= ~(1 << PC6); 
; //#define LCD_RS           PC5 	//1-out
; //#define   Out_LCD_RS       DDRC |= (1 << PC5);
; #define   Hign_LCD_RS      PORTC |= (1 << PC5);   
; #define   Low_LCD_RS       PORTC &= ~(1 << PC5); 
; //#define LCD_SCL        PC4 	//1-out
; //#define   Out_LCD_SCL      DDRC |= (1 << PC4); 
; #define   Hign_LCD_SCL     PORTC |= (1 << PC4);   
; #define   Low_LCD_SCL      PORTC &= ~(1 << PC4);
; //#define LCD_SI         PC3  	//1-ou
; //#define   Out_LCD_SI      DDRC |= (1 << PC3); 
; #define   Hign_LCD_SI    PORTC |= (1 << PC3);   
; #define   Low_LCD_SI     PORTC &= ~(1 << PC3);
; //------------------------------�����λѡ--------------------------------------
; //#define Display1   PA1  		    //���1
; #define   Hign_Display1     PORTA |= (1 << PA1);   
; #define   Low_Display1    PORTA &= ~(1 << PA1); 
; //#define Display2      PA2  		//���1
; #define   Hign_Display2     PORTA |= (1 << PA2);   
; #define   Low_Display2    PORTA &= ~(1 << PA2); 
; //#define Display3     PA3  		//���1
; #define   Hign_Display3     PORTA |= (1 << PA3);   
; #define   Low_Display3     PORTA &= ~(1 << PA3); 
; //#define Display4      PA4 		//���1
; #define   Hign_Display4     PORTA |= (1 << PA4);   
; #define   Low_Display4     PORTA &= ~(1 << PA4); 
; //-------------------------------BELL������-------------------------------------
; #define   Hign_BELL  PORTD |= (1 << PD5);   
; #define   Low_BELL     PORTD &= ~(1 << PD5); 
; //-------------------------------JDQ�̵���--------------------------------------
; #define   Hign_JDQ  PORTD |= (1 << PD7)
; #define   Low_JDQ     PORTD &= ~(1 << PD7)
; 
; //----------------------------------905-SPIָ��---------------------------------
; #define WC	0x00
; #define RRC	0x10
; #define WTP	0x20
; #define RTP	0x21
; #define WTA	0x22
; #define RTA	0x23
; #define RRP	0x24
; //---------------------------------��������-------------------------------------
; uchar TxRxBuf[4];
; //----------------------------------���յ�ַ------------------------------------
; uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
; //------------------------------------------------------------------------------
; uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9����
; //----------------------------------�Ĵ�������----------------------------------
; uchar RFConf[11]=
; {
;   0x00,                             //��������//
;   0x4c,                             //CH_NO,����Ƶ����430MHZ
;   0x0C,                             //�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
;   0x44,                             //��ַ������ã�Ϊ4�ֽ�
;   0x04,0x04,                        //���շ�����Ч���ݳ���Ϊ4�ֽ�
;   0xCC,0xCC,0xCC,0xCC,              //���յ�ַ
;   0x58,                             //CRC����8λCRCУ�飬�ⲿʱ���źŲ�ʹ�ܣ�16M����
; };
; //-------------------------------NRF905��������----------------------------------
; void Delay(uint x);
; void Spi_initial();
; uchar SpiReadSpiWrite(unsigned char cData);
; void system_Init(void);
; void Config905(void);
; void TxPacket(uchar TxBUF[4]);
; void SetTxMode(void);
; void uart0_init(void) ;
; //-------------------------------���ں�������------------------------------------
; void uart0_init(void) ;
; void uart0_rx_isr(void) ;
; //----------------------------------��ʱ�ӳ���----------------------------------
; void Delay(uint x)
; {
	xjmp L3
L2:
	.dbline 124
	clr R20
	clr R21
	xjmp L8
L5:
	.dbline 124
L6:
	.dbline 124
	subi R20,255  ; offset = 1
	sbci R21,255
L8:
	.dbline 124
	cpi R20,80
	ldi R30,0
	cpc R21,R30
	brlo L5
L3:
	.dbline 123
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
	.dbline 128
; 	for(i=0;i<80;i++);
; }
; //----------------------------------SPI��ʼ��-----------------------------------
; void Spi_initial()
; {
	.dbline 131
; 	//SPCR=0x50;
; 	//SPSR=0x00;	
; 	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);   // ����ģʽ��fck/16, SPI��ʽ0
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
	.dbline 135
; }
; //---------------------------------SPI��д����----------------------------------	
; uchar SpiReadSpiWrite(unsigned char cData)//r
; {
	.dbline 136
; 	SPDR = cData;
	out 0xf,R16
L11:
	.dbline 138
	.dbline 138
L12:
	.dbline 137
; 	while(!(SPSR & (1<<SPIF) ))
	sbis 0xe,7
	rjmp L11
	.dbline 138
; 	{};			// �ȴ�SPI�������
	.dbline 139
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
	.dbline 143
; }
; //---------------------------------ϵͳ״̬��ʼ��-------------------------------
; void system_Init(void)			//r
; {
	.dbline 145
; 
;    	Hign_nrf905_CSN;				// Spi 	disable
	sbi 0x18,4
	.dbline 146
; 	Low_nrf905_SCK;				// Spi clock line init low
	cbi 0x18,7
	.dbline 147
; 	Low_nrf905_DR;				// Init DR for input
	cbi 0x18,2
	.dbline 148
; 	Low_nrf905_AM;				// Init AM for input
	cbi 0x18,3
	.dbline 149
; 	Low_nrf905_CD;				// Init nrf905_CDfor input
	cbi 0x12,3
	.dbline 150
; 	Hign_nrf905_PWR;				// nRF905 power on
	sbi 0x18,1
	.dbline 151
; 	Low_nrf905_TRX_CE;			// Set nRF905 in standby mode
	cbi 0x12,4
	.dbline 152
; 	Low_nrf905_TX_EN ;			// set radio in Rx mode
	cbi 0x18,0
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
	.dbline 156
; }
; //--------------------------------NRF905�Ĵ�����ʼ������------------------------
; void Config905(void)
; {
	.dbline 158
; 	uchar i;
; 	Low_nrf905_CSN;	
	cbi 0x18,4
	.dbline 159
; 	Delay(1);				// Spi enable for write a spi command
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 161
; 	//SpiWrite(WC);				// Write config commandд����������
; 	for (i=0;i<11;i++)			// Write configration words  д��������
	clr R20
	xjmp L19
L16:
	.dbline 162
	.dbline 163
	ldi R24,<_RFConf
	ldi R25,>_RFConf
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 164
L17:
	.dbline 161
	inc R20
L19:
	.dbline 161
	cpi R20,11
	brlo L16
	.dbline 165
; 	{
; 	 SpiReadSpiWrite(RFConf[i]);
; 	}
; 	Hign_nrf905_CSN;					// Disable Spi
	sbi 0x18,4
	.dbline -2
L15:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbend
	.dbfunc e TxPacket _TxPacket fV
;              i -> R20
;          TxBUF -> R22,R23
	.even
_TxPacket::
	xcall push_gset2
	movw R22,R16
	.dbline -1
	.dbline 169
; }
; //--------------------------------NRF905�������ݴ��----------------------------
; void TxPacket(uchar TxBUF[4])
; {
	.dbline 171
; 	uchar i;
; 	Low_nrf905_CSN;		   						// ʹ��Spi�������nrf905���ж�д����
	cbi 0x18,4
	.dbline 172
; 	Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 173
; 	SpiReadSpiWrite(WTP);				// д����ǰ��дд��������
	ldi R16,32
	xcall _SpiReadSpiWrite
	.dbline 174
; 	for (i=0;i<4;i++)
	clr R20
	xjmp L24
L21:
	.dbline 175
	.dbline 176
	mov R30,R20
	clr R31
	add R30,R22
	adc R31,R23
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 177
L22:
	.dbline 174
	inc R20
L24:
	.dbline 174
	cpi R20,4
	brlo L21
	.dbline 178
; 	{
; 	SpiReadSpiWrite(TxBUF[i]);		// �����͵�32�ֽ�����
; 	}						
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 179
; 	Delay(1);							// �ر�Spi���������nrf905���ж�д����
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 180
; 	Low_nrf905_CSN;								// ʹ��Spi
	cbi 0x18,4
	.dbline 181
; 	SpiReadSpiWrite(WTA);				// д��ַǰ������д��ַ����
	ldi R16,34
	xcall _SpiReadSpiWrite
	.dbline 182
; 	for (i=0;i<4;i++)					// д 4 bytes ��ַ
	clr R20
	xjmp L28
L25:
	.dbline 183
	.dbline 184
	ldi R24,<_TxAddress
	ldi R25,>_TxAddress
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 185
L26:
	.dbline 182
	inc R20
L28:
	.dbline 182
	cpi R20,4
	brlo L25
	.dbline 186
; 	{
; 	SpiReadSpiWrite(TxAddress[i]);
; 	}
; 	Hign_nrf905_CSN;					// �ر�Spi
	sbi 0x18,4
	.dbline 187
; 	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	sbi 0x12,4
	.dbline 188
; 	Delay(1);							// �ȴ�DR���
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 189
; 	Low_nrf905_TRX_CE;							// ����TRX_CE=0
	cbi 0x12,4
	.dbline -2
L20:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbsym r TxBUF 22 pc
	.dbend
	.dbfunc e SetTxMode _SetTxMode fV
	.even
_SetTxMode::
	.dbline -1
	.dbline 193
; }
; //-------------------------------����ģʽ����-----------------------------------
; void SetTxMode(void)
; {
	.dbline 194
; 	Low_nrf905_TRX_CE;				//
	cbi 0x12,4
	.dbline 195
; 	Hign_nrf905_TX_EN;				//����ʹ��
	sbi 0x18,0
	.dbline 196
; 	Delay(2); 				// delay for mode change(>=650us)���ݾ���ͬҪ�ı�
	ldi R16,2
	ldi R17,0
	xcall _Delay
	.dbline -2
L29:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e uart0_init _uart0_init fV
	.even
_uart0_init::
	.dbline -1
	.dbline 200
; }
; //------------------------------���ڳ�ʼ��--------------------------------------
; void uart0_init(void) 
; { 
	.dbline 201
;  CLI(); //�ر��ж�
	cli
	.dbline 202
;  UCSRB =0x98;    //disable while setting baud rate 
	ldi R24,152
	out 0xa,R24
	.dbline 203
;  UCSRA =0x20; 
	ldi R24,32
	out 0xb,R24
	.dbline 204
;  UCSRC = 0x86; 
	ldi R24,134
	out 0x20,R24
	.dbline 205
;  UBRRL =51; //set baud rate lo 
	ldi R24,51
	out 0x9,R24
	.dbline 206
;  TIMSK = 0x00; //timer interrupt sources 
	clr R2
	out 0x39,R2
	.dbline 207
;  SEI(); //���ж�
	sei
	.dbline -2
L30:
	.dbline 0 ; func end
	ret
	.dbend
	.area vector(rom, abs)
	.org 44
	jmp _uart0_rx_isr
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
	.dbfunc e uart0_rx_isr _uart0_rx_isr fV
	.even
_uart0_rx_isr::
	st -y,R2
	in R2,0x3f
	st -y,R2
	.dbline -1
	.dbline 212
;  } 
;  //----------------------------�����жϴ�����----------------------------------
; #pragma interrupt_handler uart0_rx_isr:12 
; void uart0_rx_isr(void) 
; { 
	.dbline 213
;   KEY0=UDR; 
	in R2,0xc
	sts _KEY0,R2
	.dbline 214
;   UDR=KEY0;
	out 0xc,R2
	.dbline -2
L31:
	ld R2,y+
	out 0x3f,R2
	ld R2,y+
	.dbline 0 ; func end
	reti
	.dbend
	.dbfunc e LCD_Delay _LCD_Delay fV
;              i -> R20,R21
;           time -> R16,R17
	.even
_LCD_Delay::
	xcall push_gset1
	.dbline -1
	.dbline 221
; } 
; //******************************************************************************
; //����ΪLCD����
; //******************************************************************************
; //------------------------------------------------------------------------------
; void LCD_Delay(uint time)
; {
	.dbline 223
	movw R20,R16
	xjmp L36
L33:
	.dbline 223
L34:
	.dbline 223
	subi R20,1
	sbci R21,0
L36:
	.dbline 223
; 	uint i;
; 	for(i=time;i>0;i--);
	cpi R20,0
	cpc R20,R21
	brne L33
X1:
	.dbline -2
L32:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbsym r time 16 i
	.dbend
	.dbfunc e main _main fV
;              i -> R20,R21
	.even
_main::
	.dbline -1
	.dbline 229
; }
; 
; //------------------------------------------------------------------------------ 	
; //------------------------------������------------------------------------------
; void main(void)
; {  
	.dbline 231
; 	uint i;
; 	DDRD=0xf2;		  //
	ldi R24,242
	out 0x11,R24
	.dbline 232
; 	DDRB=0xB3;		  //
	ldi R24,179
	out 0x17,R24
	.dbline 233
; 	DDRA=0x1e;       //
	ldi R24,30
	out 0x1a,R24
	.dbline 234
; 	DDRC=0xff; 		//LED�˿�����
	ldi R24,255
	out 0x14,R24
	.dbline 235
; 	PORTA = 0xff;
	out 0x1b,R24
	.dbline 236
; 	PORTC=0xc0;
	ldi R24,192
	out 0x15,R24
	.dbline 237
; 	Low_Display4;
	cbi 0x1b,4
	.dbline 237
	.dbline 238
; 	Low_Display3;
	cbi 0x1b,3
	.dbline 238
	.dbline 239
; 	Low_Display2;
	cbi 0x1b,2
	.dbline 239
	.dbline 240
; 	Low_Display1;
	cbi 0x1b,1
	.dbline 240
	.dbline 242
; //------------------------------------------------------------------------------
; 	Hign_JDQ ;			
	sbi 0x12,7
	.dbline 243
; 	Hign_BELL ;		
	sbi 0x12,5
	.dbline 243
	.dbline 245
; //------------------------------------------------------------------------------
; 	Spi_initial();
	xcall _Spi_initial
	.dbline 246
; 	system_Init();
	xcall _system_Init
	.dbline 247
; 	Config905();
	xcall _Config905
	.dbline 249
; //------------------------------------------------------------------------------
; 	uart0_init();
	xcall _uart0_init
	.dbline 251
; //------------------------------------------------------------------------------
; 	Delay(1000); 
	ldi R16,1000
	ldi R17,3
	xcall _Delay
	.dbline 252
; 	Delay(1000);
	ldi R16,1000
	ldi R17,3
	xcall _Delay
	xjmp L39
L38:
	.dbline 254
; 	while(1)
;  {
	.dbline 257
; //********************************������������**********************************
; 
; 	if(KEY0==49)						//�м�����1
	lds R24,_KEY0
	cpi R24,49
	brne L41
	.dbline 258
; 			{
	.dbline 259
; 				 TxBuf[0]=0x11;
	ldi R24,17
	sts _TxBuf,R24
	.dbline 260
; 				 tf =1;
	ldi R24,1
	sts _tf,R24
	.dbline 261
; 				 PORTC=0xBF;
	ldi R24,191
	out 0x15,R24
	.dbline 262
; 			}
L41:
	.dbline 263
; 	if(KEY0==50)						//�м�����2
	lds R24,_KEY0
	cpi R24,50
	brne L43
	.dbline 264
; 			{
	.dbline 265
; 				 TxBuf[0]=0x21;
	ldi R24,33
	sts _TxBuf,R24
	.dbline 266
; 				 tf =2;
	ldi R24,2
	sts _tf,R24
	.dbline 267
; 				  PORTC=0xFE;
	ldi R24,254
	out 0x15,R24
	.dbline 268
; 			}	
L43:
	.dbline 269
; 	if(KEY0==51)						//�м�����3
	lds R24,_KEY0
	cpi R24,51
	brne L45
	.dbline 270
; 			{
	.dbline 271
; 				TxBuf[0]=0x31;
	ldi R24,49
	sts _TxBuf,R24
	.dbline 272
; 				tf =3;
	ldi R24,3
	sts _tf,R24
	.dbline 273
; 				 PORTC=0xf7;
	ldi R24,247
	out 0x15,R24
	.dbline 274
; 			}
L45:
	.dbline 275
; 	if(KEY0==52)						//�м�����4
	lds R24,_KEY0
	cpi R24,52
	brne L47
	.dbline 276
; 			{
	.dbline 277
; 				TxBuf[0]=0x41;
	ldi R24,65
	sts _TxBuf,R24
	.dbline 278
; 				tf =4;
	ldi R24,4
	sts _tf,R24
	.dbline 279
; 				 PORTC=0xBF;
	ldi R24,191
	out 0x15,R24
	.dbline 280
; 			}
L47:
	.dbline 281
; 	if(KEY0==53)						//�м�����5
	lds R24,_KEY0
	cpi R24,53
	brne L49
	.dbline 282
; 			{
	.dbline 283
; 				TxBuf[0]=0x51;
	ldi R24,81
	sts _TxBuf,R24
	.dbline 284
; 				tf =5;
	ldi R24,5
	sts _tf,R24
	.dbline 285
; 				 PORTC=0xFE;
	ldi R24,254
	out 0x15,R24
	.dbline 286
; 			}
L49:
	.dbline 287
; 	if(KEY0==54)						//�м�����6
	lds R24,_KEY0
	cpi R24,54
	brne L51
	.dbline 288
; 			{
	.dbline 289
; 			   TxBuf[0]=0x61;
	ldi R24,97
	sts _TxBuf,R24
	.dbline 290
; 			   tf =6;
	ldi R24,6
	sts _tf,R24
	.dbline 291
; 			   PORTC=0xf7;
	ldi R24,247
	out 0x15,R24
	.dbline 292
; 			}
L51:
	.dbline 293
; 	if(KEY0==55)						//�м�����7
	lds R24,_KEY0
	cpi R24,55
	brne L53
	.dbline 294
; 			{
	.dbline 295
; 			   TxBuf[0]=0x71;
	ldi R24,113
	sts _TxBuf,R24
	.dbline 296
; 			   tf =7;
	ldi R24,7
	sts _tf,R24
	.dbline 297
; 			   PORTC=0xbf;
	ldi R24,191
	out 0x15,R24
	.dbline 298
; 			}
L53:
	.dbline 299
; 	if(KEY0==57)						//�м�����9
	lds R24,_KEY0
	cpi R24,57
	brne L55
	.dbline 300
; 			{
	.dbline 301
; 			   TxBuf[0]=0x91;
	ldi R24,145
	sts _TxBuf,R24
	.dbline 302
; 			   tf =9;
	ldi R24,9
	sts _tf,R24
	.dbline 303
; 			   PORTC=0xfe;
	ldi R24,254
	out 0x15,R24
	.dbline 304
; 			}
L55:
	.dbline 306
; //*******************************���Ͱ�����Ϣ***********************************
; 	   if (tf)
	lds R2,_tf
	tst R2
	breq L57
	.dbline 307
;        {	 
	.dbline 308
; 		   KEY0=0;	
	clr R2
	sts _KEY0,R2
	.dbline 309
; 		   tf=0;
	sts _tf,R2
	.dbline 310
; 		   for(i=0;i<2;i++)
	clr R20
	clr R21
	xjmp L62
L59:
	.dbline 311
	.dbline 312
	xcall _SetTxMode
	.dbline 313
	ldi R16,<_TxBuf
	ldi R17,>_TxBuf
	xcall _TxPacket
	.dbline 314
L60:
	.dbline 310
	subi R20,255  ; offset = 1
	sbci R21,255
L62:
	.dbline 310
	cpi R20,2
	ldi R30,0
	cpc R21,R30
	brlo L59
	.dbline 315
; 		   {
; 		   SetTxMode();// Set nRF905 in Tx mode
; 		   TxPacket(TxBuf);// Send data by nRF905
; 		   }
; 		   TxBuf[0] = 0x00;			//�������TxBuf[1]�趨��0x00	 
	clr R2
	sts _TxBuf,R2
	.dbline 316
; 	   }
L57:
	.dbline 317
	sbi 0x12,7
	.dbline 318
	sbi 0x12,5
	.dbline 318
	.dbline 319
L39:
	.dbline 253
	xjmp L38
X2:
	.dbline -2
L37:
	.dbline 0 ; func end
	ret
	.dbsym r i 20 i
	.dbend
	.area bss(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����PC����ϵͳ\JASK_PCfasong\JASK_PCfasong.C
_TxRxBuf::
	.blkb 4
	.dbsym e TxRxBuf _TxRxBuf A[4:4]c
_TxBuf::
	.blkb 4
	.dbsym e TxBuf _TxBuf A[4:4]c
_tf::
	.blkb 1
	.dbsym e tf _tf c
_KEY0::
	.blkb 1
	.dbsym e KEY0 _KEY0 c
