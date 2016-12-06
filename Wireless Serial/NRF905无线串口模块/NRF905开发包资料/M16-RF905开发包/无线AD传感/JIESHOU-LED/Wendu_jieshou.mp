NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0023 =     35. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0077  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0078   01F0 =    496. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       003C  __start
       003C  __text_start
       005C  _exit
       005D  _Delay
       0073  _Spi_initial
       0076  _SpiReadSpiWrite
       007B  _system_Init
       0084  _Config905
       009B  _SetRxMode
       00A1  _CheckDR
       00A7  _RxPacket
       00C6  _RX
       00CF  _StartUART
       00DA  _R_S_Byte
       00DC  _dis_zhuye
       0111  _main
       0134  __text_end

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
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
Wendu_jieshou.o	[ Wendu_jieshou.c ]
<library>	

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512

