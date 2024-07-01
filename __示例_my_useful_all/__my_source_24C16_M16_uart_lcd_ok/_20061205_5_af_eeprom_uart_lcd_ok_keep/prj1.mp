NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0054   0010 =     16. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __lit_start
       0064  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0064   0081 =    129. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0064  __idata_start
       00E5  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00E6   0A10 =   2576. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0073  __start
       0073  __text_start
       0093  _exit
       0094  _LCD_init
       00AB  _clearlcd
       00B2  _Send
       00C5  _LCD_write_cmd
       00D8  _SdData
       00EB  _DispSetCursor
       0115  _WriteTextScreen2
       0166  _LCD_set_xy
       0190  _LCD_write_str
       01D7  _delay_1us
       01D9  _delay_nus
       01E8  _delay_1ms
       01F2  _delay_nms
       0201  _txdpo
       020E  _wt24c
       0288  _rd24c
       02B2  _wt24c_fc
       02DB  _i2cstart
       02E1  _i2cwt
       02EB  _i2crd
       02F2  _i2cstop
       02F5  _byte2str
       0344  _UART_init
       034B  _putchar
       0358  _puts
       0369  _putbytes
       037C  _UART_rx
       03E0  _twi_init
       03E9  _main
       0497  push_arg4
       0499  push_arg2
       049C  mod8u
       049E  div8u
       049F  xdiv8u
       04B4  empy32s
       04B4  empy32u
       04E4  pop_gset2
       04E7  pop_gset3
       04EA  pop_gset4
       04ED  pop_gset5
       04F0  push_gset5
       04F2  push_gset4
       04F4  push_gset3
       04F6  push_gset2
       04F8  push_gset1
       04FB  pop_gset1
       04FC  pop
       050F  long_prolog
       051D  long_epilog
       0528  tstzero1
       052E  tstzero2
       0534  push_lset
       054B  pop_lset
       0562  asgncblk
       057B  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0081 =    129. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _RX_data
       00C4  _flg_start
       00C5  _flg_end
       00E1  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   00E1   00CC =    204. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       00E1  __bss_start
       00E2  _RX_counter
       00E4  _str
       00E6  _w_buf
       0126  _r_buf
       0166  _txd_buf
       01AC  _syserr
       01AD  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0030 =     48. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\ICC\lib\crtatmega.o	[ crtatmega.s ]
7920.o	[ _7920.c ]
delay.o	[ delay.c ]
Debug_com.o	[ Debug_com.C ]
24Cxx.o	[ _24Cxx.C ]
r_modstring.o	[ r_modstring.c ]
usart.o	[ usart.c ]
r_modbyte.o	[ r_modbyte.c ]
modpublic.o	[ modpublic.c ]
24CxxMain.o	[ _24CxxMain.c ]
<library>	[ asave.s, div8u.s, emul32.s, gpop2.s, gpop3.s, gpop4.s, gpop5.s, gpush.s, longutil.s, lpush.s, pmstruct.s ]


User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

