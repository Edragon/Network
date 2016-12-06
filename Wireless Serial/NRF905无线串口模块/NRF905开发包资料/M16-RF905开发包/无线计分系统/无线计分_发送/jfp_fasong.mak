CC = iccavr
CFLAGS =  -IC:\iccv7avr\include -e -D__ICC_VERSION="7.00" -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LC:\iccv7avr\lib -g -ucrtatmega.o -bfunc_lit:0x54.0x1000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = jfp_fasong.o 

jfp_fasong:	$(FILES)
	$(CC) -o jfp_fasong $(LFLAGS) @jfp_fasong.lk   -lcatmega
jfp_fasong.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
jfp_fasong.o:	C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
	$(CC) -c $(CFLAGS) C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线计分系统\NRF905_发送\jfp_fasong.c
