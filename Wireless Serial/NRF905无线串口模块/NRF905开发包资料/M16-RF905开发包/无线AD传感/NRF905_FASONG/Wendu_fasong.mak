CC = iccavr
CFLAGS =  -e -D__ICC_VERSION="7.00" -DATMEGA -DATMega16  -l -g -Wf-intenum -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -ucrtatmega.o -bfunc_lit:0x54.0x1000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = Wendu_fasong.o 

Wendu_fasong:	$(FILES)
	$(CC) -o Wendu_fasong $(LFLAGS) @Wendu_fasong.lk   -lcatmega
Wendu_fasong.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
Wendu_fasong.o:	C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线AD传感\FASONG\Wendu_fasong.c
	$(CC) -c $(CFLAGS) C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线AD传感\FASONG\Wendu_fasong.c
