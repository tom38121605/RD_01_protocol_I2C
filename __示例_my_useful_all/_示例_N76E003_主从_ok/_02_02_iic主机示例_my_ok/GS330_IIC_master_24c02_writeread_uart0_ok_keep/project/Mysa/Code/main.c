
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"
#include <string.h>


unsigned char temp _at_ 0x08;
unsigned char idata itemp _at_ 0x80;
unsigned char xdata xtemp _at_ 0x80;



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

void Init_I2C_SLAVE(void)
{
    P13_Quasi_Mode;                         //set SCL (P13) is Quasi mode
    P14_Quasi_Mode;                         //set SDA (P14) is Quasi mode
    
    SDA = 1;                                //set SDA and SCL pins high
    SCL = 1;
    
    set_P0SR_6;                             //set SCL (P06) is  Schmitt triggered input select.
    
    set_EI2C;                               //enable I2C interrupt by setting IE1 bit 0
    set_EA;

    I2ADDR = EEPROM_SLA;                    //define own slave address
    set_I2CEN;                              //enable I2C circuit
    set_AA;
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
        iputs0("I2C 'Send SLA+W' error\r\n");
        goto Write_Error_Stop;
    }

    /* Step3 */
    I2DAT = iaddr;             /* Send EEPROM's  Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        I2C_Reset_Flag = 1;
        iputs0("I2C 'Send sub address' error\r\n");
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
         iputs0("I2C 'Write Data' error\r\n");
         goto Write_Error_Stop;
      }   
   }
 
   
   /* Step6 */

   set_STO;                           
   clr_SI;
   while (STO);
   

//iputs0("I2C write ok\r\n");   //--test
   
   
 
Write_Error_Stop: 
   if (I2C_Reset_Flag)
   {
      I2C_SI_Check();
      I2C_Reset_Flag	= 0;
      iputs0("I2C Write error, test stop\r\n");
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


UINT8 data_received[34], data_num = 0;


void I2C_ISR(void) interrupt 6
{
    switch (I2STAT)
    {
        case 0x00:
            STO = 1;
            break;

        case 0x60:
            AA = 1;
            //P3 = 0x60;
            break;
				
        case 0x68:
				P02 = 0;
            while(1);
            break;

        case 0x80:
            //P3 = 0x80;
            data_received[data_num] = I2DAT;
            data_num++;

            if (data_num == 34)
                AA = 0;
            else
                AA = 1;
            break;

        case 0x88:
            //P3 = 0x88;
            data_received[data_num] = I2DAT;
            data_num = 0;
            AA = 1;
            
            break;

        case 0xA0:
            //P3 = 0xA0;
            AA = 1;
            break;

        case 0xA8:
            //P3 = 0xA0;
            I2DAT = data_received[data_num];
            data_num++;
            AA = 1;
            break;
        
        case 0xB8:
            //P3 = 0xB8;
            I2DAT = data_received[data_num];
            data_num++;
            AA = 1;
            break;

        case 0xC0:
            AA = 1;
            break; 

        case 0xC8:
            //P3 = 0xC8;
            AA = 1;
            break;        
    }

    SI = 0;
//    while(STO);
}
 

void main (void) 
{
   UINT8 str1[20];
   UINT8 str2[8]="abcde\r\n";  //{0x55,0x56,0x57,0x58,0x59};
   UINT8 str3[8]="67890\r\n";  //{0x55,0x56,0x57,0x58,0x59};
   
   
   UINT8 flg_readdata=0;
   
   
   //uart0 init
   InitialUART0_Timer3(115200);
   TI = 1;

   //set_ES;					//For interrupt enable
   set_EA;	

   iputs0("12345\r\n");

   //i2c init
   Init_I2C();   
   
   Timer0_Delay1ms(1000);
   


   while(1)
   {			
//      iputs0("\n run...");  
//      Timer0_Delay1ms(1000);
      

      //-------iic slave writeread test  ---------
      
      at24c02_write(2, str2, 8); Timer0_Delay1ms(10);  
      at24c02_read(2, str1, 8);       
      
      iputs0(str1);  
      Timer0_Delay1ms(1000);       
      
      at24c02_write(2, str3, 8); Timer0_Delay1ms(10);  
      at24c02_read(2, str1, 8);       
      
      iputs0(str1);  
      Timer0_Delay1ms(1000);       

      //-------iic slave writeread test  --end-------
      
      
      
//      //-------24c02 writeread test  ---------
//      
//      at24c02_write(0, "abcde\r\n", 8);
//      Timer0_Delay1ms(10);   
//      at24c02_read(0, str1, 8);
//      
//      iputs0(str1);  
//      Timer0_Delay1ms(1000);         
//      
//  
//      at24c02_write(0, "67890\r\n", 8);
//      Timer0_Delay1ms(10);   
//      at24c02_read(0, str1, 8);  
//      
//      iputs0(str1);  
//      Timer0_Delay1ms(1000);   
//      

//      //-------24c02 writeread test  ---end------


               
   }   
		
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



