

#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"



#define I2C_CLOCK               13

//#define EEPROM_SLA              0xA4
#define EEPROM_SLA              0xA0


//UINT8 data_received[34], data_num = 0;
UINT8 data_received[64], data_num = 0;

char soutstr[30]={0};

UINT8 irxdata =0;
UINT8 isubaddr =0;


void iputs0(UINT8 *msg)
{
   while(*msg)
      Send_Data_To_UART0(*msg++);
}



void I2C_ISR(void) interrupt 6
{

    static UINT8 islavecount=0; 
   
    switch (I2STAT)
    {
        case 0x00:
            STO = 1;
        
            break;

        case 0x60:   // SLAW addr 
            AA = 1;
        
            islavecount=0;
        
            break;
				
        case 0x68:    //.
				P02 = 0;
        
            while(1);
            break;
        
        
        case 0x80:   //sub addr
        
            if(islavecount==0)
            {
               isubaddr = I2DAT; 
               AA = 1;
               islavecount++;
               
               data_num = isubaddr;
               
//sprintf(soutstr, "the sub addr is %xH \r\n", isubaddr);
//iputs0(soutstr);    
               
            }
            //else if(islavecount==1)
            else  
            {
               irxdata = I2DAT; 
               AA = 1;
               
//sprintf(soutstr, "the sub addr is %xH \r\n", irxdata);
//iputs0(soutstr);  
               
               data_received[data_num++]=irxdata;
               
               islavecount++;
               
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

//        case 0xA8:    //SLAR addr
//        
//            I2DAT = data_received[data_num];
//            data_num++;
//            AA = 1;
//        
//            break;
        
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


void Init_I2C(void)
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


 
void main(void)
{

   Set_All_GPIO_Quasi_Mode;

   //uart0 init
   InitialUART0_Timer3(115200);
   TI = 1;   

   //set_ES;			
   set_EA;	

   //iputs0("\n 12345");    


   Init_I2C();                                 

   while (1)
   {
      //iputs0("\n run...");  
      Timer0_Delay1ms(1000);   
      
   }
 
}




