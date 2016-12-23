   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  15                     	bsct
  16  0000               _USART_RX_STA:
  17  0000 00            	dc.b	0
  51                     ; 9 void UART1_Configuration(void)//串口初始化配置  
  51                     ; 10 {
  53                     	switch	.text
  54  0000               _UART1_Configuration:
  58                     ; 11 	UART1_DeInit();
  60  0000 cd0000        	call	_UART1_DeInit
  62                     ; 12 	UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, 
  62                     ; 13 							UART1_PARITY_NO,UART1_SYNCMODE_CLOCK_DISABLE,	
  62                     ; 14 							UART1_MODE_TXRX_ENABLE);
  64  0003 4b0c          	push	#12
  65  0005 4b80          	push	#128
  66  0007 4b00          	push	#0
  67  0009 4b00          	push	#0
  68  000b 4b00          	push	#0
  69  000d ae2580        	ldw	x,#9600
  70  0010 89            	pushw	x
  71  0011 ae0000        	ldw	x,#0
  72  0014 89            	pushw	x
  73  0015 cd0000        	call	_UART1_Init
  75  0018 5b09          	addw	sp,#9
  76                     ; 16 	UART1_Cmd(ENABLE);
  78  001a a601          	ld	a,#1
  79  001c cd0000        	call	_UART1_Cmd
  81                     ; 17 	UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  83  001f 4b01          	push	#1
  84  0021 ae0205        	ldw	x,#517
  85  0024 cd0000        	call	_UART1_ITConfig
  87  0027 84            	pop	a
  88                     ; 18 }
  91  0028 81            	ret
 127                     ; 20 void UART1_SendByte(uchar data_8)//发送字节函数
 127                     ; 21 {
 128                     	switch	.text
 129  0029               _UART1_SendByte:
 133                     ; 22 	UART1_SendData8(data_8);
 135  0029 cd0000        	call	_UART1_SendData8
 138  002c               L14:
 139                     ; 23 	while(UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET);
 141  002c ae0080        	ldw	x,#128
 142  002f cd0000        	call	_UART1_GetFlagStatus
 144  0032 4d            	tnz	a
 145  0033 27f7          	jreq	L14
 146                     ; 24 }
 149  0035 81            	ret
 185                     ; 26 void UART1_SendString(uchar *p)//发送字符串函数
 185                     ; 27 {
 186                     	switch	.text
 187  0036               _UART1_SendString:
 189  0036 89            	pushw	x
 190       00000000      OFST:	set	0
 193  0037 200c          	jra	L56
 194  0039               L36:
 195                     ; 30 		UART1_SendByte(*p);
 197  0039 1e01          	ldw	x,(OFST+1,sp)
 198  003b f6            	ld	a,(x)
 199  003c adeb          	call	_UART1_SendByte
 201                     ; 31 		p++;
 203  003e 1e01          	ldw	x,(OFST+1,sp)
 204  0040 1c0001        	addw	x,#1
 205  0043 1f01          	ldw	(OFST+1,sp),x
 206  0045               L56:
 207                     ; 28 	while(*p!=0)
 209  0045 1e01          	ldw	x,(OFST+1,sp)
 210  0047 7d            	tnz	(x)
 211  0048 26ef          	jrne	L36
 212                     ; 33 }
 215  004a 85            	popw	x
 216  004b 81            	ret
 263                     ; 35 @far @interrupt void UART1_RX_Handler(void)
 263                     ; 36 {
 265                     	switch	.text
 266  004c               f_UART1_RX_Handler:
 268       00000001      OFST:	set	1
 269  004c 3b0002        	push	c_x+2
 270  004f be00          	ldw	x,c_x
 271  0051 89            	pushw	x
 272  0052 3b0002        	push	c_y+2
 273  0055 be00          	ldw	x,c_y
 274  0057 89            	pushw	x
 275  0058 88            	push	a
 278                     ; 38 	if(UART1_GetITStatus(UART1_IT_RXNE)!=RESET)
 280  0059 ae0255        	ldw	x,#597
 281  005c cd0000        	call	_UART1_GetITStatus
 283  005f 4d            	tnz	a
 284  0060 2761          	jreq	L311
 285                     ; 40 		Res=UART1_ReceiveData8();
 287  0062 cd0000        	call	_UART1_ReceiveData8
 289  0065 6b01          	ld	(OFST+0,sp),a
 290                     ; 41 		if((USART_RX_STA&0x80)==0)//接收未完成
 292  0067 b600          	ld	a,_USART_RX_STA
 293  0069 a580          	bcp	a,#128
 294  006b 2656          	jrne	L311
 295                     ; 43 			if(USART_RX_STA&0x40)//接收到了0x0d
 297  006d b600          	ld	a,_USART_RX_STA
 298  006f a540          	bcp	a,#64
 299  0071 2720          	jreq	L711
 300                     ; 45 				if(Res!=0x0a)
 302  0073 7b01          	ld	a,(OFST+0,sp)
 303  0075 a10a          	cp	a,#10
 304  0077 2714          	jreq	L121
 305                     ; 47 					USART_RX_STA=0;//接收错误,重新开始
 307  0079 3f00          	clr	_USART_RX_STA
 308                     ; 48 					for(i=0;i<USART_REC_LEN;i++) USART_RX_BUF[i]=0; //清除串口接收缓冲区
 310  007b 0f01          	clr	(OFST+0,sp)
 311  007d               L321:
 314  007d 7b01          	ld	a,(OFST+0,sp)
 315  007f 5f            	clrw	x
 316  0080 97            	ld	xl,a
 317  0081 6f00          	clr	(_USART_RX_BUF,x)
 320  0083 0c01          	inc	(OFST+0,sp)
 323  0085 7b01          	ld	a,(OFST+0,sp)
 324  0087 a120          	cp	a,#32
 325  0089 25f2          	jrult	L321
 327  008b 2036          	jra	L311
 328  008d               L121:
 329                     ; 50 				else USART_RX_STA|=0x80;	//接收完成了 
 331  008d 721e0000      	bset	_USART_RX_STA,#7
 332  0091 2030          	jra	L311
 333  0093               L711:
 334                     ; 54 				if(Res==0x0d)
 336  0093 7b01          	ld	a,(OFST+0,sp)
 337  0095 a10d          	cp	a,#13
 338  0097 2606          	jrne	L531
 339                     ; 55 					USART_RX_STA|=0x40;
 341  0099 721c0000      	bset	_USART_RX_STA,#6
 343  009d 2024          	jra	L311
 344  009f               L531:
 345                     ; 58 					USART_RX_BUF[USART_RX_STA&0x3f]=Res;
 347  009f b600          	ld	a,_USART_RX_STA
 348  00a1 a43f          	and	a,#63
 349  00a3 5f            	clrw	x
 350  00a4 97            	ld	xl,a
 351  00a5 7b01          	ld	a,(OFST+0,sp)
 352  00a7 e700          	ld	(_USART_RX_BUF,x),a
 353                     ; 59 					USART_RX_STA++;
 355  00a9 3c00          	inc	_USART_RX_STA
 356                     ; 60 					if(USART_RX_STA>(USART_REC_LEN-1))
 358  00ab b600          	ld	a,_USART_RX_STA
 359  00ad a120          	cp	a,#32
 360  00af 2512          	jrult	L311
 361                     ; 62 						USART_RX_STA=0;//接收数据错误,重新开始接收
 363  00b1 3f00          	clr	_USART_RX_STA
 364                     ; 63 						for(i=0;i<USART_REC_LEN;i++) USART_RX_BUF[i]=0;//清除串口接收缓冲区
 366  00b3 0f01          	clr	(OFST+0,sp)
 367  00b5               L341:
 370  00b5 7b01          	ld	a,(OFST+0,sp)
 371  00b7 5f            	clrw	x
 372  00b8 97            	ld	xl,a
 373  00b9 6f00          	clr	(_USART_RX_BUF,x)
 376  00bb 0c01          	inc	(OFST+0,sp)
 379  00bd 7b01          	ld	a,(OFST+0,sp)
 380  00bf a120          	cp	a,#32
 381  00c1 25f2          	jrult	L341
 382  00c3               L311:
 383                     ; 70 }
 386  00c3 84            	pop	a
 387  00c4 85            	popw	x
 388  00c5 bf00          	ldw	c_y,x
 389  00c7 320002        	pop	c_y+2
 390  00ca 85            	popw	x
 391  00cb bf00          	ldw	c_x,x
 392  00cd 320002        	pop	c_x+2
 393  00d0 80            	iret
 426                     	xdef	f_UART1_RX_Handler
 427                     	switch	.ubsct
 428  0000               _USART_RX_BUF:
 429  0000 000000000000  	ds.b	32
 430                     	xdef	_USART_RX_BUF
 431                     	xdef	_USART_RX_STA
 432                     	xdef	_UART1_SendString
 433                     	xdef	_UART1_SendByte
 434                     	xdef	_UART1_Configuration
 435                     	xref	_UART1_GetITStatus
 436                     	xref	_UART1_GetFlagStatus
 437                     	xref	_UART1_SendData8
 438                     	xref	_UART1_ReceiveData8
 439                     	xref	_UART1_ITConfig
 440                     	xref	_UART1_Cmd
 441                     	xref	_UART1_Init
 442                     	xref	_UART1_DeInit
 443                     	xref.b	c_x
 444                     	xref.b	c_y
 464                     	end
