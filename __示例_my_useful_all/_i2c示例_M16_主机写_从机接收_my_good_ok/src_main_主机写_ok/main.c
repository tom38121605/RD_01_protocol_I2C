//TWI主机

unsigned char i2c_read(void);
unsigned char i2c_read2(void);
unsigned char i2c_maste_read(unsigned char addr);


#include <iom16v.h>
#include <macros.h>

#include <string.h>
//#include "config.h"


//----串口------
#define  B9600  47	//波特率 7.3728MHz clock
#define  B19200 23
#define  B38400 11
#define  B57600 7
#define  BAUD B57600

#define RX_BUFFER_SIZE 12 

void UART_Init(void);               //串口初始化函数
void UART_Receive(void);            //串口接收函数
void UART_PutChar(unsigned char c); //串口输出字符
void UART_Puts(unsigned char *s);   //串口输出字符串
void UART_PutBytes(unsigned char *s, unsigned char ilen);  //串口输出字节

unsigned char RX_data[RX_BUFFER_SIZE]={0};   //串口接收缓冲区
unsigned char RX_data2[RX_BUFFER_SIZE]={0};



// defines and constants 
#define TWCR_CMD_MASK     0x0F 
#define TWSR_STATUS_MASK  0xF8 

//清除中断标志位,使能TWI功能,开放TWI中断,在主控接收状态下对SDA线作应答
#define Twi_Ack()	  {TWCR=TWCR&TWCR_CMD_MASK|(1<<TWEA)|(1<<TWINT);}
//清除中断标志位,使能TWI功能,开放TWI中断,在主控接收状态下不对SDA线作应答
#define Twi_NoAcK()	  {TWCR=TWCR&TWCR_CMD_MASK|(1<<TWINT);}

void i2c_start(void);
unsigned char i2c_write_addr(unsigned char addr,unsigned char r_w);
unsigned char i2c_write_data(unsigned char data);
void i2c_stop(void);

void twi_master_init(void);
void i2c_maste_transt(unsigned char addr, unsigned char data);


void Delay_1us(void);  //1us精确延时函数
void Delay_nus(unsigned int n);  //nus延时函数, 10us以内为精确延时

void Delay_nus_Count(unsigned int n);     //精确nus延时函数，10us以上的精确延时
//Delay_10us： Delay_nus_Count(11);   //7.3728M
//Delay_20us： Delay_nus_Count(25);   //7.3728M
//Delay_50us： Delay_nus_Count(60);   //7.3728M
//Delay_100us： Delay_nus_Count(121);   //7.3728M
//Delay_500us： Delay_nus_Count(613);   //7.3728M


void Delay_1ms_Preci(void);  //1ms精确延时函数
void Delay_nms(unsigned int n);  //nms精确延时函数



//主机发送状态码
#define TW_START				0x08	//START已发送
#define TW_REP_START	0x10   //重复START已发送
#define TW_MT_SLA_ACK         0x18   //SLA+W 已发送收到ACK
#define TW_MT_SLA_NACK        0x20   //SLA+W 已发送接收到NOT ACK
#define TW_MT_DATA_ACK        0x28   //数据已发送接收到ACK
#define TW_MT_DATA_NACK       0x30   //数据已发送接收到NOT ACK
#define TW_MT_ARB_LOST        0x38   //SLA+W 或数据的仲裁失败

//主机接收状态码
//#define TW_START				0x08	//START已发送
//#define TW_REP_START			0x10	//重复START已发送
#define TW_MR_ARB_LOST   0x38	//SLA+R 或NOT ACK 的仲裁失败
#define TW_MR_SLA_ACK   0x40	//SLA+R 已发送接收到ACK
#define TW_MR_SLA_NACK   0x48	//SLA+R 已发送接收到NOT ACK
#define TW_MR_DATA_ACK   0x50	//接收到数据ACK 已返回
//#define TW_MR_DATA_NACK 
volatile unsigned char tmp1=0;
volatile unsigned char tmp2=0;
volatile unsigned char tmp3=0;
volatile unsigned char tmp4=0;
volatile unsigned char tmp5=0;
volatile unsigned char tmp6=0;
volatile unsigned char tmp7=0;


