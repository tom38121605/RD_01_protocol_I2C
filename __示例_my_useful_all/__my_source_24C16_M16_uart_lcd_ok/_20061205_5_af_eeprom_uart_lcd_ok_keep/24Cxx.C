//#include <iom128v.h>
#include <iom16v.h>
#include <macros.h>
#include "xd.h"
#include "xdprj.h"
#include "delay.h"


//------在此设定芯片型号------
//#define e2prom 32		// <---在此设定芯片型号, 1代表24C01; 16代表24C16; 512代表24C512
#define e2prom 16		// <---在此设定芯片型号, 1代表24C01; 16代表24C16; 512代表24C512

#if e2prom==1
	#define PAGE_SIZE 8
	#define PAGE_EXP  3
	#define SIZE 0x007f
#elif e2prom==2
	#define PAGE_SIZE 8
	#define PAGE_EXP  3
	#define SIZE 0x00ff
#elif e2prom==4
	#define PAGE_SIZE 16
	#define PAGE_EXP  4
	#define SIZE 0x01ff
#elif e2prom==8
	#define PAGE_SIZE 16
	#define PAGE_EXP  4
	#define SIZE 0x03ff
#elif e2prom==16
	#define PAGE_SIZE 16
	#define PAGE_EXP  4
	#define SIZE 0x07ff
#elif e2prom==32
	#define PAGE_SIZE 32
	#define PAGE_EXP  5
	#define SIZE 0x0fff
#elif e2prom==64
	#define PAGE_SIZE 32
	#define PAGE_EXP  5
	#define SIZE 0x1fff
#elif e2prom==128
	#define PAGE_SIZE 64
	#define PAGE_EXP  6
	#define SIZE 0x3fff
#elif e2prom==256
	#define PAGE_SIZE 64
	#define PAGE_EXP  6
	#define SIZE 0x7fff
#elif e2prom==512
	#define PAGE_SIZE 128
	#define PAGE_EXP  7
	#define SIZE 0xffff
#endif
//--------------------------

//--------在此设定芯片地址-------
#define W_ADD_COM 0xa0	//写字节命令及器件地址(根据地址实际情况改变), 1010 A2 A1 A0 0
#define R_ADD_COM 0xa1	//读命令字节及器件地址(根据地址实际情况改变), 1010 A2 A1 A0 1
//-------------------------------


#define SLAW	0x18	//SLA_W 已正常发送代码,判断器件是否正常应答的常量.

//-----在此改变预置错误号-----
#define ERR_SLAW	ERR_10	//写字节命令及器件地址错, 在此也就是读写器件错!!
//---------------------------


//-----------4个I2总线公用函数, 可供其它I2总线器件的程序调用--------------
void i2cstart(void);	//总线上起动开始条件
uchar i2cwt(uchar a);	//把一个字节数据输入器件, 返回TWI状态
uchar i2crd(void);		//i2c读要调用的函数
void i2cstop(void);		//总线上起动停止条件 
//------------------------------------------------------------------------

uchar * wt24c_fc(uchar *p, uint ad, uchar n);	//向24Cxx写入数据wt24c_h()所要调用的函数

//向24Cxx写入数据
//参数: *p_rsc要输出数据的主机内存地址指针; ad_dst要写入数据的i2c的地址(双字节); num数据个数
//参数条件: ad_dst: ad_dst+(num-1)不能大于器件的最高地址; num必须>0;
void wt24c(uchar *p_rsc, uint ad_dst, uint num)
{   uint n;

    //取得第一次发送的字节数(应该是<=1页的字节数)
    n=ad_dst/PAGE_SIZE;	 //确定地址与块地址的差  n--完整块的数量
	if(n) 
	   n=(ulong)PAGE_SIZE*(n+1)-ad_dst;	
	else 
	   n=PAGE_SIZE-ad_dst;
		
	//开始写数据
    if(n>=num)	//如果ad_dst所在的数据块的末尾地址 >= ad_dst + num, 就直接写入num个数据
    {	wt24c_fc(p_rsc, ad_dst, num);
    	if(syserr!=0) return;
    }
    else	   //如果ad_dst所在的数据块末尾地址 < ad_dst + num, 就先写入ad_dst所在的数据块末尾地址与 ad_dst 之差个数据
    {   
	    //写第1页
	    p_rsc=wt24c_fc(p_rsc, ad_dst, n);
    	if(syserr!=0) return;
		
		num-=n;     //更新剩下数据个数
        ad_dst+=n;	//更新剩下数据的起始地址

        //把剩下数据写入器件
        while(num>=PAGE_SIZE)	//先按PAGE_SIZE为长度一页一页的写入
        {	p_rsc=wt24c_fc(p_rsc, ad_dst, PAGE_SIZE);
        	if(syserr!=0) return;
        	
            num-=PAGE_SIZE;		//更新剩余数据个数
        	ad_dst+=PAGE_SIZE;	//更新剩下数据的起始地址
		}
        
		//写最后1页
		if(num)		//把最后剩下的小于一个PAGE_SIZE长度的数据写入器件
			wt24c_fc(p_rsc, ad_dst, num);
    }
}

