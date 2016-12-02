   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2589                     .const:	section	.text
2590  0000               _TX_ADDRESS:
2591  0000 34            	dc.b	52
2592  0001 43            	dc.b	67
2593  0002 10            	dc.b	16
2594  0003 10            	dc.b	16
2595  0004 01            	dc.b	1
2596  0005               _RX_ADDRESS:
2597  0005 34            	dc.b	52
2598  0006 43            	dc.b	67
2599  0007 10            	dc.b	16
2600  0008 10            	dc.b	16
2601  0009 01            	dc.b	1
2635                     ; 11 void MY_SPI_Init(void)
2635                     ; 12 {
2637                     	switch	.text
2638  0000               _MY_SPI_Init:
2642                     ; 13 	SPI_DeInit();
2644  0000 cd0000        	call	_SPI_DeInit
2646                     ; 15 	SPI_Init(SPI_FIRSTBIT_MSB, 
2646                     ; 16 					 SPI_BAUDRATEPRESCALER_2,
2646                     ; 17 					 SPI_MODE_MASTER,
2646                     ; 18 					 SPI_CLOCKPOLARITY_LOW, 
2646                     ; 19 					 SPI_CLOCKPHASE_1EDGE, 													
2646                     ; 20 					 SPI_DATADIRECTION_2LINES_FULLDUPLEX,
2646                     ; 21 					 SPI_NSS_SOFT, 
2646                     ; 22 					 0x07);
2648  0003 4b07          	push	#7
2649  0005 4b02          	push	#2
2650  0007 4b00          	push	#0
2651  0009 4b00          	push	#0
2652  000b 4b00          	push	#0
2653  000d 4b04          	push	#4
2654  000f 5f            	clrw	x
2655  0010 4f            	clr	a
2656  0011 95            	ld	xh,a
2657  0012 cd0000        	call	_SPI_Init
2659  0015 5b06          	addw	sp,#6
2660                     ; 24 	SPI_Cmd(ENABLE);//使能SPI
2662  0017 a601          	ld	a,#1
2663  0019 cd0000        	call	_SPI_Cmd
2665                     ; 26 	GPIO_Init(IOPORT_SPI_CS,PIN_SPI_CS,GPIO_MODE_OUT_PP_HIGH_FAST);//SPI_CS引脚初始化为推挽输出
2667  001c 4bf0          	push	#240
2668  001e 4b10          	push	#16
2669  0020 ae500a        	ldw	x,#20490
2670  0023 cd0000        	call	_GPIO_Init
2672  0026 85            	popw	x
2673                     ; 27 	SPI_CS_HIGH;//取消SPI传输
2675  0027 4b10          	push	#16
2676  0029 ae500a        	ldw	x,#20490
2677  002c cd0000        	call	_GPIO_WriteHigh
2679  002f 84            	pop	a
2680                     ; 28 }
2683  0030 81            	ret
2720                     ; 33 uchar SPI_ReadWriteByte(uchar dat)
2720                     ; 34 {
2721                     	switch	.text
2722  0031               _SPI_ReadWriteByte:
2724  0031 88            	push	a
2725       00000000      OFST:	set	0
2728  0032               L1171:
2729                     ; 35 	while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
2731  0032 a602          	ld	a,#2
2732  0034 cd0000        	call	_SPI_GetFlagStatus
2734  0037 4d            	tnz	a
2735  0038 27f8          	jreq	L1171
2736                     ; 36 	SPI_SendData(dat);
2738  003a 7b01          	ld	a,(OFST+1,sp)
2739  003c cd0000        	call	_SPI_SendData
2742  003f               L7171:
2743                     ; 38 	while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
2745  003f a601          	ld	a,#1
2746  0041 cd0000        	call	_SPI_GetFlagStatus
2748  0044 4d            	tnz	a
2749  0045 27f8          	jreq	L7171
2750                     ; 39 	return SPI_ReceiveData();
2752  0047 cd0000        	call	_SPI_ReceiveData
2756  004a 5b01          	addw	sp,#1
2757  004c 81            	ret
2784                     ; 43 void NRF24L01_Init(void)
2784                     ; 44 {
2785                     	switch	.text
2786  004d               _NRF24L01_Init:
2790                     ; 45 	GPIO_Init(IOPORT_24L01_CE,PIN_24L01_CE,GPIO_MODE_OUT_PP_HIGH_FAST);//NRF24L01_CE初始化为推挽输出
2792  004d 4bf0          	push	#240
2793  004f 4b08          	push	#8
2794  0051 ae500a        	ldw	x,#20490
2795  0054 cd0000        	call	_GPIO_Init
2797  0057 85            	popw	x
2798                     ; 46 	GPIO_Init(IOPORT_24L01_IRQ,PIN_24L01_IRQ, GPIO_MODE_IN_PU_NO_IT);//IRQ上拉输入
2800  0058 4b40          	push	#64
2801  005a 4b04          	push	#4
2802  005c ae500f        	ldw	x,#20495
2803  005f cd0000        	call	_GPIO_Init
2805  0062 85            	popw	x
2806                     ; 48 	MY_SPI_Init();
2808  0063 ad9b          	call	_MY_SPI_Init
2810                     ; 50 	NRF24L01_CE_LOW;//NRF24L01片选使能
2812  0065 4b08          	push	#8
2813  0067 ae500a        	ldw	x,#20490
2814  006a cd0000        	call	_GPIO_WriteLow
2816  006d 84            	pop	a
2817                     ; 51 	SPI_CS_HIGH;		//SPI片选取消
2819  006e 4b10          	push	#16
2820  0070 ae500a        	ldw	x,#20490
2821  0073 cd0000        	call	_GPIO_WriteHigh
2823  0076 84            	pop	a
2824                     ; 52 }
2827  0077 81            	ret
2830                     	switch	.const
2831  000a               L3371_buf:
2832  000a a5            	dc.b	165
2833  000b a5            	dc.b	165
2834  000c a5            	dc.b	165
2835  000d a5            	dc.b	165
2836  000e a5            	dc.b	165
2880                     ; 56 uchar NRF24L01_Check(void)
2880                     ; 57 {
2881                     	switch	.text
2882  0078               _NRF24L01_Check:
2884  0078 5206          	subw	sp,#6
2885       00000006      OFST:	set	6
2888                     ; 58 	uchar buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
2890  007a 96            	ldw	x,sp
2891  007b 1c0001        	addw	x,#OFST-5
2892  007e 90ae000a      	ldw	y,#L3371_buf
2893  0082 a605          	ld	a,#5
2894  0084 cd0000        	call	c_xymvx
2896                     ; 61 	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);//
2898  0087 4b05          	push	#5
2899  0089 96            	ldw	x,sp
2900  008a 1c0002        	addw	x,#OFST-4
2901  008d 89            	pushw	x
2902  008e a630          	ld	a,#48
2903  0090 cd0153        	call	_NRF24L01_Write_Buf
2905  0093 5b03          	addw	sp,#3
2906                     ; 62 	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
2908  0095 4b05          	push	#5
2909  0097 96            	ldw	x,sp
2910  0098 1c0002        	addw	x,#OFST-4
2911  009b 89            	pushw	x
2912  009c a610          	ld	a,#16
2913  009e ad74          	call	_NRF24L01_Read_Buf
2915  00a0 5b03          	addw	sp,#3
2916                     ; 63 	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
2918  00a2 0f06          	clr	(OFST+0,sp)
2919  00a4               L7571:
2922  00a4 96            	ldw	x,sp
2923  00a5 1c0001        	addw	x,#OFST-5
2924  00a8 9f            	ld	a,xl
2925  00a9 5e            	swapw	x
2926  00aa 1b06          	add	a,(OFST+0,sp)
2927  00ac 2401          	jrnc	L41
2928  00ae 5c            	incw	x
2929  00af               L41:
2930  00af 02            	rlwa	x,a
2931  00b0 f6            	ld	a,(x)
2932  00b1 a1a5          	cp	a,#165
2933  00b3 2608          	jrne	L3671
2938  00b5 0c06          	inc	(OFST+0,sp)
2941  00b7 7b06          	ld	a,(OFST+0,sp)
2942  00b9 a105          	cp	a,#5
2943  00bb 25e7          	jrult	L7571
2944  00bd               L3671:
2945                     ; 64 	if(i!=5)return 1;//检测24L01错误	
2947  00bd 7b06          	ld	a,(OFST+0,sp)
2948  00bf a105          	cp	a,#5
2949  00c1 2704          	jreq	L7671
2952  00c3 a601          	ld	a,#1
2954  00c5 2001          	jra	L61
2955  00c7               L7671:
2956                     ; 65 	return 0;		 //检测到24L01
2958  00c7 4f            	clr	a
2960  00c8               L61:
2962  00c8 5b06          	addw	sp,#6
2963  00ca 81            	ret
3018                     ; 71 uchar NRF24L01_Write_Reg(uchar reg,uchar value)
3018                     ; 72 {
3019                     	switch	.text
3020  00cb               _NRF24L01_Write_Reg:
3022  00cb 89            	pushw	x
3023  00cc 88            	push	a
3024       00000001      OFST:	set	1
3027                     ; 75 	SPI_CS_LOW;                 //使能SPI传输
3029  00cd 4b10          	push	#16
3030  00cf ae500a        	ldw	x,#20490
3031  00d2 cd0000        	call	_GPIO_WriteLow
3033  00d5 84            	pop	a
3034                     ; 76 	status =SPI_ReadWriteByte(reg);//发送寄存器号 
3036  00d6 7b02          	ld	a,(OFST+1,sp)
3037  00d8 cd0031        	call	_SPI_ReadWriteByte
3039  00db 6b01          	ld	(OFST+0,sp),a
3040                     ; 77 	SPI_ReadWriteByte(value);      //写入寄存器的值
3042  00dd 7b03          	ld	a,(OFST+2,sp)
3043  00df cd0031        	call	_SPI_ReadWriteByte
3045                     ; 78 	SPI_CS_HIGH;                 //禁止SPI传输	
3047  00e2 4b10          	push	#16
3048  00e4 ae500a        	ldw	x,#20490
3049  00e7 cd0000        	call	_GPIO_WriteHigh
3051  00ea 84            	pop	a
3052                     ; 80 	return(status);       			//返回状态值
3054  00eb 7b01          	ld	a,(OFST+0,sp)
3057  00ed 5b03          	addw	sp,#3
3058  00ef 81            	ret
3104                     ; 85 uchar NRF24L01_Read_Reg(uchar reg)
3104                     ; 86 {
3105                     	switch	.text
3106  00f0               _NRF24L01_Read_Reg:
3108  00f0 88            	push	a
3109  00f1 88            	push	a
3110       00000001      OFST:	set	1
3113                     ; 89  	SPI_CS_LOW;          //使能SPI传输		
3115  00f2 4b10          	push	#16
3116  00f4 ae500a        	ldw	x,#20490
3117  00f7 cd0000        	call	_GPIO_WriteLow
3119  00fa 84            	pop	a
3120                     ; 90 	SPI_ReadWriteByte(reg);   //发送寄存器号
3122  00fb 7b02          	ld	a,(OFST+1,sp)
3123  00fd cd0031        	call	_SPI_ReadWriteByte
3125                     ; 91 	reg_val=SPI_ReadWriteByte(0XFF);//读取寄存器内容
3127  0100 a6ff          	ld	a,#255
3128  0102 cd0031        	call	_SPI_ReadWriteByte
3130  0105 6b01          	ld	(OFST+0,sp),a
3131                     ; 92 	SPI_CS_HIGH;          //禁止SPI传输		
3133  0107 4b10          	push	#16
3134  0109 ae500a        	ldw	x,#20490
3135  010c cd0000        	call	_GPIO_WriteHigh
3137  010f 84            	pop	a
3138                     ; 94 	return(reg_val);           //返回状态值
3140  0110 7b01          	ld	a,(OFST+0,sp)
3143  0112 85            	popw	x
3144  0113 81            	ret
3218                     ; 102 uchar NRF24L01_Read_Buf(uchar reg,uchar *pBuf,uchar len)
3218                     ; 103 {
3219                     	switch	.text
3220  0114               _NRF24L01_Read_Buf:
3222  0114 88            	push	a
3223  0115 89            	pushw	x
3224       00000002      OFST:	set	2
3227                     ; 106 	SPI_CS_LOW;            //使能SPI传输
3229  0116 4b10          	push	#16
3230  0118 ae500a        	ldw	x,#20490
3231  011b cd0000        	call	_GPIO_WriteLow
3233  011e 84            	pop	a
3234                     ; 107 	status=SPI_ReadWriteByte(reg);//发送寄存器值(位置), 并读取状态值   	   
3236  011f 7b03          	ld	a,(OFST+1,sp)
3237  0121 cd0031        	call	_SPI_ReadWriteByte
3239  0124 6b01          	ld	(OFST-1,sp),a
3240                     ; 108  	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI_ReadWriteByte(0XFF);//读出数据
3242  0126 0f02          	clr	(OFST+0,sp)
3244  0128 2015          	jra	L3012
3245  012a               L7702:
3248  012a 7b06          	ld	a,(OFST+4,sp)
3249  012c 97            	ld	xl,a
3250  012d 7b07          	ld	a,(OFST+5,sp)
3251  012f 1b02          	add	a,(OFST+0,sp)
3252  0131 2401          	jrnc	L62
3253  0133 5c            	incw	x
3254  0134               L62:
3255  0134 02            	rlwa	x,a
3256  0135 89            	pushw	x
3257  0136 a6ff          	ld	a,#255
3258  0138 cd0031        	call	_SPI_ReadWriteByte
3260  013b 85            	popw	x
3261  013c f7            	ld	(x),a
3264  013d 0c02          	inc	(OFST+0,sp)
3265  013f               L3012:
3268  013f 7b02          	ld	a,(OFST+0,sp)
3269  0141 1108          	cp	a,(OFST+6,sp)
3270  0143 25e5          	jrult	L7702
3271                     ; 109 	SPI_CS_HIGH;       //关闭SPI传输
3273  0145 4b10          	push	#16
3274  0147 ae500a        	ldw	x,#20490
3275  014a cd0000        	call	_GPIO_WriteHigh
3277  014d 84            	pop	a
3278                     ; 111 	return status;        //返回读到的状态值	   
3280  014e 7b01          	ld	a,(OFST-1,sp)
3283  0150 5b03          	addw	sp,#3
3284  0152 81            	ret
3358                     ; 118 uchar NRF24L01_Write_Buf(uchar reg, uchar *pBuf, uchar len)
3358                     ; 119 {
3359                     	switch	.text
3360  0153               _NRF24L01_Write_Buf:
3362  0153 88            	push	a
3363  0154 89            	pushw	x
3364       00000002      OFST:	set	2
3367                     ; 122  	SPI_CS_LOW;         //使能SPI传输
3369  0155 4b10          	push	#16
3370  0157 ae500a        	ldw	x,#20490
3371  015a cd0000        	call	_GPIO_WriteLow
3373  015d 84            	pop	a
3374                     ; 123 	status = SPI_ReadWriteByte(reg);//发送寄存器值(位置), 并读取状态值
3376  015e 7b03          	ld	a,(OFST+1,sp)
3377  0160 cd0031        	call	_SPI_ReadWriteByte
3379  0163 6b01          	ld	(OFST-1,sp),a
3380                     ; 124 	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI_ReadWriteByte(*pBuf++); //写入数据	 
3382  0165 0f02          	clr	(OFST+0,sp)
3384  0167 2010          	jra	L1512
3385  0169               L5412:
3388  0169 1e06          	ldw	x,(OFST+4,sp)
3389  016b 1c0001        	addw	x,#1
3390  016e 1f06          	ldw	(OFST+4,sp),x
3391  0170 1d0001        	subw	x,#1
3392  0173 f6            	ld	a,(x)
3393  0174 cd0031        	call	_SPI_ReadWriteByte
3397  0177 0c02          	inc	(OFST+0,sp)
3398  0179               L1512:
3401  0179 7b02          	ld	a,(OFST+0,sp)
3402  017b 1108          	cp	a,(OFST+6,sp)
3403  017d 25ea          	jrult	L5412
3404                     ; 125 	SPI_CS_HIGH;       //关闭SPI传输
3406  017f 4b10          	push	#16
3407  0181 ae500a        	ldw	x,#20490
3408  0184 cd0000        	call	_GPIO_WriteHigh
3410  0187 84            	pop	a
3411                     ; 127 	return status;          //返回读到的状态值
3413  0188 7b01          	ld	a,(OFST-1,sp)
3416  018a 5b03          	addw	sp,#3
3417  018c 81            	ret
3467                     ; 133 uchar NRF24L01_TxPacket(uchar *txbuf)
3467                     ; 134 {
3468                     	switch	.text
3469  018d               _NRF24L01_TxPacket:
3471  018d 89            	pushw	x
3472  018e 88            	push	a
3473       00000001      OFST:	set	1
3476                     ; 137 	NRF24L01_CE_LOW;
3478  018f 4b08          	push	#8
3479  0191 ae500a        	ldw	x,#20490
3480  0194 cd0000        	call	_GPIO_WriteLow
3482  0197 84            	pop	a
3483                     ; 138 	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//
3485  0198 4b20          	push	#32
3486  019a 1e03          	ldw	x,(OFST+2,sp)
3487  019c 89            	pushw	x
3488  019d a6a0          	ld	a,#160
3489  019f adb2          	call	_NRF24L01_Write_Buf
3491  01a1 5b03          	addw	sp,#3
3492                     ; 139  	NRF24L01_CE_HIGH;//启动发送	   
3494  01a3 4b08          	push	#8
3495  01a5 ae500a        	ldw	x,#20490
3496  01a8 cd0000        	call	_GPIO_WriteHigh
3498  01ab 84            	pop	a
3500  01ac               L1022:
3501                     ; 140 	while(NRF24L01_IRQ!=0);//等待发送完成
3503  01ac 4b04          	push	#4
3504  01ae ae500f        	ldw	x,#20495
3505  01b1 cd0000        	call	_GPIO_ReadInputPin
3507  01b4 5b01          	addw	sp,#1
3508  01b6 4d            	tnz	a
3509  01b7 26f3          	jrne	L1022
3510                     ; 141 	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   
3512  01b9 a607          	ld	a,#7
3513  01bb cd00f0        	call	_NRF24L01_Read_Reg
3515  01be 6b01          	ld	(OFST+0,sp),a
3516                     ; 142 	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //
3518  01c0 7b01          	ld	a,(OFST+0,sp)
3519  01c2 97            	ld	xl,a
3520  01c3 a627          	ld	a,#39
3521  01c5 95            	ld	xh,a
3522  01c6 cd00cb        	call	_NRF24L01_Write_Reg
3524                     ; 143 	if(sta&MAX_TX)//达到最大重发次数
3526  01c9 7b01          	ld	a,(OFST+0,sp)
3527  01cb a510          	bcp	a,#16
3528  01cd 270d          	jreq	L5022
3529                     ; 145 		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
3531  01cf ae00ff        	ldw	x,#255
3532  01d2 a6e1          	ld	a,#225
3533  01d4 95            	ld	xh,a
3534  01d5 cd00cb        	call	_NRF24L01_Write_Reg
3536                     ; 146 		return MAX_TX; 
3538  01d8 a610          	ld	a,#16
3540  01da 2008          	jra	L43
3541  01dc               L5022:
3542                     ; 148 	if(sta&TX_OK)//发送完成
3544  01dc 7b01          	ld	a,(OFST+0,sp)
3545  01de a520          	bcp	a,#32
3546  01e0 2705          	jreq	L7022
3547                     ; 150 		return TX_OK;
3549  01e2 a620          	ld	a,#32
3551  01e4               L43:
3553  01e4 5b03          	addw	sp,#3
3554  01e6 81            	ret
3555  01e7               L7022:
3556                     ; 152 	return 0xff;//其他原因发送失败
3558  01e7 a6ff          	ld	a,#255
3560  01e9 20f9          	jra	L43
3607                     ; 158 uchar NRF24L01_RxPacket(uchar *rxbuf)
3607                     ; 159 {
3608                     	switch	.text
3609  01eb               _NRF24L01_RxPacket:
3611  01eb 89            	pushw	x
3612  01ec 88            	push	a
3613       00000001      OFST:	set	1
3616                     ; 162 	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    
3618  01ed a607          	ld	a,#7
3619  01ef cd00f0        	call	_NRF24L01_Read_Reg
3621  01f2 6b01          	ld	(OFST+0,sp),a
3622                     ; 163 	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta); //
3624  01f4 7b01          	ld	a,(OFST+0,sp)
3625  01f6 97            	ld	xl,a
3626  01f7 a627          	ld	a,#39
3627  01f9 95            	ld	xh,a
3628  01fa cd00cb        	call	_NRF24L01_Write_Reg
3630                     ; 164 	if(sta&RX_OK)//接收到数据
3632  01fd 7b01          	ld	a,(OFST+0,sp)
3633  01ff a540          	bcp	a,#64
3634  0201 2718          	jreq	L3322
3635                     ; 166 		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
3637  0203 4b20          	push	#32
3638  0205 1e03          	ldw	x,(OFST+2,sp)
3639  0207 89            	pushw	x
3640  0208 a661          	ld	a,#97
3641  020a cd0114        	call	_NRF24L01_Read_Buf
3643  020d 5b03          	addw	sp,#3
3644                     ; 167 		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
3646  020f ae00ff        	ldw	x,#255
3647  0212 a6e2          	ld	a,#226
3648  0214 95            	ld	xh,a
3649  0215 cd00cb        	call	_NRF24L01_Write_Reg
3651                     ; 168 		return 0; 
3653  0218 4f            	clr	a
3655  0219 2002          	jra	L04
3656  021b               L3322:
3657                     ; 170 	return 1;//没收到任何数据
3659  021b a601          	ld	a,#1
3661  021d               L04:
3663  021d 5b03          	addw	sp,#3
3664  021f 81            	ret
3692                     ; 176 void NRF24L01_RX_Mode(void)
3692                     ; 177 {
3693                     	switch	.text
3694  0220               _NRF24L01_RX_Mode:
3698                     ; 178 	NRF24L01_CE_LOW;
3700  0220 4b08          	push	#8
3701  0222 ae500a        	ldw	x,#20490
3702  0225 cd0000        	call	_GPIO_WriteLow
3704  0228 84            	pop	a
3705                     ; 180 	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
3707  0229 4b05          	push	#5
3708  022b ae0005        	ldw	x,#_RX_ADDRESS
3709  022e 89            	pushw	x
3710  022f a62a          	ld	a,#42
3711  0231 cd0153        	call	_NRF24L01_Write_Buf
3713  0234 5b03          	addw	sp,#3
3714                     ; 181 	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);    	//使能通道0的自动应答    
3716  0236 ae0001        	ldw	x,#1
3717  0239 a621          	ld	a,#33
3718  023b 95            	ld	xh,a
3719  023c cd00cb        	call	_NRF24L01_Write_Reg
3721                     ; 182 	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);	//使能通道0的接收地址  	 
3723  023f ae0001        	ldw	x,#1
3724  0242 a622          	ld	a,#34
3725  0244 95            	ld	xh,a
3726  0245 cd00cb        	call	_NRF24L01_Write_Reg
3728                     ; 183 	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);	    	//设置RF通信频率		  
3730  0248 ae0028        	ldw	x,#40
3731  024b a625          	ld	a,#37
3732  024d 95            	ld	xh,a
3733  024e cd00cb        	call	_NRF24L01_Write_Reg
3735                     ; 184 	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
3737  0251 ae0020        	ldw	x,#32
3738  0254 a631          	ld	a,#49
3739  0256 95            	ld	xh,a
3740  0257 cd00cb        	call	_NRF24L01_Write_Reg
3742                     ; 185 	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);	//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
3744  025a ae000f        	ldw	x,#15
3745  025d a626          	ld	a,#38
3746  025f 95            	ld	xh,a
3747  0260 cd00cb        	call	_NRF24L01_Write_Reg
3749                     ; 186 	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);		//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
3751  0263 ae000f        	ldw	x,#15
3752  0266 a620          	ld	a,#32
3753  0268 95            	ld	xh,a
3754  0269 cd00cb        	call	_NRF24L01_Write_Reg
3756                     ; 188   NRF24L01_CE_HIGH; //CE为高,进入接收模式 
3758  026c 4b08          	push	#8
3759  026e ae500a        	ldw	x,#20490
3760  0271 cd0000        	call	_GPIO_WriteHigh
3762  0274 84            	pop	a
3763                     ; 189 }			
3766  0275 81            	ret
3796                     ; 196 void NRF24L01_TX_Mode(void)
3796                     ; 197 {														 
3797                     	switch	.text
3798  0276               _NRF24L01_TX_Mode:
3802                     ; 198 	NRF24L01_CE_LOW;
3804  0276 4b08          	push	#8
3805  0278 ae500a        	ldw	x,#20490
3806  027b cd0000        	call	_GPIO_WriteLow
3808  027e 84            	pop	a
3809                     ; 200 	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
3811  027f 4b05          	push	#5
3812  0281 ae0000        	ldw	x,#_TX_ADDRESS
3813  0284 89            	pushw	x
3814  0285 a630          	ld	a,#48
3815  0287 cd0153        	call	_NRF24L01_Write_Buf
3817  028a 5b03          	addw	sp,#3
3818                     ; 201 	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  
3820  028c 4b05          	push	#5
3821  028e ae0005        	ldw	x,#_RX_ADDRESS
3822  0291 89            	pushw	x
3823  0292 a62a          	ld	a,#42
3824  0294 cd0153        	call	_NRF24L01_Write_Buf
3826  0297 5b03          	addw	sp,#3
3827                     ; 202 	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
3829  0299 ae0001        	ldw	x,#1
3830  029c a621          	ld	a,#33
3831  029e 95            	ld	xh,a
3832  029f cd00cb        	call	_NRF24L01_Write_Reg
3834                     ; 203 	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
3836  02a2 ae0001        	ldw	x,#1
3837  02a5 a622          	ld	a,#34
3838  02a7 95            	ld	xh,a
3839  02a8 cd00cb        	call	_NRF24L01_Write_Reg
3841                     ; 204 	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
3843  02ab ae001a        	ldw	x,#26
3844  02ae a624          	ld	a,#36
3845  02b0 95            	ld	xh,a
3846  02b1 cd00cb        	call	_NRF24L01_Write_Reg
3848                     ; 205 	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,40);       //设置RF通道为40
3850  02b4 ae0028        	ldw	x,#40
3851  02b7 a625          	ld	a,#37
3852  02b9 95            	ld	xh,a
3853  02ba cd00cb        	call	_NRF24L01_Write_Reg
3855                     ; 206 	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
3857  02bd ae000f        	ldw	x,#15
3858  02c0 a626          	ld	a,#38
3859  02c2 95            	ld	xh,a
3860  02c3 cd00cb        	call	_NRF24L01_Write_Reg
3862                     ; 207 	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,
3864  02c6 ae000e        	ldw	x,#14
3865  02c9 a620          	ld	a,#32
3866  02cb 95            	ld	xh,a
3867  02cc cd00cb        	call	_NRF24L01_Write_Reg
3869                     ; 209 	NRF24L01_CE_HIGH;
3871  02cf 4b08          	push	#8
3872  02d1 ae500a        	ldw	x,#20490
3873  02d4 cd0000        	call	_GPIO_WriteHigh
3875  02d7 84            	pop	a
3876                     ; 210 	delay_10us(5);
3878  02d8 ae0005        	ldw	x,#5
3879  02db cd0000        	call	_delay_10us
3881                     ; 211 }
3884  02de 81            	ret
3919                     	xdef	_RX_ADDRESS
3920                     	xdef	_TX_ADDRESS
3921                     	xdef	_NRF24L01_RxPacket
3922                     	xdef	_NRF24L01_TxPacket
3923                     	xdef	_NRF24L01_Check
3924                     	xdef	_NRF24L01_Write_Reg
3925                     	xdef	_NRF24L01_Read_Reg
3926                     	xdef	_NRF24L01_Read_Buf
3927                     	xdef	_NRF24L01_Write_Buf
3928                     	xdef	_NRF24L01_TX_Mode
3929                     	xdef	_NRF24L01_RX_Mode
3930                     	xdef	_NRF24L01_Init
3931                     	xdef	_SPI_ReadWriteByte
3932                     	xdef	_MY_SPI_Init
3933                     	xref	_delay_10us
3934                     	xref	_SPI_GetFlagStatus
3935                     	xref	_SPI_ReceiveData
3936                     	xref	_SPI_SendData
3937                     	xref	_SPI_Cmd
3938                     	xref	_SPI_Init
3939                     	xref	_SPI_DeInit
3940                     	xref	_GPIO_ReadInputPin
3941                     	xref	_GPIO_WriteLow
3942                     	xref	_GPIO_WriteHigh
3943                     	xref	_GPIO_Init
3944                     	xref.b	c_x
3963                     	xref	c_xymvx
3964                     	end
