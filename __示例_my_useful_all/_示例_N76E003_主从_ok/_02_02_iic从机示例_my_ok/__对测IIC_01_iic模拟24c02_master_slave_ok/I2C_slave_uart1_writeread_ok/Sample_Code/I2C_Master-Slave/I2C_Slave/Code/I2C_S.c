

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"



#define EEPROM_SLA              0xE6 //0xA0   //--soft slave 

#define I2C_CLOCK               13


#define RESETDETECT  P00=~P00
#define DETECT_20US   set_WDCLR; Timer0_Delay10us(1);RESETDETECT;  Timer0_Delay10us(1);RESETDETECT 
#define DETECT_60US   set_WDCLR; Timer0_Delay10us(1);RESETDETECT;  Timer0_Delay10us(1);RESETDETECT; Timer0_Delay10us(1);RESETDETECT;  Timer0_Delay10us(1);RESETDETECT; Timer0_Delay10us(1);RESETDETECT;  Timer0_Delay10us(1);RESETDETECT 


#define DETECT_1MS    set_WDCLR; Timer2_Delay500us(1);RESETDETECT;  Timer2_Delay500us(1);RESETDETECT 
#define DETECT_10MS   DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS;DETECT_1MS



//UINT8 data_received[34], data_num = 0;
UINT8 data_received[64], data_num = 0;

char soutstr[30]={0};

UINT8 irxdata =0;
UINT8 isubaddr =0;


void iputs1(UINT8 *msg)
{
   while(*msg)
      Send_Data_To_UART1(*msg++);
}


void I2C_ISR(void) interrupt 6
{

    static UINT8 flg_firstdata=0; 
   
    switch (I2STAT)
    {
        case 0x00:
            STO = 1;
        
            break;

        case 0x60:   // SLAW addr 
            AA = 1;
        
            flg_firstdata=0;
        
            break;
				
        case 0x68:    //.
				P02 = 0;
        
            while(1);
            break;
        
        
        case 0x80:   //sub addr
        
            if(flg_firstdata==0)
            {
               isubaddr = I2DAT; 
               AA = 1;
               flg_firstdata=1;
               
               data_num = isubaddr;
               
//sprintf(soutstr, "the sub addr is %xH \r\n", isubaddr);
//iputs1(soutstr);    
               
            }
            //else if(flg_firstdata==1)
            else  
            {
               irxdata = I2DAT; 
               AA = 1;
               
//sprintf(soutstr, "the sub addr is %xH \r\n", irxdata);
//iputs1(soutstr);  
               
               data_received[data_num++]=irxdata;

               
            }        
        
            break;      
        

        case 0x88:
        
            data_received[data_num] = I2DAT;
            data_num = 0;
            AA = 1;
        
            break;


        case 0xA0:     //.
            
            AA = 1;
            break;

        
        case 0xA8:    //SLAR addr
        
            data_num=isubaddr;
        
            I2DAT = data_received[data_num];
            data_num++;
            AA = 1;
        
            break;        
        
        case 0xB8:  // read data request           
        
            I2DAT = data_received[data_num];
            data_num++;
            AA = 1;
        
            break;

        case 0xC0:      //.
            AA = 1;
            break; 

        case 0xC8:      //.    
        
            AA = 1;
 
            break;        
    }

    SI = 0;
    
}
 
void Init_I2C_SLAVE(void)
{
    P13_Quasi_Mode;                         //set SCL (P13) is Quasi mode
    P14_Quasi_Mode;                         //set SDA (P14) is Quasi mode
    
    SDA = 1;                                //set SDA and SCL pins high
    SCL = 1;
    
    //--set_P0SR_6;                             //set SCL (P06) is  Schmitt triggered input select.
    
    set_EI2C;                               //enable I2C interrupt by setting IE1 bit 0
    set_EA;

    I2ADDR = EEPROM_SLA;                    //define own slave address
    set_I2CEN;                              //enable I2C circuit
    set_AA;
}

 
void main(void)
{

   Set_All_GPIO_Quasi_Mode;

   //uart0 init
   InitialUART1_Timer3(115200);
   TI = 1;   

   //set_ES;			
   set_EA;	

   //iputs1("\n 12345");    

   Init_I2C_SLAVE();    
   

   while (1)
   {
      //iputs1("\n run...");  
      //Timer0_Delay1ms(1000);  

      DETECT_10MS;     
      
   }
 
}




