	.module jfp_fasong.c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
_TxAddress::
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.dbsym e TxAddress _TxAddress A[4:4]c
_seg::
	.blkb 2
	.area idata
	.byte 192,207
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 164,176
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 153,146
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 130,248
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 128,144
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.dbsym e seg _seg A[10:10]c
_RFConf::
	.blkb 2
	.area idata
	.byte 0,'L
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 12,'D
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 4,4
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.blkb 1
	.area idata
	.byte 'X
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.dbsym e RFConf _RFConf A[11:11]c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	.dbfunc e Delay _Delay fV
;              i -> R20,R21
;              x -> R16,R17
	.even
_Delay::
	xcall push_gset1
	.dbline -1
	.dbline 105
; //ICC-AVR application builder : 2007-8-11 20:37:32
; // Target : M16
; // Crystal: 8.0000Mhz
; #include <iom16v.h>
; #include <macros.h>
; #define uint  unsigned int
; #define uchar unsigned char
; ///////////////////////////模式控制定义/////////////////////////////////
; //#define  nrf905_TX_EN	  PB0	    //输出1   
; #define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0)
; #define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0)
; //#define  nrf905_TRX_CE  PD4	    //输出1
; #define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4)  
; #define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4) 
; //#define  nrf905_PWR     PB1 	    //输出1
; #define   Hign_nrf905_PWR    PORTB |= (1 << PB1) 
; #define   Low_nrf905_PWR     PORTB &= ~(1 << PB1)
; //--------------------------------SPI口定义-------------------------------------
; //#define  nrf905_MISO	  PB6   	//输入0
; //#define  nrf905_MOSI    PB5	    //输出1
; //#define  nrf905_SCK     PB7	    //输出1
; #define   Low_nrf905_SCK     PORTB &= ~(1 << PB7)
; //------------------------------------------------------------------------------
; //#define  nrf905_CSN     PB4		//输出1		
; #define   Hign_nrf905_CSN    PORTB |= (1 << PB4)  
; #define   Low_nrf905_CSN     PORTB &= ~(1 << PB4)				
; //-------------------------------状态输出口-------------------------------------
; //#define  nrf905_CD      PD3	    //输入0
; #define   Hign_nrf905_CD    PORTD |= (1 << PD3) 
; #define   Low_nrf905_CD     PORTD &= ~(1 << PD3) 
; #define   Read_nrf905_CD    PINB & (1 << PD3)
; //#define  nrf905_AM      PB3	    //输入0
; #define   Hign_nrf905_AM    PORTB |= (1 << PB3) 
; #define   Low_nrf905_AM     PORTB &= ~(1 << PB3)
; #define   Read_nrf905_AM    PINB & (1 << PB3)
; //#define  nrf905_DR      PB2  		//输入0
; #define   Hign_nrf905_DR    PORTB |= (1 << PB2)
; #define   Low_nrf905_DR     PORTB &= ~(1 << PB2)
; #define   Read_nrf905_DR    PINB & (1 << PB2)
; //读取键值KEY2-KEY3-KEY4  
; #define   Read_KEY_2  	    PINA & (1 << PA5)        
; //甲队加3分
; #define   Read_KEY_3    	PINA & (1 << PA6)
; //乙队加2分
; #define   Read_KEY_4   	    PINA & (1 << PA7)   
; //乙队加3分
; //------------------------------数码管位选--------------------------------------
; //#define Display1   PA1  		    //输出1
; #define   Hign_Display1     PORTA |= (1 << PA1);   
; #define   Low_Display1    PORTA &= ~(1 << PA1); 
; //#define Display2      PA2  		//输出1
; #define   Hign_Display2     PORTA |= (1 << PA2);   
; #define   Low_Display2    PORTA &= ~(1 << PA2); 
; //#define Display3     PA3  		//输出1
; #define   Hign_Display3     PORTA |= (1 << PA3);   
; #define   Low_Display3     PORTA &= ~(1 << PA3); 
; //#define Display4      PA4 		//输出1
; #define   Hign_Display4     PORTA |= (1 << PA4);   
; #define   Low_Display4     PORTA &= ~(1 << PA4); 
; //-------------------------------BELL蜂明器-------------------------------------
; #define   Hign_BELL  PORTD |= (1 << PD5);   
; #define   Low_BELL     PORTD &= ~(1 << PD5); 
; //-------------------------------JDQ继电器--------------------------------------
; #define   Hign_JDQ  PORTD |= (1 << PD7)
; #define   Low_JDQ     PORTD &= ~(1 << PD7)
; //----------------------------------905-SPI指令---------------------------------
; #define WC	0x00
; #define RRC	0x10
; #define WTP	0x20
; #define RTP	0x21
; #define WTA	0x22
; #define RTA	0x23
; #define RRP	0x24
; //---------------------------------发送数据缓冲区-------------------------------
; uchar TxRxBuf[4];
; //----------------------------------接收地址------------------------------------
; uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
; uchar tf;
; uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9段码
; //------------------------------------------------------------------------------
; //----------------------------------寄存器配置----------------------------------
; uchar RFConf[11]=
; {
;   0x00,                             //配置命令//
;   0x4c,                             //CH_NO,配置频段在430MHZ
;   0x0C,                             //输出功率为10db,不重发，节电为正常模式
;   0x44,                             //地址宽度设置，为4字节
;   0x04,0x04,                        //接收发送有效数据长度为4字节
;   0xCC,0xCC,0xCC,0xCC,              //接收地址
;   0x58,                              //CRC充许，8位CRC校验，外部时钟信号不使能，16M晶振
; };
; //----------------------------------函数申明------------------------------------
; void Delay(uint x);
; void Spi_initial();
; uchar SpiReadSpiWrite(uchar DATA);
; void system_Init(void);
; void Config905(void);
; void TxPacket(uchar TxBUF[4]);
; void SetTxMode(void);
; void TX(void);
; void StartUART(void);
; void R_S_Byte(uchar R_Byte);
; //----------------------------------100us延时子程序-----------------------------
; void Delay(uint x)
; {
	xjmp L3
L2:
	.dbline 108
	clr R20
	clr R21
	xjmp L8
L5:
	.dbline 108
L6:
	.dbline 108
	subi R20,255  ; offset = 1
	sbci R21,255
L8:
	.dbline 108
	cpi R20,80
	ldi R30,0
	cpc R21,R30
	brlo L5
L3:
	.dbline 107
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
	.dbline 112
; 	for(i=0;i<80;i++);
; }
; //----------------------------------SPI初始化-----------------------------------
; void Spi_initial()
; {
	.dbline 115
; 	//SPCR=0x50;
; 	//SPSR=0x00;	
; 	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);   // 主机模式，fck/16, SPI方式0
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
	.dbline 119
