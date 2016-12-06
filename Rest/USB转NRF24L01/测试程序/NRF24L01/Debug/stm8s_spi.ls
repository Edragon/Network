   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
  43                     ; 50 void SPI_DeInit(void)
  43                     ; 51 {
  45                     	switch	.text
  46  0000               _SPI_DeInit:
  50                     ; 52   SPI->CR1    = SPI_CR1_RESET_VALUE;
  52  0000 725f5200      	clr	20992
  53                     ; 53   SPI->CR2    = SPI_CR2_RESET_VALUE;
  55  0004 725f5201      	clr	20993
  56                     ; 54   SPI->ICR    = SPI_ICR_RESET_VALUE;
  58  0008 725f5202      	clr	20994
  59                     ; 55   SPI->SR     = SPI_SR_RESET_VALUE;
  61  000c 35025203      	mov	20995,#2
  62                     ; 56   SPI->CRCPR  = SPI_CRCPR_RESET_VALUE;
  64  0010 35075205      	mov	20997,#7
  65                     ; 57 }
  68  0014 81            	ret
 384                     ; 78 void SPI_Init(SPI_FirstBit_TypeDef FirstBit, SPI_BaudRatePrescaler_TypeDef BaudRatePrescaler, SPI_Mode_TypeDef Mode, SPI_ClockPolarity_TypeDef ClockPolarity, SPI_ClockPhase_TypeDef ClockPhase, SPI_DataDirection_TypeDef Data_Direction, SPI_NSS_TypeDef Slave_Management, uint8_t CRCPolynomial)
 384                     ; 79 {
 385                     	switch	.text
 386  0015               _SPI_Init:
 388  0015 89            	pushw	x
 389  0016 88            	push	a
 390       00000001      OFST:	set	1
 393                     ; 81   assert_param(IS_SPI_FIRSTBIT_OK(FirstBit));
 395                     ; 82   assert_param(IS_SPI_BAUDRATE_PRESCALER_OK(BaudRatePrescaler));
 397                     ; 83   assert_param(IS_SPI_MODE_OK(Mode));
 399                     ; 84   assert_param(IS_SPI_POLARITY_OK(ClockPolarity));
 401                     ; 85   assert_param(IS_SPI_PHASE_OK(ClockPhase));
 403                     ; 86   assert_param(IS_SPI_DATA_DIRECTION_OK(Data_Direction));
 405                     ; 87   assert_param(IS_SPI_SLAVEMANAGEMENT_OK(Slave_Management));
 407                     ; 88   assert_param(IS_SPI_CRC_POLYNOMIAL_OK(CRCPolynomial));
 409                     ; 91   SPI->CR1 = (uint8_t)((uint8_t)((uint8_t)FirstBit | BaudRatePrescaler) |
 409                     ; 92                        (uint8_t)((uint8_t)ClockPolarity | ClockPhase));
 411  0017 7b07          	ld	a,(OFST+6,sp)
 412  0019 1a08          	or	a,(OFST+7,sp)
 413  001b 6b01          	ld	(OFST+0,sp),a
 414  001d 9f            	ld	a,xl
 415  001e 1a02          	or	a,(OFST+1,sp)
 416  0020 1a01          	or	a,(OFST+0,sp)
 417  0022 c75200        	ld	20992,a
 418                     ; 95   SPI->CR2 = (uint8_t)((uint8_t)(Data_Direction) | (uint8_t)(Slave_Management));
 420  0025 7b09          	ld	a,(OFST+8,sp)
 421  0027 1a0a          	or	a,(OFST+9,sp)
 422  0029 c75201        	ld	20993,a
 423                     ; 97   if (Mode == SPI_MODE_MASTER)
 425  002c 7b06          	ld	a,(OFST+5,sp)
 426  002e a104          	cp	a,#4
 427  0030 2606          	jrne	L302
 428                     ; 99     SPI->CR2 |= (uint8_t)SPI_CR2_SSI;
 430  0032 72105201      	bset	20993,#0
 432  0036 2004          	jra	L502
 433  0038               L302:
 434                     ; 103     SPI->CR2 &= (uint8_t)~(SPI_CR2_SSI);
 436  0038 72115201      	bres	20993,#0
 437  003c               L502:
 438                     ; 107   SPI->CR1 |= (uint8_t)(Mode);
 440  003c c65200        	ld	a,20992
 441  003f 1a06          	or	a,(OFST+5,sp)
 442  0041 c75200        	ld	20992,a
 443                     ; 110   SPI->CRCPR = (uint8_t)CRCPolynomial;
 445  0044 7b0b          	ld	a,(OFST+10,sp)
 446  0046 c75205        	ld	20997,a
 447                     ; 111 }
 450  0049 5b03          	addw	sp,#3
 451  004b 81            	ret
 506                     ; 119 void SPI_Cmd(FunctionalState NewState)
 506                     ; 120 {
 507                     	switch	.text
 508  004c               _SPI_Cmd:
 512                     ; 122   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 514                     ; 124   if (NewState != DISABLE)
 516  004c 4d            	tnz	a
 517  004d 2706          	jreq	L532
 518                     ; 126     SPI->CR1 |= SPI_CR1_SPE; /* Enable the SPI peripheral*/
 520  004f 721c5200      	bset	20992,#6
 522  0053 2004          	jra	L732
 523  0055               L532:
 524                     ; 130     SPI->CR1 &= (uint8_t)(~SPI_CR1_SPE); /* Disable the SPI peripheral*/
 526  0055 721d5200      	bres	20992,#6
 527  0059               L732:
 528                     ; 132 }
 531  0059 81            	ret
 640                     ; 141 void SPI_ITConfig(SPI_IT_TypeDef SPI_IT, FunctionalState NewState)
 640                     ; 142 {
 641                     	switch	.text
 642  005a               _SPI_ITConfig:
 644  005a 89            	pushw	x
 645  005b 88            	push	a
 646       00000001      OFST:	set	1
 649                     ; 143   uint8_t itpos = 0;
 651                     ; 145   assert_param(IS_SPI_CONFIG_IT_OK(SPI_IT));
 653                     ; 146   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 655                     ; 149   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)SPI_IT & (uint8_t)0x0F));
 657  005c 9e            	ld	a,xh
 658  005d a40f          	and	a,#15
 659  005f 5f            	clrw	x
 660  0060 97            	ld	xl,a
 661  0061 a601          	ld	a,#1
 662  0063 5d            	tnzw	x
 663  0064 2704          	jreq	L41
 664  0066               L61:
 665  0066 48            	sll	a
 666  0067 5a            	decw	x
 667  0068 26fc          	jrne	L61
 668  006a               L41:
 669  006a 6b01          	ld	(OFST+0,sp),a
 670                     ; 151   if (NewState != DISABLE)
 672  006c 0d03          	tnz	(OFST+2,sp)
 673  006e 270a          	jreq	L113
 674                     ; 153     SPI->ICR |= itpos; /* Enable interrupt*/
 676  0070 c65202        	ld	a,20994
 677  0073 1a01          	or	a,(OFST+0,sp)
 678  0075 c75202        	ld	20994,a
 680  0078 2009          	jra	L313
 681  007a               L113:
 682                     ; 157     SPI->ICR &= (uint8_t)(~itpos); /* Disable interrupt*/
 684  007a 7b01          	ld	a,(OFST+0,sp)
 685  007c 43            	cpl	a
 686  007d c45202        	and	a,20994
 687  0080 c75202        	ld	20994,a
 688  0083               L313:
 689                     ; 159 }
 692  0083 5b03          	addw	sp,#3
 693  0085 81            	ret
 727                     ; 166 void SPI_SendData(uint8_t Data)
 727                     ; 167 {
 728                     	switch	.text
 729  0086               _SPI_SendData:
 733                     ; 168   SPI->DR = Data; /* Write in the DR register the data to be sent*/
 735  0086 c75204        	ld	20996,a
 736                     ; 169 }
 739  0089 81            	ret
 762                     ; 176 uint8_t SPI_ReceiveData(void)
 762                     ; 177 {
 763                     	switch	.text
 764  008a               _SPI_ReceiveData:
 768                     ; 178   return ((uint8_t)SPI->DR); /* Return the data in the DR register*/
 770  008a c65204        	ld	a,20996
 773  008d 81            	ret
 809                     ; 187 void SPI_NSSInternalSoftwareCmd(FunctionalState NewState)
 809                     ; 188 {
 810                     	switch	.text
 811  008e               _SPI_NSSInternalSoftwareCmd:
 815                     ; 190   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 817                     ; 192   if (NewState != DISABLE)
 819  008e 4d            	tnz	a
 820  008f 2706          	jreq	L163
 821                     ; 194     SPI->CR2 |= SPI_CR2_SSI; /* Set NSS pin internally by software*/
 823  0091 72105201      	bset	20993,#0
 825  0095 2004          	jra	L363
 826  0097               L163:
 827                     ; 198     SPI->CR2 &= (uint8_t)(~SPI_CR2_SSI); /* Reset NSS pin internally by software*/
 829  0097 72115201      	bres	20993,#0
 830  009b               L363:
 831                     ; 200 }
 834  009b 81            	ret
 857                     ; 207 void SPI_TransmitCRC(void)
 857                     ; 208 {
 858                     	switch	.text
 859  009c               _SPI_TransmitCRC:
 863                     ; 209   SPI->CR2 |= SPI_CR2_CRCNEXT; /* Enable the CRC transmission*/
 865  009c 72185201      	bset	20993,#4
 866                     ; 210 }
 869  00a0 81            	ret
 905                     ; 218 void SPI_CalculateCRCCmd(FunctionalState NewState)
 905                     ; 219 {
 906                     	switch	.text
 907  00a1               _SPI_CalculateCRCCmd:
 911                     ; 221   assert_param(IS_FUNCTIONALSTATE_OK(NewState));
 913                     ; 223   if (NewState != DISABLE)
 915  00a1 4d            	tnz	a
 916  00a2 2706          	jreq	L314
 917                     ; 225     SPI->CR2 |= SPI_CR2_CRCEN; /* Enable the CRC calculation*/
 919  00a4 721a5201      	bset	20993,#5
 921  00a8 2004          	jra	L514
 922  00aa               L314:
 923                     ; 229     SPI->CR2 &= (uint8_t)(~SPI_CR2_CRCEN); /* Disable the CRC calculation*/
 925  00aa 721b5201      	bres	20993,#5
 926  00ae               L514:
 927                     ; 231 }
 930  00ae 81            	ret
 994                     ; 238 uint8_t SPI_GetCRC(SPI_CRC_TypeDef SPI_CRC)
 994                     ; 239 {
 995                     	switch	.text
 996  00af               _SPI_GetCRC:
 998  00af 88            	push	a
 999       00000001      OFST:	set	1
1002                     ; 240   uint8_t crcreg = 0;
1004                     ; 243   assert_param(IS_SPI_CRC_OK(SPI_CRC));
1006                     ; 245   if (SPI_CRC != SPI_CRC_RX)
1008  00b0 4d            	tnz	a
1009  00b1 2707          	jreq	L154
1010                     ; 247     crcreg = SPI->TXCRCR;  /* Get the Tx CRC register*/
1012  00b3 c65207        	ld	a,20999
1013  00b6 6b01          	ld	(OFST+0,sp),a
1015  00b8 2005          	jra	L354
1016  00ba               L154:
1017                     ; 251     crcreg = SPI->RXCRCR; /* Get the Rx CRC register*/
1019  00ba c65206        	ld	a,20998
1020  00bd 6b01          	ld	(OFST+0,sp),a
1021  00bf               L354:
1022                     ; 255   return crcreg;
1024  00bf 7b01          	ld	a,(OFST+0,sp)
1027  00c1 5b01          	addw	sp,#1
1028  00c3 81            	ret
1053                     ; 263 void SPI_ResetCRC(void)
1053                     ; 264 {
1054                     	switch	.text
1055  00c4               _SPI_ResetCRC:
1059                     ; 267   SPI_CalculateCRCCmd(ENABLE);
1061  00c4 a601          	ld	a,#1
1062  00c6 add9          	call	_SPI_CalculateCRCCmd
1064                     ; 270   SPI_Cmd(ENABLE);
1066  00c8 a601          	ld	a,#1
1067  00ca ad80          	call	_SPI_Cmd
1069                     ; 271 }
1072  00cc 81            	ret
1096                     ; 278 uint8_t SPI_GetCRCPolynomial(void)
1096                     ; 279 {
1097                     	switch	.text
1098  00cd               _SPI_GetCRCPolynomial:
1102                     ; 280   return SPI->CRCPR; /* Return the CRC polynomial register */
1104  00cd c65205        	ld	a,20997
1107  00d0 81            	ret
1163                     ; 288 void SPI_BiDirectionalLineConfig(SPI_Direction_TypeDef SPI_Direction)
1163                     ; 289 {
1164                     	switch	.text
1165  00d1               _SPI_BiDirectionalLineConfig:
1169                     ; 291   assert_param(IS_SPI_DIRECTION_OK(SPI_Direction));
1171                     ; 293   if (SPI_Direction != SPI_DIRECTION_RX)
1173  00d1 4d            	tnz	a
1174  00d2 2706          	jreq	L325
1175                     ; 295     SPI->CR2 |= SPI_CR2_BDOE; /* Set the Tx only mode*/
1177  00d4 721c5201      	bset	20993,#6
1179  00d8 2004          	jra	L525
1180  00da               L325:
1181                     ; 299     SPI->CR2 &= (uint8_t)(~SPI_CR2_BDOE); /* Set the Rx only mode*/
1183  00da 721d5201      	bres	20993,#6
1184  00de               L525:
1185                     ; 301 }
1188  00de 81            	ret
1309                     ; 311 FlagStatus SPI_GetFlagStatus(SPI_Flag_TypeDef SPI_FLAG)
1309                     ; 312 {
1310                     	switch	.text
1311  00df               _SPI_GetFlagStatus:
1313  00df 88            	push	a
1314       00000001      OFST:	set	1
1317                     ; 313   FlagStatus status = RESET;
1319                     ; 315   assert_param(IS_SPI_FLAGS_OK(SPI_FLAG));
1321                     ; 318   if ((SPI->SR & (uint8_t)SPI_FLAG) != (uint8_t)RESET)
1323  00e0 c45203        	and	a,20995
1324  00e3 2706          	jreq	L306
1325                     ; 320     status = SET; /* SPI_FLAG is set */
1327  00e5 a601          	ld	a,#1
1328  00e7 6b01          	ld	(OFST+0,sp),a
1330  00e9 2002          	jra	L506
1331  00eb               L306:
1332                     ; 324     status = RESET; /* SPI_FLAG is reset*/
1334  00eb 0f01          	clr	(OFST+0,sp)
1335  00ed               L506:
1336                     ; 328   return status;
1338  00ed 7b01          	ld	a,(OFST+0,sp)
1341  00ef 5b01          	addw	sp,#1
1342  00f1 81            	ret
1377                     ; 346 void SPI_ClearFlag(SPI_Flag_TypeDef SPI_FLAG)
1377                     ; 347 {
1378                     	switch	.text
1379  00f2               _SPI_ClearFlag:
1383                     ; 348   assert_param(IS_SPI_CLEAR_FLAGS_OK(SPI_FLAG));
1385                     ; 350   SPI->SR = (uint8_t)(~SPI_FLAG);
1387  00f2 43            	cpl	a
1388  00f3 c75203        	ld	20995,a
1389                     ; 351 }
1392  00f6 81            	ret
1474                     ; 366 ITStatus SPI_GetITStatus(SPI_IT_TypeDef SPI_IT)
1474                     ; 367 {
1475                     	switch	.text
1476  00f7               _SPI_GetITStatus:
1478  00f7 88            	push	a
1479  00f8 89            	pushw	x
1480       00000002      OFST:	set	2
1483                     ; 368   ITStatus pendingbitstatus = RESET;
1485                     ; 369   uint8_t itpos = 0;
1487                     ; 370   uint8_t itmask1 = 0;
1489                     ; 371   uint8_t itmask2 = 0;
1491                     ; 372   uint8_t enablestatus = 0;
1493                     ; 373   assert_param(IS_SPI_GET_IT_OK(SPI_IT));
1495                     ; 375   itpos = (uint8_t)((uint8_t)1 << ((uint8_t)SPI_IT & (uint8_t)0x0F));
1497  00f9 a40f          	and	a,#15
1498  00fb 5f            	clrw	x
1499  00fc 97            	ld	xl,a
1500  00fd a601          	ld	a,#1
1501  00ff 5d            	tnzw	x
1502  0100 2704          	jreq	L05
1503  0102               L25:
1504  0102 48            	sll	a
1505  0103 5a            	decw	x
1506  0104 26fc          	jrne	L25
1507  0106               L05:
1508  0106 6b01          	ld	(OFST-1,sp),a
1509                     ; 378   itmask1 = (uint8_t)((uint8_t)SPI_IT >> (uint8_t)4);
1511  0108 7b03          	ld	a,(OFST+1,sp)
1512  010a 4e            	swap	a
1513  010b a40f          	and	a,#15
1514  010d 6b02          	ld	(OFST+0,sp),a
1515                     ; 380   itmask2 = (uint8_t)((uint8_t)1 << itmask1);
1517  010f 7b02          	ld	a,(OFST+0,sp)
1518  0111 5f            	clrw	x
1519  0112 97            	ld	xl,a
1520  0113 a601          	ld	a,#1
1521  0115 5d            	tnzw	x
1522  0116 2704          	jreq	L45
1523  0118               L65:
1524  0118 48            	sll	a
1525  0119 5a            	decw	x
1526  011a 26fc          	jrne	L65
1527  011c               L45:
1528  011c 6b02          	ld	(OFST+0,sp),a
1529                     ; 382   enablestatus = (uint8_t)((uint8_t)SPI->SR & itmask2);
1531  011e c65203        	ld	a,20995
1532  0121 1402          	and	a,(OFST+0,sp)
1533  0123 6b02          	ld	(OFST+0,sp),a
1534                     ; 384   if (((SPI->ICR & itpos) != RESET) && enablestatus)
1536  0125 c65202        	ld	a,20994
1537  0128 1501          	bcp	a,(OFST-1,sp)
1538  012a 270a          	jreq	L766
1540  012c 0d02          	tnz	(OFST+0,sp)
1541  012e 2706          	jreq	L766
1542                     ; 387     pendingbitstatus = SET;
1544  0130 a601          	ld	a,#1
1545  0132 6b02          	ld	(OFST+0,sp),a
1547  0134 2002          	jra	L176
1548  0136               L766:
1549                     ; 392     pendingbitstatus = RESET;
1551  0136 0f02          	clr	(OFST+0,sp)
1552  0138               L176:
1553                     ; 395   return  pendingbitstatus;
1555  0138 7b02          	ld	a,(OFST+0,sp)
1558  013a 5b03          	addw	sp,#3
1559  013c 81            	ret
1604                     ; 412 void SPI_ClearITPendingBit(SPI_IT_TypeDef SPI_IT)
1604                     ; 413 {
1605                     	switch	.text
1606  013d               _SPI_ClearITPendingBit:
1608  013d 88            	push	a
1609       00000001      OFST:	set	1
1612                     ; 414   uint8_t itpos = 0;
1614                     ; 415   assert_param(IS_SPI_CLEAR_IT_OK(SPI_IT));
1616                     ; 420   itpos = (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)(SPI_IT & (uint8_t)0xF0) >> 4));
1618  013e a4f0          	and	a,#240
1619  0140 4e            	swap	a
1620  0141 a40f          	and	a,#15
1621  0143 5f            	clrw	x
1622  0144 97            	ld	xl,a
1623  0145 a601          	ld	a,#1
1624  0147 5d            	tnzw	x
1625  0148 2704          	jreq	L26
1626  014a               L46:
1627  014a 48            	sll	a
1628  014b 5a            	decw	x
1629  014c 26fc          	jrne	L46
1630  014e               L26:
1631  014e 6b01          	ld	(OFST+0,sp),a
1632                     ; 422   SPI->SR = (uint8_t)(~itpos);
1634  0150 7b01          	ld	a,(OFST+0,sp)
1635  0152 43            	cpl	a
1636  0153 c75203        	ld	20995,a
1637                     ; 424 }
1640  0156 84            	pop	a
1641  0157 81            	ret
1654                     	xdef	_SPI_ClearITPendingBit
1655                     	xdef	_SPI_GetITStatus
1656                     	xdef	_SPI_ClearFlag
1657                     	xdef	_SPI_GetFlagStatus
1658                     	xdef	_SPI_BiDirectionalLineConfig
1659                     	xdef	_SPI_GetCRCPolynomial
1660                     	xdef	_SPI_ResetCRC
1661                     	xdef	_SPI_GetCRC
1662                     	xdef	_SPI_CalculateCRCCmd
1663                     	xdef	_SPI_TransmitCRC
1664                     	xdef	_SPI_NSSInternalSoftwareCmd
1665                     	xdef	_SPI_ReceiveData
1666                     	xdef	_SPI_SendData
1667                     	xdef	_SPI_ITConfig
1668                     	xdef	_SPI_Cmd
1669                     	xdef	_SPI_Init
1670                     	xdef	_SPI_DeInit
1689                     	end
