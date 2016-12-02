NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0004   0023 =     35. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0004  __idata_start
       0027  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0028   027C =    636. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0014  __start
       0014  __text_start
       0033  _exit
       0034  _Delay
       004B  _Spi_initial
       004E  _SpiReadSpiWrite
       0053  _system_Init
       005C  _Config905
       0073  _SetRxMode
       0079  _CheckDR
       007F  _RxPacket
       009E  _RX
       00A7  _dis_zhuye
       00DC  _StartUART
       00E7  _R_S_Byte
       00E9  _main
       0152  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0023 =     35. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _TxAddress
       0064  _seg
       006E  _seg1
       0078  _RFConf
       0083  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0083   0010 =     16. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0083  _temp
       0083  __bss_start
       008F  _TxRxBuffer
       0093  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0002 =      2. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtAVR.o	[ crtavr.s ]
Wendu_jieshou.o	[ Wendu_jieshou.c ]
<library>	

User Global Definitions

ram_end = 0x25f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x4
data = 0x60
eeprom:0.512

