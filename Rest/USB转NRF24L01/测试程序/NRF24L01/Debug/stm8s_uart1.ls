   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  43                     ; 53 void UART1_DeInit(void)
  43                     ; 54 {
  45                     	switch	.text
  46  0000               _UART1_DeInit:
  50                     ; 57   (void)UART1->SR;
  52  0000 c65230        	ld	a,21040
  53                     ; 58   (void)UART1->DR;
  55  0003 c65231        	ld	a,21041
  56                     ; 60   UART1->BRR2 = UART1_BRR2_RESET_VALUE;  /* Set UART1_BRR2 to reset value 0x00 */
  58  0006 725f5233      	clr	21043
  59                     ; 61   UART1->BRR1 = UART1_BRR1_RESET_VALUE;  /* Set UART1_BRR1 to reset value 0x00 */
  61  000a 725f5232      	clr	21042
  62                     ; 63   UART1->CR1 = UART1_CR1_RESET_VALUE;  /* Set UART1_CR1 to reset value 0x00 */
  64  000e 725f5234      	clr	21044
  65                     ; 64   UART1->CR2 = UART1_CR2_RESET_VALUE;  /* Set UART1_CR2 to reset value 0x00 */
  67  0012 725f5235      	clr	21045
  68                     ; 65   UART1->CR3 = UART1_CR3_RESET_VALUE;  /* Set UART1_CR3 to reset value 0x00 */
  70  0016 725f5236      	clr	21046
  71                     ; 66   UART1->CR4 = UART1_CR4_RESET_VALUE;  /* Set UART1_CR4 to reset value 0x00 */
  73  001a 725f5237      	clr	21047
  74                     ; 67   UART1->CR5 = UART1_CR5_RESET_VALUE;  /* Set UART1_CR5 to reset value 0x00 */
  76  001e 725f5238      	clr	21048
  77                     ; 69   UART1->GTR = UART1_GTR_RESET_VALUE;
  79  0022 725f5239      	clr	21049
  80                     ; 70   UART1->PSCR = UART1_PSCR_RESET_VALUE;
  82  0026 725f523a      	clr	21050
  83                     ; 71 }
  86  002a 81            	ret
 389                     .const:	section	.text
 390  0000               L01:
 391  0000 00000064      	dc.l	100
 392                     ; 90 void UART1_Init(uint32_t BaudRate, UART1_WordLength_TypeDef WordLength, 
 392                     ; 91                 UART1_StopBits_TypeDef StopBits, UART1_Parity_TypeDef Parity, 
 392                     ; 92                 UART1_SyncMode_TypeDef SyncMode, UART1_Mode_TypeDef Mode)
 392                     ; 93 {
 393                     	switch	.text
 394  002b               _UART1_Init:
 396  002b 520c          	subw	sp,#12
 397       0000000c      OFST:	set	12
 400                     ; 94   uint32_t BaudRate_Mantissa = 0, BaudRate_Mantissa100 = 0;
 404                     ; 97   assert_param(IS_UART1_BAUDRATE_OK(BaudRate));
 406                     ; 98   assert_param(IS_UART1_WORDLENGTH_OK(WordLength));
 408                     ; 99   assert_param(IS_UART1_STOPBITS_OK(StopBits));
 410                     ; 100   assert_param(IS_UART1_PARITY_OK(Parity));
 412                     ; 101   assert_param(IS_UART1_MODE_OK((uint8_t)Mode));
 414                     ; 102   assert_param(IS_UART1_SYNCMODE_OK((uint8_t)SyncMode));
 416                     ; 105   UART1->CR1 &= (uint8_t)(~UART1_CR1_M);  
 418  002d 72195234      	bres	21044,#4
 419                     ; 108   UART1->CR1 |= (uint8_t)WordLength;
 421  0031 c65234        	ld	a,21044
 422  0034 1a13          	or	a,(OFST+7,sp)
 423  0036 c75234        	ld	21044,a
 424                     ; 111   UART1->CR3 &= (uint8_t)(~UART1_CR3_STOP);  
 426  0039 c65236        	ld	a,21046
 427  003c a4cf          	and	a,#207
 428  003e c75236        	ld	21046,a
 429                     ; 113   UART1->CR3 |= (uint8_t)StopBits;  
 431  0041 c65236        	ld	a,21046
 432  0044 1a14          	or	a,(OFST+8,sp)
 433  0046 c75236        	ld	21046,a
 434                     ; 116   UART1->CR1 &= (uint8_t)(~(UART1_CR1_PCEN | UART1_CR1_PS  ));  
 436  0049 c65234        	ld	a,21044
 437  004c a4f9          	and	a,#249
 438  004e c75234        	ld	21044,a
 439                     ; 118   UART1->CR1 |= (uint8_t)Parity;  
 441  0051 c65234        	ld	a,21044
 442  0054 1a15          	or	a,(OFST+9,sp)
 443  0056 c75234        	ld	21044,a
 444                     ; 121   UART1->BRR1 &= (uint8_t)(~UART1_BRR1_DIVM);  
 446  0059 725f5232      	clr	21042
 447                     ; 123   UART1->BRR2 &= (uint8_t)(~UART1_BRR2_DIVM);  
 449  005d c65233        	ld	a,21043
 450  0060 a40f          	and	a,#15
 451  0062 c75233        	ld	21043,a
 452                     ; 125   UART1->BRR2 &= (uint8_t)(~UART1_BRR2_DIVF);  
 454  0065 c65233        	ld	a,21043
 455  0068 a4f0          	and	a,#240
 456  006a c75233        	ld	21043,a
 457                     ; 128   BaudRate_Mantissa    = ((uint32_t)CLK_GetClockFreq() / (BaudRate << 4));
 459  006d 96            	ldw	x,sp
 460  006e 1c000f        	addw	x,#OFST+3
 461  0071 cd0000        	call	c_ltor
 463  0074 a604          	ld	a,#4
 464  0076 cd0000        	call	c_llsh
 466  0079 96            	ldw	x,sp
 467  007a 1c0001        	addw	x,#OFST-11
 468  007d cd0000        	call	c_rtol
 470  0080 cd0000        	call	_CLK_GetClockFreq
 472  0083 96            	ldw	x,sp
 473  0084 1c0001        	addw	x,#OFST-11
 474  0087 cd0000        	call	c_ludv
 476  008a 96            	ldw	x,sp
 477  008b 1c0009        	addw	x,#OFST-3
 478  008e cd0000        	call	c_rtol
 480                     ; 129   BaudRate_Mantissa100 = (((uint32_t)CLK_GetClockFreq() * 100) / (BaudRate << 4));
 482  0091 96            	ldw	x,sp
 483  0092 1c000f        	addw	x,#OFST+3
 484  0095 cd0000        	call	c_ltor
 486  0098 a604          	ld	a,#4
 487  009a cd0000        	call	c_llsh
 489  009d 96            	ldw	x,sp
 490  009e 1c0001        	addw	x,#OFST-11
 491  00a1 cd0000        	call	c_rtol
 493  00a4 cd0000        	call	_CLK_GetClockFreq
 495  00a7 a664          	ld	a,#100
 496  00a9 cd0000        	call	c_smul
 498  00ac 96            	ldw	x,sp
 499  00ad 1c0001        	addw	x,#OFST-11
 500  00b0 cd0000        	call	c_ludv
 502  00b3 96            	ldw	x,sp
 503  00b4 1c0005        	addw	x,#OFST-7
 504  00b7 cd0000        	call	c_rtol
 506                     ; 131   UART1->BRR2 |= (uint8_t)((uint8_t)(((BaudRate_Mantissa100 - (BaudRate_Mantissa * 100)) << 4) / 100) & (uint8_t)0x0F); 
 508  00ba 96            	ldw	x,sp
 509  00bb 1c0009        	addw	x,#OFST-3
 510  00be cd0000        	call	c_ltor
 512  00c1 a664          	ld	a,#100
 513  00c3 cd0000        	call	c_smul
 515  00c6 96            	ldw	x,sp
 516  00c7 1c0001        	addw	x,#OFST-11
 517  00ca cd0000        	call	c_rtol
 519  00cd 96            	ldw	x,sp
 520  00ce 1c0005        	addw	x,#OFST-7
 521  00d1 cd0000        	call	c_ltor
 523  00d4 96            	ldw	x,sp
 524  00d5 1c0001        	addw	x,#OFST-11
 525  00d8 cd0000        	call	c_lsub
 527  00db a604          	ld	a,#4
 528  00dd cd0000        	call	c_llsh
 530  00e0 ae0000        	ldw	x,#L01
 531  00e3 cd0000        	call	c_ludv
 533  00e6 b603          	ld	a,c_lreg+3
 534  00e8 a40f          	and	a,#15
 535  00ea ca5233        	or	a,21043
 536  00ed c75233        	ld	21043,a
 537                     ; 133   UART1->BRR2 |= (uint8_t)((BaudRate_Mantissa >> 4) & (uint8_t)0xF0); 
 539  00f0 96            	ldw	x,sp
 540  00f1 1c0009        	addw	x,#OFST-3
 541  00f4 cd0000        	call	c_ltor
 543  00f7 a604          	ld	a,#4
 544  00f9 cd0000        	call	c_lursh
 546  00fc b603          	ld	a,c_lreg+3
 547  00fe a4f0          	and	a,#240
 548  0100 b703          	ld	c_lreg+3,a
 549  0102 3f02          	clr	c_lreg+2
 550  0104 3f01          	clr	c_lreg+1
 551  0106 3f00          	clr	c_lreg
 552  0108 b603          	ld	a,c_lreg+3
 553  010a ca5233        	or	a,21043
 554  010d c75233        	ld	21043,a
 555                     ; 135   UART1->BRR1 |= (uint8_t)BaudRate_Mantissa;           
 557  0110 c65232        	ld	a,21042
 558  0113 1a0c          	or	a,(OFST+0,sp)
 559  0115 c75232        	ld	21042,a
 560                     ; 138   UART1->CR2 &= (uint8_t)~(UART1_CR2_TEN | UART1_CR2_REN); 
 562  0118 c65235        	ld	a,21045
 563  011b a4f3          	and	a,#243
 564  011d c75235        	ld	21045,a
 565                     ; 140   UART1->CR3 &= (uint8_t)~(UART1_CR3_CPOL | UART1_CR3_CPHA | UART1_CR3_LBCL); 
 567  0120 c65236        	ld	a,21046
 568  0123 a4f8          	and	a,#248
 569  0125 c75236        	ld	21046,a
 570                     ; 142   UART1->CR3 |= (uint8_t)((uint8_t)SyncMode & (uint8_t)(UART1_CR3_CPOL | 
 570                     ; 143                                                         UART1_CR3_CPHA | UART1_CR3_LBCL));  
 572  0128 7b16          	ld	a,(OFST+10,sp)
 573  012a a407          	and	a,#7
 574  012c ca5236        	or	a,21046
 575  012f c75236        	ld	21046,a
 576                     ; 145   if ((uint8_t)(Mode & UART1_MODE_TX_ENABLE))
 578  0132 7b17          	ld	a,(OFST+11,sp)
 579  0134 a504          	bcp	a,#4
 580  0136 2706          	jreq	L371
 581                     ; 148     UART1->CR2 |= (uint8_t)UART1_CR2_TEN;  
 583  0138 72165235      	bset	21045,#3
 585  013c 2004          	jra	L571
 586  013e               L371:
 587                     ; 153     UART1->CR2 &= (uint8_t)(~UART1_CR2_TEN);  
 589  013e 72175235      	bres	21045,#3
 590  0142               L571:
 591                     ; 155   if ((uint8_t)(Mode & UART1_MODE_RX_ENABLE))
 593  0142 7b17          	ld	a,(OFST+11,sp)
 594  0144 a508          	bcp	a,#8
 595  0146 2706          	jreq	L771
 596                     ; 158     UART1->CR2 |= (uint8_t)UART1_CR2_REN;  
 598  0148 72145235      	bset	21045,#2
 600  014c 2004          	jra	L102
 601  014e               L771:
 602                     ; 163     UART1->CR2 &= (uint8_t)(~UART1_CR2_REN);  
 604  014e 72155235      	bres	21045,#2
 605  0152               L102:
 606                     ; 167   if ((uint8_t)(SyncMode & UART1_SYNCMODE_CLOCK_DISABLE))
 608  0152 7b16          	ld	a,(OFST+10,sp)
 609  0154 a580          	bcp	a,#128
 610  0156 2706          	jreq	L302
 611                     ; 170     UART1->CR3 &= (uint8_t)(~UART1_CR3_CKEN); 
 613  0158 72175236      	bres	21046,#3
 615  015c 200a          	jra	L502
 616  015e               L302:
 617                     ; 174     UART1->CR3 |= (uint8_t)((uint8_t)SyncMode & UART1_CR3_CKEN);
 619  015e 7b16          	ld	a,(OFST+10,sp)
 620  0160 a408          	and	a,#8
 621  0162 ca5236        	or	a,21046
 622  0165 c75236        	ld	21046,a
 623  0168               L502:
 624                     ; 176 }
 627  0168 5b0c          	addw	sp,#12
 628  016a 81            	ret
 683                     ; 184 void UART1_Cmd(FunctionalState NewState)
 683                     ; 185 {
 684                     	switch	.text
 685  016b               _UART1_Cmd:
 689                     ; 186   if (NewState != DISABLE)
 691  016b 4d            	tnz	a
 692  016c 2706          	jreq	L532
 693                     ; 189     UART1->CR1 &= (uint8_t)(~UART1_CR1_UARTD); 
 695  016e 721b5234      	bres	21044,#5
 697  0172 2004          	jra	L732
 698  0174               L532:
 699                     ; 194     UART1->CR1 |= UART1_CR1_UARTD;  
 701  0174 721a5234      	bset	21044,#5
 702  0178               L732:
 703                     ; 196 }
 706  0178 81            	ret
 831                     ; 211 void UART1_ITConfig(UART1_IT_TypeDef UART1_IT, FunctionalState NewState)
 831                     ; 212 {
 832                     	switch	.text
 833  0179               _UART1_ITConfig:
 835  0179 89            	pushw	x
 836  017a 89            	pushw	x
 837       00000002      OFST:	set	2
 840                     ; 213   uint8_t uartreg = 0, itpos = 0x00;
 844                     ; 216   assert_param(IS_UART1_CONFIG_IT_OK(UART1_IT));
 846                     ; 217   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 848                     ; 220   uartreg = (uint8_t)((uint16_t)UART1_IT >> 0x08);
 850  017b 9e            	ld	a,xh
 851  017c 6b01          	ld	(OFST-1,sp),a
 852                     ; 222   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)UART1_IT & (uint8_t)0x0F));
 854  017e 9f            	ld	a,xl
 855  017f a40f          	and	a,#15
 856  0181 5f            	clrw	x
 857  0182 97            	ld	xl,a
 858  0183 a601          	ld	a,#1
 859  0185 5d            	tnzw	x
 860  0186 2704          	jreq	L61
 861  0188               L02:
 862  0188 48            	sll	a
 863  0189 5a            	decw	x
 864  018a 26fc          	jrne	L02
 865  018c               L61:
 866  018c 6b02          	ld	(OFST+0,sp),a
 867                     ; 224   if (NewState != DISABLE)
 869  018e 0d07          	tnz	(OFST+5,sp)
 870  0190 272a          	jreq	L713
 871                     ; 227     if (uartreg == 0x01)
 873  0192 7b01          	ld	a,(OFST-1,sp)
 874  0194 a101          	cp	a,#1
 875  0196 260a          	jrne	L123
 876                     ; 229       UART1->CR1 |= itpos;
 878  0198 c65234        	ld	a,21044
 879  019b 1a02          	or	a,(OFST+0,sp)
 880  019d c75234        	ld	21044,a
 882  01a0 2045          	jra	L133
 883  01a2               L123:
 884                     ; 231     else if (uartreg == 0x02)
 886  01a2 7b01          	ld	a,(OFST-1,sp)
 887  01a4 a102          	cp	a,#2
 888  01a6 260a          	jrne	L523
 889                     ; 233       UART1->CR2 |= itpos;
 891  01a8 c65235        	ld	a,21045
 892  01ab 1a02          	or	a,(OFST+0,sp)
 893  01ad c75235        	ld	21045,a
 895  01b0 2035          	jra	L133
 896  01b2               L523:
 897                     ; 237       UART1->CR4 |= itpos;
 899  01b2 c65237        	ld	a,21047
 900  01b5 1a02          	or	a,(OFST+0,sp)
 901  01b7 c75237        	ld	21047,a
 902  01ba 202b          	jra	L133
 903  01bc               L713:
 904                     ; 243     if (uartreg == 0x01)
 906  01bc 7b01          	ld	a,(OFST-1,sp)
 907  01be a101          	cp	a,#1
 908  01c0 260b          	jrne	L333
 909                     ; 245       UART1->CR1 &= (uint8_t)(~itpos);
 911  01c2 7b02          	ld	a,(OFST+0,sp)
 912  01c4 43            	cpl	a
 913  01c5 c45234        	and	a,21044
 914  01c8 c75234        	ld	21044,a
 916  01cb 201a          	jra	L133
 917  01cd               L333:
 918                     ; 247     else if (uartreg == 0x02)
 920  01cd 7b01          	ld	a,(OFST-1,sp)
 921  01cf a102          	cp	a,#2
 922  01d1 260b          	jrne	L733
 923                     ; 249       UART1->CR2 &= (uint8_t)(~itpos);
 925  01d3 7b02          	ld	a,(OFST+0,sp)
 926  01d5 43            	cpl	a
 927  01d6 c45235        	and	a,21045
 928  01d9 c75235        	ld	21045,a
 930  01dc 2009          	jra	L133
 931  01de               L733:
 932                     ; 253       UART1->CR4 &= (uint8_t)(~itpos);
 934  01de 7b02          	ld	a,(OFST+0,sp)
 935  01e0 43            	cpl	a
 936  01e1 c45237        	and	a,21047
 937  01e4 c75237        	ld	21047,a
 938  01e7               L133:
 939                     ; 257 }
 942  01e7 5b04          	addw	sp,#4
 943  01e9 81            	ret
 979                     ; 265 void UART1_HalfDuplexCmd(FunctionalState NewState)
 979                     ; 266 {
 980                     	switch	.text
 981  01ea               _UART1_HalfDuplexCmd:
 985                     ; 267   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 987                     ; 269   if (NewState != DISABLE)
 989  01ea 4d            	tnz	a
 990  01eb 2706          	jreq	L163
 991                     ; 271     UART1->CR5 |= UART1_CR5_HDSEL;  /**< UART1 Half Duplex Enable  */
 993  01ed 72165238      	bset	21048,#3
 995  01f1 2004          	jra	L363
 996  01f3               L163:
 997                     ; 275     UART1->CR5 &= (uint8_t)~UART1_CR5_HDSEL; /**< UART1 Half Duplex Disable */
 999  01f3 72175238      	bres	21048,#3
1000  01f7               L363:
1001                     ; 277 }
1004  01f7 81            	ret
1061                     ; 285 void UART1_IrDAConfig(UART1_IrDAMode_TypeDef UART1_IrDAMode)
1061                     ; 286 {
1062                     	switch	.text
1063  01f8               _UART1_IrDAConfig:
1067                     ; 287   assert_param(IS_UART1_IRDAMODE_OK(UART1_IrDAMode));
1069                     ; 289   if (UART1_IrDAMode != UART1_IRDAMODE_NORMAL)
1071  01f8 4d            	tnz	a
1072  01f9 2706          	jreq	L314
1073                     ; 291     UART1->CR5 |= UART1_CR5_IRLP;
1075  01fb 72145238      	bset	21048,#2
1077  01ff 2004          	jra	L514
1078  0201               L314:
1079                     ; 295     UART1->CR5 &= ((uint8_t)~UART1_CR5_IRLP);
1081  0201 72155238      	bres	21048,#2
1082  0205               L514:
1083                     ; 297 }
1086  0205 81            	ret
1121                     ; 305 void UART1_IrDACmd(FunctionalState NewState)
1121                     ; 306 {
1122                     	switch	.text
1123  0206               _UART1_IrDACmd:
1127                     ; 308   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1129                     ; 310   if (NewState != DISABLE)
1131  0206 4d            	tnz	a
1132  0207 2706          	jreq	L534
1133                     ; 313     UART1->CR5 |= UART1_CR5_IREN;
1135  0209 72125238      	bset	21048,#1
1137  020d 2004          	jra	L734
1138  020f               L534:
1139                     ; 318     UART1->CR5 &= ((uint8_t)~UART1_CR5_IREN);
1141  020f 72135238      	bres	21048,#1
1142  0213               L734:
1143                     ; 320 }
1146  0213 81            	ret
1205                     ; 329 void UART1_LINBreakDetectionConfig(UART1_LINBreakDetectionLength_TypeDef UART1_LINBreakDetectionLength)
1205                     ; 330 {
1206                     	switch	.text
1207  0214               _UART1_LINBreakDetectionConfig:
1211                     ; 331   assert_param(IS_UART1_LINBREAKDETECTIONLENGTH_OK(UART1_LINBreakDetectionLength));
1213                     ; 333   if (UART1_LINBreakDetectionLength != UART1_LINBREAKDETECTIONLENGTH_10BITS)
1215  0214 4d            	tnz	a
1216  0215 2706          	jreq	L764
1217                     ; 335     UART1->CR4 |= UART1_CR4_LBDL;
1219  0217 721a5237      	bset	21047,#5
1221  021b 2004          	jra	L174
1222  021d               L764:
1223                     ; 339     UART1->CR4 &= ((uint8_t)~UART1_CR4_LBDL);
1225  021d 721b5237      	bres	21047,#5
1226  0221               L174:
1227                     ; 341 }
1230  0221 81            	ret
1265                     ; 349 void UART1_LINCmd(FunctionalState NewState)
1265                     ; 350 {
1266                     	switch	.text
1267  0222               _UART1_LINCmd:
1271                     ; 351   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1273                     ; 353   if (NewState != DISABLE)
1275  0222 4d            	tnz	a
1276  0223 2706          	jreq	L115
1277                     ; 356     UART1->CR3 |= UART1_CR3_LINEN;
1279  0225 721c5236      	bset	21046,#6
1281  0229 2004          	jra	L315
1282  022b               L115:
1283                     ; 361     UART1->CR3 &= ((uint8_t)~UART1_CR3_LINEN);
1285  022b 721d5236      	bres	21046,#6
1286  022f               L315:
1287                     ; 363 }
1290  022f 81            	ret
1325                     ; 371 void UART1_SmartCardCmd(FunctionalState NewState)
1325                     ; 372 {
1326                     	switch	.text
1327  0230               _UART1_SmartCardCmd:
1331                     ; 373   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1333                     ; 375   if (NewState != DISABLE)
1335  0230 4d            	tnz	a
1336  0231 2706          	jreq	L335
1337                     ; 378     UART1->CR5 |= UART1_CR5_SCEN;
1339  0233 721a5238      	bset	21048,#5
1341  0237 2004          	jra	L535
1342  0239               L335:
1343                     ; 383     UART1->CR5 &= ((uint8_t)(~UART1_CR5_SCEN));
1345  0239 721b5238      	bres	21048,#5
1346  023d               L535:
1347                     ; 385 }
1350  023d 81            	ret
1386                     ; 394 void UART1_SmartCardNACKCmd(FunctionalState NewState)
1386                     ; 395 {
1387                     	switch	.text
1388  023e               _UART1_SmartCardNACKCmd:
1392                     ; 396   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1394                     ; 398   if (NewState != DISABLE)
1396  023e 4d            	tnz	a
1397  023f 2706          	jreq	L555
1398                     ; 401     UART1->CR5 |= UART1_CR5_NACK;
1400  0241 72185238      	bset	21048,#4
1402  0245 2004          	jra	L755
1403  0247               L555:
1404                     ; 406     UART1->CR5 &= ((uint8_t)~(UART1_CR5_NACK));
1406  0247 72195238      	bres	21048,#4
1407  024b               L755:
1408                     ; 408 }
1411  024b 81            	ret
1468                     ; 416 void UART1_WakeUpConfig(UART1_WakeUp_TypeDef UART1_WakeUp)
1468                     ; 417 {
1469                     	switch	.text
1470  024c               _UART1_WakeUpConfig:
1474                     ; 418   assert_param(IS_UART1_WAKEUP_OK(UART1_WakeUp));
1476                     ; 420   UART1->CR1 &= ((uint8_t)~UART1_CR1_WAKE);
1478  024c 72175234      	bres	21044,#3
1479                     ; 421   UART1->CR1 |= (uint8_t)UART1_WakeUp;
1481  0250 ca5234        	or	a,21044
1482  0253 c75234        	ld	21044,a
1483                     ; 422 }
1486  0256 81            	ret
1522                     ; 430 void UART1_ReceiverWakeUpCmd(FunctionalState NewState)
1522                     ; 431 {
1523                     	switch	.text
1524  0257               _UART1_ReceiverWakeUpCmd:
1528                     ; 432   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
1530                     ; 434   if (NewState != DISABLE)
1532  0257 4d            	tnz	a
1533  0258 2706          	jreq	L526
1534                     ; 437     UART1->CR2 |= UART1_CR2_RWU;
1536  025a 72125235      	bset	21045,#1
1538  025e 2004          	jra	L726
1539  0260               L526:
1540                     ; 442     UART1->CR2 &= ((uint8_t)~UART1_CR2_RWU);
1542  0260 72135235      	bres	21045,#1
1543  0264               L726:
1544                     ; 444 }
1547  0264 81            	ret
1570                     ; 451 uint8_t UART1_ReceiveData8(void)
1570                     ; 452 {
1571                     	switch	.text
1572  0265               _UART1_ReceiveData8:
1576                     ; 453   return ((uint8_t)UART1->DR);
1578  0265 c65231        	ld	a,21041
1581  0268 81            	ret
1615                     ; 461 uint16_t UART1_ReceiveData9(void)
1615                     ; 462 {
1616                     	switch	.text
1617  0269               _UART1_ReceiveData9:
1619  0269 89            	pushw	x
1620       00000002      OFST:	set	2
1623                     ; 463   uint16_t temp = 0;
1625                     ; 465   temp = (uint16_t)(((uint16_t)( (uint16_t)UART1->CR1 & (uint16_t)UART1_CR1_R8)) << 1);
1627  026a c65234        	ld	a,21044
1628  026d 5f            	clrw	x
1629  026e a480          	and	a,#128
1630  0270 5f            	clrw	x
1631  0271 02            	rlwa	x,a
1632  0272 58            	sllw	x
1633  0273 1f01          	ldw	(OFST-1,sp),x
1634                     ; 466   return (uint16_t)( (((uint16_t) UART1->DR) | temp ) & ((uint16_t)0x01FF));
1636  0275 c65231        	ld	a,21041
1637  0278 5f            	clrw	x
1638  0279 97            	ld	xl,a
1639  027a 01            	rrwa	x,a
1640  027b 1a02          	or	a,(OFST+0,sp)
1641  027d 01            	rrwa	x,a
1642  027e 1a01          	or	a,(OFST-1,sp)
1643  0280 01            	rrwa	x,a
1644  0281 01            	rrwa	x,a
1645  0282 a4ff          	and	a,#255
1646  0284 01            	rrwa	x,a
1647  0285 a401          	and	a,#1
1648  0287 01            	rrwa	x,a
1651  0288 5b02          	addw	sp,#2
1652  028a 81            	ret
1686                     ; 474 void UART1_SendData8(uint8_t Data)
1686                     ; 475 {
1687                     	switch	.text
1688  028b               _UART1_SendData8:
1692                     ; 477   UART1->DR = Data;
1694  028b c75231        	ld	21041,a
1695                     ; 478 }
1698  028e 81            	ret
1732                     ; 486 void UART1_SendData9(uint16_t Data)
1732                     ; 487 {
1733                     	switch	.text
1734  028f               _UART1_SendData9:
1736  028f 89            	pushw	x
1737       00000000      OFST:	set	0
1740                     ; 489   UART1->CR1 &= ((uint8_t)~UART1_CR1_T8);
1742  0290 721d5234      	bres	21044,#6
1743                     ; 491   UART1->CR1 |= (uint8_t)(((uint8_t)(Data >> 2)) & UART1_CR1_T8);
1745  0294 54            	srlw	x
1746  0295 54            	srlw	x
1747  0296 9f            	ld	a,xl
1748  0297 a440          	and	a,#64
1749  0299 ca5234        	or	a,21044
1750  029c c75234        	ld	21044,a
1751                     ; 493   UART1->DR   = (uint8_t)(Data);
1753  029f 7b02          	ld	a,(OFST+2,sp)
1754  02a1 c75231        	ld	21041,a
1755                     ; 494 }
1758  02a4 85            	popw	x
1759  02a5 81            	ret
1782                     ; 501 void UART1_SendBreak(void)
1782                     ; 502 {
1783                     	switch	.text
1784  02a6               _UART1_SendBreak:
1788                     ; 503   UART1->CR2 |= UART1_CR2_SBK;
1790  02a6 72105235      	bset	21045,#0
1791                     ; 504 }
1794  02aa 81            	ret
1828                     ; 511 void UART1_SetAddress(uint8_t UART1_Address)
1828                     ; 512 {
1829                     	switch	.text
1830  02ab               _UART1_SetAddress:
1832  02ab 88            	push	a
1833       00000000      OFST:	set	0
1836                     ; 514   assert_param(IS_UART1_ADDRESS_OK(UART1_Address));
1838                     ; 517   UART1->CR4 &= ((uint8_t)~UART1_CR4_ADD);
1840  02ac c65237        	ld	a,21047
1841  02af a4f0          	and	a,#240
1842  02b1 c75237        	ld	21047,a
1843                     ; 519   UART1->CR4 |= UART1_Address;
1845  02b4 c65237        	ld	a,21047
1846  02b7 1a01          	or	a,(OFST+1,sp)
1847  02b9 c75237        	ld	21047,a
1848                     ; 520 }
1851  02bc 84            	pop	a
1852  02bd 81            	ret
1886                     ; 528 void UART1_SetGuardTime(uint8_t UART1_GuardTime)
1886                     ; 529 {
1887                     	switch	.text
1888  02be               _UART1_SetGuardTime:
1892                     ; 531   UART1->GTR = UART1_GuardTime;
1894  02be c75239        	ld	21049,a
1895                     ; 532 }
1898  02c1 81            	ret
1932                     ; 556 void UART1_SetPrescaler(uint8_t UART1_Prescaler)
1932                     ; 557 {
1933                     	switch	.text
1934  02c2               _UART1_SetPrescaler:
1938                     ; 559   UART1->PSCR = UART1_Prescaler;
1940  02c2 c7523a        	ld	21050,a
1941                     ; 560 }
1944  02c5 81            	ret
2087                     ; 568 FlagStatus UART1_GetFlagStatus(UART1_Flag_TypeDef UART1_FLAG)
2087                     ; 569 {
2088                     	switch	.text
2089  02c6               _UART1_GetFlagStatus:
2091  02c6 89            	pushw	x
2092  02c7 88            	push	a
2093       00000001      OFST:	set	1
2096                     ; 570   FlagStatus status = RESET;
2098                     ; 573   assert_param(IS_UART1_FLAG_OK(UART1_FLAG));
2100                     ; 577   if (UART1_FLAG == UART1_FLAG_LBDF)
2102  02c8 a30210        	cpw	x,#528
2103  02cb 2610          	jrne	L7501
2104                     ; 579     if ((UART1->CR4 & (uint8_t)UART1_FLAG) != (uint8_t)0x00)
2106  02cd 9f            	ld	a,xl
2107  02ce c45237        	and	a,21047
2108  02d1 2706          	jreq	L1601
2109                     ; 582       status = SET;
2111  02d3 a601          	ld	a,#1
2112  02d5 6b01          	ld	(OFST+0,sp),a
2114  02d7 202b          	jra	L5601
2115  02d9               L1601:
2116                     ; 587       status = RESET;
2118  02d9 0f01          	clr	(OFST+0,sp)
2119  02db 2027          	jra	L5601
2120  02dd               L7501:
2121                     ; 590   else if (UART1_FLAG == UART1_FLAG_SBK)
2123  02dd 1e02          	ldw	x,(OFST+1,sp)
2124  02df a30101        	cpw	x,#257
2125  02e2 2611          	jrne	L7601
2126                     ; 592     if ((UART1->CR2 & (uint8_t)UART1_FLAG) != (uint8_t)0x00)
2128  02e4 c65235        	ld	a,21045
2129  02e7 1503          	bcp	a,(OFST+2,sp)
2130  02e9 2706          	jreq	L1701
2131                     ; 595       status = SET;
2133  02eb a601          	ld	a,#1
2134  02ed 6b01          	ld	(OFST+0,sp),a
2136  02ef 2013          	jra	L5601
2137  02f1               L1701:
2138                     ; 600       status = RESET;
2140  02f1 0f01          	clr	(OFST+0,sp)
2141  02f3 200f          	jra	L5601
2142  02f5               L7601:
2143                     ; 605     if ((UART1->SR & (uint8_t)UART1_FLAG) != (uint8_t)0x00)
2145  02f5 c65230        	ld	a,21040
2146  02f8 1503          	bcp	a,(OFST+2,sp)
2147  02fa 2706          	jreq	L7701
2148                     ; 608       status = SET;
2150  02fc a601          	ld	a,#1
2151  02fe 6b01          	ld	(OFST+0,sp),a
2153  0300 2002          	jra	L5601
2154  0302               L7701:
2155                     ; 613       status = RESET;
2157  0302 0f01          	clr	(OFST+0,sp)
2158  0304               L5601:
2159                     ; 617   return status;
2161  0304 7b01          	ld	a,(OFST+0,sp)
2164  0306 5b03          	addw	sp,#3
2165  0308 81            	ret
2200                     ; 646 void UART1_ClearFlag(UART1_Flag_TypeDef UART1_FLAG)
2200                     ; 647 {
2201                     	switch	.text
2202  0309               _UART1_ClearFlag:
2206                     ; 648   assert_param(IS_UART1_CLEAR_FLAG_OK(UART1_FLAG));
2208                     ; 651   if (UART1_FLAG == UART1_FLAG_RXNE)
2210  0309 a30020        	cpw	x,#32
2211  030c 2606          	jrne	L1211
2212                     ; 653     UART1->SR = (uint8_t)~(UART1_SR_RXNE);
2214  030e 35df5230      	mov	21040,#223
2216  0312 2004          	jra	L3211
2217  0314               L1211:
2218                     ; 658     UART1->CR4 &= (uint8_t)~(UART1_CR4_LBDF);
2220  0314 72195237      	bres	21047,#4
2221  0318               L3211:
2222                     ; 660 }
2225  0318 81            	ret
2307                     ; 675 ITStatus UART1_GetITStatus(UART1_IT_TypeDef UART1_IT)
2307                     ; 676 {
2308                     	switch	.text
2309  0319               _UART1_GetITStatus:
2311  0319 89            	pushw	x
2312  031a 89            	pushw	x
2313       00000002      OFST:	set	2
2316                     ; 677   ITStatus pendingbitstatus = RESET;
2318                     ; 678   uint8_t itpos = 0;
2320                     ; 679   uint8_t itmask1 = 0;
2322                     ; 680   uint8_t itmask2 = 0;
2324                     ; 681   uint8_t enablestatus = 0;
2326                     ; 684   assert_param(IS_UART1_GET_IT_OK(UART1_IT));
2328                     ; 687   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)UART1_IT & (uint8_t)0x0F));
2330  031b 9f            	ld	a,xl
2331  031c a40f          	and	a,#15
2332  031e 5f            	clrw	x
2333  031f 97            	ld	xl,a
2334  0320 a601          	ld	a,#1
2335  0322 5d            	tnzw	x
2336  0323 2704          	jreq	L27
2337  0325               L47:
2338  0325 48            	sll	a
2339  0326 5a            	decw	x
2340  0327 26fc          	jrne	L47
2341  0329               L27:
2342  0329 6b01          	ld	(OFST-1,sp),a
2343                     ; 689   itmask1 = (uint8_t)((uint8_t)UART1_IT >> (uint8_t)4);
2345  032b 7b04          	ld	a,(OFST+2,sp)
2346  032d 4e            	swap	a
2347  032e a40f          	and	a,#15
2348  0330 6b02          	ld	(OFST+0,sp),a
2349                     ; 691   itmask2 = (uint8_t)((uint8_t)1 << itmask1);
2351  0332 7b02          	ld	a,(OFST+0,sp)
2352  0334 5f            	clrw	x
2353  0335 97            	ld	xl,a
2354  0336 a601          	ld	a,#1
2355  0338 5d            	tnzw	x
2356  0339 2704          	jreq	L67
2357  033b               L001:
2358  033b 48            	sll	a
2359  033c 5a            	decw	x
2360  033d 26fc          	jrne	L001
2361  033f               L67:
2362  033f 6b02          	ld	(OFST+0,sp),a
2363                     ; 695   if (UART1_IT == UART1_IT_PE)
2365  0341 1e03          	ldw	x,(OFST+1,sp)
2366  0343 a30100        	cpw	x,#256
2367  0346 261c          	jrne	L7611
2368                     ; 698     enablestatus = (uint8_t)((uint8_t)UART1->CR1 & itmask2);
2370  0348 c65234        	ld	a,21044
2371  034b 1402          	and	a,(OFST+0,sp)
2372  034d 6b02          	ld	(OFST+0,sp),a
2373                     ; 701     if (((UART1->SR & itpos) != (uint8_t)0x00) && enablestatus)
2375  034f c65230        	ld	a,21040
2376  0352 1501          	bcp	a,(OFST-1,sp)
2377  0354 270a          	jreq	L1711
2379  0356 0d02          	tnz	(OFST+0,sp)
2380  0358 2706          	jreq	L1711
2381                     ; 704       pendingbitstatus = SET;
2383  035a a601          	ld	a,#1
2384  035c 6b02          	ld	(OFST+0,sp),a
2386  035e 2041          	jra	L5711
2387  0360               L1711:
2388                     ; 709       pendingbitstatus = RESET;
2390  0360 0f02          	clr	(OFST+0,sp)
2391  0362 203d          	jra	L5711
2392  0364               L7611:
2393                     ; 713   else if (UART1_IT == UART1_IT_LBDF)
2395  0364 1e03          	ldw	x,(OFST+1,sp)
2396  0366 a30346        	cpw	x,#838
2397  0369 261c          	jrne	L7711
2398                     ; 716     enablestatus = (uint8_t)((uint8_t)UART1->CR4 & itmask2);
2400  036b c65237        	ld	a,21047
2401  036e 1402          	and	a,(OFST+0,sp)
2402  0370 6b02          	ld	(OFST+0,sp),a
2403                     ; 718     if (((UART1->CR4 & itpos) != (uint8_t)0x00) && enablestatus)
2405  0372 c65237        	ld	a,21047
2406  0375 1501          	bcp	a,(OFST-1,sp)
2407  0377 270a          	jreq	L1021
2409  0379 0d02          	tnz	(OFST+0,sp)
2410  037b 2706          	jreq	L1021
2411                     ; 721       pendingbitstatus = SET;
2413  037d a601          	ld	a,#1
2414  037f 6b02          	ld	(OFST+0,sp),a
2416  0381 201e          	jra	L5711
2417  0383               L1021:
2418                     ; 726       pendingbitstatus = RESET;
2420  0383 0f02          	clr	(OFST+0,sp)
2421  0385 201a          	jra	L5711
2422  0387               L7711:
2423                     ; 732     enablestatus = (uint8_t)((uint8_t)UART1->CR2 & itmask2);
2425  0387 c65235        	ld	a,21045
2426  038a 1402          	and	a,(OFST+0,sp)
2427  038c 6b02          	ld	(OFST+0,sp),a
2428                     ; 734     if (((UART1->SR & itpos) != (uint8_t)0x00) && enablestatus)
2430  038e c65230        	ld	a,21040
2431  0391 1501          	bcp	a,(OFST-1,sp)
2432  0393 270a          	jreq	L7021
2434  0395 0d02          	tnz	(OFST+0,sp)
2435  0397 2706          	jreq	L7021
2436                     ; 737       pendingbitstatus = SET;
2438  0399 a601          	ld	a,#1
2439  039b 6b02          	ld	(OFST+0,sp),a
2441  039d 2002          	jra	L5711
2442  039f               L7021:
2443                     ; 742       pendingbitstatus = RESET;
2445  039f 0f02          	clr	(OFST+0,sp)
2446  03a1               L5711:
2447                     ; 747   return  pendingbitstatus;
2449  03a1 7b02          	ld	a,(OFST+0,sp)
2452  03a3 5b04          	addw	sp,#4
2453  03a5 81            	ret
2489                     ; 775 void UART1_ClearITPendingBit(UART1_IT_TypeDef UART1_IT)
2489                     ; 776 {
2490                     	switch	.text
2491  03a6               _UART1_ClearITPendingBit:
2495                     ; 777   assert_param(IS_UART1_CLEAR_IT_OK(UART1_IT));
2497                     ; 780   if (UART1_IT == UART1_IT_RXNE)
2499  03a6 a30255        	cpw	x,#597
2500  03a9 2606          	jrne	L1321
2501                     ; 782     UART1->SR = (uint8_t)~(UART1_SR_RXNE);
2503  03ab 35df5230      	mov	21040,#223
2505  03af 2004          	jra	L3321
2506  03b1               L1321:
2507                     ; 787     UART1->CR4 &= (uint8_t)~(UART1_CR4_LBDF);
2509  03b1 72195237      	bres	21047,#4
2510  03b5               L3321:
2511                     ; 789 }
2514  03b5 81            	ret
2527                     	xdef	_UART1_ClearITPendingBit
2528                     	xdef	_UART1_GetITStatus
2529                     	xdef	_UART1_ClearFlag
2530                     	xdef	_UART1_GetFlagStatus
2531                     	xdef	_UART1_SetPrescaler
2532                     	xdef	_UART1_SetGuardTime
2533                     	xdef	_UART1_SetAddress
2534                     	xdef	_UART1_SendBreak
2535                     	xdef	_UART1_SendData9
2536                     	xdef	_UART1_SendData8
2537                     	xdef	_UART1_ReceiveData9
2538                     	xdef	_UART1_ReceiveData8
2539                     	xdef	_UART1_ReceiverWakeUpCmd
2540                     	xdef	_UART1_WakeUpConfig
2541                     	xdef	_UART1_SmartCardNACKCmd
2542                     	xdef	_UART1_SmartCardCmd
2543                     	xdef	_UART1_LINCmd
2544                     	xdef	_UART1_LINBreakDetectionConfig
2545                     	xdef	_UART1_IrDACmd
2546                     	xdef	_UART1_IrDAConfig
2547                     	xdef	_UART1_HalfDuplexCmd
2548                     	xdef	_UART1_ITConfig
2549                     	xdef	_UART1_Cmd
2550                     	xdef	_UART1_Init
2551                     	xdef	_UART1_DeInit
2552                     	xref	_CLK_GetClockFreq
2553                     	xref.b	c_lreg
2554                     	xref.b	c_x
2573                     	xref	c_lursh
2574                     	xref	c_lsub
2575                     	xref	c_smul
2576                     	xref	c_ludv
2577                     	xref	c_rtol
2578                     	xref	c_llsh
2579                     	xref	c_ltor
2580                     	end
