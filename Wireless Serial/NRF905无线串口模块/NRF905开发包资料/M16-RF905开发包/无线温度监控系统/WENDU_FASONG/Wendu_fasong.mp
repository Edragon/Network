NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0054   0020 =     32. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __func_lit_start
       0074  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0074   0025 =     37. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0074  __idata_start
       0099  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   009A   0478 =   1144. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       004D  __text_start
       004D  __start
       006D  _exit
       006E  _delay
       0084  _Spi_initial
       0087  _SpiReadSpiWrite
       008C  _system_Init
       0095  _Config905
       00AC  _TxPacket
       00DE  _SetTxMode
       00E4  _TX
       00E7  _DS1820_delay
       00EF  _Init_DS18B20
       0107  _ReadOneChar
       0120  _WriteOneChar
       013B  _ReadTemperature
       014C  _work_temp
       01F4  _dis_zhuye
       0229  _main
       023F  mod8u
       0241  div8u
       0242  xdiv8u
       0257  empy16s
       0267  pop_gset2
       026A  push_gset5
       026C  push_gset4
       026E  push_gset3
       0270  push_gset2
       0272  push_gset1
       0275  pop_gset1
       0276  pop
       0289  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0025 =     37. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _temp_data
       0060  __data_start
       0062  _seg
       006C  _seg1
       0076  _TxAddress
       007A  _RFConf
       0085  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0085   000B =     11. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0085  __bss_start
       0085  _TxRxBuf
       0089  _dispaly
       0090  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
Wendu_fasong.o	[ Wendu_fasong.c ]
<library>	[ div8u.s, emul16s.s, gpop2.s, gpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

