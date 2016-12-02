CC = iccavr
CFLAGS =  -e -D__ICC_VERSION="7.07" -DATMEGA -DATMega16  -l -g -Wf-intenum -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:0.512 -fihx_coff -S2
FILES = Wendu_jieshou.o 

WENDU_JIESHOU:	$(FILES)
	$(CC) -o WENDU_JIESHOU $(LFLAGS) @WENDU_JIESHOU.lk   -lcatmega
Wendu_jieshou.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
Wendu_jieshou.o:	F:\PROTELDXP\123\无线参考程序\开发板备份\JASK2001软件开发包\M16-NRF905开发包\无线AD传感\JIESHOU-LED\Wendu_jieshou.c
	$(CC) -c $(CFLAGS) F:\PROTELDXP\123\无线参考程序\开发板备份\JASK2001软件开发包\M16-NRF905开发包\无线AD传感\JIESHOU-LED\Wendu_jieshou.c
