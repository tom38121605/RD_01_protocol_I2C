#include <iom16v.h>
#include <macros.h>

#include "delay.h"
#include "7920.h"

//----串口------
unsigned char RX_data[100]={0};
unsigned char *str;
unsigned int RX_counter;
unsigned char flg_start={0};
unsigned char flg_end={0};


void UART_init(void)
{
     UCSRB = BIT(RXCIE)| BIT(RXEN) |BIT(TXEN);  //允许串口发送和接收，并响应接收完成中断
     UBRR = 47;   //波特率 9600
     //UBRRL = (fosc/16/(baud+1))%256;
     //UBRRH = (fosc/16/(baud+1))/256;
     UCSRC = BIT(URSEL)|BIT(UCSZ1)|BIT(UCSZ0);   //8位数据＋1位stop位
}
  
void putchar(unsigned char c)       
{
     while (!(UCSRA&(1 << UDRE)));   //check busy
	 delay_nus(2);	 
     UDR = c;
}

void puts(unsigned char *s1)
{
unsigned char *s = s1;

     while (*s)
       {
          putchar(*s);
          s++;
       }
}
  
void putbytes(unsigned char *s1, unsigned char ilen1)
{
unsigned char i;
unsigned char *s = s1;
unsigned char ilen=ilen1;
  
  for(i=0;i<ilen;i++)
  {
      putchar(*s);
	  s++;
  }
}

#pragma interrupt_handler UART_rx: iv_USART_RX
void UART_rx(void)
  {
     //static unsigned char RX_counter;	 
     static unsigned char RX_char[1];
	 
     RX_char[0]= UDR;
	 
     //if ((RX_char[0]=='$') && (flg_start=='f'))  //是否开始
     //if (flg_start=='f')  //是否开始
     if (RX_char[0]=='$' && flg_start=='f')  //是否开始
       {
       	  RX_counter=0;
		  RX_data[0]=0;
		  //RX_data[0]='\0'; 
		  
		  flg_start='t';
		  
		  return ;
       }
	 
     if (RX_char[0]=='#' && flg_start=='t')  //是否结束
     //if (RX_char[0]=='#' )  //是否结束
       {
		  flg_end='t';
		  
	 	  str=RX_data;	 
		  
     	  delay_nms(2);
 		  LCD_write_cmd(0x01);  //清屏		
 		  delay_nms(2);
		  
     	  //LCD_write_str_1602(0,0,str);  //写数据
     	  //LCD_write_str(0,0,str);  //写数据
     	  WriteTextScreen2(str);  //写数据
     	  delay_nms(100);
		  
    	  //delay_nms(1000);
 		  //LCD_write_cmd(0x01);  //清屏		
 		  //delay_nms(2);
     	  //LCD_write_str_1601(0,0,"hello!");  //写数据

	 	  flg_start='f';
	 	  flg_end='f';
	 	  return;
       }

     //RX_data[RX_counter]=RX_char[0];
     //RX_counter++;	 
	 
     RX_data[RX_counter]=RX_char[0];
	 RX_data[RX_counter+1]='\0';
     RX_counter++;	 

  }

