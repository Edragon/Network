NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   002F =     47. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0083  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0084   0190 =    400. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0042  __text_start
       0042  __start
       0062  _exit
       0063  _Delay
       0079  _Spi_initial
       007C  _SpiReadSpiWrite
       0081  _system_Init
       008A  _Config905
       00A1  _TxPacket
       00D3  _SetTxMode
       00D9  _TX
       00DC  _main
       00EB  push_gset5
       00ED  push_gset4
       00EF  push_gset3
       00F1  push_gset2
       00F3  push_gset1
       00F6  pop_gset1
       00F7  pop
       010A  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   002F =     47. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _TxRxBuf
       0080  _TxAddress
       0084  _RFConf
       008F  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
jfp_fasong.o	[ jfp_fasong.c ]
<library>	[ gpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

