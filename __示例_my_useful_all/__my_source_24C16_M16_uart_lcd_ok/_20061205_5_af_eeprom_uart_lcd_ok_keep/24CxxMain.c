#include<iom16v.h>
#include<macros.h>

#include "xd.h"
#define XDmain
#include "xdprj.h"

#include "7920.h"
#include "usart.h"
#include "delay.h"

uchar r_buf[64];
uchar w_buf[64];

//TWI initialize
// bit rate:100
void twi_init(void)
{
 TWCR= 0X00; //disable twi
 TWBR= 0x64; //set bit rate
 TWSR= 0x00; //set prescale
 TWAR= 0x00; //set slave address
 TWCR= 0x04; //enable twi
}

void main()
{
     uint i;
	
     uchar *r;
     uint b;
     uint c;

     uchar *w;
     uint x;
     uint y;
	 
     //-----初始化cpu------
     //setreg_m16();	//初始化cpu
	 
 CLI(); //disable all interrupts
 
 //port_init();
 PORTC = 0b00000011; 
 DDRC  = 0x00;
 LCD_init();
 twi_init();
 //uart0_init();
 UART_init();

 MCUCR = 0x00;
 GICR  = 0x00;
 TIMSK = 0x00; //timer interrupt sources
 
 SEI(); //re-enable interrupts

	WriteTextScreen2("eeprom 20061205C");
	 
	//tms(100);
	delay_nms(800);
	
	for(i=0;i<64;i++)		//清主机读和写缓存区
		r_buf[i]=w_buf[i]=0;

	for(i=0;i<64;i++)		//写缓存区赋初值
		w_buf[i]=i;

	 byte2str(r_buf,10,txd_buf);
	 WriteTextScreen2(r_buf);
	 
	 puts("wbuf");
	 delay_nms(800);
	 putbytes(r_buf, 10);

     r=r_buf;	//读参数
     b=0x00;
     c=64;

     w=w_buf;	//写参数
     x=0x00;
     y=64;

     wt24c(w,x,y);	//写

     rd24c(r,b,c);	//读    
	      
     //-----读出的数据发送到PC-----
     //for(i=0;i<64;i++)
     //	txd_buf[i]=r_buf[i];
     
	 byte2str(r_buf,10,txd_buf);
     txd_buf[69]=syserr;
     
	 WriteTextScreen2(txd_buf);
	 
	 puts("tbuf");
	 delay_nms(100);
     //txdpo(txd_buf, 69);
	 putbytes(txd_buf, 10);
	 
	c=0;
}
