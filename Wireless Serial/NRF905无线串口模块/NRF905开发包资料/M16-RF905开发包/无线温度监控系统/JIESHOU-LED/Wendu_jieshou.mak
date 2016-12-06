CC = iccavr
CFLAGS =  -e -D__ICC_VERSION="7.07"  -l -g -Wf-intenum -Wa-W 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -Wl-W -bfunc_lit:0x4.0x2000 -dram_end:0x25f -bdata:0x60.0x25f -dhwstk_size:16 -beeprom:0.512 -fihx_coff -S2
FILES = Wendu_jieshou.o 

WENDU_JIESHOU:	$(FILES)
	$(CC) -o WENDU_JIESHOU $(LFLAGS) @WENDU_JIESHOU.lk  
Wendu_jieshou.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
Wendu_jieshou.o:	F:\JASK\无线资料集锦\开发备份\JASK系列评估板0906\JASK2001系列案例参考代码\M16-RF905开发包\无线温度监控系统\JIESHOU-LED\Wendu_jieshou.c
	$(CC) -c $(CFLAGS) F:\JASK\无线资料集锦\开发备份\JASK系列评估板0906\JASK2001系列案例参考代码\M16-RF905开发包\无线温度监控系统\JIESHOU-LED\Wendu_jieshou.c
