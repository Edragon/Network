CC = iccavr
CFLAGS =  -e -D__ICC_VERSION="7.07" -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:0.512 -fihx_coff -S2
FILES = jifeng_jieshou.o 

JIFENG_JIESHOU:	$(FILES)
	$(CC) -o JIFENG_JIESHOU $(LFLAGS) @JIFENG_JIESHOU.lk   -lcatmega
jifeng_jieshou.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
jifeng_jieshou.o:	F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
	$(CC) -c $(CFLAGS) F:\JASK\�������ϼ���\��������\JASK2001������0905\M16-NRF905������\�������߿��ؿ���\NRF905_����\jifeng_jieshou.c
