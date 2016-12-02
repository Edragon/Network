CC = iccavr
CFLAGS =  -IC:\iccv7avr\include -e -D__ICC_VERSION="7.07" -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LC:\iccv7avr\lib -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:0.512 -fihx_coff -S2
FILES = jfp_fasong.o 

JFP_FASONG:	$(FILES)
	$(CC) -o JFP_FASONG $(LFLAGS) @JFP_FASONG.lk   -lcatmega
jfp_fasong.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
jfp_fasong.o:	F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jfp_fasong.c
	$(CC) -c $(CFLAGS) F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jfp_fasong.c
