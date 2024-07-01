	.module main.c
	.area data(ram, con, rel)
_RX_data::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.blkb 11
	.area idata
	.word 0,0,0,0,0
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e RX_data _RX_data A[12:12]c
_RX_data2::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.blkb 11
	.area idata
	.word 0,0,0,0,0
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e RX_data2 _RX_data2 A[12:12]c
_tmp1::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e tmp1 _tmp1 c
_tmp2::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e tmp2 _tmp2 c
_tmp3::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e tmp3 _tmp3 c
_tmp4::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e tmp4 _tmp4 c
_tmp5::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e tmp5 _tmp5 c
_tmp6::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e tmp6 _tmp6 c
_tmp7::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source\main.c
	.dbsym e tmp7 _tmp7 c
	.area text(rom, con, rel)
	.dbfile E:\__test\source\main.c
	.dbfunc e i2c_StartIC _i2c_StartIC fV
	.even
_i2c_StartIC::
	.dbline -1
	.dbline 70
; //模拟IIC主机
; 
; 
; #include <iom16v.h>
; #include <macros.h>
; 
; #include <string.h>
; //#include "config.h"
; 
; 
; //----串口------
; #define  B9600  47	//波特率 7.3728MHz clock
; #define  B19200 23
; #define  B38400 11
; #define  B57600 7
; #define  BAUD B19200
; 
; #define RX_BUFFER_SIZE 12 
; 
; void UART_Init(void);               //串口初始化函数
; void UART_Receive(void);            //串口接收函数
; void UART_PutChar(unsigned char c); //串口输出字符
; void UART_Puts(unsigned char *s);   //串口输出字符串
; void UART_PutBytes(unsigned char *s, unsigned char ilen);  //串口输出字节
; 
; unsigned char RX_data[RX_BUFFER_SIZE]={0};   //串口接收缓冲区
; unsigned char RX_data2[RX_BUFFER_SIZE]={0};
; 
; 
; 
; 
; void Delay_1us(void);  //1us精确延时函数
; void Delay_nus(unsigned int n);  //nus延时函数, 10us以内为精确延时
; 
; void Delay_nus_Count(unsigned int n);     //精确nus延时函数，10us以上的精确延时
; //Delay_10us： Delay_nus_Count(11);   //7.3728M
; //Delay_20us： Delay_nus_Count(25);   //7.3728M
; //Delay_50us： Delay_nus_Count(60);   //7.3728M
; //Delay_100us： Delay_nus_Count(121);   //7.3728M
; //Delay_500us： Delay_nus_Count(613);   //7.3728M
; 
; 
; void Delay_1ms_Preci(void);  //1ms精确延时函数
; void Delay_nms(unsigned int n);  //nms精确延时函数
; 
; 
; //#define TW_MR_DATA_NACK 
; volatile unsigned char tmp1=0;
; volatile unsigned char tmp2=0;
; volatile unsigned char tmp3=0;
; volatile unsigned char tmp4=0;
; volatile unsigned char tmp5=0;
; volatile unsigned char tmp6=0;
; volatile unsigned char tmp7=0;
; 
; 
; #define VSCL 0
; #define VSDA 1
; 
; void i2c_StartIC(void);
; void i2c_StopIC(void);
; void i2c_MAck(void);
; void i2c_MNAck(void);
; unsigned char i2c_WaitAck(void);
; void i2c_WriteByte(unsigned char iByte);
; unsigned char  i2c_ReadByte(void);
; 
; 
; void i2c_StartIC(void)
; {
	.dbline 73
;    //output_high(VSDA);
;    //output_high(VSCL);
;    PORTC|=(1<<VSDA);
	sbi 0x15,1
	.dbline 74
;    PORTC|=(1<<VSCL);
	sbi 0x15,0
	.dbline 76
;    
;    Delay_nus(5);
	ldi R16,5
	ldi R17,0
	xcall _Delay_nus
	.dbline 79
; 
;    //output_low(VSDA);
;    PORTC&=~(1<<VSDA);
	cbi 0x15,1
	.dbline 81
;    
;    Delay_nus(4);
	ldi R16,4
	ldi R17,0
	xcall _Delay_nus
	.dbline 84
; 
;    //output_low(VSCL);
;    PORTC&=~(1<<VSCL);
	cbi 0x15,0
	.dbline -2
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_StopIC _i2c_StopIC fV
	.even
_i2c_StopIC::
	.dbline -1
	.dbline 88
; }
; 
; void i2c_StopIC(void)
; {
	.dbline 91
;    //output_low(VSDA);
;    //output_high(VSCL);
;    PORTC&=~(1<<VSDA);
	cbi 0x15,1
	.dbline 92
;    PORTC|=(1<<VSCL);
	sbi 0x15,0
	.dbline 94
; 
;    Delay_nus(4);
	ldi R16,4
	ldi R17,0
	xcall _Delay_nus
	.dbline 97
; 
;    //output_high(VSDA);
;    PORTC|=(1<<VSDA);
	sbi 0x15,1
	.dbline 99
; 
;    Delay_nus(5);
	ldi R16,5
	ldi R17,0
	xcall _Delay_nus
	.dbline 103
; 
;    //output_low(VSDA);
;    //output_low(VSCL);
;    PORTC&=~(1<<VSDA);   //--这句应可去掉
	cbi 0x15,1
	.dbline 104
;    PORTC&=~(1<<VSCL);
	cbi 0x15,0
	.dbline -2
L2:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_MAck _i2c_MAck fV
	.even
_i2c_MAck::
	.dbline -1
	.dbline 108
; }
; 
; void i2c_MAck(void)
; {
	.dbline 111
;    //output_low(VSDA);
;    //output_high(VSCL);
;    PORTC&=~(1<<VSDA);
	cbi 0x15,1
	.dbline 112
;    PORTC|=(1<<VSCL);
	sbi 0x15,0
	.dbline 114
;    
;    Delay_nus(4);
	ldi R16,4
	ldi R17,0
	xcall _Delay_nus
	.dbline 118
;    
;    //output_low(VSCL);
;    //output_high(VSDA);
;    PORTC&=~(1<<VSCL);
	cbi 0x15,0
	.dbline 119
;    PORTC|=(1<<VSDA);
	sbi 0x15,1
	.dbline -2
L3:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_MNAck _i2c_MNAck fV
	.even
_i2c_MNAck::
	.dbline -1
	.dbline 124
; }
; 
; 
; void i2c_MNAck(void)
; {
	.dbline 127
;    //output_high(VSDA);
;    //output_high(VSCL);
;    PORTC|=(1<<VSDA);
	sbi 0x15,1
	.dbline 128
;    PORTC|=(1<<VSCL);
	sbi 0x15,0
	.dbline 130
; 
;    Delay_nus(4);
	ldi R16,4
	ldi R17,0
	xcall _Delay_nus
	.dbline 134
; 
;    //output_low(VSCL);
;    //output_low(VSDA);
;    PORTC&=~(1<<VSDA);
	cbi 0x15,1
	.dbline 135
;    PORTC&=~(1<<VSCL);
	cbi 0x15,0
	.dbline -2
L4:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_WaitAck _i2c_WaitAck fc
;           iRet -> R20
;     iErrorTime -> R22
	.even
_i2c_WaitAck::
	xcall push_gset2
	.dbline -1
	.dbline 140
; }
; 
; 
; unsigned char i2c_WaitAck(void)
; {
	.dbline 141
;    unsigned char iErrorTime=255;
	ldi R22,255
	.dbline 145
;    unsigned char iRet;
; 
;    //output_high(VSDA);
;    PORTC|=(1<<VSDA);
	sbi 0x15,1
	.dbline 146
;    Delay_nus(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay_nus
	.dbline 148
;    //output_high(VSCL);
;    PORTC|=(1<<VSCL);
	sbi 0x15,0
	.dbline 150
;    
;    iRet=1;
	ldi R20,1
	xjmp L7
L6:
	.dbline 153
; 
;    while( PINC|=(1<<VSDA) )
;    {
	.dbline 154
;       iErrorTime--;
	dec R22
	.dbline 155
;       if(!iErrorTime)
	brne L9
	.dbline 156
;       {
	.dbline 158
;          //return 0;
;          iRet=0;
	clr R20
	.dbline 159
;       }
L9:
	.dbline 160
L7:
	.dbline 152
	in R24,0x13
	ori R24,2
	out 0x13,R24
	tst R24
	brne L6
	.dbline 163
;    }
; 
;    //output_low(VSCL);
;    PORTC&=~(1<<VSCL);
	cbi 0x15,0
	.dbline 166
; 
;    //output_high(VSDA);  //test
;    PORTC|=(1<<VSDA);
	sbi 0x15,1
	.dbline 169
;    
;    //return 1;
;    return iRet;
	mov R16,R20
	.dbline -2
L5:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r iRet 20 c
	.dbsym r iErrorTime 22 c
	.dbend
	.dbfunc e i2c_WriteByte _i2c_WriteByte fV
;              i -> R20
;          iByte -> R22
	.even
_i2c_WriteByte::
	xcall push_gset2
	mov R22,R16
	.dbline -1
	.dbline 175
; 
; }
; 
; 
; void i2c_WriteByte(unsigned char iByte)
; {
	.dbline 178
;    unsigned char  i;
; 
;    for (i=0; i<0x08; i++)
	clr R20
	xjmp L15
L12:
	.dbline 179
;    {
	.dbline 180
;       if(iByte & 0x80)
	sbrs R22,7
	rjmp L16
	.dbline 182
;          //output_high(VSDA);
;          PORTC|=(1<<VSDA);
	sbi 0x15,1
	xjmp L17
L16:
	.dbline 185
;       else
;          //output_low(VSDA);
;          PORTC&=~(1<<VSDA);
	cbi 0x15,1
L17:
	.dbline 188
	sbi 0x15,0
	.dbline 190
	ldi R16,4
	ldi R17,0
	xcall _Delay_nus
	.dbline 193
	cbi 0x15,0
	.dbline 196
	lsl R22
	.dbline 197
L13:
	.dbline 178
	inc R20
L15:
	.dbline 178
	cpi R20,8
	brlo L12
	.dbline -2
L11:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbsym r iByte 22 c
	.dbend
	.dbfunc e i2c_ReadByte _i2c_ReadByte fc
;          iByte -> R20
;              i -> R22
	.even
_i2c_ReadByte::
	xcall push_gset2
	.dbline -1
	.dbline 203
; 
;       //output_high(VSCL);
;       PORTC|=(1<<VSCL);
; 
;       Delay_nus(4);
; 
;       //output_low(VSCL);
;       PORTC&=~(1<<VSCL);
;       
; 
;       iByte <<= 0x01;
;    }
; 
; }
; 
; 
; unsigned char i2c_ReadByte(void)
; {
	.dbline 207
;    unsigned char   i;
;    unsigned char   iByte;
; 
;    for (i=0; i<0x08; i++)
	clr R22
	xjmp L22
L19:
	.dbline 208
;    {
	.dbline 209
;       iByte <<= 0x01;
	lsl R20
	.dbline 211
;       //output_high(VSCL);
;       PORTC|=(1<<VSCL);
	sbi 0x15,0
	.dbline 213
; 
;       if( PINC|=(1<<VSDA) )
	in R24,0x13
	ori R24,2
	out 0x13,R24
	tst R24
	breq L23
	.dbline 214
;          iByte |= 0x01;
	ori R20,1
L23:
	.dbline 216
	ldi R16,4
	ldi R17,0
	xcall _Delay_nus
	.dbline 219
	cbi 0x15,0
	.dbline 220
L20:
	.dbline 207
	inc R22
L22:
	.dbline 207
	cpi R22,8
	brlo L19
	.dbline 222
; 
;       Delay_nus(4);
; 
;       //output_low(VSCL);
;       PORTC&=~(1<<VSCL);
;    }
; 
;    return iByte;
	mov R16,R20
	.dbline -2
L18:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r iByte 20 c
	.dbsym r i 22 c
	.dbend
	.dbfunc e main _main fV
	.even
_main::
	.dbline -1
	.dbline 229
; 
; }
; 
; 
; 
; void main(void)
; {
	.dbline 231
; 
;    CLI();                                                                                                     
	cli
	.dbline 233
;    
;    UART_Init();
	xcall _UART_Init
	.dbline 237
;    
;    //DDRC&=~(1<<VSCL|1<<VSDA); //SDA,SCL设置为输入
;    //PORTC|=(1<<VSCL|1<<VSDA); //使能内部上拉电阻   
;    DDRC|=(1<<VSCL|1<<VSDA); //SDA,SCL设置为输入
	in R24,0x14
	ori R24,3
	out 0x14,R24
	.dbline 238
;    PORTC&=~(1<<VSCL|1<<VSDA); //使能内部上拉电阻   
	in R24,0x15
	andi R24,252
	out 0x15,R24
	.dbline 241
;    
;  
;    SEI();
	sei
	xjmp L27
L26:
	.dbline 247
	.dbline 267
	xcall _i2c_StartIC
	.dbline 268
	ldi R16,91
	xcall _i2c_WriteByte
	.dbline 272
	xcall _i2c_ReadByte
	sts _tmp1,R16
	.dbline 272
	xcall _i2c_MAck
	.dbline 273
	xcall _i2c_ReadByte
	sts _tmp2,R16
	.dbline 273
	xcall _i2c_MAck
	.dbline 274
	xcall _i2c_ReadByte
	sts _tmp3,R16
	.dbline 274
	xcall _i2c_MAck
	.dbline 275
	xcall _i2c_ReadByte
	sts _tmp4,R16
	.dbline 275
	xcall _i2c_MAck
	.dbline 276
	xcall _i2c_ReadByte
	sts _tmp5,R16
	.dbline 276
	xcall _i2c_MAck
	.dbline 277
	xcall _i2c_ReadByte
	sts _tmp6,R16
	.dbline 277
	xcall _i2c_MAck
	.dbline 278
	xcall _i2c_ReadByte
	sts _tmp7,R16
	.dbline 281
	xcall _i2c_StopIC
	.dbline 284
	lds R16,_tmp1
	xcall _UART_PutChar
	.dbline 285
	lds R16,_tmp2
	xcall _UART_PutChar
	.dbline 286
	lds R16,_tmp3
	xcall _UART_PutChar
	.dbline 287
	lds R16,_tmp4
	xcall _UART_PutChar
	.dbline 288
	lds R16,_tmp5
	xcall _UART_PutChar
	.dbline 289
	lds R16,_tmp6
	xcall _UART_PutChar
	.dbline 290
	lds R16,_tmp7
	xcall _UART_PutChar
	.dbline 292
	ldi R16,8
	ldi R17,0
	xcall _Delay_nms
	.dbline 293
	ldi R16,300
	ldi R17,1
	xcall _Delay_nus
	.dbline 294
L27:
	.dbline 246
	xjmp L26
X0:
	.dbline -2
L25:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Delay_1us _Delay_1us fV
	.even
_Delay_1us::
	.dbline -1
	.dbline 306
;    
;    
;    //return;
; 
;    while(1)
;    {   
; 
;       //--------- 从i2c读数据  -------------
;       
;       /*i2c_start();
;       if(i2c_write_addr(0x5A, 1)==TW_MR_SLA_ACK)  //发送地址成功并收到ACK
;       {     
;          tmp1=i2c_read();                          
;          tmp2=i2c_read();
;          tmp3=i2c_read();
;          tmp4=i2c_read();
;          tmp5=i2c_read();
;          tmp6=i2c_read();   
;          tmp7=i2c_read();         
;                      
;       }
;       i2c_stop();
;       */
; 
; 
;       i2c_StartIC(); 
;       i2c_WriteByte(0x5b);
;       
;       //if (i2c_WaitAck() ==1 )
;       //{
;          tmp1=i2c_ReadByte(); i2c_MAck();
;          tmp2=i2c_ReadByte(); i2c_MAck();
;          tmp3=i2c_ReadByte(); i2c_MAck();
;          tmp4=i2c_ReadByte(); i2c_MAck();
;          tmp5=i2c_ReadByte(); i2c_MAck();
;          tmp6=i2c_ReadByte(); i2c_MAck();
;          tmp7=i2c_ReadByte(); //i2c_MAck();
;       //}
;       
;       i2c_StopIC();
;       
;   
;          UART_PutChar(tmp1);      
;          UART_PutChar(tmp2);      
;          UART_PutChar(tmp3);      
;          UART_PutChar(tmp4);      
;          UART_PutChar(tmp5);      
;          UART_PutChar(tmp6);      
;          UART_PutChar(tmp7);      
;        
;       Delay_nms(8);
;       Delay_nus(300);
;    } 
; 
; }
; 
; 
; 
; /*-----------------------------------------------------------------------
; 延时函数
; 系统时钟：7.3728M
; -----------------------------------------------------------------------*/
; //1us精确延时函数
; void Delay_1us(void)     // 实际 8/7.3728＝1.085 us
; {
	.dbline 307
;    asm("nop");
	nop
	.dbline -2
L29:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Delay_nus _Delay_nus fV
;              n -> R20,R21
	.even
_Delay_nus::
	xcall push_gset1
	movw R20,R16
	.dbline -1
	.dbline 312
; }
; 
; //nus延时函数, 10us以内为精确延时
; void Delay_nus(unsigned int n)     
; {
	xjmp L32
L31:
	.dbline 314
	xcall _Delay_1us
L32:
	.dbline 313
;    while (n--)
	movw R2,R20
	subi R20,1
	sbci R21,0
	tst R2
	brne L31
	tst R3
	brne L31
X1:
	.dbline -2
L30:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r n 20 i
	.dbend
	.dbfunc e Delay_nus_Count _Delay_nus_Count fV
;              n -> R16,R17
	.even
_Delay_nus_Count::
	.dbline -1
	.dbline 319
;       Delay_1us();   
; }  
; 
; //精确nus延时函数，10us以上的精确延时
; void Delay_nus_Count(unsigned int n)   
; { 
	xjmp L36
L35:
	.dbline 327
	subi R16,1
	sbci R17,0
L36:
	.dbline 326
;    //Delay_10us： Delay_nus_Count(11);   //7.3728M
;    //Delay_20us： Delay_nus_Count(25);   //7.3728M
;    //Delay_50us： Delay_nus_Count(60);   //7.3728M
;    //Delay_100us： Delay_nus_Count(121);   //7.3728M
;    //Delay_500us： Delay_nus_Count(613);   //7.3728M
; 
;    while(n) 
	cpi R16,0
	cpc R16,R17
	brne L35
X2:
	.dbline -2
L34:
	.dbline 0 ; func end
	ret
	.dbsym r n 16 i
	.dbend
	.dbfunc e Delay_1ms_Preci _Delay_1ms_Preci fV
;              n -> R16,R17
	.even
_Delay_1ms_Preci::
	.dbline -1
	.dbline 332
;       n--;    
; }
; 
; //1ms精确延时函数
; void Delay_1ms_Preci(void)    //7.3728M             
; {
	.dbline 334
;    unsigned int n;
;    n=1225; 
	ldi R16,1225
	ldi R17,4
	xjmp L40
L39:
	.dbline 336
	subi R16,1
	sbci R17,0
L40:
	.dbline 335
;    while (n) 
	cpi R16,0
	cpc R16,R17
	brne L39
X3:
	.dbline -2
L38:
	.dbline 0 ; func end
	ret
	.dbsym r n 16 i
	.dbend
	.dbfunc e Delay_nms _Delay_nms fV
;              n -> R20,R21
	.even
_Delay_nms::
	xcall push_gset1
	movw R20,R16
	.dbline -1
	.dbline 341
;       n--;
; }
; 
; //nms精确延时函数
; void Delay_nms(unsigned int n)       
; {
	xjmp L44
L43:
	.dbline 343
	xcall _Delay_1ms_Preci
L44:
	.dbline 342
;    while(n--)
	movw R2,R20
	subi R20,1
	sbci R21,0
	tst R2
	brne L43
	tst R3
	brne L43
X4:
	.dbline -2
L42:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r n 20 i
	.dbend
	.dbfunc e UART_Init _UART_Init fV
	.even
_UART_Init::
	.dbline -1
	.dbline 348
;      Delay_1ms_Preci();
; }
; 
; //串口初始化函数
; void UART_Init(void)
; {
	.dbline 349
;    UCSRB = (1<<RXCIE)| (1<<RXEN) |(1<<TXEN);   //允许串口发送和接收，并响应接收完成中断
	ldi R24,152
	out 0xa,R24
	.dbline 350
;    UBRR = BAUD;
	ldi R24,23
	out 0x9,R24
	.dbline 351
;    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);   //8位数据＋1位stop位
	ldi R24,134
	out 0x20,R24
	.dbline -2
L46:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e UART_PutChar _UART_PutChar fV
;              c -> R16
	.even
_UART_PutChar::
	.dbline -1
	.dbline 356
; }
; 
; //串口输出字符
; void UART_PutChar(unsigned char c)  
; {
L48:
	.dbline 357
L49:
	.dbline 357
;    while (!(UCSRA&(1 << UDRE)));    //判断上次发送有没有完成
	sbis 0xb,5
	rjmp L48
	.dbline 358
;    UDR = c;
	out 0xc,R16
	.dbline -2
L47:
	.dbline 0 ; func end
	ret
	.dbsym r c 16 c
	.dbend
	.dbfunc e UART_Puts _UART_Puts fV
;              s -> R20,R21
	.even
_UART_Puts::
	xcall push_gset1
	movw R20,R16
	.dbline -1
	.dbline 363
; }
; 
; //串口输出字符串
; void UART_Puts(unsigned char *s)
; {
	xjmp L53
L52:
	.dbline 365
	.dbline 366
	movw R30,R20
	ld R16,Z+
	movw R20,R30
	xcall _UART_PutChar
	.dbline 367
L53:
	.dbline 364
;    while (*s)
	movw R30,R20
	ldd R2,z+0
	tst R2
	brne L52
	.dbline -2
L51:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r s 20 pc
	.dbend
	.dbfunc e UART_PutBytes _UART_PutBytes fV
;              i -> R20
;           ilen -> R22
;              s -> R10,R11
	.even
_UART_PutBytes::
	xcall push_gset3
	mov R22,R18
	movw R10,R16
	.dbline -1
	.dbline 372
;    {
;       UART_PutChar(*s++);
;    }
; }
; 
; //串口输出字节
; void UART_PutBytes(unsigned char *s, unsigned char ilen)
; {
	.dbline 375
; unsigned char i;
; 
;    for(i=0;i<ilen;i++)
	clr R20
	xjmp L59
L56:
	.dbline 376
	.dbline 377
	movw R30,R10
	ld R16,Z+
	movw R10,R30
	xcall _UART_PutChar
	.dbline 378
L57:
	.dbline 375
	inc R20
L59:
	.dbline 375
	cp R20,R22
	brlo L56
	.dbline -2
L55:
	xcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbsym r ilen 22 c
	.dbsym r s 10 pc
	.dbend
