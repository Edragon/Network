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
                            text   0078   0370 =    880. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       003C  __text_start
       003C  __start
       005C  _exit
       005D  _Delay
       0073  _Spi_initial
       0076  _SpiReadSpiWrite
       007B  _system_Init
       0084  _Config905
       009B  _TxPacket
       00CD  _SetTxMode
       00D3  _SetRxMode
       00D9  _TX
       00DC  _CheckDR
       00E2  _RxPacket
       0101  _RX
       0107  _StartUART
       0112  _R_S_Byte
       0114  _dis_zhuye
       0164  _main
       019B  mod16s
       019F  div16s
       01B9  mod16u
       01BB  div16u
       01BC  xdiv16u
       01D5  push_gset5
       01D7  push_gset4
       01D9  push_gset3
       01DB  push_gset2
       01DD  push_gset1
       01E0  pop_gset1
       01E1  pop
       01F4  __text_end

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
                             bss   0083   0006 =      6. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0083  _count2
       0083  __bss_start
       0084  _count1
       0085  _TxRxBuffer
       0089  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
jifeng_jieshou.o	[ jifeng_jieshou.c ]
<library>	[ div16s.s, div16u.s, gpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

