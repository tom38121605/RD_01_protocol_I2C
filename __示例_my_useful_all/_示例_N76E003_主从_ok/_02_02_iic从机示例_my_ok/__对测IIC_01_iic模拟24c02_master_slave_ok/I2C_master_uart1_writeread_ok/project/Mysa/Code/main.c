
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include <string.h>


unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x80;
unsigned char xdata xtemp _at_ 0x80;


#define RESETDETECT  P00=~P00
#define DETECT_20US   set_WDCLR; Timer0_Delay10us(1);RESETDETECT;  Timer0_Delay10us(1);RESETDETECT 
#define DETECT_60US   set_WDCLR; Timer0_Delay10us(1);RESETDETECT;  Timer0_Delay10us(1);RESETDETECT; Timer0_Delay10us(1);RESETDETECT;  Timer0_Delay10us(1);RESETDETECT; Timer0_Delay10us(1);RESETDETECT;  Timer0_Delay10us(1);RESETDETECT 


#define DETECT_1MS    set_WDCLR; Timer2_Delay500us(1);RESETDETECT;  Timer2_Delay500us(1);RESETDETECT 
#define DETECT_10MS   DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS



//uart
UINT8  irxdata1=0;

//i2c
#define I2C_CLOCK_400KHz    9

#define EEPROM_SLA              0xA0   //0xAE  24c02 + A2A1A0 
#define EEPROM_WR               0
#define EEPROM_RD               1

//#define LED                     P3

#define PAGE_SIZE               32
#define PAGE_NUMBER             4

//#define ERROR_CODE              0x78
//#define TEST_OK                 0x00

bit I2C_Reset_Flag;


#define EEPROM_SLA   0xA0   //at24c02


UINT8 data_received[64];
UINT8  data_num = 0;

char soutstr[30]={0};

UINT8 irxdata =0;
UINT8 isubaddr =0;

 
void iputs1(UINT8 *msg)
{
   while(*msg)
      Send_Data_To_UART1(*msg++);
}

 
void Init_I2C(void)
{
   P13_OpenDrain_Mode;				 
   P14_OpenDrain_Mode;				 

   // Set I2C clock rate  
   I2CLK =  I2C_CLOCK_400KHz; 

   // Enable I2C  
   set_I2CEN;                                   
}

void I2C_SI_Check(void)
{
   if (I2STAT == 0x00)
   {
      I2C_Reset_Flag = 1;
      set_STO;
      SI = 0;
      if(SI)
      {
         clr_I2CEN;
         set_I2CEN;
         clr_SI;
         clr_I2CEN;		
      } 	
   }	
}


void at24c02_write( UINT8 iaddr, UINT8 *sbuf, UINT8 ilen )
{
   
    UINT8  u8Count;

    /* Step1 */
    set_STA;                                /* Send Start bit to I2C EEPROM */         
    clr_SI;
    while (!SI);
   
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        I2C_Reset_Flag = 1;
        iputs1("I2C 'Send STA' error\r\n");
        goto Write_Error_Stop;
    }
    

    /* Step2 */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = EEPROM_SLA | EEPROM_WR;         /* Send (SLA+W) to EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */             
    {
        I2C_Reset_Flag = 1;
        iputs1("I2C 'Send SLA+W' error\r\n");
        goto Write_Error_Stop;
    }

    /* Step3 */
    I2DAT = iaddr;             /* Send EEPROM's  Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        I2C_Reset_Flag = 1;
        iputs1("I2C 'Send sub address' error\r\n");
        goto Write_Error_Stop;
    }
 

    /* Step5 */
    /* Write data to I2C EEPROM */ 

    for (u8Count = 0; u8Count < ilen; u8Count++)
    {
    
      I2DAT = sbuf[u8Count];                    /* Send data to EEPROM */
      clr_SI;
      while (!SI);
      if (I2STAT != 0x28)                 /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
      {
         I2C_Reset_Flag = 1;
         iputs1("I2C 'Write Data' error\r\n");
         goto Write_Error_Stop;
      }   
   }
 
   
   /* Step6 */

   set_STO;                           
   clr_SI;
   while (STO);
   

//iputs1("I2C write ok\r\n");   //--test
   
   
 
Write_Error_Stop: 
   if (I2C_Reset_Flag)
   {
      I2C_SI_Check();
      I2C_Reset_Flag	= 0;
      iputs1("I2C Write error, test stop\r\n");
   }		
		
}



