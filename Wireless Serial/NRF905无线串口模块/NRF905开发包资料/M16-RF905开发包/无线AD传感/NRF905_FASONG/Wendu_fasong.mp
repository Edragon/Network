NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   002D =     45. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0081  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0082   0306 =    774. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0041  __start
       0041  __text_start
       0061  _exit
       0062  _delay
       0078  _Spi_initial
       007B  _SpiReadSpiWrite
       0080  _system_Init
       0089  _Config905
       00A0  _TxPacket
       00D2  _SetTxMode
       00D8  _TX
       00DB  _GetADResult
       00F1  _GetBaiwei
       00FC  _GetShiwei
       010F  _GetGewei
       011A  _dis_zhuye
       014F  _main
       018D  mod8u
       018F  div8u
       0190  xdiv8u
       01A5  push_gset5
       01A7  push_gset4
       01A9  push_gset3
       01AB  push_gset2
       01AD  push_gset1
       01B0  pop_gset1
       01B1  pop
       01C4  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   002D =     45. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _table
       0060  __data_start
       006A  _seg
       0074  _seg1
       007E  _TxAddress
       0082  _RFConf
       008D  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   008D   0009 =      9. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       008D  _TxRxBuf
       008D  __bss_start
       0091  _AD_data
       0095  _AD_num
       0096  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
Wendu_fasong.o	[ Wendu_fasong.c ]
<library>	[ div8u.s, gpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

