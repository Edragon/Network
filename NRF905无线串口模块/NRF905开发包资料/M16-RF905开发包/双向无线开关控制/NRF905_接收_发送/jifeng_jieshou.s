	.module jifeng_jieshou.c
	.area text(rom, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
_TxAddress::
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.dbsym e TxAddress _TxAddress A[4:4]c
_seg::
	.blkb 2
	.area idata
	.byte 192,207
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 164,176
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 153,146
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 130,248
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 128,144
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.dbsym e seg _seg A[10:10]c
_RFConf::
	.blkb 2
	.area idata
	.byte 0,'L
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 12,'D
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 4,4
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.blkb 1
	.area idata
	.byte 'X
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.dbsym e RFConf _RFConf A[11:11]c
	.area text(rom, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
	.dbfunc e Delay _Delay fV
;              i -> R20,R21
;              x -> R16,R17
	.even
_Delay::
	st -y,R20
	st -y,R21
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
; 	uint i;
; 	while(x--)
; 	for(i=0;i<80;i++);
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
X0:
L3:
	.dbline 107
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
	.dbline 112
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
; 	while(!(SPSR & (1<<SPIF) ))
; 	{};			// 等待SPI发送完毕
	.dbline 122
L12:
	.dbline 121
	sbis 0xe,7
	rjmp L11
X2:
	.dbline 122
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
	st -y,R20
	st -y,R21
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
; 	{
	.dbline 147
; 	 SpiReadSpiWrite(RFConf[i]);
	ldi R24,<_RFConf
	ldi R25,>_RFConf
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 148
; 	}
L17:
	.dbline 145
	inc R20
L19:
	.dbline 145
	cpi R20,11
	brlo L16
X3:
	.dbline 149
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
; 	{
	.dbline 160
; 	SpiReadSpiWrite(TxBUF[i]);		// 待发送的32字节数据
	mov R30,R20
	clr R31
	add R30,R10
	adc R31,R11
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 161
; 	}						
L22:
	.dbline 158
	inc R20
L24:
	.dbline 158
	cpi R20,4
	brlo L21
X4:
	.dbline 162
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
; 	{
	.dbline 168
; 	SpiReadSpiWrite(TxAddress[i]);
	ldi R24,<_TxAddress
	ldi R25,>_TxAddress
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 169
; 	}
L26:
	.dbline 166
	inc R20
L28:
	.dbline 166
	cpi R20,4
	brlo L25
X5:
	.dbline 170
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
	.dbline 0 ; func end
	xjmp pop_xgset300C
	.dbsym r i 20 c
	.dbsym r TxBUF 10 pc
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
	.dbfunc e SetRxMode _SetRxMode fV
	.even
_SetRxMode::
	.dbline -1
	.dbline 185
; }
; //------------------------------------------------------------------------
; //------------------------------设置接收模式激发--------------------------------
; void SetRxMode(void)
; {
	.dbline 186
; 	Low_nrf905_TX_EN;
	cbi 0x18,0
	.dbline 187
; 	Hign_nrf905_TRX_CE;
	sbi 0x12,4
	.dbline 188
; 	Delay(1000); 					// delay for mode change(>=650us)
	ldi R16,1000
	ldi R17,3
	xcall _Delay
	.dbline -2
L30:
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
	.dbline 192
; }
; //-----------------------------------读接收数据包-------------------------------
; void RxPacket(void)							//读数据
; {
	.dbline 194
; 	uchar i;
;     Low_nrf905_TRX_CE;
	cbi 0x12,4
	.dbline 195
; 	Low_nrf905_CSN;						    // 使能SPI
	cbi 0x18,4
	.dbline 196
;     Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 197
; 	SpiReadSpiWrite(RRP);				   // 写入数据接收缓冲区数据命令
	ldi R16,36
	xcall _SpiReadSpiWrite
	.dbline 198
; 	for (i = 0 ;i < 4 ;i++)
	clr R20
	xjmp L35
L32:
	.dbline 199
; 	{   
	.dbline 200
; 	TxRxBuf[i]=SpiReadSpiWrite(0);	  // 读取数据接收缓冲区数据       
	clr R16
	xcall _SpiReadSpiWrite
	ldi R24,<_TxRxBuf
	ldi R25,>_TxRxBuf
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	std z+0,R16
	.dbline 201
; 	}
L33:
	.dbline 198
	inc R20
L35:
	.dbline 198
	cpi R20,4
	brlo L32
X6:
	.dbline 202
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 203
;     Delay(2);                            //
	ldi R16,2
	ldi R17,0
	xcall _Delay
	.dbline 204
; 	Hign_nrf905_TRX_CE;							
	sbi 0x12,4
	.dbline -2
L31:
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
	.dbline 208
; }
; //--------------------------------设置接收模式----------------------------------
; void  RX(void)
; {
	.dbline 209
;     SetRxMode();			          //设置NRF905接收模式
	xcall _SetRxMode
	.dbline 210
; 	RxPacket();                     //读取接收数据缓冲区
	xcall _RxPacket
	.dbline 211
; 	Delay(10);
	ldi R16,10
	ldi R17,0
	xcall _Delay
	.dbline 212
; 	if(TxRxBuf[0]==0x29)
	lds R24,_TxRxBuf
	cpi R24,41
	brne L37
X7:
	.dbline 213
; 	{
	.dbline 214
; 	 PORTC=seg[1];
	lds R2,_seg+1
	out 0x15,R2
	.dbline 215
; 	 Low_Display4;
	cbi 0x1b,4
	.dbline 215
	.dbline 216
; 	 Hign_Display3;
	sbi 0x1b,3
	.dbline 216
	.dbline 217
; 	 Hign_Display2;
	sbi 0x1b,2
	.dbline 217
	.dbline 218
; 	 Hign_Display1;
	sbi 0x1b,1
	.dbline 218
	.dbline 219
; 	}
L37:
	.dbline 220
; 	if(TxRxBuf[0]==0x30)
	lds R24,_TxRxBuf
	cpi R24,48
	brne L40
X8:
	.dbline 221
; 	{
	.dbline 222
; 	 PORTC=seg[2];
	lds R2,_seg+2
	out 0x15,R2
	.dbline 223
; 	 Hign_Display4;
	sbi 0x1b,4
	.dbline 223
	.dbline 224
; 	 Low_Display3;
	cbi 0x1b,3
	.dbline 224
	.dbline 225
; 	 Hign_Display2;
	sbi 0x1b,2
	.dbline 225
	.dbline 226
; 	 Hign_Display1;
	sbi 0x1b,1
	.dbline 226
	.dbline 227
; 	}
L40:
	.dbline 228
; 	if(TxRxBuf[0]==0x31)
	lds R24,_TxRxBuf
	cpi R24,49
	brne L43
X9:
	.dbline 229
; 	{
	.dbline 230
; 	 PORTC=seg[3];
	lds R2,_seg+3
	out 0x15,R2
	.dbline 231
; 	 Hign_Display4;
	sbi 0x1b,4
	.dbline 231
	.dbline 232
; 	 Hign_Display3;
	sbi 0x1b,3
	.dbline 232
	.dbline 233
; 	 Low_Display2;
	cbi 0x1b,2
	.dbline 233
	.dbline 234
; 	 Hign_Display1;
	sbi 0x1b,1
	.dbline 234
	.dbline 236
; 
; 	}
L43:
	.dbline -2
L36:
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
	.dbline 240
; }
; //------------------------------主函数------------------------------------------
; void main(void)
; {  
	.dbline 242
; 	uint i,j,temp[32];
; 	DDRD=0xf2;		  //
	ldi R24,242
	out 0x11,R24
	.dbline 243
; 	DDRB=0xB3;		  //
	ldi R24,179
	out 0x17,R24
	.dbline 244
; 	DDRA=0x1e;       //
	ldi R24,30
	out 0x1a,R24
	.dbline 245
; 	DDRC=0xff; 		//LED端口设置
	ldi R24,255
	out 0x14,R24
	.dbline 246
; 	PORTA=0x00;
	clr R2
	out 0x1b,R2
	.dbline 247
; 	PORTC=0xbf;
	ldi R24,191
	out 0x15,R24
	.dbline 248
; 	Hign_BELL;
	sbi 0x12,5
	.dbline 248
	.dbline 249
; 	Hign_JDQ ;
	sbi 0x12,7
	.dbline 250
; 	Spi_initial();
	xcall _Spi_initial
	.dbline 251
; 	system_Init();
	xcall _system_Init
	.dbline 252
; 	Config905();
	xcall _Config905
	xjmp L48
L47:
	.dbline 254
; 	while(1)
;  {
	.dbline 255
;      RX();
	xcall _RX
	.dbline 257
; //------------------------------------------------------------------------------
; 	if((PINA & 0x20) == 0)		  //有键按下KEY1
	sbic 0x19,5
	rjmp L50
X10:
	.dbline 258
; 	{
L52:
	.dbline 259
; 	while(!(PINA & 0x20));   			//等待按键松开GREEN
L53:
	.dbline 259
	sbis 0x19,5
	rjmp L52
X11:
	.dbline 260
; 	 TxRxBuf[0]=0x29;
	ldi R24,41
	sts _TxRxBuf,R24
	.dbline 261
; 	 tf=1;   
	ldi R24,1
	sts _tf,R24
	.dbline 262
; 	 PORTC=seg[1];
	lds R2,_seg+1
	out 0x15,R2
	.dbline 263
; 	 Low_Display4;
	cbi 0x1b,4
	.dbline 263
	.dbline 264
; 	 Hign_Display3;
	sbi 0x1b,3
	.dbline 264
	.dbline 265
; 	 Hign_Display2;
	sbi 0x1b,2
	.dbline 265
	.dbline 266
; 	 Hign_Display1;
	sbi 0x1b,1
	.dbline 266
	.dbline 267
; 	 }
L50:
	.dbline 269
; //------------------------------------------------------------------------------
; 	if((PINA & 0x40) == 0)			//有键按下KEY2
	sbic 0x19,6
	rjmp L56
X12:
	.dbline 270
; 	{
L58:
	.dbline 271
; 	while(!(PINA & 0x40));   			//等待按键松开GREEN
L59:
	.dbline 271
	sbis 0x19,6
	rjmp L58
X13:
	.dbline 272
;  	 TxRxBuf[0]=0x30; 
	ldi R24,48
	sts _TxRxBuf,R24
	.dbline 273
; 	 tf=1;    
	ldi R24,1
	sts _tf,R24
	.dbline 274
; 	 PORTC=seg[2];
	lds R2,_seg+2
	out 0x15,R2
	.dbline 275
; 	 Hign_Display4;
	sbi 0x1b,4
	.dbline 275
	.dbline 276
; 	 Low_Display3;
	cbi 0x1b,3
	.dbline 276
	.dbline 277
; 	 Hign_Display2;
	sbi 0x1b,2
	.dbline 277
	.dbline 278
; 	 Hign_Display1;
	sbi 0x1b,1
	.dbline 278
	.dbline 279
; 	 }
L56:
	.dbline 281
; //------------------------------------------------------------------------------
; 	if((PINA & 0x80) == 0)			//有键按下KEY3
	sbic 0x19,7
	rjmp L62
X14:
	.dbline 282
; 	{
L64:
	.dbline 283
; 	while(!(PINA & 0x80));   			//等待按键松开GREEN
L65:
	.dbline 283
	sbis 0x19,7
	rjmp L64
X15:
	.dbline 284
;  	 TxRxBuf[0]=0x31;
	ldi R24,49
	sts _TxRxBuf,R24
	.dbline 285
; 	 tf=3;
	ldi R24,3
	sts _tf,R24
	.dbline 286
; 	 PORTC=seg[3];
	lds R2,_seg+3
	out 0x15,R2
	.dbline 287
; 	 Hign_Display4;
	sbi 0x1b,4
	.dbline 287
	.dbline 288
; 	 Hign_Display3;
	sbi 0x1b,3
	.dbline 288
	.dbline 289
; 	 Low_Display2;
	cbi 0x1b,2
	.dbline 289
	.dbline 290
; 	 Hign_Display1;
	sbi 0x1b,1
	.dbline 290
	.dbline 291
; 	}
L62:
	.dbline 293
; //------------------------------------------------------------------------------
; 	if(tf)
	lds R2,_tf
	tst R2
	breq L68
X16:
	.dbline 294
; 	{
	.dbline 295
; 	tf=0;
	clr R2
	sts _tf,R2
	.dbline 296
; 	Low_JDQ ;
	cbi 0x12,7
	.dbline 298
; 	//--------------------------------------------------------
; 	SetTxMode();				// 激发数据发s送
	xcall _SetTxMode
	.dbline 299
; 	TxPacket(TxRxBuf);			// 装载待发送数据	
	ldi R16,<_TxRxBuf
	ldi R17,>_TxRxBuf
	xcall _TxPacket
	.dbline 300
; 	Delay(200); 	
	ldi R16,200
	ldi R17,0
	xcall _Delay
	.dbline 302
; 	//-------------------------------------------------
; 	TxRxBuf[0]=0;
	clr R2
	sts _TxRxBuf,R2
	.dbline 303
; 	 }
L68:
	.dbline 306
; 	 //****************************************************************
; 
; 	Hign_BELL;
	sbi 0x12,5
	.dbline 306
	.dbline 307
; 	Hign_JDQ ;															
	sbi 0x12,7
	.dbline 308
; }
L48:
	.dbline 253
	xjmp L47
X17:
	.dbline -2
L46:
	.dbline 0 ; func end
	adiw R28,63
	adiw R28,1  ; offset = 64
	ret
	.dbsym l temp 0 A[64:32]i
	.dbsym l j 1 i
	.dbsym l i 1 i
	.dbend
	.area bss(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\双向无线开关控制\NRF905_接收_发送\jifeng_jieshou.c
_tf::
	.blkb 1
	.dbsym e tf _tf c
_TxRxBuf::
	.blkb 4
	.dbsym e TxRxBuf _TxRxBuf A[4:4]c
; }
