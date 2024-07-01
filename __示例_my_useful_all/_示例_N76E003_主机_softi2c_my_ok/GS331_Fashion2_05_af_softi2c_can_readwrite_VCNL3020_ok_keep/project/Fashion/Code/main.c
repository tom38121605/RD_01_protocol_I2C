#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include <string.h>


unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x80;
unsigned char xdata xtemp _at_ 0x80;

UINT8 flg_addr_log=0;
 

//i2c

#define IIC_SCL_PIN         P03                  
#define SCL_OPENDRAIN_MODE  P03_OpenDrain_Mode   

#define IIC_SDA_PIN         P01                  
#define SDA_OPENDRAIN_MODE  P01_OpenDrain_Mode  
#define SDA_INPUT_MODE      P01_Input_Mode   



#define I2C_CLOCK_400KHz    9 

#define SLAVEADDR_SLA_SLA       0x26  //0xA0   //


#define SLAVEADDR_SLA_WR               0
#define SLAVEADDR_SLA_RD               1

#define  REG00  0x80
#define  REG01  0x81
#define  REG02  0x82
#define  REG03  0x83

#define  REG07  0x87
#define  REG08  0x88
#define  REG09  0x89
#define  REG10  0x8A
#define  REG11  0x8B
#define  REG12  0x8C
#define  REG13  0x8D
#define  REG14  0x8E
#define  REG15  0x8F
//#define  REG16  0x90


bit I2C_Reset_Flag;
  
   
void iputs0(UINT8 *msg)
{
   while(*msg)
		 Send_Data_To_UART0(*msg++);
}


void delay_1us()  //16M
{
 
      //_nop_();  
   
}

void delay_2us()  //16M
{  
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_();
}

void delay_4us()  //16M
{
   
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
   
   
}



void Init_I2C_soft(void)
{                          
   SCL_OPENDRAIN_MODE;  //scl
   SDA_OPENDRAIN_MODE;  //sda 
}


void SDA_OUT(void)
{
   SDA_OPENDRAIN_MODE;   
}

void SDA_IN(void)
{
   SDA_INPUT_MODE;   
}



void IIC_Start(void)
{
   SDA_OUT(); 
   
   IIC_SDA_PIN=1;   
   
   IIC_SCL_PIN=1;
   delay_4us();
   
   IIC_SDA_PIN=0;   
   delay_4us();
   
   IIC_SCL_PIN=0;    
}   

void IIC_Stop(void)
{
   SDA_OUT(); 
   
   IIC_SCL_PIN=0;
   
   IIC_SDA_PIN=0;  
   delay_4us();
   
   IIC_SCL_PIN=1; 
   
   IIC_SDA_PIN=1; 
   delay_4us();                           
} 

void IIC_Ack(void)
{
   SDA_OUT();
   
   IIC_SCL_PIN=0;
   
   IIC_SDA_PIN=0;
   delay_2us();
   IIC_SCL_PIN=1;
   delay_2us();
   IIC_SCL_PIN=0;
}

void IIC_NAck(void)
{
   SDA_OUT();

   IIC_SCL_PIN=0;

   IIC_SDA_PIN=1;   
   delay_2us();
   
   IIC_SCL_PIN=1;
   delay_2us();
   
   IIC_SCL_PIN=0;
}      



UINT8 IIC_Wait_Ack(void)
{
   
   UINT8 ucErrTime=0;
   
   SDA_IN();      
   
   IIC_SDA_PIN=1;delay_1us();      
   IIC_SCL_PIN=1;delay_1us();    
   
   while(IIC_SDA_PIN==1)
   {
      ucErrTime++;
      //if(ucErrTime>250)
      if(ucErrTime>2)
      {
         //--IIC_Stop();
         
         IIC_SCL_PIN=0; 
         return 1;

      }
   }
   IIC_SCL_PIN=0; 
   
   return 0;  
} 


