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
                            text   0074   02A4 =    676. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       003A  __text_start
       003A  __start
       005A  _exit
       005B  _i2c_StartIC
       0066  _i2c_StopIC
       0072  _i2c_MAck
       007A  _i2c_MNAck
       0082  _i2c_WaitAck
       009A  _i2c_WriteByte
       00B0  _i2c_ReadByte
       00C7  _main
       010D  _Delay_1us
       010F  _Delay_nus
       011E  _Delay_nus_Count
       0125  _Delay_1ms_Preci
       012E  _Delay_nms
       013D  _UART_Init
       0144  _UART_PutChar
       0148  _UART_Puts
       0157  _UART_PutBytes
       0167  pop_gset2
       016A  pop_gset3
       016D  push_gset5
       016F  push_gset4
       0171  push_gset3
       0173  push_gset2
       0175  push_gset1
       0178  pop_gset1
       0179  pop
       018C  __text_end

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

