#include<iom16v.h>		//在此设定avr类MCU的头文件
#include<macros.h>
#include"xd.h"
#include"xdprj.h"



//参数:1)为要发送数据的起始地址, 2)a为数据长度
void txdpo(uchar *txdbuf, uchar a)
{   
    for(;a>0;a--)
    {   UDR=*txdbuf;
    	txdbuf++;
        while(!(UCSRA & BIT(UDRE)));
    }
}



