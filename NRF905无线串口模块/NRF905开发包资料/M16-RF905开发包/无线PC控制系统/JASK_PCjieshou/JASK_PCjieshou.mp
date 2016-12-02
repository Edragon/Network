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
                            text   006E   03CC =    972. bytes (rel,con,rom)

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
       00C8  _SetTxMode
       00CE  _SetRxMode
       00D4  _TX
       00D7  _CheckDR
       00DD  _RxPacket
       00FC  _RX
       0102  _dis_zhuye
       0152  _main
       01C4  mod16s
       01C8  div16s
       01E2  mod16u
       01E4  div16u
       01E5  xdiv16u
       01FE  push_gset5
       0200  push_gset4
       0202  push_gset3
       0204  push_gset2
       0206  push_gset1
       0209  pop_gset1
       020A  pop
       021D  __text_end

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
                             bss   0079   0006 =      6. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0079  _count2
       0079  __bss_start
       007A  _count1
       007B  _TxRxBuffer
       007F  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
JASK_PCjieshou.o	[ JASK_PCjieshou.c ]
<library>	[ div16s.s, div16u.s, gpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

