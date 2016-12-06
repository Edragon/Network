	.module JASK_PCjieshou.c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
_TxAddress::
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.dbsym e TxAddress _TxAddress A[4:4]c
_seg::
	.blkb 2
	.area idata
	.byte 192,207
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 164,176
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 153,146
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 130,248
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 128,144
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.dbsym e seg _seg A[10:10]c
_RFConf::
	.blkb 2
	.area idata
	.byte 0,'L
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 12,'D
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 4,4
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 2
	.area idata
	.byte 204,204
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.blkb 1
	.area idata
	.byte 'X
	.area data(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.dbsym e RFConf _RFConf A[11:11]c
	.area text(rom, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	.dbfunc e Delay _Delay fV
;              i -> R20,R21
;              x -> R16,R17
	.even
_Delay::
	xcall push_gset1
	.dbline -1
	.dbline 120
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
; //------------------------------LCD状态输出口-----------------------------------
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
; //-------------------------------BELL蜂明器-------------------------------------
; #define   Hign_BELL  PORTD |= (1 << PD5)  
; #define   Low_BELL     PORTD &= ~(1 << PD5) 
; //-------------------------------JDQ继电器--------------------------------------
; #define   Hign_JDQ  PORTD |= (1 << PD7)
; #define   Low_JDQ     PORTD &= ~(1 << PD7)
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
; uchar count1,count2;
; uchar seg[10]={0xC0,0xCF,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};         //0~~9段码
; //---------------------------------NRF905寄存器配置-----------------------------
; uchar RFConf[11]=
; {
;   0x00,                            //配置命令//
;   0x4c,                           //CH_NO,配置频段在430MHZ
;   0x0C,                          //输出功率为10db,不重发，节电为正常模式
;   0x44,                         //地址宽度设置，为4字节
;   0x04,0x04,                   //接收发送有效数据长度为32字节
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
; //----------------------------------100us延时子程序-----------------------------
; void Delay(uint x)
; {
	xjmp L3
L2:
	.dbline 123
	clr R20
	clr R21
	xjmp L8
L5:
	.dbline 123
L6:
	.dbline 123
	subi R20,255  ; offset = 1
	sbci R21,255
L8:
	.dbline 123
	cpi R20,80
	ldi R30,0
	cpc R21,R30
	brlo L5
L3:
	.dbline 122
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
	.dbline 127
; 	for(i=0;i<80;i++);
; }
; //----------------------------------SPI初始化-----------------------------------
; void Spi_initial()
; {
	.dbline 128
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
	.dbline 132
; }
; //---------------------------------SPI读写程序----------------------------------	
; uchar SpiReadSpiWrite(unsigned char cData)
; {
	.dbline 133
; 	SPDR = cData;
	out 0xf,R16
L11:
	.dbline 135
	.dbline 135
L12:
	.dbline 134
; 	while(!(SPSR & (1<<SPIF) ))  // 等待SPI发送完毕
	sbis 0xe,7
	rjmp L11
	.dbline 135
; 	{};			
	.dbline 136
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
	.dbline 140
; }
; //--------------------------------系统状态初始化--------------------------------
; void system_Init(void)			
; {
	.dbline 142
; 
;    	Hign_nrf905_CSN;			// SPI使能
	sbi 0x18,4
	.dbline 142
	.dbline 143
; 	Low_nrf905_SCK;				
	cbi 0x18,7
	.dbline 143
	.dbline 144
; 	Low_nrf905_DR;				// DR=0
	cbi 0x18,2
	.dbline 144
	.dbline 145
; 	Low_nrf905_AM;				// AM=0
	cbi 0x18,3
	.dbline 145
	.dbline 146
; 	Low_nrf905_CD;				// CD=0
	cbi 0x12,3
	.dbline 146
	.dbline 147
; 	Hign_nrf905_PWR;		    // PWR=1
	sbi 0x18,1
	.dbline 147
	.dbline 148
; 	Low_nrf905_TRX_CE;			// nrf905_TRX_CE=0
	cbi 0x12,4
	.dbline 148
	.dbline 149
; 	Low_nrf905_TX_EN ;			// nrf905_TX_EN=0
	cbi 0x18,0
	.dbline 149
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
	.dbline 153
; }
; //--------------------------------NRF905寄存器初始化函数------------------------
; void Config905(void)
; {
	.dbline 155
; 	uchar i;
; 	Low_nrf905_CSN;				//SPI使能											
	cbi 0x18,4
	.dbline 155
	.dbline 156
; 	Delay(1);				   
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 157
; 	for (i=0;i<11;i++)			//碞RF905配置字
	clr R20
	xjmp L19
L16:
	.dbline 158
	.dbline 159
	ldi R24,<_RFConf
	ldi R25,>_RFConf
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 160
L17:
	.dbline 157
	inc R20
L19:
	.dbline 157
	cpi R20,11
	brlo L16
	.dbline 161
; 	{
; 	 SpiReadSpiWrite(RFConf[i]);
; 	}
; 	Hign_nrf905_CSN;					// Disable Spi
	sbi 0x18,4
	.dbline 161
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
	.dbline 165
; }
; //--------------------------------NRF905待发数据打包----------------------------
; void TxPacket(void)
; {
	.dbline 167
; 	uchar i;
; 	Low_nrf905_CSN;		   				// 使能Spi，允许对nrf905进行读写操作
	cbi 0x18,4
	.dbline 167
	.dbline 168
; 	Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 169
; 	SpiReadSpiWrite(WTP);				// 写数据前先写写数据命令
	ldi R16,32
	xcall _SpiReadSpiWrite
	.dbline 170
; 	for (i=0;i<32;i++)
	clr R20
	xjmp L24
L21:
	.dbline 171
	.dbline 172
	ldi R24,<_TxRxBuffer
	ldi R25,>_TxRxBuffer
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 173
L22:
	.dbline 170
	inc R20
L24:
	.dbline 170
	cpi R20,32
	brlo L21
	.dbline 174
; 	{
; 	SpiReadSpiWrite(TxRxBuffer[i]);		// 待发送的32字节数据
; 	}						
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 174
	.dbline 175
; 	Delay(1);							// 关闭Spi，不允许对nrf905进行读写操作
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 176
; 	Low_nrf905_CSN;						// 使能Spi
	cbi 0x18,4
	.dbline 176
	.dbline 177
; 	SpiReadSpiWrite(WTA);				// 写地址前首先先写地址命令
	ldi R16,34
	xcall _SpiReadSpiWrite
	.dbline 178
; 	for (i=0;i<4;i++)					// 写入4 bytes 接收地址
	clr R20
	xjmp L28
L25:
	.dbline 179
	.dbline 180
	ldi R24,<_TxAddress
	ldi R25,>_TxAddress
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	ldd R16,z+0
	xcall _SpiReadSpiWrite
	.dbline 181
L26:
	.dbline 178
	inc R20
L28:
	.dbline 178
	cpi R20,4
	brlo L25
	.dbline 182
; 	{
; 	SpiReadSpiWrite(TxAddress[i]);
; 	}
; 	Hign_nrf905_CSN;					// 关闭Spi
	sbi 0x18,4
	.dbline 182
	.dbline 183
; 	Hign_nrf905_TRX_CE;					// Set TRX_CE high,start Tx data transmission
	sbi 0x12,4
	.dbline 183
	.dbline 184
; 	Delay(1);							// 等待DR变高
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 185
; 	Low_nrf905_TRX_CE;					// 设置TRX_CE=0
	cbi 0x12,4
	.dbline 185
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
	.dbline 189
; }
; //------------------------------设置发送模式------------------------------------
; void SetTxMode(void)
; {
	.dbline 190
; 	Low_nrf905_TRX_CE;				//
	cbi 0x12,4
	.dbline 190
	.dbline 191
; 	Hign_nrf905_TX_EN;				//发送使能
	sbi 0x18,0
	.dbline 191
	.dbline 192
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
	.dbline 196
; }
; //------------------------------设置接收模式激发--------------------------------
; void SetRxMode(void)
; {
	.dbline 197
; 	Low_nrf905_TX_EN;
	cbi 0x18,0
	.dbline 197
	.dbline 198
; 	Hign_nrf905_TRX_CE;
	sbi 0x12,4
	.dbline 198
	.dbline 199
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
	.dbline 203
; }
; //------------------------------发送数据----------------------------------------
; void TX(void)
; {
	.dbline 204
;      SetTxMode();	   // Set nRF905 in Tx mode
	xcall _SetTxMode
	.dbline 205
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
	.dbline 209
; }
; //-----------------------------判断是否收到数据---------------------------------
; unsigned char CheckDR(void)		//检查是否有新数据传入 
; {
	.dbline 210
; 	if (PINB & (1 << PB2))
	sbis 0x16,2
	rjmp L33
	.dbline 211
; 	{
	.dbline 212
; 		return 1; 	 	  		//收到数据
	ldi R16,1
	xjmp L32
L33:
	.dbline 215
; 	}
; 	else
; 	{
	.dbline 216
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
	.dbline 221
; 	}
; }
; //-----------------------------------读接收数据包-------------------------------
; void RxPacket(void)							//读数据
; {
	.dbline 223
; 	uchar i;
;     Low_nrf905_TRX_CE;
	cbi 0x12,4
	.dbline 223
	.dbline 224
; 	Low_nrf905_CSN;						    // 使能SPI
	cbi 0x18,4
	.dbline 224
	.dbline 225
;     Delay(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay
	.dbline 226
; 	SpiReadSpiWrite(RRP);				   // 写入数据接收缓冲区数据命令
	ldi R16,36
	xcall _SpiReadSpiWrite
	.dbline 227
; 	for (i = 0 ;i < 4 ;i++)
	clr R20
	xjmp L39
L36:
	.dbline 228
	.dbline 229
	clr R16
	xcall _SpiReadSpiWrite
	ldi R24,<_TxRxBuffer
	ldi R25,>_TxRxBuffer
	mov R30,R20
	clr R31
	add R30,R24
	adc R31,R25
	std z+0,R16
	.dbline 230
L37:
	.dbline 227
	inc R20
L39:
	.dbline 227
	cpi R20,4
	brlo L36
	.dbline 231
; 	{   
; 	TxRxBuffer[i]=SpiReadSpiWrite(0);	  // 读取数据接收缓冲区数据       
; 	}
; 	Hign_nrf905_CSN;
	sbi 0x18,4
	.dbline 231
	.dbline 232
;     Delay(2);                            //
	ldi R16,2
	ldi R17,0
	xcall _Delay
	.dbline 233
; 	Hign_nrf905_TRX_CE;							
	sbi 0x12,4
	.dbline 233
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
	.dbline 237
; }
; //--------------------------------设置接收模式----------------------------------
; void  RX(void)
; {
	.dbline 238
;     SetRxMode();			          //设置NRF905接收模式
	xcall _SetRxMode
	.dbline 240
;     //while (CheckDR()==0);	         //等待接收完成
; 	RxPacket();                     //读取接收数据缓冲区
	xcall _RxPacket
	.dbline 241
; 	Delay(10);
	ldi R16,10
	ldi R17,0
	xcall _Delay
	.dbline -2
L40:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e dis_zhuye _dis_zhuye fV
	.even
_dis_zhuye::
	.dbline -1
	.dbline 245
; }
; //-------------------------------主界面显示--------------------------------------
; void  dis_zhuye()
; {
	.dbline 246
; 	 PORTC=seg[count2/10];
	ldi R18,10
	ldi R19,0
	lds R16,_count2
	clr R17
	xcall div16s
	movw R30,R16
	ldi R24,<_seg
	ldi R25,>_seg
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	out 0x15,R2
	.dbline 247
; 	 Hign_Display4;
	sbi 0x1b,4
	.dbline 247
	.dbline 248
; 	 Hign_Display3;
	sbi 0x1b,3
	.dbline 248
	.dbline 249
; 	 Hign_Display2;
	sbi 0x1b,2
	.dbline 249
	.dbline 250
; 	 Low_Display1;
	cbi 0x1b,1
	.dbline 250
	.dbline 251
; 	 Delay(80);
	ldi R16,80
	ldi R17,0
	xcall _Delay
	.dbline 252
; 	 Hign_Display1;
	sbi 0x1b,1
	.dbline 252
	.dbline 254
; //------------------------------------------------------------------------------
; 	 PORTC=seg[count2%10];
	ldi R18,10
	ldi R19,0
	lds R16,_count2
	clr R17
	xcall mod16s
	movw R30,R16
	ldi R24,<_seg
	ldi R25,>_seg
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	out 0x15,R2
	.dbline 255
; 	 Low_Display2;
	cbi 0x1b,2
	.dbline 255
	.dbline 256
; 	 Delay(80);
	ldi R16,80
	ldi R17,0
	xcall _Delay
	.dbline 257
; 	 Hign_Display2;
	sbi 0x1b,2
	.dbline 257
	.dbline 259
; //------------------------------------------------ ---------------------------
; 	 PORTC=seg[count1/10];
	ldi R18,10
	ldi R19,0
	lds R16,_count1
	clr R17
	xcall div16s
	movw R30,R16
	ldi R24,<_seg
	ldi R25,>_seg
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	out 0x15,R2
	.dbline 260
; 	 Low_Display3;
	cbi 0x1b,3
	.dbline 260
	.dbline 261
; 	 Delay(80);
	ldi R16,80
	ldi R17,0
	xcall _Delay
	.dbline 262
; 	 Hign_Display3;
	sbi 0x1b,3
	.dbline 262
	.dbline 264
; //----------------------------------------------------------------------------- 
; 	 PORTC=seg[count1%10];
	ldi R18,10
	ldi R19,0
	lds R16,_count1
	clr R17
	xcall mod16s
	movw R30,R16
	ldi R24,<_seg
	ldi R25,>_seg
	add R30,R24
	adc R31,R25
	ldd R2,z+0
	out 0x15,R2
	.dbline 265
; 	 Low_Display4;
	cbi 0x1b,4
	.dbline 265
	.dbline 266
; 	 Delay(80);
	ldi R16,80
	ldi R17,0
	xcall _Delay
	.dbline 267
; 	 Hign_Display4;	  
	sbi 0x1b,4
	.dbline 267
	.dbline -2
L41:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
;              i -> <dead>
	.even
_main::
	.dbline -1
	.dbline 271
; }
; //------------------------------主函数------------------------------------------
; void main(void)
; {  
	.dbline 274
; 	uint i;	
; //------------------------------------------------------------------------------
; 	DDRD=0xb2;		  //
	ldi R24,178
	out 0x11,R24
	.dbline 275
; 	DDRB=0xB3;		  //
	ldi R24,179
	out 0x17,R24
	.dbline 276
; 	DDRA=0x1e;       //
	ldi R24,30
	out 0x1a,R24
	.dbline 277
; 	DDRC=0xff; 		//LED端口设置
	ldi R24,255
	out 0x14,R24
	.dbline 278
; 	PORTA = 0xff;
	out 0x1b,R24
	.dbline 279
; 	Hign_BELL;	
	sbi 0x12,5
	.dbline 280
; 	Hign_JDQ ;
	sbi 0x12,7
	.dbline 282
; //------------------------------------------------------------------------------
; 	Hign_BELL ;
	sbi 0x12,5
	.dbline 283
; 	Hign_JDQ;
	sbi 0x12,7
	.dbline 285
; //------------------------------------------------------------------------------				  			 				
; 	Spi_initial();	                //SPI初始化															  
	xcall _Spi_initial
	.dbline 286
; 	system_Init();				   //系统状态初始化												
	xcall _system_Init
	.dbline 287
; 	Config905();  				  //NRF905初始化						  
	xcall _Config905
	.dbline 289
; //------------------------------------------------------------------------------ 
; 	Delay(6000);
	ldi R16,6000
	ldi R17,23
	xcall _Delay
	.dbline 290
; 		dis_zhuye();	
	xcall _dis_zhuye
	xjmp L44
L43:
	.dbline 293
; //------------------------------------------------------------------------------
; 	while(1)
; 	{
	.dbline 294
; 	RX();  					//接收数据
	xcall _RX
	.dbline 295
; 	if(TxRxBuffer[0])
	lds R2,_TxRxBuffer
	tst R2
	brne X2
	xjmp L46
X2:
	.dbline 296
; 	{
	.dbline 298
; 	
; 		if(TxRxBuffer[0]==0x11)              //A队+1
	mov R24,R2
	cpi R24,17
	brne L48
	.dbline 299
; 			{
	.dbline 300
; 			count1=count1+1;
	lds R24,_count1
	subi R24,255    ; addi 1
	sts _count1,R24
	.dbline 301
; 			Low_BELL;
	cbi 0x12,5
	.dbline 302
; 			}
L48:
	.dbline 303
; 		if(TxRxBuffer[0]==0x21)             //A队+2
	lds R24,_TxRxBuffer
	cpi R24,33
	brne L50
	.dbline 304
; 			{
	.dbline 305
; 			count1=count1+2;
	lds R24,_count1
	subi R24,254    ; addi 2
	sts _count1,R24
	.dbline 306
; 			Low_JDQ;
	cbi 0x12,7
	.dbline 307
; 			}
L50:
	.dbline 308
; 		if(TxRxBuffer[0]==0x31)            //A队+3
	lds R24,_TxRxBuffer
	cpi R24,49
	brne L52
	.dbline 309
; 			{
	.dbline 310
; 			count1=count1+3;
	lds R24,_count1
	subi R24,253    ; addi 3
	sts _count1,R24
	.dbline 311
; 			Low_BELL;
	cbi 0x12,5
	.dbline 312
; 			}
L52:
	.dbline 313
; 		if(TxRxBuffer[0]==0x41)           //B队+1
	lds R24,_TxRxBuffer
	cpi R24,65
	brne L54
	.dbline 314
; 			{
	.dbline 315
; 			count2=count2+1;
	lds R24,_count2
	subi R24,255    ; addi 1
	sts _count2,R24
	.dbline 316
; 			Low_JDQ;
	cbi 0x12,7
	.dbline 317
; 			}
L54:
	.dbline 318
; 		if(TxRxBuffer[0]==0x51)          //B队+2
	lds R24,_TxRxBuffer
	cpi R24,81
	brne L56
	.dbline 319
; 			{
	.dbline 320
; 			count2=count2+2;
	lds R24,_count2
	subi R24,254    ; addi 2
	sts _count2,R24
	.dbline 321
; 			Low_BELL;
	cbi 0x12,5
	.dbline 322
; 			}
L56:
	.dbline 323
; 		if(TxRxBuffer[0]==0x61)         //B队+3
	lds R24,_TxRxBuffer
	cpi R24,97
	brne L58
	.dbline 324
; 			{
	.dbline 325
; 			count2=count2+3;
	lds R24,_count2
	subi R24,253    ; addi 3
	sts _count2,R24
	.dbline 326
; 			Low_JDQ;
	cbi 0x12,7
	.dbline 327
; 			}
L58:
	.dbline 328
; 		if(TxRxBuffer[0]==0x71)        //B队-1
	lds R24,_TxRxBuffer
	cpi R24,113
	brne L60
	.dbline 329
; 			{
	.dbline 330
; 			count1=count1-1;
	lds R24,_count1
	subi R24,1
	sts _count1,R24
	.dbline 331
; 			Low_BELL;
	cbi 0x12,5
	.dbline 332
; 			}
L60:
	.dbline 333
; 		if(TxRxBuffer[0]==0x91)       //B队-1
	lds R24,_TxRxBuffer
	cpi R24,145
	brne L62
	.dbline 334
; 			{
	.dbline 335
; 			count2=count2-1;
	lds R24,_count2
	subi R24,1
	sts _count2,R24
	.dbline 336
; 			Low_BELL;
	cbi 0x12,5
	.dbline 337
; 			}
L62:
	.dbline 339
; 	
; 	}
L46:
	.dbline 340
	xcall _dis_zhuye
	.dbline 341
	sbi 0x12,5
	.dbline 342
	sbi 0x12,7
	.dbline 343
	clr R2
	sts _TxRxBuffer,R2
	.dbline 344
L44:
	.dbline 292
	xjmp L43
X1:
	.dbline -2
L42:
	.dbline 0 ; func end
	ret
	.dbsym l i 1 i
	.dbend
	.area bss(ram, con, rel)
	.dbfile C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
_count2::
	.blkb 1
	.dbsym e count2 _count2 c
_count1::
	.blkb 1
	.dbsym e count1 _count1 c
_TxRxBuffer::
	.blkb 4
	.dbsym e TxRxBuffer _TxRxBuffer A[4:4]c
