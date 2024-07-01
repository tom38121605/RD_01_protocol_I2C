//ģ��IIC����


#include <iom16v.h>
#include <macros.h>

#include <string.h>
//#include "config.h"


//----����------
#define  B9600  47	//������ 7.3728MHz clock
#define  B19200 23
#define  B38400 11
#define  B57600 7
#define  BAUD B19200

#define RX_BUFFER_SIZE 12 

void UART_Init(void);               //���ڳ�ʼ������
void UART_Receive(void);            //���ڽ��պ���
void UART_PutChar(unsigned char c); //��������ַ�
void UART_Puts(unsigned char *s);   //��������ַ���
void UART_PutBytes(unsigned char *s, unsigned char ilen);  //��������ֽ�

unsigned char RX_data[RX_BUFFER_SIZE]={0};   //���ڽ��ջ�����
unsigned char RX_data2[RX_BUFFER_SIZE]={0};




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


//#define TW_MR_DATA_NACK 
volatile unsigned char tmp1=0;
volatile unsigned char tmp2=0;
volatile unsigned char tmp3=0;
volatile unsigned char tmp4=0;
volatile unsigned char tmp5=0;
volatile unsigned char tmp6=0;
volatile unsigned char tmp7=0;


#define VSCL 0
#define VSDA 1

void i2c_StartIC(void);
void i2c_StopIC(void);
void i2c_MAck(void);
void i2c_MNAck(void);
unsigned char i2c_WaitAck(void);
void i2c_WriteByte(unsigned char iByte);
unsigned char  i2c_ReadByte(void);


void i2c_StartIC(void)
{
   //output_high(VSDA);
   //output_high(VSCL);
   PORTC|=(1<<VSDA);
   PORTC|=(1<<VSCL);
   
   Delay_nus(5);

   //output_low(VSDA);
   PORTC&=~(1<<VSDA);
   
   Delay_nus(4);

   //output_low(VSCL);
   PORTC&=~(1<<VSCL);
}

void i2c_StopIC(void)
{
   //output_low(VSDA);
   //output_high(VSCL);
   PORTC&=~(1<<VSDA);
   PORTC|=(1<<VSCL);

   Delay_nus(4);

   //output_high(VSDA);
   PORTC|=(1<<VSDA);

   Delay_nus(5);

   //output_low(VSDA);
   //output_low(VSCL);
   PORTC&=~(1<<VSDA);   //--���Ӧ��ȥ��
   PORTC&=~(1<<VSCL);
}

void i2c_MAck(void)
{
   //output_low(VSDA);
   //output_high(VSCL);
   PORTC&=~(1<<VSDA);
   PORTC|=(1<<VSCL);
   
   Delay_nus(4);
   
   //output_low(VSCL);
   //output_high(VSDA);
   PORTC&=~(1<<VSCL);
   PORTC|=(1<<VSDA);
}


void i2c_MNAck(void)
{
   //output_high(VSDA);
   //output_high(VSCL);
   PORTC|=(1<<VSDA);
   PORTC|=(1<<VSCL);

   Delay_nus(4);

   //output_low(VSCL);
   //output_low(VSDA);
   PORTC&=~(1<<VSDA);
   PORTC&=~(1<<VSCL);
}


unsigned char i2c_WaitAck(void)
{
   unsigned char iErrorTime=255;
   unsigned char iRet;

   //output_high(VSDA);
   PORTC|=(1<<VSDA);
   Delay_nus(1);
   //output_high(VSCL);
   PORTC|=(1<<VSCL);
   
   iRet=1;

   while( PINC|=(1<<VSDA) )
   {
      iErrorTime--;
      if(!iErrorTime)
      {
         //return 0;
         iRet=0;
      }
   }

   //output_low(VSCL);
   PORTC&=~(1<<VSCL);

   //output_high(VSDA);  //test
   PORTC|=(1<<VSDA);
   
   //return 1;
   return iRet;

}


void i2c_WriteByte(unsigned char iByte)
{
   unsigned char  i;

   for (i=0; i<0x08; i++)
   {
      if(iByte & 0x80)
         //output_high(VSDA);
         PORTC|=(1<<VSDA);
      else
         //output_low(VSDA);
         PORTC&=~(1<<VSDA);

      //output_high(VSCL);
      PORTC|=(1<<VSCL);

      Delay_nus(4);

      //output_low(VSCL);
      PORTC&=~(1<<VSCL);
      

      iByte <<= 0x01;
   }

}


unsigned char i2c_ReadByte(void)
{
   unsigned char   i;
   unsigned char   iByte;

   for (i=0; i<0x08; i++)
   {
      iByte <<= 0x01;
      //output_high(VSCL);
      PORTC|=(1<<VSCL);

      if( PINC|=(1<<VSDA) )
         iByte |= 0x01;

      Delay_nus(4);

      //output_low(VSCL);
      PORTC&=~(1<<VSCL);
   }

   return iByte;

}



