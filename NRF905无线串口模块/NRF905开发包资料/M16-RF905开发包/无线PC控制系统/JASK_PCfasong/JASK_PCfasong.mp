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
                            text   006E   02EA =    746. bytes (rel,con,rom)

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
       00C7  _SetTxMode
       00CD  _uart0_init
       00DA  _uart0_rx_isr
       00E5  _LCD_Delay
       00F1  _main
       018A  pop_gset2
       018D  push_gset5
       018F  push_gset4
       0191  push_gset3
       0193  push_gset2
       0195  push_gset1
       0198  pop_gset1
       0199  pop
       01AC  __text_end

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
                             bss   0079   000A =     10. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0079  __bss_start
       0079  _TxRxBuf
       007D  _TxBuf
       0081  _tf
       0082  _KEY0
       0083  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0030 =     48. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
JASK_PCfasong.o	[ JASK_PCfasong.C ]
<library>	[ gpop2.s, gpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