//从24cxx读出数据
//参数: *p_dst要读入数据的主机内存地址指针; ad_rsc要输出数据的i2c的地址(整形); num数据个数(整形)
//参数条件:  ad_dst+(num-1)不能大于器件的最高地址; num必须>0;
void rd24c(uchar *p_dst, uint ad_rsc, uint num)
{   uchar t=0;

	#if e2prom<32
	t=ad_rsc>>8;  
	t<<=1;        //左移1位
	#endif
		
	i2cstart();					//发送起始信号
		
	if(i2cwt(W_ADD_COM+t)==SLAW)//发送SLA_W, 写字节命令及器件地址
	{	
		#if e2prom>16
		i2cwt(ad_rsc>>8);		//ad_rsc的高位,  发送要读出数据的地址
		#endif
		i2cwt(ad_rsc);			//ad_rsc的低位
				
		i2cstart();				//再发送起始信号
		i2cwt(R_ADD_COM+t);		//发送SLA_R, 读命令字节及器件地址
				
		for(;num>0;num--)
		{   *p_dst=i2crd();		//从器件读出一个字节
			p_dst++;
		}
	}
	else syserr=ERR_SLAW;		//写字节命令及器件地址错或对方无应答
		
	i2cstop();	
}

//向24Cxx写入数据wt24c_h()所要调用的函数
//返回写入n个字节后的主机内存指针
uchar * wt24c_fc(uchar *p, uint ad, uchar n)
{	uchar t=0;

	#if e2prom<32
	t=ad>>8;
	t<<=1;
	#endif
	
	i2cstart();					//发送起始信号
		
	if(i2cwt(W_ADD_COM+t)==SLAW) //发送SLA_W, 写字节命令及器件地址
	{	
		#if e2prom>16
		i2cwt(ad>>8);			 //ad_dst的高位到器件
		#endif
		i2cwt(ad);				 //ad_dst的低位到器件
			
		for(;n>0;n--)			 //发送要写入的数据
		{   i2cwt(*p);
			p++;
		}
	}
	else syserr=ERR_SLAW;		//写字节命令及器件地址错
	
	i2cstop();
    //tms(6);				   //延时6ms
	delay_nms(6);
	
	return(p);
	
}

//-------------------------------以下为其它I2总线器件可调用的函数--------------------------

//总线上起动开始条件
void i2cstart(void)
{ 
	TWCR= BIT(TWINT) | BIT(TWSTA) | BIT(TWEN); 
   	while (!(TWCR & BIT(TWINT)));
} 

//把一个字节数据输入器件, 返回TWI状态
uchar i2cwt(uchar a)
{ 
	TWDR = a; 
   	TWCR = BIT(TWINT) | BIT(TWEN); 
   	while (!(TWCR & BIT(TWINT)));
   	_NOP();
   	return(TWSR&0b11111000);
} 

//i2c读要调用的函数
//从器件读出一个字节
uchar i2crd(void)
{
   	TWCR= BIT(TWINT) | BIT(TWEA) | BIT(TWEN); 
   	while (!(TWCR & BIT(TWINT)));
   	return(TWDR);
} 

//总线上起动停止条件 
void i2cstop(void) 
{ 
   TWCR = BIT(TWINT) | BIT(TWSTO) | BIT(TWEN); 
} 