void i2c_MAck(void);
void i2c_MNAck(void);



//TWI master initialize
// bit rate:100
void twi_master_init(void)
{
 TWCR= 0x00; //disable twi
 
 TWBR= 14;//14;//0x64; //set bit rate  //14 -- 166.7K
 
 
 TWSR= 0x00; //set prescale
 TWAR= 0x00; //set slave address
 
 TWCR= 0x04; //enable twi
}

//总线上起动开始条件
void i2c_start(void)
{
   TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
   while (!(TWCR & (1<<TWINT))); //等待START 信号成功发送
}

//总线上起动停止条件 
void i2c_stop(void) 
{ 
   TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); 
}

void i2c_MAck(void)
{
   //output_low(VSDA);
   //output_high(VSCL);
   PORTC&=~(1<<1);
   PORTC|=(1<<0);
   
   Delay_nus(2);
   
   //output_low(VSCL);
   //output_high(VSDA);
   PORTC&=~(1<<0);
   PORTC|=(1<<1);
   
   Delay_nus(1);
}

void i2c_MNAck(void)
{
    DDRC|=(1<<0|1<<1); //SDA,SCL设置为输入 
   
   //output_high(VSDA);
   //output_high(VSCL);
   PORTC|=(1<<1);
   PORTC|=(1<<0);

   Delay_nus(2);

   //output_low(VSCL);
   //output_low(VSDA);
   PORTC&=~(1<<1);
   PORTC&=~(1<<0);
   Delay_nus(1);
   
    DDRC&=~(1<<0|1<<1); //SDA,SCL设置为输入
}

void main(void)
{

   CLI();                                                                                                     
   
   UART_Init();
   
   DDRC&=~(1<<0|1<<1); //SDA,SCL设置为输入
   PORTC|=(1<<0|1<<1); //使能内部上拉电阻   
   
   twi_master_init();
 
   SEI();

   while(1)
   {
   
      //---------- 写数据到i2c --------------
      /*i2c_start();    
  
      //i2c_write_addr(0x5A, 0);   
      i2c_write_data(0x5A);
  
      i2c_write_data(0x68);
      i2c_write_data(0x27);
      i2c_write_data(0x2b);
      i2c_write_data(0x83);
      i2c_write_data(0x35);
      i2c_write_data(0x97);
      i2c_write_data(0x10);  

      i2c_stop();
      */

      //--------- 从i2c读数据  -------------
      
      i2c_start();
      
      if(i2c_write_addr(0x5A, 1)==TW_MR_SLA_ACK)  //发送地址成功并收到ACK
      {     
         tmp1=i2c_read();   //i2c_MAck();                       
         tmp2=i2c_read();   //i2c_MAck();  
         tmp3=i2c_read();   //i2c_MAck();  
         tmp4=i2c_read();   //i2c_MAck();  
         tmp5=i2c_read();   //i2c_MAck();  
         tmp6=i2c_read();   //i2c_MAck();    
         tmp7=i2c_read2();   //i2c_MNAck();           
                     
      }
      i2c_stop();
  
         UART_PutChar(0x80);      
         UART_PutChar(tmp1);      
         UART_PutChar(tmp2);      
         UART_PutChar(tmp3);      
         UART_PutChar(tmp4);      
         UART_PutChar(tmp5);      
         UART_PutChar(tmp6);      
         UART_PutChar(tmp7);      
       
      Delay_nms(8);
      Delay_nus(300);
   } 

}


//操作步骤： 启动，发送地址，发送数据，关闭总线
void i2c_maste_transt(unsigned char addr, unsigned char data)
{
   i2c_start();
      
 
   //if(i2c_write_addr(addr, 0)==TW_MT_SLA_ACK) //发送地址成功并收到ACK
   //{
   //   i2c_write_data(data);
   //}
   //else
   //    i2c_write_data(data);  //--test
   
  
   i2c_write_addr(addr, 0);   
   //i2c_write_data(0x5A);
  
   i2c_write_data(0x68);
   i2c_write_data(0x27);
   i2c_write_data(0x2b);
   i2c_write_data(0x83);
   i2c_write_data(0x35);
   i2c_write_data(0x97);
   i2c_write_data(0x10);  
   
    
   
   i2c_stop();
   
}