void main(void)
{

   CLI();                                                                                                     
   
   UART_Init();
   
   //DDRC&=~(1<<VSCL|1<<VSDA); //SDA,SCL����Ϊ����
   //PORTC|=(1<<VSCL|1<<VSDA); //ʹ���ڲ���������   
   DDRC|=(1<<VSCL|1<<VSDA); //SDA,SCL����Ϊ����
   PORTC&=~(1<<VSCL|1<<VSDA); //ʹ���ڲ���������   
   
 
   SEI();
   
   
   //return;

   while(1)
   {   

      //--------- ��i2c������  -------------
      
      /*i2c_start();
      if(i2c_write_addr(0x5A, 1)==TW_MR_SLA_ACK)  //���͵�ַ�ɹ����յ�ACK
      {     
         tmp1=i2c_read();                          
         tmp2=i2c_read();
         tmp3=i2c_read();
         tmp4=i2c_read();
         tmp5=i2c_read();
         tmp6=i2c_read();   
         tmp7=i2c_read();         
                     
      }
      i2c_stop();
      */


      i2c_StartIC(); 
      i2c_WriteByte(0x5b);
      
      //if (i2c_WaitAck() ==1 )
      //{
         tmp1=i2c_ReadByte(); i2c_MAck();
         tmp2=i2c_ReadByte(); i2c_MAck();
         tmp3=i2c_ReadByte(); i2c_MAck();
         tmp4=i2c_ReadByte(); i2c_MAck();
         tmp5=i2c_ReadByte(); i2c_MAck();
         tmp6=i2c_ReadByte(); i2c_MAck();
         tmp7=i2c_ReadByte(); //i2c_MAck();
      //}
      
      i2c_StopIC();
      
  
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




/*

void i2c_SendByte_24c32(int8 iRomAddr_h, int8 iRomAddr_l,int8 iByte)
{
   i2c_StartIC();
   i2c_WriteByte(0xa0);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iRomAddr_h);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iRomAddr_l);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iByte);
   if( !i2c_WaitAck() );

   i2c_StopIC();

   delay_ms(11);
}

void i2c_Send_NByte_24c32(int8 iRomAddr_h, int8 iRomAddr_l, int8 iNum, int8 *iBytes)
{
   int8 i;
   unsigned int16 iAddr;
   int8 iTemp;

   i2c_StartIC();
   i2c_WriteByte(0xa0);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iRomAddr_h);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iRomAddr_l);
   if( !i2c_WaitAck() );

   iAddr = iRomAddr_h * 256 + iRomAddr_l;
   for(i=0; i<iNum; i++)
   {
      i2c_WriteByte(iBytes[i]);
      if( !i2c_WaitAck() );

      iAddr++;
      iTemp = iAddr % PAGESIZE;
      if (iTemp ==0)
      {
         delay_ms(10);

         i2c_StartIC();
         i2c_WriteByte(0xa0);
         if( !i2c_WaitAck() );

         i2c_WriteByte( iAddr>>8 );
         if( !i2c_WaitAck() );

         i2c_WriteByte( iAddr && 0x00ff );
         if( !i2c_WaitAck() );

      }

   }

   i2c_StopIC();
   delay_ms(11);

}


int8 i2c_GetByte_24c32(int8 iRomAddr_h, int8 iRomAddr_l)
{
   int8  iByte;

   i2c_StartIC();
   i2c_WriteByte(0xa0);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iRomAddr_h);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iRomAddr_l);
   if( !i2c_WaitAck() );

   i2c_StartIC();
   i2c_WriteByte(0xa1);
   if( !i2c_WaitAck() );

   iByte= i2c_ReadByte();
   i2c_MNAck();

   i2c_StopIC();

}

i2c_Get_NByte_24c32(int8 iRomAddr_h, int8 iRomAddr_l, int iNum, int *iBytes)
{
   int8  i;

   if(iNum =0) return;

   i2c_StartIC();
   i2c_WriteByte(0xa0);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iRomAddr_h);
   if( !i2c_WaitAck() );

   i2c_WriteByte(iRomAddr_l);
   if( !i2c_WaitAck() );

   i2c_StartIC();
   i2c_WriteByte(0xa1);
   if( !i2c_WaitAck() );

   for (i=0; i < iNum-1; i++)
   {
      iBytes[i] = i2c_ReadByte();
      i2c_mack();
   }

   iBytes[iNum-1] = i2c_ReadByte();
   i2c_MNAck();

   i2c_StopIC();
}

void setDB()
{
   unsigned int16 iNDB;

   //Ƶ�μ���
   //iNDB = (cDB1*256 + cDB2)/16 ;    //Fosc
   iNDB = (cDB1*256 + cDB2)/32 ;    //Fosc
   iNDB = iNDB  - 38.9;               //Fpicture = Fosc - Fpif

   if(iNDB>0 && iNDB<170) cPB=0xa0;    //VHF-L
   if(iNDB>170 && iNDB<450) cPB=0x90;  //VHF-H
   if(iNDB>450 && iNDB<864) cPB=0x30;  //UHF

   restart_wdt();
   delay_ms(1);



   //Write the data to FI1256 by I2C
   i2c_StartIC();

   i2c_WriteByte(0xc2);
   i2c_MAck();

   i2c_WriteByte(cDB1);
   i2c_MAck();
   i2c_WriteByte(cDB2);
   i2c_MAck();
   i2c_WriteByte(cCB);
   i2c_MAck();
   i2c_WriteByte(cPB);
   i2c_MAck();

   i2c_StopIC();
   delay_ms(11);

}
*/