void at24c02_read( UINT8 iaddr, UINT8 *sbuf, UINT8 ilen )
{
    UINT8  u8Count; 
   

    /* Step1 */
    set_STA;                                /* Send Start bit to I2C EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        I2C_Reset_Flag = 1;
				iputs1("I2C 'Send STA' error\r\n");
				goto Read_Error_Stop;
    }

    /* Step2 */
    I2DAT = (EEPROM_SLA | EEPROM_WR);       /* Send (SLA+W) to EEPROM */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */    
    clr_SI;
    while (!SI);
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */              
    {
      I2C_Reset_Flag = 1;
      iputs1("I2C 'Send SLA+W' error\r\n");
      goto Read_Error_Stop;
    }

    /* Step3 */
    I2DAT = iaddr;             /* Send I2C EEPROM's Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */              
    {
      I2C_Reset_Flag = 1;
      iputs1("I2C 'Send I2C High Byte Address' error\r\n");
      goto Read_Error_Stop;
    }
 
    /* Step5 */
    set_STA;                                /* Repeated START */
    clr_SI; 
    while (!SI);
    if (I2STAT != 0x10)                     /* 0x10: A repeated START condition has been transmitted */
    {
      I2C_Reset_Flag = 1;
      iputs1("I2C 'Send STA' error\r\n");
      goto Read_Error_Stop;
    }

    /* Step6 */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = (EEPROM_SLA | EEPROM_RD);       /* Send (SLA+R) to EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x40)                     /* 0x40:  SLA+R has been transmitted; ACK has been received */              
    {
      I2C_Reset_Flag = 1;
      iputs1("I2C 'Send SLA+R' error\r\n");
      goto Read_Error_Stop;
    }

    /* Step7 */                             /* Verify I2C EEPROM data */
    for (u8Count = 0; u8Count <ilen; u8Count++)
    {
        set_AA;                             /* Set Assert Acknowledge Control Bit */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x50)                 /* 0x50:Data byte has been received; NOT ACK has been returned */              
        {
            I2C_Reset_Flag = 1;
            iputs1("I2C 'No Ack' error\r\n");
            goto Read_Error_Stop;
        }
       
        sbuf[u8Count] = I2DAT;
    }

    /* Step8 */
    clr_AA;                                 /* Send a NACK to disconnect 24xx64 */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x58)                     /* 0x58:Data byte has been received; ACK has been returned */
    {
        I2C_Reset_Flag = 1;
        iputs1("I2C 'Ack' error\r\n");
        goto Read_Error_Stop;
    }
    
	/* Step9 */    
	 clr_SI;
    set_STO;
    
    while (STO);
    
    
    
//iputs1("I2C Read ok\r\n");   //--test
    
    
 
Read_Error_Stop: 
		if (I2C_Reset_Flag)
		{
         I2C_SI_Check();
         iputs1("I2C Read error, test stop\r\n");
         I2C_Reset_Flag = 0;
		}
}


void main (void) 
{
   UINT8 str1[20];
   
   
   //UINT8 flg_readdata=0;   
   
   //uart1 init
   InitialUART1_Timer3(115200);
   TI_1 = 1;

   //set_ES_1;					//For interrupt enable
   set_EA;	

   iputs1("12345\r\n");

   //i2c init
   Init_I2C();
   
   //Timer0_Delay1ms(1000);  
   DETECT_10MS;  //1000ms


   while(1)
   {			
//      iputs1("\n run...");  
//      Timer0_Delay1ms(1000);
      

      P00=1;
      
      //-------iic slave writeread test  ---------      
 
      at24c02_write(2, "abcde\r\n", 8); DETECT_10MS;  
      at24c02_read(2, str1, 8);       
      
      iputs1(str1);  
      DETECT_10MS;       
      

      at24c02_write(2, "67890\r\n", 8); DETECT_10MS;  
      at24c02_read(2, str1, 8);       
      
      iputs1(str1);  
      DETECT_10MS;       

      //-------iic slave writeread test  --end-------            
      
   }   
		
}


#define REG_WDCLR      0x09
void write_watchdogreg (void) 
{
   UINT8 sbuf[20]={0};

   sbuf[0]=1;
   
   at24c02_write(REG_WDCLR, sbuf, 1); 
   DETECT_10MS; 

}  


void SerialPort1_ISR(void) interrupt 15 
{
   if (RI_1==1) 
   {                                      
      clr_RI_1;    
      
      irxdata1 = SBUF_1;
      Send_Data_To_UART1(irxdata1);
   }

   if(TI_1==1)
       clr_TI_1;                           
 
}





