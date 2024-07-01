NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   001F =     31. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0073  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0074   02E2 =    738. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       003A  __text_start
       003A  __start
       005A  _exit
       005B  _twi_master_init
       0064  _i2c_start
       006A  _i2c_stop
       006D  _i2c_MAck
       0078  _i2c_MNAck
       0089  _main
       00CF  _i2c_maste_transt
       00E9  _i2c_write_addr
       00FB  _i2c_write_data
       0105  _i2c_read
       0110  _i2c_read2
       011B  _i2c_maste_read
       012C  _Delay_1us
       012E  _Delay_nus
       013D  _Delay_nus_Count
       0144  _Delay_1ms_Preci
       014D  _Delay_nms
       015C  _UART_Init
       0163  _UART_PutChar
       0167  _UART_Puts
       0176  _UART_PutBytes
       0186  pop_gset2
       0189  pop_gset3
       018C  push_gset5
       018E  push_gset4
       0190  push_gset3
       0192  push_gset2
       0194  push_gset1
       0197  pop_gset1
       0198  pop
       01AB  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   001F =     31. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _RX_data
       006C  _RX_data2
       0078  _tmp1
       0079  _tmp2
       007A  _tmp3
       007B  _tmp4
       007C  _tmp5
       007D  _tmp6
       007E  _tmp7
       007F  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0004 =      4. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

d:\ICC\lib\crtatmega.o	[ crtatmega.s ]
main.o	[ main.c ]
<library>	[ gpop2.s, gpop3.s, gpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x10

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:1.512

