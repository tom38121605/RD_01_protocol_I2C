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
	.dbfile main.c
	.dbsym e RX_data _RX_data A[12:12]c
_RX_data2::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.blkb 11
	.area idata
	.word 0,0,0,0,0
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.dbsym e RX_data2 _RX_data2 A[12:12]c
_tmp1::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.dbsym e tmp1 _tmp1 c
_tmp2::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.dbsym e tmp2 _tmp2 c
_tmp3::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.dbsym e tmp3 _tmp3 c
_tmp4::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.dbsym e tmp4 _tmp4 c
_tmp5::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.dbsym e tmp5 _tmp5 c
_tmp6::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.dbsym e tmp6 _tmp6 c
_tmp7::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile main.c
	.dbsym e tmp7 _tmp7 c
	.area text(rom, con, rel)
	.dbfile main.c
	.dbfunc e Int0_Init _Int0_Init fV
	.even
_Int0_Init::
	.dbline -1
	.dbline 110
; //TWI主机
; 
; unsigned char i2c_read(void);
; unsigned char i2c_read2(void);
; unsigned char i2c_maste_read(unsigned char addr);
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
; #define  BAUD B57600
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
; // defines and constants 
; #define TWCR_CMD_MASK     0x0F 
; #define TWSR_STATUS_MASK  0xF8 
; 
; //清除中断标志位,使能TWI功能,开放TWI中断,在主控接收状态下对SDA线作应答
; #define Twi_Ack()	  {TWCR=TWCR&TWCR_CMD_MASK|(1<<TWEA)|(1<<TWINT);}
; //清除中断标志位,使能TWI功能,开放TWI中断,在主控接收状态下不对SDA线作应答
; #define Twi_NoAcK()	  {TWCR=TWCR&TWCR_CMD_MASK|(1<<TWINT);}
; 
; void i2c_start(void);
; unsigned char i2c_write_addr(unsigned char addr,unsigned char r_w);
; unsigned char i2c_write_data(unsigned char data);
; void i2c_stop(void);
; 
; void twi_master_init(void);
; void i2c_maste_transt(unsigned char addr, unsigned char data);
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
; //主机发送状态码
; #define TW_START				0x08	//START已发送
; #define TW_REP_START	0x10   //重复START已发送
; #define TW_MT_SLA_ACK         0x18   //SLA+W 已发送收到ACK
; #define TW_MT_SLA_NACK        0x20   //SLA+W 已发送接收到NOT ACK
; #define TW_MT_DATA_ACK        0x28   //数据已发送接收到ACK
; #define TW_MT_DATA_NACK       0x30   //数据已发送接收到NOT ACK
; #define TW_MT_ARB_LOST        0x38   //SLA+W 或数据的仲裁失败
; 
; //主机接收状态码
; //#define TW_START				0x08	//START已发送
; //#define TW_REP_START			0x10	//重复START已发送
; #define TW_MR_ARB_LOST   0x38	//SLA+R 或NOT ACK 的仲裁失败
; #define TW_MR_SLA_ACK   0x40	//SLA+R 已发送接收到ACK
; #define TW_MR_SLA_NACK   0x48	//SLA+R 已发送接收到NOT ACK
; #define TW_MR_DATA_ACK   0x50	//接收到数据ACK 已返回
; //#define TW_MR_DATA_NACK 
; volatile unsigned char tmp1=0;
; volatile unsigned char tmp2=0;
; volatile unsigned char tmp3=0;
; volatile unsigned char tmp4=0;
; volatile unsigned char tmp5=0;
; volatile unsigned char tmp6=0;
; volatile unsigned char tmp7=0;
; 
; void i2c_MAck(void);
; void i2c_MNAck(void);
; 
; //--------int0 ----------
; #define INT0_DDR  DDRD
; #define INT0_PORT PORTD
; #define INT0_PIN  PIND
; #define INT0_IO   2 
; 
; unsigned char flg_Int0_In;
; 
; void Int0_Init(void);
; void ISR_Int0(void);
; void Int0_DoWithInt(void);
; 
; 
; void Int0_Init(void)
; {
	.dbline 111
;    GICR|= (1<<6);      //enable int0
	in R24,0x3b
	ori R24,64
	out 0x3b,R24
	.dbline 114
; 
;    //设置中断引脚为输入(示例为M16的PD3)
;    INT0_DDR&=~(1<<INT0_IO);
	cbi 0x11,2
	.dbline 117
;    //INT0_PORT|=(1<<INT0_IO);		 
;   
;    MCUCR|= (1<<1);   //mod set --下降沿方式
	in R24,0x35
	ori R24,2
	out 0x35,R24
	.dbline 118
;    MCUCR&= ~(1<<0);  
	in R24,0x35
	andi R24,254
	out 0x35,R24
	.dbline -2
L1:
	.dbline 0 ; func end
	ret
	.dbend
	.area vector(rom, abs)
	.org 4
	jmp _ISR_Int0
	.area text(rom, con, rel)
	.dbfile main.c
	.dbfunc e ISR_Int0 _ISR_Int0 fV
	.even
_ISR_Int0::
	st -y,R24
	in R24,0x3f
	st -y,R24
	.dbline -1
	.dbline 124
; }
; 
; 
; #pragma interrupt_handler ISR_Int0:iv_INT0
; void ISR_Int0(void)
; {
	.dbline 125
;    flg_Int0_In=1;
	ldi R24,1
	sts _flg_Int0_In,R24
	.dbline 127
; 
;    GICR&= ~(1<<6);   //disable int0  -- 关闭中断  
	in R24,0x3b
	andi R24,191
	out 0x3b,R24
	.dbline -2
L2:
	ld R24,y+
	out 0x3f,R24
	ld R24,y+
	.dbline 0 ; func end
	reti
	.dbend
	.dbfunc e Int0_DoWithInt _Int0_DoWithInt fV
	.even
_Int0_DoWithInt::
	.dbline -1
	.dbline 132
;     
; }
; 
; void Int0_DoWithInt(void)
; {			
	.dbline 134
;    //PORTA&=~(1<<4);  //PA4置低电平
;    PORTB^=(1<<3);  //翻转PB3的电平
	ldi R24,8
	in R2,0x18
	eor R2,R24
	out 0x18,R2
	.dbline 136
; 		   
;    GIFR|= (1<<6);      //通过写入"1"到GIFR.6来清零中断int0的标志位
	in R24,0x3a
	ori R24,64
	out 0x3a,R24
	.dbline 137
;    GICR|= (1<<6);      //enable int1  
	in R24,0x3b
	ori R24,64
	out 0x3b,R24
	.dbline -2
L3:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e twi_master_init _twi_master_init fV
	.even
_twi_master_init::
	.dbline -1
	.dbline 146
; }
; 
; 
; 
; 
; //TWI master initialize
; // bit rate:100
; void twi_master_init(void)
; {
	.dbline 147
;  TWCR= 0x00; //disable twi
	clr R2
	out 0x36,R2
	.dbline 149
;  
;  TWBR= 14;//14;//0x64; //set bit rate  //14 -- 166.7K
	ldi R24,14
	out 0x0,R24
	.dbline 152
;  
;  
;  TWSR= 0x00; //set prescale
	out 0x1,R2
	.dbline 153
;  TWAR= 0x00; //set slave address
	out 0x2,R2
	.dbline 155
;  
;  TWCR= 0x04; //enable twi
	ldi R24,4
	out 0x36,R24
	.dbline -2
L4:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_start _i2c_start fV
	.even
_i2c_start::
	.dbline -1
	.dbline 160
; }
; 
; //总线上起动开始条件
; void i2c_start(void)
; {
	.dbline 161
;    TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	ldi R24,164
	out 0x36,R24
L6:
	.dbline 162
L7:
	.dbline 162
;    while (!(TWCR & (1<<TWINT))); //等待START 信号成功发送
	in R2,0x36
	sbrs R2,7
	rjmp L6
	.dbline -2
L5:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_stop _i2c_stop fV
	.even
_i2c_stop::
	.dbline -1
	.dbline 167
; }
; 
; //总线上起动停止条件 
; void i2c_stop(void) 
; { 
	.dbline 168
;    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); 
	ldi R24,148
	out 0x36,R24
	.dbline -2
