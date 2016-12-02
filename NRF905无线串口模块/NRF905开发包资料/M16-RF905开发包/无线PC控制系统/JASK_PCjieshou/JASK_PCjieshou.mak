CC = iccavr
CFLAGS =  -e -D__ICC_VERSION="7.00" -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -ucrtatmega.o -bfunc_lit:0x54.0x1000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = JASK_PCjieshou.o 

JASK_PCjieshou:	$(FILES)
	$(CC) -o JASK_PCjieshou $(LFLAGS) @JASK_PCjieshou.lk   -lcatmega
JASK_PCjieshou.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
JASK_PCjieshou.o:	C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
	$(CC) -c $(CFLAGS) C:\DOCUME~1\Administrator\桌面\JASK2001软件开发包\M16-NRF905开发包\无线PC控制系统\JASK_PCjieshou\JASK_PCjieshou.c
