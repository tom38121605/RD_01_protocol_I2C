//TWI����

unsigned char i2c_read(void);
unsigned char i2c_read2(void);
unsigned char i2c_maste_read(unsigned char addr);


#include <iom16v.h>
#include <macros.h>

#include <string.h>
//#include "config.h"


//----����------
#define  B9600  47	//������ 7.3728MHz clock
#define  B19200 23
#define  B38400 11
#define  B57600 7
#define  BAUD B57600

#define RX_BUFFER_SIZE 12 

void UART_Init(void);               //���ڳ�ʼ������
void UART_Receive(void);            //���ڽ��պ���
void UART_PutChar(unsigned char c); //��������ַ�
void UART_Puts(unsigned char *s);   //��������ַ���
void UART_PutBytes(unsigned char *s, unsigned char ilen);  //��������ֽ�

unsigned char RX_data[RX_BUFFER_SIZE]={0};   //���ڽ��ջ�����
unsigned char RX_data2[RX_BUFFER_SIZE]={0};



// defines and constants 
#define TWCR_CMD_MASK     0x0F 
#define TWSR_STATUS_MASK  0xF8 

//����жϱ�־λ,ʹ��TWI����,����TWI�ж�,�����ؽ���״̬�¶�SDA����Ӧ��
#define Twi_Ack()	  {TWCR=TWCR&TWCR_CMD_MASK|(1<<TWEA)|(1<<TWINT);}
//����жϱ�־λ,ʹ��TWI����,����TWI�ж�,�����ؽ���״̬�²���SDA����Ӧ��
#define Twi_NoAcK()	  {TWCR=TWCR&TWCR_CMD_MASK|(1<<TWINT);}

void i2c_start(void);
unsigned char i2c_write_addr(unsigned char addr,unsigned char r_w);
unsigned char i2c_write_data(unsigned char data);
void i2c_stop(void);

void twi_master_init(void);
void i2c_maste_transt(unsigned char addr, unsigned char data);


void Delay_1us(void);  //1us��ȷ��ʱ����
void Delay_nus(unsigned int n);  //nus��ʱ����, 10us����Ϊ��ȷ��ʱ

void Delay_nus_Count(unsigned int n);     //��ȷnus��ʱ������10us���ϵľ�ȷ��ʱ
//Delay_10us�� Delay_nus_Count(11);   //7.3728M
//Delay_20us�� Delay_nus_Count(25);   //7.3728M
//Delay_50us�� Delay_nus_Count(60);   //7.3728M
//Delay_100us�� Delay_nus_Count(121);   //7.3728M
//Delay_500us�� Delay_nus_Count(613);   //7.3728M


void Delay_1ms_Preci(void);  //1ms��ȷ��ʱ����
void Delay_nms(unsigned int n);  //nms��ȷ��ʱ����



//��������״̬��
#define TW_START				0x08	//START�ѷ���
#define TW_REP_START	0x10   //�ظ�START�ѷ���
#define TW_MT_SLA_ACK         0x18   //SLA+W �ѷ����յ�ACK
#define TW_MT_SLA_NACK        0x20   //SLA+W �ѷ��ͽ��յ�NOT ACK
#define TW_MT_DATA_ACK        0x28   //�����ѷ��ͽ��յ�ACK
#define TW_MT_DATA_NACK       0x30   //�����ѷ��ͽ��յ�NOT ACK
#define TW_MT_ARB_LOST        0x38   //SLA+W �����ݵ��ٲ�ʧ��

//��������״̬��
//#define TW_START				0x08	//START�ѷ���
//#define TW_REP_START			0x10	//�ظ�START�ѷ���
#define TW_MR_ARB_LOST   0x38	//SLA+R ��NOT ACK ���ٲ�ʧ��
#define TW_MR_SLA_ACK   0x40	//SLA+R �ѷ��ͽ��յ�ACK
#define TW_MR_SLA_NACK   0x48	//SLA+R �ѷ��ͽ��յ�NOT ACK
#define TW_MR_DATA_ACK   0x50	//���յ�����ACK �ѷ���
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

//�������𶯿�ʼ����
void i2c_start(void)
{
   TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
   while (!(TWCR & (1<<TWINT))); //�ȴ�START �źųɹ�����
}

//��������ֹͣ���� 
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
    DDRC|=(1<<0|1<<1); //SDA,SCL����Ϊ���� 
   
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
   
    DDRC&=~(1<<0|1<<1); //SDA,SCL����Ϊ����
}