void IIC_Send_Byte(UINT8 txd)
{   
   
    UINT8 t;   
    SDA_OUT();        
    IIC_SCL_PIN=0; 
   
    for(t=0;t<8;t++)
    {              

         //if(txd&0x80)
         if((txd&0x80)>>7)
            IIC_SDA_PIN=1;
         else
            IIC_SDA_PIN=0;
         
         //txd<<=1;   
         
         delay_2us();    
         IIC_SCL_PIN=1;
         delay_2us(); 
         IIC_SCL_PIN=0;   
         delay_2us();

         txd<<=1;          
    }   
   
}        


UINT8 IIC_Read_Byte(UINT8 ack) 
{
   UINT8 i=0;
   UINT8 receive=0;
   
   SDA_IN();    
   
   for(i=0;i<8;i++ )
   {
      IIC_SCL_PIN=0; 
      delay_2us();
      IIC_SCL_PIN=1;
      
      receive<<=1;
      
      if(IIC_SDA_PIN==1) 
         receive++;   
      
      delay_1us(); 
  }      
   
  if (!ack)
    IIC_NAck(); 
  else
    IIC_Ack();  
   
  return receive;
}


void i2cslave_WriteOneByte(UINT8 iaddr, UINT8 idata1)
{		
		 
   IIC_Start();  

   IIC_Send_Byte(SLAVEADDR_SLA_SLA | SLAVEADDR_SLA_WR);  
   flg_addr_log = IIC_Wait_Ack(); 

   
   IIC_Send_Byte(iaddr);   
   IIC_Wait_Ack();  		
   
   IIC_Send_Byte(idata1); 
   IIC_Wait_Ack();  
   
  
   IIC_Stop(); 
   
//   if (flg_addr_log==0) 
//      iputs0("I2C write ok\r\n");   //--test
   
}

UINT8 i2cslave_ReadOneByte(UINT8 iaddr)
{				  
   UINT8 temp=0;		
    
   IIC_Start();  

   IIC_Send_Byte(SLAVEADDR_SLA_SLA | SLAVEADDR_SLA_WR);   
   IIC_Wait_Ack();	 
   
   IIC_Send_Byte(iaddr);    
   IIC_Wait_Ack();

   //--IIC_Stop(); 
       
   IIC_Start();  

   IIC_Send_Byte(SLAVEADDR_SLA_SLA | SLAVEADDR_SLA_RD);    
   IIC_Wait_Ack();	
   
   temp=IIC_Read_Byte(0);  //or 1
   IIC_Stop(); 

   return temp;
}


void main (void) 
{
   UINT8 sbuf1[10]={0};
   UINT8 sbuf2[10]={0};
   UINT8 stemp[20]={0};
   
   
   //uart0 init
   InitialUART0_Timer3(115200);
   TI = 1;
   //set_ES;					//For interrupt enable
   set_EA;	

   iputs0("start.........................................\r\n");
   

   //i2c init
   Init_I2C_soft();   
   
   Timer0_Delay1ms(1000);

   P12_Quasi_Mode;


   while(1)
   {			
      //iputs0("\n run...");  
      //Timer0_Delay1ms(1000);
      
      if(flg_addr_log==1)
      {
         flg_addr_log=0;
         iputs0("I2C 'Send SLA+W' error\r\n");
         
      }
      
      sbuf2[0]=0;
      i2cslave_WriteOneByte(0x8a, 6);
      Timer0_Delay1ms(50); 
      
      sbuf2[0] = i2cslave_ReadOneByte(0x8a);
      sprintf (stemp,"reg02 = %bu\r\n",sbuf2[0]); 
      iputs0(stemp);   
      Timer0_Delay1ms(100);
      
      
      sbuf2[0]=0;
      i2cslave_WriteOneByte(0x8a, 9);
      Timer0_Delay1ms(50); 
      
      sbuf2[0] = i2cslave_ReadOneByte(0x8a);
      sprintf (stemp,"reg02 = %bu\r\n",sbuf2[0]); 
      iputs0(stemp);   
      Timer0_Delay1ms(100);
      
   }   
		
}




 

