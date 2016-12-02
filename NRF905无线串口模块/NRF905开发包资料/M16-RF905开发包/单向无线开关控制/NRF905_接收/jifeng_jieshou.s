	.module jifeng_jieshou.c
	.area text(rom, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
_TxAddress::
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.dbsym e TxAddress _TxAddress A[4:4]c
_RFConf::
	.blkb 2
	.area idata
	.byte 0,'L
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 12,'D
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 4,4
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.blkb 1
	.area idata
	.byte 'X
	.area data(ram, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	.dbsym e RFConf _RFConf A[11:11]c
	.area text(rom, con, rel)
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
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
; //---------------------------------模式控制定义---------------------------------
; //#define  nrf905_TX_EN	  PB0	    //输出1
; #define   Hign_nrf905_TX_EN    PORTB |= (1 << PB0);   
; #define   Low_nrf905_TX_EN     PORTB &= ~(1 << PB0); 
; //#define  nrf905_TRX_CE  PD4	    //输出1
; #define   Hign_nrf905_TRX_CE    PORTD |= (1 << PD4);   
; #define   Low_nrf905_TRX_CE     PORTD &= ~(1 << PD4); 
; //#define  nrf905_PWR     PB1 	    //输出1
; #define   Hign_nrf905_PWR    PORTB |= (1 << PB1);   
; #define   Low_nrf905_PWR     PORTB &= ~(1 << PB1); 
; //--------------------------------NRF905-SPI口接口定义--------------------------
; //#define  nrf905_MISO	  PB6   	//输入0
; //#define  nrf905_MOSI    PB5	    //输出1
; //#define  nrf905_SCK     PB7	    //输出1
; #define   Low_nrf905_SCK     PORTB &= ~(1 << PB7); 
; //#define  nrf905_CSN     PB4		//输出1		
; #define   Hign_nrf905_CSN    PORTB |= (1 << PB4);   
; #define   Low_nrf905_CSN     PORTB &= ~(1 << PB4); 						
; //-------------------------------NRF905状态输出口-------------------------------
; //#define  nrf905_CD      PD3	    //输入0
; #define   Hign_nrf905_CD    PORTD |= (1 << PD3);   
; #define   Low_nrf905_CD     PORTD &= ~(1 << PD3); 
; #define   Read_nrf905_CD    PINB & (1 << PD4);
; //#define  nrf905_AM      PB3	    //输入0
; #define   Hign_nrf905_AM    PORTB |= (1 << PB3);   
; #define   Low_nrf905_AM     PORTB &= ~(1 << PB3); 
; #define   Read_nrf905_AM    PINB & (1 << PB3);
; //#define  nrf905_DR      PB2  		//输入0
; #define   Hign_nrf905_DR     PORTB |= (1 << PB2);   
; #define   Low_nrf905_DR     PORTB &= ~(1 << PB2); 
; #define   Read_nrf905_DR    PINB & (1 << PB2);   
; //-------------------------------BELL蜂明器-------------------------------------
; #define   Hign_BELL  PORTD |= (1 << PD5);   
; #define   Low_BELL     PORTD &= ~(1 << PD5); 
; //-------------------------------JDQ继电器--------------------------------------
; #define   Hign_JDQ  PORTD |= (1 << PD7)
; #define   Low_JDQ     PORTD &= ~(1 << PD7)
; 
; //----------------------------------NRF905-SPI指令------------------------------
; #define WC	0x00
; #define RRC	0x10
; #define WTP	0x20
; #define RTP	0x21
; #define WTA	0x22
; #define RTA	0x23
; #define RRP	0x24
; //---------------------------------发送数据-------------------------------------
; uchar TxRxBuffer[4];
; //----------------------------------接收地址------------------------------------
; uchar TxAddress[4]={0xcc,0xcc,0xcc,0xcc };    
; //------------------------------------------------------------------------------
; uchar count1 ,count2;
; //----------------------------------寄存器配置----------------------------------
; uchar RFConf[11]=
; {
;   0x00,                            //配置命令//
;   0x4c,                           //CH_NO,配置频段在430MHZ
;   0x0C,                          //输出功率为10db,不重发，节电为正常模式
;   0x44,                         //地址宽度设置，为4字节
;   0x04,0x04,                   //接收发送有效数据长度为4字节
;   0xCC,0xCC,0xCC,0xCC,        //接收地址
;   0x58,                      //CRC充许，8位CRC校验，外部时钟信号不使能，16M晶振
; };
; //----------------------------------NRF905函数申明------------------------------
; void Delay(uint x);						       //延时子程序																							
; void Spi_initial();                            //SPI初始化
; uchar SpiReadSpiWrite(unsigned char cData);    //SPI读写子程序
; void system_Init(void);		   				   //系统初始化
; void Config905(void);						   //NRF905初始化子程序
; void TxPacket(void);						
; void SetTxMode(void);						   //数据发送
; void SetRxMode(void);						   //
; void TX(void);
; unsigned char CheckDR(void);
; void RxPacket(void);
; void  RX(void);
; //-------------------------------串口函数申明-----------------------------------
; void StartUART(void);
; void R_S_Byte(uchar R_Byte);
; //----------------------------------100us延时子程序-----------------------------
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
; //----------------------------------SPI初始化-----------------------------------
; void Spi_initial()
; {
	.dbline 97
; 	SPCR   = (1<<SPE)|(1<<MSTR)|(0<<CPOL)|(0<<SPR0);// 主机模式，fck/16, SPI方式0
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
; //---------------------------------SPI读写程序----------------------------------	
; uchar SpiReadSpiWrite(unsigned char cData)
; {
	.dbline 102
; 	SPDR = cData;
	out 0xf,R16
L11:
	.dbline 104
; 	while(!(SPSR & (1<<SPIF) ))  // 等待SPI发送完毕
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
; //--------------------------------系统状态初始化--------------------------------
; void system_Init(void)			
; {
	.dbline 111
; 
;    	Hign_nrf905_CSN;			// SPI使能
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
; //--------------------------------NRF905寄存器初始化函数------------------------
; void Config905(void)
; {
	.dbline 124
; 	uchar i;
; 	Low_nrf905_CSN;				//SPI使能											
	cbi 0x18,4
	.dbline 124
	.dbline 125
; 	Delay(1);				   
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 126
; 	for (i=0;i<11;i++)			//碞RF905配置字
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
; //--------------------------------NRF905待发数据打包----------------------------
; void TxPacket(void)
; {
	.dbline 136
; 	uchar i;
; 	Low_nrf905_CSN;		   				// 使能Spi，允许对nrf905进行读写操作
	cbi 0x18,4
	.dbline 136
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
; 	for (i=0;i<32;i++)
	clr R20
	xjmp L24
L21:
	.dbline 140
; 	{
	.dbline 141
; 	SpiReadSpiWrite(TxRxBuffer[i]);		// 待发送的32字节数据
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
; 	Delay(1);							// 关闭Spi，不允许对nrf905进行读写操作
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 145
; 	Low_nrf905_CSN;						// 使能Spi
	cbi 0x18,4
	.dbline 145
	.dbline 146
; 	SpiReadSpiWrite(WTA);				// 写地址前首先先写地址命令
	ldi R16,34
	xcall _SpiReadSpiWrite
	.dbline 147
; 	for (i=0;i<4;i++)					// 写入4 bytes 接收地址
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
	.dbline 151
	.dbline 152
; 	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	sbi 0x12,4
	.dbline 152
	.dbline 153
; 	Delay(1);							// 等待DR变高
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 154
; 	Low_nrf905_TRX_CE;					// 设置TRX_CE=0
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
; //------------------------------设置发送模式------------------------------------
; void SetTxMode(void)
; {
	.dbline 159
; 	Low_nrf905_TRX_CE;				//
	cbi 0x12,4
	.dbline 159
	.dbline 160
; 	Hign_nrf905_TX_EN;				//发送使能
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
; //------------------------------设置接收模式激发--------------------------------
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
; //------------------------------发送数据----------------------------------------
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
; //-----------------------------判断是否收到数据---------------------------------
; unsigned char CheckDR(void)		//检查是否有新数据传入 
; {
	.dbline 179
; 	if (PINB & (1 << PB2))
	sbis 0x16,2
	rjmp L33
X6:
	.dbline 180
; 	{
	.dbline 181
; 		return 1; 	 	  		//收到数据
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
; //-----------------------------------读接收数据包-------------------------------
; void RxPacket(void)							//读数据
; {
	.dbline 192
; 	uchar i;
;     Low_nrf905_TRX_CE;
	cbi 0x12,4
	.dbline 192
	.dbline 193
; 	Low_nrf905_CSN;						    // 使能SPI
	cbi 0x18,4
	.dbline 193
	.dbline 194
;     Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 195
; 	SpiReadSpiWrite(RRP);				   // 写入数据接收缓冲区数据命令
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
; 	TxRxBuffer[i]=SpiReadSpiWrite(0);	  // 读取数据接收缓冲区数据       
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
; //--------------------------------设置接收模式----------------------------------
; void  RX(void)
; {
	.dbline 207
;     SetRxMode();			          //设置NRF905接收模式
	xcall _SetRxMode
L41:
	.dbline 208
;     while (CheckDR()==0);	         //等待接收完成
L42:
	.dbline 208
	xcall _CheckDR
	tst R16
	breq L41
X8:
	.dbline 209
; 	RxPacket();                     //读取接收数据缓冲区
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
; //------------------------------主函数------------------------------------------
; void main(void)
; {  
	.dbline 216
; 	uint i;
; 	DDRD=0xF2;						  //端口D设置											  
	ldi R24,242
	out 0x11,R24
	.dbline 217
; 	DDRB=0xB3;					     //端口B设置	
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
; 	Hign_JDQ;			  //关闭继电器				
	sbi 0x12,7
	.dbline 222
; 	Hign_BELL;							
	sbi 0x12,5
	.dbline 222
	.dbline 224
; //------------------------------------------------------------------------------				  			 				
; 	Spi_initial();	                //SPI初始化															  
	xcall _Spi_initial
	.dbline 225
; 	system_Init();				   //系统状态初始化												
	xcall _system_Init
	.dbline 226
; 	Config905();  				  //NRF905初始化	
	xcall _Config905
	xjmp L46
L45:
	.dbline 230
; 	
; //------------------------------------------------------------------------------
; 	while(1)
; 	{
	.dbline 231
; 	RX();  					//接收数据
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
; 	Low_JDQ;			   //打开继电器
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
; 	Low_BELL;			   //打开蜂明器
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
; 	Hign_JDQ;			  //关闭继电器				
	sbi 0x12,7
	.dbline 246
; 	Hign_BELL;			  //关闭蜂明器		
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
	.dbfile F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
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
