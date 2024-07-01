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
                            text   0074   034A =    842. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       003A  __text_start
       003A  __start
       005A  _exit
       005B  _Int0_Init
       0066  _ISR_Int0
       0073  _Int0_DoWithInt
       007E  _twi_master_init
       0087  _i2c_start
       008D  _i2c_stop
       0090  _i2c_MAck
       009B  _i2c_MNAck
       00AC  _main
       0103  _i2c_maste_transt
       011D  _i2c_write_addr
       012F  _i2c_write_data
       0139  _i2c_read
       0144  _i2c_read2
       014F  _i2c_maste_read
       0160  _Delay_1us
       0162  _Delay_nus
       0171  _Delay_nus_Count
       0178  _Delay_1ms_Preci
       0181  _Delay_nms
       0190  _UART_Init
       0197  _UART_PutChar
       019B  _UART_Puts
       01AA  _UART_PutBytes
       01BA  pop_gset2
       01BD  pop_gset3
       01C0  push_gset5
       01C2  push_gset4
       01C4  push_gset3
       01C6  push_gset2
       01C8  push_gset1
       01CB  pop_gset1
       01CC  pop
       01DF  __text_end

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

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   007F   0001 =      1. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       007F  _flg_Int0_In
       007F  __bss_start
       0080  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0008 =      8. bytes (abs,ovr,rom)

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

