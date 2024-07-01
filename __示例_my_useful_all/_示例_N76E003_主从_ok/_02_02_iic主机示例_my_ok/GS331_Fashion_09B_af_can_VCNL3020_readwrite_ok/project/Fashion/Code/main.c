#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include <string.h>


unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x80;
unsigned char xdata xtemp _at_ 0x80;
 

//i2c
#define I2C_CLOCK_400KHz    9 
#define EEPROM_SLA          0x26   

#define EEPROM_WR               0
#define EEPROM_RD               1

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
        iputs0("I2C 'Send STA' error\r\n");
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
        //iputs0("I2C 'Send SLA+W' error\r\n");
        goto Write_Error_Stop;
    }

    /* Step3 */
    I2DAT = iaddr;             /* Send EEPROM's  Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        I2C_Reset_Flag = 1;
        //iputs0("I2C 'Send sub address' error\r\n");
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
         //iputs0("I2C 'Write Data' error\r\n");
         goto Write_Error_Stop;
      }   
   }
 
   
   /* Step6 */

   set_STO;                           
   clr_SI;
   while (STO);
   

//--iputs0("I2C write ok\r\n");   //--test
   
   
 
Write_Error_Stop: 
   if (I2C_Reset_Flag)
   {
      I2C_SI_Check();
      I2C_Reset_Flag	= 0;
      //iputs0("I2C Write error, test stop\r\n");
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
				iputs0("I2C 'Send STA' error\r\n");
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
      iputs0("I2C 'Send SLA+W' error\r\n");
      goto Read_Error_Stop;
    }

    /* Step3 */
    I2DAT = iaddr;             /* Send I2C EEPROM's Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */              
    {
      I2C_Reset_Flag = 1;
      iputs0("I2C 'Send I2C High Byte Address' error\r\n");
      goto Read_Error_Stop;
    }
 
    /* Step5 */
    set_STA;                                /* Repeated START */
    clr_SI; 
    while (!SI);
    if (I2STAT != 0x10)                     /* 0x10: A repeated START condition has been transmitted */
    {
      I2C_Reset_Flag = 1;
      iputs0("I2C 'Send STA' error\r\n");
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
      iputs0("I2C 'Send SLA+R' error\r\n");
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
            iputs0("I2C 'No Ack' error\r\n");
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
        iputs0("I2C 'Ack' error\r\n");
        goto Read_Error_Stop;
    }
    
	/* Step9 */    
	 clr_SI;
    set_STO;
    
    while (STO);
    
    
    
//iputs0("I2C Read ok\r\n");   //--test
    
    
 
Read_Error_Stop: 
		if (I2C_Reset_Flag)
		{
         I2C_SI_Check();
         iputs0("I2C Read error, test stop\r\n");
         I2C_Reset_Flag = 0;
		}
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

   iputs0("start.................................\r\n");
   

   //i2c init
   Init_I2C();   
   
   Timer0_Delay1ms(1000);


   while(1)
   {			
      //iputs0("\n run...");  
      //Timer0_Delay1ms(100);
      
      sbuf1[0] = 8; sbuf2[0]=0; 
      at24c02_write(0x8a, sbuf1, 1);
      Timer0_Delay1ms(10);         
      
      at24c02_read(0x8a, sbuf2, 1);    
      sprintf (stemp,"reg02 = %bu\r\n",sbuf2[0]); 
      iputs0(stemp);

      Timer0_Delay1ms(10);
      
      sbuf1[0] = 9; sbuf2[0]=0;  
      at24c02_write(0x8a, sbuf1, 1);
      Timer0_Delay1ms(10);         
      
      at24c02_read(0x8a, sbuf2, 1);    
      sprintf (stemp,"reg02 = %bu\r\n",sbuf2[0]); 
      iputs0(stemp);    

      Timer0_Delay1ms(10);
      
   }   
		
}

 

