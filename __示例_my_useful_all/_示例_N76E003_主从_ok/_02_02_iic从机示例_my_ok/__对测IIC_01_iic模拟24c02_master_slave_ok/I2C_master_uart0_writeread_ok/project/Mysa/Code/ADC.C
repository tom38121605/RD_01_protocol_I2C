
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"


void main (void) 
{
   
   UINT16 BAND_value=0;
   UINT16 AIN_value=0;
   UINT16 iadcvalue=0;
   double iadc =0;
    
   
   InitialUART0_Timer1(115200);

   while(1)
   {
    
      
      Timer0_Delay1ms(500);
      printf ("\r\n");
       
                  
      //-------------BAND-----------------
      
      Enable_ADC_BandGap;	   
      
      
      clr_ADCF;
      set_ADCS;										 
      while(ADCF == 0);
      
//      printf ("BANDH = 0x%bx \r\n",ADCRH);
//      printf ("BANDL = 0x%bx \r\n",ADCRL);     

      BAND_value =  ADCRH ;
      BAND_value <<=  4 ;
      BAND_value |=  ADCRL & 0x0f ;      
      printf( "band: %d  \r\n", BAND_value); 
 
      
      Disable_ADC;        
      
      
      //-------------AIN4-----------------
      
      Enable_ADC_AIN4;	
       
      
      clr_ADCF;
      set_ADCS;							 

      while(ADCF == 0);
      
//      printf ("AINH = 0x%bx \r\n",ADCRH);
//      printf ("AINL = 0x%bx \r\n",ADCRL);
      
      AIN_value =  ADCRH ;
      AIN_value <<=  4 ;
      AIN_value |=  ADCRL & 0x0f ;      
      printf( "AIN4: %d  \r\n", AIN_value); 
      
      iadc = 1.22 * AIN_value / BAND_value * 1000;  //mv
      
      printf( "iadcvalue: %6.2f  \r\n", iadc); 
      
      iadcvalue = (UINT16)iadc;
      printf( "iadcvalue: %d  \r\n", iadcvalue);   
      
      
      Disable_ADC;  
      
   }
		
}