L9:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_MAck _i2c_MAck fV
	.even
_i2c_MAck::
	.dbline -1
	.dbline 172
; }
; 
; void i2c_MAck(void)
; {
	.dbline 175
;    //output_low(VSDA);
;    //output_high(VSCL);
;    PORTC&=~(1<<1);
	cbi 0x15,1
	.dbline 176
;    PORTC|=(1<<0);
	sbi 0x15,0
	.dbline 178
;    
;    Delay_nus(2);
	ldi R16,2
	ldi R17,0
	xcall _Delay_nus
	.dbline 182
;    
;    //output_low(VSCL);
;    //output_high(VSDA);
;    PORTC&=~(1<<0);
	cbi 0x15,0
	.dbline 183
;    PORTC|=(1<<1);
	sbi 0x15,1
	.dbline 185
;    
;    Delay_nus(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay_nus
	.dbline -2
L10:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_MNAck _i2c_MNAck fV
	.even
_i2c_MNAck::
	.dbline -1
	.dbline 189
; }
; 
; void i2c_MNAck(void)
; {
	.dbline 190
;     DDRC|=(1<<0|1<<1); //SDA,SCL设置为输入 
	in R24,0x14
	ori R24,3
	out 0x14,R24
	.dbline 194
;    
;    //output_high(VSDA);
;    //output_high(VSCL);
;    PORTC|=(1<<1);
	sbi 0x15,1
	.dbline 195
;    PORTC|=(1<<0);
	sbi 0x15,0
	.dbline 197
; 
;    Delay_nus(2);
	ldi R16,2
	ldi R17,0
	xcall _Delay_nus
	.dbline 201
; 
;    //output_low(VSCL);
;    //output_low(VSDA);
;    PORTC&=~(1<<1);
	cbi 0x15,1
	.dbline 202
;    PORTC&=~(1<<0);
	cbi 0x15,0
	.dbline 203
;    Delay_nus(1);
	ldi R16,1
	ldi R17,0
	xcall _Delay_nus
	.dbline 205
;    
;     DDRC&=~(1<<0|1<<1); //SDA,SCL设置为输入
	in R24,0x14
	andi R24,252
	out 0x14,R24
	.dbline -2
L11:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e main _main fV
	.even
_main::
	.dbline -1
	.dbline 209
; }
; 
; void main(void)
; {
	.dbline 211
; 
;    CLI();         
	cli
	.dbline 214
;    
;    //设置PB1为输出,置高电平
;    DDRB|=(1<<3);
	sbi 0x17,3
	.dbline 215
;    PORTB|=(1<<3);	 
	sbi 0x18,3
	.dbline 216
;    Int0_Init();                                                                                               
	xcall _Int0_Init
	.dbline 218
;    
;    UART_Init();
	xcall _UART_Init
	.dbline 220
;    
;    DDRC&=~(1<<0|1<<1); //SDA,SCL设置为输入
	in R24,0x14
	andi R24,252
	out 0x14,R24
	.dbline 221
;    PORTC|=(1<<0|1<<1); //使能内部上拉电阻   
	in R24,0x15
	ori R24,3
	out 0x15,R24
	.dbline 223
;    
;    twi_master_init();
	xcall _twi_master_init
	.dbline 225
;  
;    SEI();
	sei
	xjmp L14
L13:
	.dbline 240
;    
;    /*while(1)    //循环
;    {        
;       if (flg_Int0_In==1) 
;       {  		   		   	
;          flg_Int0_In=0;		
;          Int0_DoWithInt();
;          
;       }        
; 		
;    }  
;    */
; 
;    while(1)
;    {
	.dbline 259
;    
;       //---------- 写数据到i2c --------------
;       /*i2c_start();    
;   
;       //i2c_write_addr(0x5A, 0);   
;       i2c_write_data(0x5A);
;   
;       i2c_write_data(0x68);
;       i2c_write_data(0x27);
;       i2c_write_data(0x2b);
;       i2c_write_data(0x83);
;       i2c_write_data(0x35);
;       i2c_write_data(0x97);
;       i2c_write_data(0x10);  
; 
;       i2c_stop();
;       */
;       
;        if (flg_Int0_In==1) 
	lds R24,_flg_Int0_In
	cpi R24,1
	breq X1
	xjmp L16
X1:
	.dbline 260
;       {  		   		   	
	.dbline 261
;          flg_Int0_In=0;		
	clr R2
	sts _flg_Int0_In,R2
	.dbline 268
;          //Int0_DoWithInt();
;          
;      
; 
;          //--------- 从i2c读数据  -------------
;          
;          i2c_start();
	xcall _i2c_start
	.dbline 270
;          
;          if(i2c_write_addr(0x5A, 1)==TW_MR_SLA_ACK)  //发送地址成功并收到ACK
	ldi R18,1
	ldi R16,90
	xcall _i2c_write_addr
	cpi R16,64
	brne L18
	.dbline 271
;          {
	.dbline 272
;             tmp1=i2c_read();   //i2c_MAck();
	xcall _i2c_read
	sts _tmp1,R16
	.dbline 273
;             tmp2=i2c_read();   //i2c_MAck();
	xcall _i2c_read
	sts _tmp2,R16
	.dbline 274
;             tmp3=i2c_read();   //i2c_MAck();
	xcall _i2c_read
	sts _tmp3,R16
	.dbline 275
;             tmp4=i2c_read();   //i2c_MAck();
	xcall _i2c_read
	sts _tmp4,R16
	.dbline 276
;             tmp5=i2c_read();   //i2c_MAck();
	xcall _i2c_read
	sts _tmp5,R16
	.dbline 277
;             tmp6=i2c_read();   //i2c_MAck();
	xcall _i2c_read
	sts _tmp6,R16
	.dbline 278
;             tmp7=i2c_read2();   //i2c_MNAck();
	xcall _i2c_read2
	sts _tmp7,R16
	.dbline 280
;                         
;          }
L18:
	.dbline 281
;          i2c_stop();
	xcall _i2c_stop
	.dbline 283
;      
;             UART_PutChar(0x80);
	ldi R16,128
	xcall _UART_PutChar
	.dbline 284
;             UART_PutChar(tmp1);
	lds R16,_tmp1
	xcall _UART_PutChar
	.dbline 285
;             UART_PutChar(tmp2);
	lds R16,_tmp2
	xcall _UART_PutChar
	.dbline 286
;             UART_PutChar(tmp3);
	lds R16,_tmp3
	xcall _UART_PutChar
	.dbline 287
;             UART_PutChar(tmp4);
	lds R16,_tmp4
	xcall _UART_PutChar
	.dbline 288
;             UART_PutChar(tmp5);
	lds R16,_tmp5
	xcall _UART_PutChar
	.dbline 289
;             UART_PutChar(tmp6);
	lds R16,_tmp6
	xcall _UART_PutChar
	.dbline 290
;             UART_PutChar(tmp7);
	lds R16,_tmp7
	xcall _UART_PutChar
	.dbline 292
;           
;          Delay_nms(8);
	ldi R16,8
	ldi R17,0
	xcall _Delay_nms
	.dbline 293
;          Delay_nus(300);
	ldi R16,300
	ldi R17,1
	xcall _Delay_nus
	.dbline 294
;       }
L16:
	.dbline 296
	in R24,0x3a
	ori R24,64
	out 0x3a,R24
	.dbline 297
	in R24,0x3b
	ori R24,64
	out 0x3b,R24
	.dbline 299
L14:
	.dbline 239
	xjmp L13
X0:
	.dbline -2
L12:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_maste_transt _i2c_maste_transt fV
;           data -> R22
;           addr -> R20
	.even
_i2c_maste_transt::
	xcall push_gset2
	mov R22,R18
	mov R20,R16
	.dbline -1
	.dbline 307
;       
;       GIFR|= (1<<6);      //通过写入"1"到GIFR.6来清零中断int0的标志位
;       GICR|= (1<<6);      //enable int1
;    
;    }        
;   
; 
; }
; 
; 
; //操作步骤： 启动，发送地址，发送数据，关闭总线
; void i2c_maste_transt(unsigned char addr, unsigned char data)
; {
	.dbline 308
;    i2c_start();
	xcall _i2c_start
	.dbline 319
;       
;  
;    //if(i2c_write_addr(addr, 0)==TW_MT_SLA_ACK) //发送地址成功并收到ACK
;    //{
;    //   i2c_write_data(data);
;    //}
;    //else
;    //    i2c_write_data(data);  //--test
;    
;   
;    i2c_write_addr(addr, 0);   
	clr R18
	mov R16,R20
	xcall _i2c_write_addr
	.dbline 322
;    //i2c_write_data(0x5A);
;   
;    i2c_write_data(0x68);
	ldi R16,104
	xcall _i2c_write_data
	.dbline 323
;    i2c_write_data(0x27);
	ldi R16,39
	xcall _i2c_write_data
	.dbline 324
;    i2c_write_data(0x2b);
	ldi R16,43
	xcall _i2c_write_data
	.dbline 325
;    i2c_write_data(0x83);
	ldi R16,131
	xcall _i2c_write_data
	.dbline 326
;    i2c_write_data(0x35);
	ldi R16,53
	xcall _i2c_write_data
	.dbline 327
;    i2c_write_data(0x97);
	ldi R16,151
	xcall _i2c_write_data
	.dbline 328
;    i2c_write_data(0x10);     
	ldi R16,16
	xcall _i2c_write_data
	.dbline 331
;     
;    
;    i2c_stop();
	xcall _i2c_stop
	.dbline -2
L20:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r data 22 c
	.dbsym r addr 20 c
	.dbend
	.dbfunc e i2c_write_addr _i2c_write_addr fc
;            r_w -> R18
;           addr -> R16
	.even
_i2c_write_addr::
	.dbline -1
	.dbline 338
;    
; }
; 
; //把一个字节数据输入器件, 返回TWI状态
; //发送地址,r_w：1为读，0为写
; unsigned char i2c_write_addr(unsigned char addr,unsigned char r_w)
; {
	.dbline 339
;    if(r_w)
	tst R18
	breq L22
	.dbline 340
;    {
	.dbline 341
;     TWDR = addr|r_w;     //RW 为1：读操作
	mov R2,R16
	or R2,R18
	out 0x3,R2
	.dbline 342
;    }
	xjmp L23
L22:
	.dbline 344
;    else
;    {
	.dbline 345
;    TWDR = addr & 0xFE;   // RW 为0: 写操作
	mov R24,R16
	andi R24,254
	out 0x3,R24
	.dbline 346
;    } 
L23:
	.dbline 348
; 
;    TWCR = (1<<TWINT)|(1<<TWEN); 
	ldi R24,132
	out 0x36,R24
L24:
	.dbline 349
L25:
	.dbline 349
;    while (!(TWCR & (1<<TWINT)));
	in R2,0x36
	sbrs R2,7
	rjmp L24
	.dbline 350
;    asm("nop");
	nop
	.dbline 351
;    return(TWSR&0b11111000); //TWSR高五位为I2C工作状态。
	in R16,0x1
	andi R16,248
	.dbline -2
L21:
	.dbline 0 ; func end
	ret
	.dbsym r r_w 18 c
	.dbsym r addr 16 c
	.dbend
	.dbfunc e i2c_write_data _i2c_write_data fc
;           data -> R16
	.even
_i2c_write_data::
	.dbline -1
	.dbline 358
; }
; 
; 
; //把一个字节数据输入器件, 返回TWI状态
; //发送数据
; unsigned char i2c_write_data(unsigned char data)
; {
	.dbline 359
;    TWDR = data;
	out 0x3,R16
	.dbline 360
;    TWCR = (1<<TWINT)|(1<<TWEN); 
	ldi R24,132
	out 0x36,R24
L28:
	.dbline 361
L29:
	.dbline 361
;    while (!(TWCR & (1<<TWINT)));
	in R2,0x36
	sbrs R2,7
	rjmp L28
	.dbline 362
;    asm("nop");
	nop
	.dbline 363
;    return(TWSR&0b11111000); //TWSR高五位为I2C工作状态。
	in R16,0x1
	andi R16,248
	.dbline -2
L27:
	.dbline 0 ; func end
	ret
	.dbsym r data 16 c
	.dbend
	.dbfunc e i2c_read _i2c_read fc
	.even
_i2c_read::
	.dbline -1
	.dbline 369
; }
; 
; 
; //从器件读出一个字节
; unsigned char i2c_read(void)
; {
	.dbline 370
;    TWCR = (1<<TWINT)|(1<<TWEN); 
	ldi R24,132
	out 0x36,R24
	.dbline 371
;    Twi_Ack();  //Twi_AcK(); 
	.dbline 371
	in R24,0x36
	andi R24,15
	ori R24,192
	out 0x36,R24
	.dbline 371
	.dbline 371
L32:
	.dbline 372
L33:
	.dbline 372
;    while (!(TWCR & (1<<TWINT)));
	in R2,0x36
	sbrs R2,7
	rjmp L32
	.dbline 373
;    return(TWDR);
	in R16,0x3
	.dbline -2
L31:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_read2 _i2c_read2 fc
	.even
_i2c_read2::
	.dbline -1
	.dbline 378
; }
; 
; //从器件读出一个字节
; unsigned char i2c_read2(void)
; {
	.dbline 379
;    TWCR = (1<<TWINT)|(1<<TWEN); 
	ldi R24,132
	out 0x36,R24
	.dbline 380
;    Twi_NoAcK();
	.dbline 380
	in R24,0x36
	andi R24,15
	ori R24,128
	out 0x36,R24
	.dbline 380
	.dbline 380
L36:
	.dbline 381
L37:
	.dbline 381
;    while (!(TWCR & (1<<TWINT)));
	in R2,0x36
	sbrs R2,7
	rjmp L36
	.dbline 382
;    return(TWDR);
	in R16,0x3
	.dbline -2
L35:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e i2c_maste_read _i2c_maste_read fc
;            tmp -> R20
;           addr -> R22
	.even
_i2c_maste_read::
	xcall push_gset2
	mov R22,R16
	.dbline -1
	.dbline 388
; }
; 
; 
; //操作步骤，启动，发送地址，读数据，关闭总线
; unsigned char i2c_maste_read(unsigned char addr)
; {
	.dbline 389
;   unsigned char tmp=0; 
	clr R20
	.dbline 390
;   i2c_start();
	xcall _i2c_start
	.dbline 391
;   if(i2c_write_addr(addr, 1)==TW_MR_SLA_ACK)  //发送地址成功并收到ACK
	ldi R18,1
	mov R16,R22
	xcall _i2c_write_addr
	cpi R16,64
	brne L40
	.dbline 392
;   {
	.dbline 393
;    tmp=i2c_read();
	xcall _i2c_read
	mov R20,R16
	.dbline 394
;   }
L40:
	.dbline 395
;   i2c_stop();
	xcall _i2c_stop
	.dbline 396
;   return tmp;
	mov R16,R20
	.dbline -2
L39:
	xcall pop_gset2
	.dbline 0 ; func end
	ret
	.dbsym r tmp 20 c
	.dbsym r addr 22 c
	.dbend
	.dbfunc e Delay_1us _Delay_1us fV
	.even
_Delay_1us::
	.dbline -1
	.dbline 406
; }
; 
; 
; /*-----------------------------------------------------------------------
; 延时函数
; 系统时钟：7.3728M
; -----------------------------------------------------------------------*/
; //1us精确延时函数
; void Delay_1us(void)     // 实际 8/7.3728＝1.085 us
; {
	.dbline 407
;    asm("nop");
	nop
	.dbline -2
L42:
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
	.dbline 412
; }
; 
; //nus延时函数, 10us以内为精确延时
; void Delay_nus(unsigned int n)     
; {
	xjmp L45
L44:
	.dbline 414
	xcall _Delay_1us
L45:
	.dbline 413
;    while (n--)
	movw R2,R20
	subi R20,1
	sbci R21,0
	tst R2
	brne L44
	tst R3
	brne L44
X2:
	.dbline -2
L43:
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
	.dbline 419
;       Delay_1us();   
; }  
; 
; //精确nus延时函数，10us以上的精确延时
; void Delay_nus_Count(unsigned int n)   
; { 
	xjmp L49
L48:
	.dbline 427
	subi R16,1
	sbci R17,0
L49:
	.dbline 426
;    //Delay_10us： Delay_nus_Count(11);   //7.3728M
;    //Delay_20us： Delay_nus_Count(25);   //7.3728M
;    //Delay_50us： Delay_nus_Count(60);   //7.3728M
;    //Delay_100us： Delay_nus_Count(121);   //7.3728M
;    //Delay_500us： Delay_nus_Count(613);   //7.3728M
; 
;    while(n) 
	cpi R16,0
	cpc R16,R17
	brne L48
X3:
	.dbline -2
L47:
	.dbline 0 ; func end
	ret
	.dbsym r n 16 i
	.dbend
	.dbfunc e Delay_1ms_Preci _Delay_1ms_Preci fV
;              n -> R16,R17
	.even
_Delay_1ms_Preci::
	.dbline -1
	.dbline 432
;       n--;    
; }
; 
; //1ms精确延时函数
; void Delay_1ms_Preci(void)    //7.3728M             
; {
	.dbline 434
;    unsigned int n;
;    n=1225; 
	ldi R16,1225
	ldi R17,4
	xjmp L53
L52:
	.dbline 436
	subi R16,1
	sbci R17,0
L53:
	.dbline 435
;    while (n) 
	cpi R16,0
	cpc R16,R17
	brne L52
X4:
	.dbline -2
L51:
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
	.dbline 441
;       n--;
; }
; 
; //nms精确延时函数
; void Delay_nms(unsigned int n)       
; {
	xjmp L57
L56:
	.dbline 443
	xcall _Delay_1ms_Preci
L57:
	.dbline 442
;    while(n--)
	movw R2,R20
	subi R20,1
	sbci R21,0
	tst R2
	brne L56
	tst R3
	brne L56
X5:
	.dbline -2
L55:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r n 20 i
	.dbend
	.dbfunc e UART_Init _UART_Init fV
	.even
_UART_Init::
	.dbline -1
	.dbline 448
;      Delay_1ms_Preci();
; }
; 
; //串口初始化函数
; void UART_Init(void)
; {
	.dbline 449
;    UCSRB = (1<<RXCIE)| (1<<RXEN) |(1<<TXEN);   //允许串口发送和接收，并响应接收完成中断
	ldi R24,152
	out 0xa,R24
	.dbline 450
;    UBRR = BAUD;
	ldi R24,7
	out 0x9,R24
	.dbline 451
;    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);   //8位数据＋1位stop位
	ldi R24,134
	out 0x20,R24
	.dbline -2
L59:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e UART_PutChar _UART_PutChar fV
;              c -> R16
	.even
_UART_PutChar::
	.dbline -1
	.dbline 456
; }
; 
; //串口输出字符
; void UART_PutChar(unsigned char c)  
; {
L61:
	.dbline 457
L62:
	.dbline 457
;    while (!(UCSRA&(1 << UDRE)));    //判断上次发送有没有完成
	sbis 0xb,5
	rjmp L61
	.dbline 458
;    UDR = c;
	out 0xc,R16
	.dbline -2
L60:
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
	.dbline 463
; }
; 
; //串口输出字符串
; void UART_Puts(unsigned char *s)
; {
	xjmp L66
L65:
	.dbline 465
	.dbline 466
	movw R30,R20
	ld R16,Z+
	movw R20,R30
	xcall _UART_PutChar
	.dbline 467
L66:
	.dbline 464
;    while (*s)
	movw R30,R20
	ldd R2,z+0
	tst R2
	brne L65
	.dbline -2
L64:
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
	.dbline 472
;    {
;       UART_PutChar(*s++);
;    }
; }
; 
; //串口输出字节
; void UART_PutBytes(unsigned char *s, unsigned char ilen)
; {
	.dbline 475
; unsigned char i;
; 
;    for(i=0;i<ilen;i++)
	clr R20
	xjmp L72
L69:
	.dbline 476
	.dbline 477
	movw R30,R10
	ld R16,Z+
	movw R10,R30
	xcall _UART_PutChar
	.dbline 478
L70:
	.dbline 475
	inc R20
L72:
	.dbline 475
	cp R20,R22
	brlo L69
	.dbline -2
L68:
	xcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbsym r ilen 22 c
	.dbsym r s 10 pc
	.dbend
	.area bss(ram, con, rel)
	.dbfile main.c
_flg_Int0_In::
	.blkb 1
	.dbsym e flg_Int0_In _flg_Int0_In c
