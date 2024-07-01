#ifdef XDmain
    #define XD_EXT

#else
    #define XD_EXT extern

#endif

XD_EXT uchar syserr;


XD_EXT uchar txd_buf[70];	//用于通过串口向PC机传送读写数据及状态



extern void txdpo(uchar *txdbuf, uchar a);





//-------------以下函数供其它程序调用-------------------------------------------
extern void wt24c(uchar *p_rsc, uint ad_dst, uint num);     //把数据写入24cxx
extern void rd24c(uchar *p_dst, uint ad_rsc, uint num);     //从24cxx读出数据
//------------------------------------------------------------------------------

//-----毫秒级延时;包含于delay.lib--------------
extern void tms(uchar t);
//---------------------------------------------

extern void setreg_m16(void);	//初始化cpu