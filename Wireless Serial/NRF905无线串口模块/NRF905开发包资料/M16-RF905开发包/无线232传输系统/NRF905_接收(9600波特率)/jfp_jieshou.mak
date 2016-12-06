CC = iccavr
CFLAGS =  -IC:\iccv7avr\lib -e -D__ICC_VERSION="7.00" -DATMEGA -DATMega16  -l -g -Wa-IC:\iccv7avr\include -Wf-intenum -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -ucrtatmega.o -bfunc_lit:0x54.0x1000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = jfp_jieshou.o 

jfp_jieshou:	$(FILES)
	$(CC) -o jfp_jieshou $(LFLAGS) @jfp_jieshou.lk   -lcatmega
jfp_jieshou.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
jfp_jieshou.o:	C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
	$(CC) -c $(CFLAGS) C:\DOCUME~1\Administrator\����\JASK2001���������\M16-NRF905������\����232����ϵͳ\NRF905_����(9600������)\jfp_jieshou.c