; }
; //---------------------------------SPI读写程序----------------------------------	
; uchar SpiReadSpiWrite(unsigned char cData)//r
; {
	.dbline 120
; 	SPDR = cData;
	out 0xf,R16
L11:
	.dbline 122
	.dbline 122
L12:
	.dbline 121
; 	while(!(SPSR & (1<<SPIF) ))
	sbis 0xe,7
	rjmp L11
	.dbline 122
; 	{};			// 等待SPI发送完毕
	.dbline 123
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
	.dbline 127
; }
; //---------------------------------系统状态初始化-------------------------------
; void system_Init(void)			//r
; {
	.dbline 129
; 
;    	Hign_nrf905_CSN;				// Spi 	disable
	sbi 0x18,4
	.dbline 130
; 	Low_nrf905_SCK;				// Spi clock line init low
	cbi 0x18,7
	.dbline 131
; 	Low_nrf905_DR;				// Init DR for input
	cbi 0x18,2
	.dbline 132
; 	Low_nrf905_AM;				// Init AM for input
	cbi 0x18,3
	.dbline 133
; 	Low_nrf905_CD;				// Init nrf905_CDfor input
	cbi 0x12,3
	.dbline 134
; 	Hign_nrf905_PWR;				// nRF905 power on
	sbi 0x18,1
	.dbline 135
; 	Low_nrf905_TRX_CE;			// Set nRF905 in standby mode
	cbi 0x12,4
	.dbline 136
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
	.dbline 140
; }
; //--------------------------------NRF905寄存器初始化函数------------------------
; void Config905(void)
; {
	.dbline 142
; 	uchar i;
; 	Low_nrf905_CSN;	
	cbi 0x18,4
	.dbline 143
; 	Delay(1);				// Spi enable for write a spi command
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 145
; 	//SpiWrite(WC);				// Write config command写放配置命令
; 	for (i=0;i<11;i++)			// Write configration words  写放配置字
	clr R20
	xjmp L19
L16:
	.dbline 146
	.dbline 147
	ldi R24,<_RFConf
	ldi R25,>_RFConf
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 148
L17:
	.dbline 145
	inc R20
L19:
	.dbline 145
	cpi R20,11
	brlo L16
	.dbline 149
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
	.dbline 153
; }
; //--------------------------------NRF905待发数据打包----------------------------
; void TxPacket(uchar TxBUF[4])
; {
	.dbline 155
; 	uchar i;
; 	Low_nrf905_CSN;		   						// 使能Spi，允许对nrf905进行读写操作
	cbi 0x18,4
	.dbline 156
; 	Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 157
; 	SpiReadSpiWrite(WTP);				// 写数据前先写写数据命令
	ldi R16,32
	xcall _SpiReadSpiWrite
	.dbline 158
; 	for (i=0;i<4;i++)
	clr R20
	xjmp L24
L21:
	.dbline 159
	.dbline 160
	mov R30,R20
	clr R31
	add R30,R22
	adc R31,R23
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 161
L22:
	.dbline 158
	inc R20
L24:
	.dbline 158
	cpi R20,4
	brlo L21
	.dbline 162
; 	{
; 	SpiReadSpiWrite(TxBUF[i]);		// 待发送的32字节数据
; 	}						
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 163
; 	Delay(1);							// 关闭Spi，不允许对nrf905进行读写操作
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 164
; 	Low_nrf905_CSN;								// 使能Spi
	cbi 0x18,4
	.dbline 165
; 	SpiReadSpiWrite(WTA);				// 写地址前首先先写地址命令
	ldi R16,34
	xcall _SpiReadSpiWrite
	.dbline 166
; 	for (i=0;i<4;i++)					// 写 4 bytes 地址
	clr R20
	xjmp L28
L25:
	.dbline 167
	.dbline 168
	ldi R24,<_TxAddress
	ldi R25,>_TxAddress
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 169
L26:
	.dbline 166
	inc R20
L28:
	.dbline 166
	cpi R20,4
	brlo L25
	.dbline 170
; 	{
; 	SpiReadSpiWrite(TxAddress[i]);
; 	}
; 	Hign_nrf905_CSN;					// 关闭Spi
	sbi 0x18,4
	.dbline 171
; 	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	sbi 0x12,4
	.dbline 172
; 	Delay(1);							// 等待DR变高
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 173
; 	Low_nrf905_TRX_CE;							// 设置TRX_CE=0
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
	.dbline 177
; }
; //-------------------------------发送模式激发-----------------------------------
; void SetTxMode(void)
; {
	.dbline 178
; 	Low_nrf905_TRX_CE;				//
	cbi 0x12,4
	.dbline 179
; 	Hign_nrf905_TX_EN;				//发送使能
	sbi 0x18,0
	.dbline 180
; 	Delay(2); 				// delay for mode change(>=650us)根据晶振不同要改变
	ldi R16,2
	ldi R17,0
	xcall _Delay
	.dbline -2
L29:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
;           temp -> y+0
;              j -> <dead>
;              i -> <dead>
	.even
_main::
	sbiw R28,63
	sbiw R28,1  ; offset = 64
	.dbline -1
	.dbline 185
; }
; //------------------------------------------------------------------------
; //------------------------------主函数------------------------------------------
; void main(void)
; {  
	.dbline 187
; 	uint i,j,temp[32];
; 	DDRD=0xf2;		  //
	ldi R24,242
	out 0x11,R24
	.dbline 188
; 	DDRB=0xB3;		  //
	ldi R24,179
	out 0x17,R24
	.dbline 189
; 	DDRA=0x1e;       //
	ldi R24,30
	out 0x1a,R24
	.dbline 190
; 	DDRC=0xff; 		//LED端口设置
	ldi R24,255
	out 0x14,R24
	.dbline 191
; 	PORTA = 0xff;
	out 0x1b,R24
	.dbline 192
; 	Hign_BELL;
	sbi 0x12,5
	.dbline 192
	.dbline 193
; 	Hign_JDQ ;
	sbi 0x12,7
	.dbline 194
; 	Spi_initial();
	xcall _Spi_initial
	.dbline 195
; 	system_Init();
	xcall _system_Init
	.dbline 196
; 	Config905();
	xcall _Config905
	xjmp L32
L31:
	.dbline 198
; 	while(1)
;  {
	.dbline 200
; //------------------------------------------------------------------------------
; 	if((PINA & 0x20) == 0)		  //有键按下KEY1
	sbic 0x19,5
	rjmp L34
	.dbline 201
; 	{
L36:
	.dbline 202
L37:
	.dbline 202
; 	while(!(PINA & 0x20));   			//等待按键松开GREEN
	sbis 0x19,5
	rjmp L36
	.dbline 203
; 	 TxRxBuf[0]=0x29;
	ldi R24,41
	sts _TxRxBuf,R24
	.dbline 204
; 	 TxRxBuf[1]=0x30;
	ldi R24,48
	sts _TxRxBuf+1,R24
	.dbline 205
; 	 TxRxBuf[2]=0x31;
	ldi R24,49
	sts _TxRxBuf+2,R24
	.dbline 206
; 	 TxRxBuf[3]=0x32; 
	ldi R24,50
	sts _TxRxBuf+3,R24
	.dbline 207
; 	 tf=1;   
	ldi R24,1
	sts _tf,R24
	.dbline 208
; 	 }
L34:
	.dbline 210
; //------------------------------------------------------------------------------
; 	if((PINA & 0x40) == 0)			//有键按下KEY2
	sbic 0x19,6
	rjmp L42
	.dbline 211
; 	{
L44:
	.dbline 212
L45:
	.dbline 212
; 	while(!(PINA & 0x40));   			//等待按键松开GREEN
	sbis 0x19,6
	rjmp L44
	.dbline 213
;  	 TxRxBuf[0]=0x30;
	ldi R24,48
	sts _TxRxBuf,R24
	.dbline 214
; 	 TxRxBuf[1]=0x31;
	ldi R24,49
	sts _TxRxBuf+1,R24
	.dbline 215
; 	 TxRxBuf[2]=0x32;
	ldi R24,50
	sts _TxRxBuf+2,R24
	.dbline 216
; 	 TxRxBuf[3]=0x29;  
	ldi R24,41
	sts _TxRxBuf+3,R24
	.dbline 217
; 	 tf=2;    
	ldi R24,2
	sts _tf,R24
	.dbline 218
; 	 }
L42:
	.dbline 220
; //------------------------------------------------------------------------------
; 	if((PINA & 0x80) == 0)			//有键按下KEY3
	sbic 0x19,7
	rjmp L50
	.dbline 221
; 	{
L52:
	.dbline 222
L53:
	.dbline 222
; 	while(!(PINA & 0x80));   			//等待按键松开GREEN
	sbis 0x19,7
	rjmp L52
	.dbline 223
;  	 TxRxBuf[0]=0x31;
	ldi R24,49
	sts _TxRxBuf,R24
	.dbline 224
; 	 TxRxBuf[1]=0x32;
	ldi R24,50
	sts _TxRxBuf+1,R24
	.dbline 225
; 	 TxRxBuf[2]=0x29;
	ldi R24,41
	sts _TxRxBuf+2,R24
	.dbline 226
; 	 TxRxBuf[3]=0x30;  
	ldi R24,48
	sts _TxRxBuf+3,R24
	.dbline 227
; 	tf=3;
	ldi R24,3
	sts _tf,R24
	.dbline 228
; 	}
L50:
	.dbline 230
; //------------------------------------------------------------------------------
; 	if(tf)
	lds R2,_tf
	tst R2
	breq L58
	.dbline 231
; 	{
	.dbline 232
; 	 PORTC=seg[tf];
	ldi R24,<_seg
	ldi R25,>_seg
	mov R30,R2
	clr R31
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	out 0x15,R2
	.dbline 233
; 	 Low_Display4;
	cbi 0x1b,4
	.dbline 233
	.dbline 234
; 	 Low_Display3;
	cbi 0x1b,3
	.dbline 234
	.dbline 235
; 	 Low_Display2;
	cbi 0x1b,2
	.dbline 235
	.dbline 236
; 	 Low_Display1;
	cbi 0x1b,1
	.dbline 236
	.dbline 237
; 	tf=0;
	clr R2
	sts _tf,R2
	.dbline 238
; 	Low_JDQ ;
	cbi 0x12,7
	.dbline 239
; 	SetTxMode();				// 激发数据发s送
	xcall _SetTxMode
	.dbline 240
; 	TxPacket(TxRxBuf);			// 装载待发送数据	
	ldi R16,<_TxRxBuf
	ldi R17,>_TxRxBuf
	xcall _TxPacket
	.dbline 241
; 	Delay(200); 	
	ldi R16,200
	ldi R17,0
	xcall _Delay
	.dbline 242
; 	TxRxBuf[0]=0;
	clr R2
	sts _TxRxBuf,R2
	.dbline 243
; 	Hign_JDQ ;
	sbi 0x12,7
	.dbline 244
; 	 }																		
L58:
	.dbline 245
L32:
	.dbline 197
	xjmp L31
X1:
	.dbline -2
L30:
	adiw R28,63
	adiw R28,1  ; offset = 64
	.dbline 0 ; func end
	ret
	.dbsym l temp 0 A[64:32]i
	.dbsym l j 1 i
	.dbsym l i 1 i
	.dbend
	.area bss(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
_tf::
	.blkb 1
	.dbsym e tf _tf c
_TxRxBuf::
	.blkb 4
	.dbsym e TxRxBuf _TxRxBuf A[4:4]c
