NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0054   0011 =     17. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __lit_start
       0065  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0065   0025 =     37. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0065  __idata_start
       008A  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   008A   0712 =   1810. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0045  __start
       0045  __text_start
       0065  _exit
       0066  _UART_Init
       006D  _UART_Receive
       00A4  _UART_PutChar
       00A8  _UART_Puts
       00B7  _UART_PutBytes
       00C7  _DoWithUart
       00D7  _Delay_1us
       00D9  _Delay_nus
       00E8  _Delay_nus_Count
       00EF  _Delay_1ms_Preci
       00F8  _Delay_nms
       0107  _MakeSum_Int8_EX
       0121  _ULong2Str_16
       020C  _ReadData
       033B  _main
       0346  _memcpy
       0354  push_arg4
       0356  push_arg2
       0359  pop_gset3
       035C  push_gset5
       035E  push_gset4
       0360  push_gset3
       0362  push_gset2
       0364  push_gset1
       0367  pop_gset1
       0368  pop
       037B  push_lset
       0392  pop_lset
       03A9  lsr32
       03B5  asgncblk
       03CE  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0025 =     37. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _RX_data
       006C  _RX_data2
       0078  _flg_Received
       0085  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0085   0003 =      3. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0085  _flg_datain
       0085  __bss_start
       0086  _iNum
       0088  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0030 =     48. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

d:\ICC\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
<library>	[ memcpy.s, asave.s, gpop3.s, gpush.s, lpush.s, lsr32.s, pmstruct.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

