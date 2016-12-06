NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0019 =     25. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       006D  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   006E   0296 =    662. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0037  __text_start
       0037  __start
       0057  _exit
       0058  _Delay
       006E  _Spi_initial
       0071  _SpiReadSpiWrite
       0076  _system_Init
       007F  _Config905
       0096  _TxPacket
       00C6  _SetTxMode
       00CC  _SetRxMode
       00D2  _RxPacket
       00F1  _RX
       0118  _main
       0178  push_xgset300C
       017D  pop_xgset300C
       0182  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0019 =     25. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _TxAddress
       0064  _seg
       006E  _RFConf
       0079  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0079   0005 =      5. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0079  __bss_start
       0079  _tf
       007A  _TxRxBuf
       007E  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
jifeng_jieshou.o	[ jifeng_jieshou.c ]
<library>	[ gpushx.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512