//把一个字节数据输入器件, 返回TWI状态
//发送地址,r_w：1为读，0为写
unsigned char i2c_write_addr(unsigned char addr,unsigned char r_w)
{
   if(r_w)
   {
    TWDR = addr|r_w;     //RW 为1：读操作
   }
   else
   {
   TWDR = addr & 0xFE;   // RW 为0: 写操作
   } 

   TWCR = (1<<TWINT)|(1<<TWEN); 
   while (!(TWCR & (1<<TWINT)));
   asm("nop");
   return(TWSR&0b11111000); //TWSR高五位为I2C工作状态。
}


//把一个字节数据输入器件, 返回TWI状态
//发送数据
unsigned char i2c_write_data(unsigned char data)
{
   TWDR = data;
   TWCR = (1<<TWINT)|(1<<TWEN); 
   while (!(TWCR & (1<<TWINT)));
   asm("nop");
   return(TWSR&0b11111000); //TWSR高五位为I2C工作状态。
}


//从器件读出一个字节
unsigned char i2c_read(void)
{
   TWCR = (1<<TWINT)|(1<<TWEN); 
   Twi_Ack();  //Twi_AcK(); 
   while (!(TWCR & (1<<TWINT)));
   return(TWDR);
}

//从器件读出一个字节
unsigned char i2c_read2(void)
{
   TWCR = (1<<TWINT)|(1<<TWEN); 
   Twi_NoAcK();
   while (!(TWCR & (1<<TWINT)));
   return(TWDR);
}


//操作步骤，启动，发送地址，读数据，关闭总线
unsigned char i2c_maste_read(unsigned char addr)
{
  unsigned char tmp=0; 
  i2c_start();
  if(i2c_write_addr(addr, 1)==TW_MR_SLA_ACK)  //发送地址成功并收到ACK
  {
   tmp=i2c_read();
  }
  i2c_stop();
  return tmp;
}


/*-----------------------------------------------------------------------
延时函数
系统时钟：7.3728M
-----------------------------------------------------------------------*/
//1us精确延时函数
void Delay_1us(void)     // 实际 8/7.3728＝1.085 us
{
   asm("nop");
}

//nus延时函数, 10us以内为精确延时
void Delay_nus(unsigned int n)     
{
   while (n--)
      Delay_1us();   
}  

//精确nus延时函数，10us以上的精确延时
void Delay_nus_Count(unsigned int n)   
{ 
   //Delay_10us： Delay_nus_Count(11);   //7.3728M
   //Delay_20us： Delay_nus_Count(25);   //7.3728M
   //Delay_50us： Delay_nus_Count(60);   //7.3728M
   //Delay_100us： Delay_nus_Count(121);   //7.3728M
   //Delay_500us： Delay_nus_Count(613);   //7.3728M

   while(n) 
      n--;    
}

//1ms精确延时函数
void Delay_1ms_Preci(void)    //7.3728M             
{
   unsigned int n;
   n=1225; 
   while (n) 
      n--;
}

//nms精确延时函数
void Delay_nms(unsigned int n)       
{
   while(n--)
     Delay_1ms_Preci();
}

//串口初始化函数
void UART_Init(void)
{
   UCSRB = (1<<RXCIE)| (1<<RXEN) |(1<<TXEN);   //允许串口发送和接收，并响应接收完成中断
   UBRR = BAUD;
   UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);   //8位数据＋1位stop位
}

//串口输出字符
void UART_PutChar(unsigned char c)  
{
   while (!(UCSRA&(1 << UDRE)));    //判断上次发送有没有完成
   UDR = c;
}

//串口输出字符串
void UART_Puts(unsigned char *s)
{
   while (*s)
   {
      UART_PutChar(*s++);
   }
}

//串口输出字节
void UART_PutBytes(unsigned char *s, unsigned char ilen)
{
unsigned char i;

   for(i=0;i<ilen;i++)
   {
      UART_PutChar(*s++);
   }
}
