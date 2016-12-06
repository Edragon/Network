CC = iccavr
CFLAGS =  -e -D__ICC_VERSION="7.07"  -l -g -Wf-intenum -Wa-W 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -g -Wl-W -bfunc_lit:0x4.0x2000 -dram_end:0x25f -bdata:0x60.0x25f -dhwstk_size:16 -beeprom:0.512 -fihx_coff -S2
FILES = Wendu_jieshou.o 

WENDU_JIESHOU:	$(FILES)
	$(CC) -o WENDU_JIESHOU $(LFLAGS) @WENDU_JIESHOU.lk  
Wendu_jieshou.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h
Wendu_jieshou.o:	F:\JASK\�������ϼ���\��������\JASKϵ��������0906\JASK2001ϵ�а����ο�����\M16-RF905������\�����¶ȼ��ϵͳ\JIESHOU-LED\Wendu_jieshou.c
	$(CC) -c $(CFLAGS) F:\JASK\�������ϼ���\��������\JASKϵ��������0906\JASK2001ϵ�а����ο�����\M16-RF905������\�����¶ȼ��ϵͳ\JIESHOU-LED\Wendu_jieshou.c
