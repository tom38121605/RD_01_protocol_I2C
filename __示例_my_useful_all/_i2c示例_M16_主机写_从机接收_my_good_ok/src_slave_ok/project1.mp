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
                            text   006E   02CE =    718. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0037  __start
       0037  __text_start
       0057  _exit
       0058  _twi_slave_init
       0061  _twi_isr
       0117  _UART_Init
       011E  _UART_PutChar
       0122  _UART_Puts
       0131  _UART_PutBytes
       0141  _main
       014E  pop_gset3
       0151  push_gset5
       0153  push_gset4
       0155  push_gset3
       0157  push_gset2
       0159  push_gset1
       015C  pop_gset1
       015D  pop
       0170  push_lset
       0187  pop_lset
       019E  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0019 =     25. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _RX_data
       006C  _RX_data2
       0078  _main_tmp
       0079  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0048 =     72. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

d:\ICC\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
<library>	[ gpop3.s, gpush.s, lpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