void main(void)
{

   CLI();                                                                                                     
   
   UART_Init();
   
   DDRC&=~(1<<0|1<<1); //SDA,SCL����Ϊ����
   PORTC|=(1<<0|1<<1); //ʹ���ڲ���������   
   
   twi_master_init();
 
   SEI();

   while(1)
   {
   
      //---------- д���ݵ�i2c --------------
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

      //--------- ��i2c������  -------------
      
      i2c_start();
      
      if(i2c_write_addr(0x5A, 1)==TW_MR_SLA_ACK)  //���͵�ַ�ɹ����յ�ACK
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


//�������裺 ���������͵�ַ���������ݣ��ر�����
void i2c_maste_transt(unsigned char addr, unsigned char data)
{
   i2c_start();
      
 
   //if(i2c_write_addr(addr, 0)==TW_MT_SLA_ACK) //���͵�ַ�ɹ����յ�ACK
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

//��һ���ֽ�������������, ����TWI״̬
//���͵�ַ,r_w��1Ϊ����0Ϊд
unsigned char i2c_write_addr(unsigned char addr,unsigned char r_w)
{
   if(r_w)
   {
    TWDR = addr|r_w;     //RW Ϊ1��������
   }
   else
   {
   TWDR = addr & 0xFE;   // RW Ϊ0: д����
   } 

   TWCR = (1<<TWINT)|(1<<TWEN); 
   while (!(TWCR & (1<<TWINT)));
   asm("nop");
   return(TWSR&0b11111000); //TWSR����λΪI2C����״̬��
}


//��һ���ֽ�������������, ����TWI״̬
//��������
unsigned char i2c_write_data(unsigned char data)
{
   TWDR = data;
   TWCR = (1<<TWINT)|(1<<TWEN); 
   while (!(TWCR & (1<<TWINT)));
   asm("nop");
   return(TWSR&0b11111000); //TWSR����λΪI2C����״̬��
}


//����������һ���ֽ�
unsigned char i2c_read(void)
{
   TWCR = (1<<TWINT)|(1<<TWEN); 
   Twi_Ack();  //Twi_AcK(); 
   while (!(TWCR & (1<<TWINT)));
   return(TWDR);
}

//����������һ���ֽ�
unsigned char i2c_read2(void)
{
   TWCR = (1<<TWINT)|(1<<TWEN); 
   Twi_NoAcK();
   while (!(TWCR & (1<<TWINT)));
   return(TWDR);
}


//�������裬���������͵�ַ�������ݣ��ر�����
unsigned char i2c_maste_read(unsigned char addr)
{
  unsigned char tmp=0; 
  i2c_start();
  if(i2c_write_addr(addr, 1)==TW_MR_SLA_ACK)  //���͵�ַ�ɹ����յ�ACK
  {
   tmp=i2c_read();
  }
  i2c_stop();
  return tmp;
}


/*-----------------------------------------------------------------------
��ʱ����
ϵͳʱ�ӣ�7.3728M
-----------------------------------------------------------------------*/
//1us��ȷ��ʱ����
void Delay_1us(void)     // ʵ�� 8/7.3728��1.085 us
{
   asm("nop");
}

//nus��ʱ����, 10us����Ϊ��ȷ��ʱ
void Delay_nus(unsigned int n)     
{
   while (n--)
      Delay_1us();   
}  

//��ȷnus��ʱ������10us���ϵľ�ȷ��ʱ
void Delay_nus_Count(unsigned int n)   
{ 
   //Delay_10us�� Delay_nus_Count(11);   //7.3728M
   //Delay_20us�� Delay_nus_Count(25);   //7.3728M
   //Delay_50us�� Delay_nus_Count(60);   //7.3728M
   //Delay_100us�� Delay_nus_Count(121);   //7.3728M
   //Delay_500us�� Delay_nus_Count(613);   //7.3728M

   while(n) 
      n--;    
}

//1ms��ȷ��ʱ����
void Delay_1ms_Preci(void)    //7.3728M             
{
   unsigned int n;
   n=1225; 
   while (n) 
      n--;
}

//nms��ȷ��ʱ����
void Delay_nms(unsigned int n)       
{
   while(n--)
     Delay_1ms_Preci();
}

//���ڳ�ʼ������
void UART_Init(void)
{
   UCSRB = (1<<RXCIE)| (1<<RXEN) |(1<<TXEN);   //�����ڷ��ͺͽ��գ�����Ӧ��������ж�
   UBRR = BAUD;
   UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);   //8λ���ݣ�1λstopλ
}

//��������ַ�
void UART_PutChar(unsigned char c)  
{
   while (!(UCSRA&(1 << UDRE)));    //�ж��ϴη�����û�����
   UDR = c;
}

//��������ַ���
void UART_Puts(unsigned char *s)
{
   while (*s)
   {
      UART_PutChar(*s++);
   }
}

//��������ֽ�
void UART_PutBytes(unsigned char *s, unsigned char ilen)
{
unsigned char i;

   for(i=0;i<ilen;i++)
   {
      UART_PutChar(*s++);
   }
}
