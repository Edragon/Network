	.module jfp_fasong.c
	.area text(rom, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
_TxAddress::
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.dbsym e TxAddress _TxAddress A[4:4]c
_RFConf::
	.blkb 2
	.area idata
	.byte 0,'L
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 12,'D
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 4,4
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.blkb 1
	.area idata
	.byte 'X
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.dbsym e RFConf _RFConf A[11:11]c
	.area text(rom, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
	.dbfunc e Delay _Delay fV
;              i -> R20,R21
;              x -> R16,R17
	.even
_Delay::
	st -y,R20
	st -y,R21
	.dbline -1
	.dbline 86
; //ICC-AVR application builder : 2007-8-11 20:37:32
; // Target : M16
; // Crystal: 8.0000Mhz
; #include <iom16v.h>
; #include <macros.h>
; #define uint  unsigned int
; #define uchar unsigned char
; ///////////////////////////模式控制定义/////////////////////////////////
; //#define  nrf905_TX_EN	  PB0	    //输出1  
; #define    Low_nrf905_TX_EN     PORTB &= ~(1 << PB0)
; #define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0)
; //#define  nrf905_TRX_CE  PD4 	    //输出1
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
; //#define  nrf905_CD      PD3    //输入0
; #define   Hign_nrf905_CD    PORTD |= (1 << PD3) 
; #define   Low_nrf905_CD     PORTD &= ~(1 << PD3) 
; #define   Read_nrf905_CD    PINB & (1 << PD4)
; //#define  nrf905_AM      PB3	    //输入0
; #define   Hign_nrf905_AM    PORTB |= (1 << PB3) 
; #define   Low_nrf905_AM     PORTB &= ~(1 << PB3)
; #define   Read_nrf905_AM    PINB & (1 << PB3)
; //#define  nrf905_DR      PB2  		//输入0
; #define   Hign_nrf905_DR    PORTB |= (1 << PB2)
; #define   Low_nrf905_DR     PORTB &= ~(1 << PB2)
; #define   Read_nrf905_DR    PINB & (1 << PB2)
; //-------------------------------BELL蜂明器-------------------------------------
; #define   High_BELL  PORTD |= (1 << PD5);   
; #define   Low_BELL     PORTD &= ~(1 << PD5); 
; //-------------------------------JDQ继电器--------------------------------------
; #define   Hign_JDQ  PORTD |= (1 << PD7)
; #define   Low_JDQ     PORTD &= ~(1 << PD7)
; //读取键值KEYA-KEYB-KEYC  
; #define   Read_KEY_A   	    PINA & (1 << PA6)
; #define   Read_KEY_B   	    PINA & (1 << PA5)
; #define   Read_KEY_C    	PINA & (1 << PA4)
; //----------------------------------905-SPI指令---------------------------------
; #define WC	0x00
; #define RRC	0x10
; #define WTP	0x20
; #define RTP	0x21
; #define WTA	0x22
; #define RTA	0x23
; #define RRP	0x24
; //---------------------------------发送数据-------------------------------------
; uchar TxRxBuf[4];
; //----------------------------------接收地址------------------------------------
; uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
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
	.dbline 89
; 	uint i;
; 	while(x--)
; 	for(i=0;i<80;i++);
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
X0:
L3:
	.dbline 88
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
	.dbline 93
; }
; //----------------------------------SPI初始化-----------------------------------
; void Spi_initial()
; {
	.dbline 96
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
	.dbline 100
; }
; //---------------------------------SPI读写程序----------------------------------	
; uchar SpiReadSpiWrite(unsigned char cData)//r
; {
	.dbline 101
; 	SPDR = cData;
	out 0xf,R16
L11:
	.dbline 103
; 	while(!(SPSR & (1<<SPIF) ))
; 	{};			// 等待SPI发送完毕
	.dbline 103
L12:
	.dbline 102
	sbis 0xe,7
	rjmp L11
X2:
	.dbline 103
	.dbline 104
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
	.dbline 108
; }
; //---------------------------------系统状态初始化-------------------------------
; void system_Init(void)			//r
; {
	.dbline 110
; 
;    	Hign_nrf905_CSN;				// Spi 	disable
	sbi 0x18,4
	.dbline 111
; 	Low_nrf905_SCK;				// Spi clock line init low
	cbi 0x18,7
	.dbline 112
; 	Low_nrf905_DR;				// Init DR for input
	cbi 0x18,2
	.dbline 113
; 	Low_nrf905_AM;				// Init AM for input
	cbi 0x18,3
	.dbline 114
; 	Low_nrf905_CD;				// Init nrf905_CDfor input
	cbi 0x12,3
	.dbline 115
; 	Hign_nrf905_PWR;				// nRF905 power on
	sbi 0x18,1
	.dbline 116
; 	Low_nrf905_TRX_CE;			// Set nRF905 in standby mode
	cbi 0x12,4
	.dbline 117
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
	st -y,R20
	st -y,R21
	.dbline -1
	.dbline 121
; }
; //--------------------------------NRF905寄存器初始化函数------------------------
; void Config905(void)
; {
	.dbline 123
; 	uchar i;
; 	Low_nrf905_CSN;	
	cbi 0x18,4
	.dbline 124
; 	Delay(1);				// Spi enable for write a spi command
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 126
; 	//SpiWrite(WC);				// Write config command写放配置命令
; 	for (i=0;i<11;i++)			// Write configration words  写放配置字
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
;          TxBUF -> R10,R11
	.even
_TxPacket::
	xcall push_xgset300C
	movw R10,R16
	.dbline -1
	.dbline 134
; }
; //--------------------------------NRF905待发数据打包----------------------------
; void TxPacket(uchar TxBUF[4])
; {
	.dbline 136
; 	uchar i;
; 	Low_nrf905_CSN;		   						// 使能Spi，允许对nrf905进行读写操作
	cbi 0x18,4
	.dbline 137
; 	Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 138
; 	SpiReadSpiWrite(WTP);				// 写数据前先写写数据命令
	ldi R16,32
	xcall _SpiReadSpiWrite
	.dbline 139
; 	for (i=0;i<4;i++)
	clr R20
	xjmp L24
L21:
	.dbline 140
; 	{
	.dbline 141
; 	SpiReadSpiWrite(TxBUF[i]);		// 待发送的32字节数据
	mov R30,R20
	clr R31
	add R30,R10
	adc R31,R11
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 142
; 	}						
L22:
	.dbline 139
	inc R20
L24:
	.dbline 139
	cpi R20,4
	brlo L21
X4:
	.dbline 143
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 144
; 	Delay(1);							// 关闭Spi，不允许对nrf905进行读写操作
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 145
; 	Low_nrf905_CSN;								// 使能Spi
	cbi 0x18,4
	.dbline 146
; 	SpiReadSpiWrite(WTA);				// 写地址前首先先写地址命令
	ldi R16,34
	xcall _SpiReadSpiWrite
	.dbline 147
; 	for (i=0;i<4;i++)					// 写 4 bytes 地址
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
; 	Hign_nrf905_CSN;					// 关闭Spi
	sbi 0x18,4
	.dbline 152
; 	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	sbi 0x12,4
	.dbline 153
; 	Delay(1);							// 等待DR变高
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 154
; 	Low_nrf905_TRX_CE;							// 设置TRX_CE=0
	cbi 0x12,4
	.dbline -2
L20:
	.dbline 0 ; func end
	xjmp pop_xgset300C
	.dbsym r i 20 c
	.dbsym r TxBUF 10 pc
	.dbend
	.dbfunc e SetTxMode _SetTxMode fV
	.even
_SetTxMode::
	.dbline -1
	.dbline 158
; }
; //-------------------------------发送模式激发-----------------------------------
; void SetTxMode(void)
; {
	.dbline 159
; 	Low_nrf905_TRX_CE;				//
	cbi 0x12,4
	.dbline 160
; 	Hign_nrf905_TX_EN;				//发送使能
	sbi 0x18,0
	.dbline 161
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
	.dbline 165
; }
; //------------------------------主函数------------------------------------------
; void main(void)
; {  
	.dbline 167
; 	uint i,j,temp[32];
; 	DDRD=0x32;		  //
	ldi R24,50
	out 0x11,R24
	.dbline 168
; 	DDRB=0xB3;		  //
	ldi R24,179
	out 0x17,R24
	.dbline 169
; 	DDRA=0x8f;		  //
	ldi R24,143
	out 0x1a,R24
	.dbline 170
; 	PORTA=0x00;
	clr R2
	out 0x1b,R2
	.dbline 171
; 	PORTC=0xbf;
	ldi R24,191
	out 0x15,R24
	.dbline 172
; 	 High_BELL;
	sbi 0x12,5
	.dbline 172
	.dbline 173
; 	 Hign_JDQ;
	sbi 0x12,7
	.dbline 174
; 	Spi_initial();
	xcall _Spi_initial
	.dbline 175
; 	system_Init();
	xcall _system_Init
	.dbline 176
; 	Config905();
	xcall _Config905
	.dbline 177
; 	Delay(500);
	ldi R16,500
	ldi R17,1
	xcall _Delay
	xjmp L32
L31:
	.dbline 179
; 	while(1)
;  {
	.dbline 183
; 	//TX();
; 
; //------------------------------------------------------------------------------
; 	if((PINA & 0x10) == 0x00)						//有键按下
	sbic 0x19,4
	rjmp L34
X6:
	.dbline 184
; 	{
L36:
	.dbline 185
; 	 while(!(PINA & 0x10));   			//等待按键松开  RED
L37:
	.dbline 185
	sbis 0x19,4
	rjmp L36
X7:
	.dbline 186
; 	 TxRxBuf[0]=0x31;
	ldi R24,49
	sts _TxRxBuf,R24
	.dbline 187
; 	 TxRxBuf[1]=0x31;
	sts _TxRxBuf+1,R24
	.dbline 188
; 	 TxRxBuf[2]=0x29;
	ldi R24,41
	sts _TxRxBuf+2,R24
	.dbline 189
; 	 TxRxBuf[3]=0x30;   
	ldi R24,48
	sts _TxRxBuf+3,R24
	.dbline 192
; 
; //------------------------------------------------------------------------------
;      SetTxMode();
	xcall _SetTxMode
	.dbline 193
; 	 TxPacket(TxRxBuf);													
	ldi R16,<_TxRxBuf
	ldi R17,>_TxRxBuf
	xcall _TxPacket
	.dbline 194
; 	}
L34:
	.dbline 196
; //------------------------------------------------------------------------------
; 	if((PINA & 0x20) == 0x00)		//有键按下
	sbic 0x19,5
	rjmp L42
X8:
	.dbline 197
; 	{
L44:
	.dbline 198
; while(!(PINA & 0x20));   			//等待按键松开GREEN
L45:
	.dbline 198
	sbis 0x19,5
	rjmp L44
X9:
	.dbline 199
; 	 TxRxBuf[0]=0x30;
	ldi R24,48
	sts _TxRxBuf,R24
	.dbline 200
; 	 TxRxBuf[1]=0x31;
	ldi R24,49
	sts _TxRxBuf+1,R24
	.dbline 201
; 	 TxRxBuf[2]=0x32;
	ldi R24,50
	sts _TxRxBuf+2,R24
	.dbline 202
; 	 TxRxBuf[3]=0x29;    
	ldi R24,41
	sts _TxRxBuf+3,R24
	.dbline 204
; //------------------------------------------------------------------------------
;      SetTxMode();			        // 设置进入发送状态
	xcall _SetTxMode
	.dbline 205
; 	 TxPacket(TxRxBuf);			    // 装载待发送数据
	ldi R16,<_TxRxBuf
	ldi R17,>_TxRxBuf
	xcall _TxPacket
	.dbline 206
; 	 }
L42:
	.dbline 208
; //------------------------------------------------------------------------------
; 	if((PINA & 0x40) == 0x00)	    //有键按下
	sbic 0x19,6
	rjmp L50
X10:
	.dbline 209
; 	{
L52:
	.dbline 210
; 	while(!(PINA & 0x40));   		//等待按键松开GREEN
L53:
	.dbline 210
	sbis 0x19,6
	rjmp L52
X11:
	.dbline 211
;  	 TxRxBuf[0]=0x29;
	ldi R24,41
	sts _TxRxBuf,R24
	.dbline 212
; 	 TxRxBuf[1]=0x30;
	ldi R24,48
	sts _TxRxBuf+1,R24
	.dbline 213
; 	 TxRxBuf[2]=0x31;
	ldi R24,49
	sts _TxRxBuf+2,R24
	.dbline 214
; 	 TxRxBuf[3]=0x32;  
	ldi R24,50
	sts _TxRxBuf+3,R24
	.dbline 216
; //------------------------------------------------------------------------------
;      SetTxMode();                   // 设置进入发送状态
	xcall _SetTxMode
	.dbline 217
; 	 TxPacket(TxRxBuf);             // 装载待发送数据
	ldi R16,<_TxRxBuf
	ldi R17,>_TxRxBuf
	xcall _TxPacket
	.dbline 218
; 	 }
L50:
	.dbline 219
; }
L32:
	.dbline 178
	xjmp L31
X12:
	.dbline -2
L30:
	.dbline 0 ; func end
	adiw R28,63
	adiw R28,1  ; offset = 64
	ret
	.dbsym l temp 0 A[64:32]i
	.dbsym l j 1 i
	.dbsym l i 1 i
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_发送\jfp_fasong.c
_TxRxBuf::
	.blkb 4
	.dbsym e TxRxBuf _TxRxBuf A[4:4]c
; }
