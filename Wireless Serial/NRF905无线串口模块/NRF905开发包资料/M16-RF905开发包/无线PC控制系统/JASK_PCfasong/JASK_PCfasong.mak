CC = iccavr
CFLAGS =  -e -D__ICC_VERSION="7.00" -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -ucrtatmega.o -bfunc_lit:0x54.0x1000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = JASK_PCfasong.o 

JASK_PCfasong:	$(FILES)
	$(CC) -o JASK_PCfasong $(LFLAGS) @JASK_PCfasong.lk   -lcatmega
JASK_PCfasong.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
JASK_PCfasong.o:	C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCfasong\JASK_PCfasong.C
	$(CC) -c $(CFLAGS) C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCfasong\JASK_PCfasong.C
