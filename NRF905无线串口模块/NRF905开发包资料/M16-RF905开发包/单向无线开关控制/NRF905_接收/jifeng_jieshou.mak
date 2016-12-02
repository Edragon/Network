CC = iccavr
CFLAGS =  -e -D__ICC_VERSION="7.07" -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:0.512 -fihx_coff -S2
FILES = jifeng_jieshou.o 

JIFENG_JIESHOU:	$(FILES)
	$(CC) -o JIFENG_JIESHOU $(LFLAGS) @JIFENG_JIESHOU.lk   -lcatmega
jifeng_jieshou.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
jifeng_jieshou.o:	F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
	$(CC) -c $(CFLAGS) F:\JASK\无线资料集锦\开发备份\JASK2001开发包0905\M16-NRF905开发包\单向无线开关控制\NRF905_接收\jifeng_jieshou.c
