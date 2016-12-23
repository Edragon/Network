   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
2589                     	bsct
2590  0000               _NRF24L01_RX_BUF:
2591  0000 00            	dc.b	0
2592  0001 000000000000  	ds.b	32
2659                     ; 12 main()
2659                     ; 13 {
2661                     	switch	.text
2662  0000               _main:
2664  0000 89            	pushw	x
2665       00000002      OFST:	set	2
2668                     ; 16 	SysClkInit();//初始化主时钟，
2670  0001 cd00c1        	call	_SysClkInit
2672                     ; 17 	NRF24L01_Init();//初始化NRF24L01
2674  0004 cd0000        	call	_NRF24L01_Init
2676                     ; 18 	UART1_Configuration();//初始化串口
2678  0007 cd0000        	call	_UART1_Configuration
2680                     ; 19 	enableInterrupts();//开总中断
2683  000a 9a            rim
2685                     ; 20 	GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_IN_PU_NO_IT);//模式控制位，，上拉输入
2688  000b 4b40          	push	#64
2689  000d 4b02          	push	#2
2690  000f ae500f        	ldw	x,#20495
2691  0012 cd0000        	call	_GPIO_Init
2693  0015 85            	popw	x
2695  0016 200c          	jra	L5071
2696  0018               L3071:
2697                     ; 24 		UART1_SendString("请检查NRF24L01\r\n");
2699  0018 ae00ae        	ldw	x,#L1171
2700  001b cd0000        	call	_UART1_SendString
2702                     ; 25 		delay_ms(500);
2704  001e ae01f4        	ldw	x,#500
2705  0021 cd00c6        	call	_delay_ms
2707  0024               L5071:
2708                     ; 22 	while(NRF24L01_Check())//检测NRF24L01是否存在
2710  0024 cd0000        	call	_NRF24L01_Check
2712  0027 4d            	tnz	a
2713  0028 26ee          	jrne	L3071
2714                     ; 27 	UART1_SendString("\r\n检测NRF24L01成功\r\n"); //检测到NRF24L01
2716  002a ae0099        	ldw	x,#L3171
2717  002d cd0000        	call	_UART1_SendString
2719                     ; 29 	NRF24L01_Status_TX();//开机默认发送模式
2721  0030 cd0170        	call	_NRF24L01_Status_TX
2723  0033               L5171:
2724                     ; 33 		Mode_Config(PinLevel_Check());//根据控制引脚电平配置模式
2726  0033 cd010e        	call	_PinLevel_Check
2728  0036 cd0149        	call	_Mode_Config
2730                     ; 35 		if((USART_RX_STA&0x80)!=0)//串口数据接收完成
2732  0039 b600          	ld	a,_USART_RX_STA
2733  003b a580          	bcp	a,#128
2734  003d 2761          	jreq	L1271
2735                     ; 37 			if(Mode_Status==MODE_TX)//24L01发送模式
2737  003f 3d00          	tnz	_Mode_Status
2738  0041 263d          	jrne	L3271
2739                     ; 39 				UART1_SendString("\r\n你发送的信息为：");
2741  0043 ae0086        	ldw	x,#L5271
2742  0046 cd0000        	call	_UART1_SendString
2744                     ; 40 				data_len=USART_RX_STA&0x3f;//得到接收到的数据长度
2746  0049 b600          	ld	a,_USART_RX_STA
2747  004b a43f          	and	a,#63
2748  004d 6b01          	ld	(OFST-1,sp),a
2749                     ; 41 				USART_RX_STA=0;
2751  004f 3f00          	clr	_USART_RX_STA
2752                     ; 42 				for(i=0;i<data_len;i++) UART1_SendByte(USART_RX_BUF[i]);//将串口发送的数据返回
2754  0051 0f02          	clr	(OFST+0,sp)
2756  0053 200b          	jra	L3371
2757  0055               L7271:
2760  0055 7b02          	ld	a,(OFST+0,sp)
2761  0057 5f            	clrw	x
2762  0058 97            	ld	xl,a
2763  0059 e600          	ld	a,(_USART_RX_BUF,x)
2764  005b cd0000        	call	_UART1_SendByte
2768  005e 0c02          	inc	(OFST+0,sp)
2769  0060               L3371:
2772  0060 7b02          	ld	a,(OFST+0,sp)
2773  0062 1101          	cp	a,(OFST-1,sp)
2774  0064 25ef          	jrult	L7271
2775                     ; 44 				if(NRF24L01_TxPacket(USART_RX_BUF)==TX_OK) UART1_SendString("\r\nNRF24L01发送成功\r\n");
2777  0066 ae0000        	ldw	x,#_USART_RX_BUF
2778  0069 cd0000        	call	_NRF24L01_TxPacket
2780  006c a120          	cp	a,#32
2781  006e 2608          	jrne	L7371
2784  0070 ae0071        	ldw	x,#L1471
2785  0073 cd0000        	call	_UART1_SendString
2788  0076 2016          	jra	L7471
2789  0078               L7371:
2790                     ; 45 				else 	UART1_SendString("\r\nNRF24L01发送失败\r\n");
2792  0078 ae005c        	ldw	x,#L5471
2793  007b cd0000        	call	_UART1_SendString
2795  007e 200e          	jra	L7471
2796  0080               L3271:
2797                     ; 47 			else if(Mode_Status==MODE_RX) 
2799  0080 b600          	ld	a,_Mode_Status
2800  0082 a101          	cp	a,#1
2801  0084 2608          	jrne	L7471
2802                     ; 49 				USART_RX_STA=0;
2804  0086 3f00          	clr	_USART_RX_STA
2805                     ; 50 				UART1_SendString("\r\nNRF24L01接收模式，无法发送\r\n");
2807  0088 ae003d        	ldw	x,#L3571
2808  008b cd0000        	call	_UART1_SendString
2810  008e               L7471:
2811                     ; 52 			for(i=0;i<data_len;i++) USART_RX_BUF[i]=0;//每次串口接收完成后，需要重新清除接收缓存
2813  008e 0f02          	clr	(OFST+0,sp)
2815  0090 2008          	jra	L1671
2816  0092               L5571:
2819  0092 7b02          	ld	a,(OFST+0,sp)
2820  0094 5f            	clrw	x
2821  0095 97            	ld	xl,a
2822  0096 6f00          	clr	(_USART_RX_BUF,x)
2825  0098 0c02          	inc	(OFST+0,sp)
2826  009a               L1671:
2829  009a 7b02          	ld	a,(OFST+0,sp)
2830  009c 1101          	cp	a,(OFST-1,sp)
2831  009e 25f2          	jrult	L5571
2832  00a0               L1271:
2833                     ; 55 		if(Mode_Status==MODE_RX)//接收模式
2835  00a0 b600          	ld	a,_Mode_Status
2836  00a2 a101          	cp	a,#1
2837  00a4 268d          	jrne	L5171
2838                     ; 57 			if(NRF24L01_RxPacket(NRF24L01_RX_BUF)==0)//接收完成
2840  00a6 ae0000        	ldw	x,#_NRF24L01_RX_BUF
2841  00a9 cd0000        	call	_NRF24L01_RxPacket
2843  00ac 4d            	tnz	a
2844  00ad 2684          	jrne	L5171
2845                     ; 59 				UART1_SendString("\r\n你接收的信息为：");
2847  00af ae002a        	ldw	x,#L1771
2848  00b2 cd0000        	call	_UART1_SendString
2850                     ; 60 				NRF24L01_RX_BUF[RX_PLOAD_WIDTH]=0;//最后要补0，这句 不是必须的，因为已经初始化为0
2852  00b5 3f20          	clr	_NRF24L01_RX_BUF+32
2853                     ; 61 				UART1_SendString(NRF24L01_RX_BUF); //将24L01接收的信息发送给串口
2855  00b7 ae0000        	ldw	x,#_NRF24L01_RX_BUF
2856  00ba cd0000        	call	_UART1_SendString
2858  00bd ac330033      	jpf	L5171
2882                     ; 67 void SysClkInit(void)//启用外部晶振作为主时钟
2882                     ; 68 {
2883                     	switch	.text
2884  00c1               _SysClkInit:
2888                     ; 74 CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);   //1分频 16MHZ
2890  00c1 4f            	clr	a
2891  00c2 cd0000        	call	_CLK_HSIPrescalerConfig
2893                     ; 75 }
2896  00c5 81            	ret
2948                     ; 77 void delay_ms(uint z)//ms延时函数
2948                     ; 78 {
2949                     	switch	.text
2950  00c6               _delay_ms:
2952  00c6 5204          	subw	sp,#4
2953       00000004      OFST:	set	4
2956                     ; 80 	for(x=z;x>0;x--)
2958  00c8 1f01          	ldw	(OFST-3,sp),x
2960  00ca 2017          	jra	L5302
2961  00cc               L1302:
2962                     ; 81 		for(y=1330;y>0;y--);
2964  00cc ae0532        	ldw	x,#1330
2965  00cf 1f03          	ldw	(OFST-1,sp),x
2966  00d1               L1402:
2970  00d1 1e03          	ldw	x,(OFST-1,sp)
2971  00d3 1d0001        	subw	x,#1
2972  00d6 1f03          	ldw	(OFST-1,sp),x
2975  00d8 1e03          	ldw	x,(OFST-1,sp)
2976  00da 26f5          	jrne	L1402
2977                     ; 80 	for(x=z;x>0;x--)
2979  00dc 1e01          	ldw	x,(OFST-3,sp)
2980  00de 1d0001        	subw	x,#1
2981  00e1 1f01          	ldw	(OFST-3,sp),x
2982  00e3               L5302:
2985  00e3 1e01          	ldw	x,(OFST-3,sp)
2986  00e5 26e5          	jrne	L1302
2987                     ; 82 }
2990  00e7 5b04          	addw	sp,#4
2991  00e9 81            	ret
3043                     ; 84 void delay_10us(uint z)//10us延时函数
3043                     ; 85 {
3044                     	switch	.text
3045  00ea               _delay_10us:
3047  00ea 5204          	subw	sp,#4
3048       00000004      OFST:	set	4
3051                     ; 87 	for(x=z;x>0;x--)
3053  00ec 1f01          	ldw	(OFST-3,sp),x
3055  00ee 2017          	jra	L1012
3056  00f0               L5702:
3057                     ; 88 		for(y=15;y>0;y--);
3059  00f0 ae000f        	ldw	x,#15
3060  00f3 1f03          	ldw	(OFST-1,sp),x
3061  00f5               L5012:
3065  00f5 1e03          	ldw	x,(OFST-1,sp)
3066  00f7 1d0001        	subw	x,#1
3067  00fa 1f03          	ldw	(OFST-1,sp),x
3070  00fc 1e03          	ldw	x,(OFST-1,sp)
3071  00fe 26f5          	jrne	L5012
3072                     ; 87 	for(x=z;x>0;x--)
3074  0100 1e01          	ldw	x,(OFST-3,sp)
3075  0102 1d0001        	subw	x,#1
3076  0105 1f01          	ldw	(OFST-3,sp),x
3077  0107               L1012:
3080  0107 1e01          	ldw	x,(OFST-3,sp)
3081  0109 26e5          	jrne	L5702
3082                     ; 89 }
3085  010b 5b04          	addw	sp,#4
3086  010d 81            	ret
3089                     	bsct
3090  0021               L3112_up_falg:
3091  0021 01            	dc.b	1
3125                     ; 91 uchar PinLevel_Check(void)//检测模式配置引脚的电平
3125                     ; 92 {
3126                     	switch	.text
3127  010e               _PinLevel_Check:
3131                     ; 94 	if(up_falg&&MODE_CTRL_PIN==0)
3133  010e 3d21          	tnz	L3112_up_falg
3134  0110 2723          	jreq	L3312
3136  0112 4b02          	push	#2
3137  0114 ae500f        	ldw	x,#20495
3138  0117 cd0000        	call	_GPIO_ReadInputPin
3140  011a 5b01          	addw	sp,#1
3141  011c 4d            	tnz	a
3142  011d 2616          	jrne	L3312
3143                     ; 96 		delay_ms(10);
3145  011f ae000a        	ldw	x,#10
3146  0122 ada2          	call	_delay_ms
3148                     ; 97 		if(MODE_CTRL_PIN==0) 
3150  0124 4b02          	push	#2
3151  0126 ae500f        	ldw	x,#20495
3152  0129 cd0000        	call	_GPIO_ReadInputPin
3154  012c 5b01          	addw	sp,#1
3155  012e 4d            	tnz	a
3156  012f 2604          	jrne	L3312
3157                     ; 99 			up_falg=0;
3159  0131 3f21          	clr	L3112_up_falg
3160                     ; 100 			return 0;
3162  0133 4f            	clr	a
3165  0134 81            	ret
3166  0135               L3312:
3167                     ; 103 	if(MODE_CTRL_PIN!=0) up_falg=1;
3169  0135 4b02          	push	#2
3170  0137 ae500f        	ldw	x,#20495
3171  013a cd0000        	call	_GPIO_ReadInputPin
3173  013d 5b01          	addw	sp,#1
3174  013f 4d            	tnz	a
3175  0140 2704          	jreq	L7312
3178  0142 35010021      	mov	L3112_up_falg,#1
3179  0146               L7312:
3180                     ; 104 	return 1;
3182  0146 a601          	ld	a,#1
3185  0148 81            	ret
3188                     	bsct
3189  0022               L1412_ModeConfig_flag:
3190  0022 00            	dc.b	0
3233                     ; 107 void Mode_Config(uchar sta)//配置NRF24L01的收发模式
3233                     ; 108 {
3234                     	switch	.text
3235  0149               _Mode_Config:
3239                     ; 110 	if(sta==0)
3241  0149 4d            	tnz	a
3242  014a 2615          	jrne	L5612
3243                     ; 112 		ModeConfig_flag=!ModeConfig_flag;
3245  014c 3d22          	tnz	L1412_ModeConfig_flag
3246  014e 2604          	jrne	L02
3247  0150 a601          	ld	a,#1
3248  0152 2001          	jra	L22
3249  0154               L02:
3250  0154 4f            	clr	a
3251  0155               L22:
3252  0155 b722          	ld	L1412_ModeConfig_flag,a
3253                     ; 113 		if(ModeConfig_flag==0)
3255  0157 3d22          	tnz	L1412_ModeConfig_flag
3256  0159 2604          	jrne	L7612
3257                     ; 115 			NRF24L01_Status_TX();
3259  015b ad13          	call	_NRF24L01_Status_TX
3262  015d 2002          	jra	L5612
3263  015f               L7612:
3264                     ; 119 			NRF24L01_Status_RX();
3266  015f ad01          	call	_NRF24L01_Status_RX
3268  0161               L5612:
3269                     ; 122 }
3272  0161 81            	ret
3298                     ; 124 void NRF24L01_Status_RX(void)
3298                     ; 125 {
3299                     	switch	.text
3300  0162               _NRF24L01_Status_RX:
3304                     ; 126 	NRF24L01_RX_Mode();//NRF24L01配置成接收模式
3306  0162 cd0000        	call	_NRF24L01_RX_Mode
3308                     ; 127 	Mode_Status=MODE_RX;
3310  0165 35010000      	mov	_Mode_Status,#1
3311                     ; 128 	UART1_SendString("\r\nNRF24L01接收模式\r\n");
3313  0169 ae0015        	ldw	x,#L3022
3314  016c cd0000        	call	_UART1_SendString
3316                     ; 129 }
3319  016f 81            	ret
3345                     ; 131 void NRF24L01_Status_TX(void)
3345                     ; 132 {
3346                     	switch	.text
3347  0170               _NRF24L01_Status_TX:
3351                     ; 133 	NRF24L01_TX_Mode();//NRF24L01配置成发射模式
3353  0170 cd0000        	call	_NRF24L01_TX_Mode
3355                     ; 134 	Mode_Status=MODE_TX;
3357  0173 3f00          	clr	_Mode_Status
3358                     ; 135 	UART1_SendString("\r\nNRF24L01发送模式\r\n");
3360  0175 ae0000        	ldw	x,#L5122
3361  0178 cd0000        	call	_UART1_SendString
3363                     ; 136 }
3366  017b 81            	ret
3400                     	xdef	_main
3401                     	xdef	_NRF24L01_RX_BUF
3402                     	switch	.ubsct
3403  0000               _Mode_Status:
3404  0000 00            	ds.b	1
3405                     	xdef	_Mode_Status
3406                     	xref.b	_USART_RX_BUF
3407                     	xref.b	_USART_RX_STA
3408                     	xref	_UART1_SendString
3409                     	xref	_UART1_SendByte
3410                     	xref	_UART1_Configuration
3411                     	xref	_NRF24L01_RxPacket
3412                     	xref	_NRF24L01_TxPacket
3413                     	xref	_NRF24L01_Check
3414                     	xref	_NRF24L01_TX_Mode
3415                     	xref	_NRF24L01_RX_Mode
3416                     	xref	_NRF24L01_Init
3417                     	xdef	_NRF24L01_Status_TX
3418                     	xdef	_NRF24L01_Status_RX
3419                     	xdef	_Mode_Config
3420                     	xdef	_PinLevel_Check
3421                     	xdef	_delay_10us
3422                     	xdef	_delay_ms
3423                     	xdef	_SysClkInit
3424                     	xref	_GPIO_ReadInputPin
3425                     	xref	_GPIO_Init
3426                     	xref	_CLK_HSIPrescalerConfig
3427                     .const:	section	.text
3428  0000               L5122:
3429  0000 0d0a4e524632  	dc.b	13,10,78,82,70,50
3430  0006 344c3031b7    	dc.b	"4L01",183
3431  000b a2cbcdc4a3ca  	dc.b	162,203,205,196,163,202
3432  0011 bd0d0a00      	dc.b	189,13,10,0
3433  0015               L3022:
3434  0015 0d0a4e524632  	dc.b	13,10,78,82,70,50
3435  001b 344c3031bd    	dc.b	"4L01",189
3436  0020 d3cad5c4a3ca  	dc.b	211,202,213,196,163,202
3437  0026 bd0d0a00      	dc.b	189,13,10,0
3438  002a               L1771:
3439  002a 0d0ac4e3bdd3  	dc.b	13,10,196,227,189,211
3440  0030 cad5b5c4d0c5  	dc.b	202,213,181,196,208,197
3441  0036 cfa2ceaaa3ba  	dc.b	207,162,206,170,163,186,0
3442  003d               L3571:
3443  003d 0d0a4e524632  	dc.b	13,10,78,82,70,50
3444  0043 344c3031bd    	dc.b	"4L01",189
3445  0048 d3cad5c4a3ca  	dc.b	211,202,213,196,163,202
3446  004e bda3accedeb7  	dc.b	189,163,172,206,222,183
3447  0054 a8b7a2cbcd0d  	dc.b	168,183,162,203,205,13
3448  005a 0a00          	dc.b	10,0
3449  005c               L5471:
3450  005c 0d0a4e524632  	dc.b	13,10,78,82,70,50
3451  0062 344c3031b7    	dc.b	"4L01",183
3452  0067 a2cbcdcaa7b0  	dc.b	162,203,205,202,167,176
3453  006d dc0d0a00      	dc.b	220,13,10,0
3454  0071               L1471:
3455  0071 0d0a4e524632  	dc.b	13,10,78,82,70,50
3456  0077 344c3031b7    	dc.b	"4L01",183
3457  007c a2cbcdb3c9b9  	dc.b	162,203,205,179,201,185
3458  0082 a60d0a00      	dc.b	166,13,10,0
3459  0086               L5271:
3460  0086 0d0ac4e3b7a2  	dc.b	13,10,196,227,183,162
3461  008c cbcdb5c4d0c5  	dc.b	203,205,181,196,208,197
3462  0092 cfa2ceaaa3ba  	dc.b	207,162,206,170,163,186,0
3463  0099               L3171:
3464  0099 0d0abcecb2e2  	dc.b	13,10,188,236,178,226
3465  009f 4e524632344c  	dc.b	"NRF24L01",179
3466  00a8 c9b9a60d0a00  	dc.b	201,185,166,13,10,0
3467  00ae               L1171:
3468  00ae c7ebbcecb2e9  	dc.b	199,235,188,236,178,233
3469  00b4 4e524632344c  	dc.b	"NRF24L01",13
3470  00bd 0a00          	dc.b	10,0
3490                     	end
