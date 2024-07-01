CC = iccavr
CFLAGS =  -IC:\ICC\include\ -e -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -LC:\ICC\lib\ -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = 7920.o delay.o Debug_com.o 24Cxx.o r_modstring.o usart.o r_modbyte.o modpublic.o 24CxxMain.o 

prj1:	$(FILES)
	$(CC) -o prj1 $(LFLAGS) @prj1.lk   -lcatmega
7920.o: E:\__test\_source/r_modbyte.h C:/ICC/include/iom16v.h C:/ICC/include/macros.h E:\__test\_source/7920.h C:/ICC/include/iom16v.h C:/ICC/include/macros.h E:\__test\_source/delay.h
7920.o:	E:\__test\_source\7920.c
	$(CC) -c $(CFLAGS) E:\__test\_source\7920.c
delay.o: C:/ICC/include/macros.h E:\__test\_source/delay.h
delay.o:	E:\__test\_source\delay.c
	$(CC) -c $(CFLAGS) E:\__test\_source\delay.c
Debug_com.o: C:/ICC/include/iom16v.h C:/ICC/include/macros.h E:\__test\_source/xd.h E:\__test\_source/xdprj.h
Debug_com.o:	E:\__test\_source\Debug_com.C
	$(CC) -c $(CFLAGS) E:\__test\_source\Debug_com.C
24Cxx.o: C:/ICC/include/iom16v.h C:/ICC/include/macros.h E:\__test\_source/xd.h E:\__test\_source/xdprj.h E:\__test\_source/delay.h
24Cxx.o:	E:\__test\_source\24Cxx.C
	$(CC) -c $(CFLAGS) E:\__test\_source\24Cxx.C
r_modstring.o: E:\__test\_source/r_modstring.h
r_modstring.o:	E:\__test\_source\r_modstring.c
	$(CC) -c $(CFLAGS) E:\__test\_source\r_modstring.c
usart.o: C:/ICC/include/iom16v.h C:/ICC/include/macros.h E:\__test\_source/delay.h E:\__test\_source/7920.h C:/ICC/include/iom16v.h C:/ICC/include/macros.h
usart.o:	E:\__test\_source\usart.c
	$(CC) -c $(CFLAGS) E:\__test\_source\usart.c
r_modbyte.o: E:\__test\_source/r_modbyte.h C:/ICC/include/iom16v.h C:/ICC/include/macros.h
r_modbyte.o:	E:\__test\_source\r_modbyte.c
	$(CC) -c $(CFLAGS) E:\__test\_source\r_modbyte.c
modpublic.o: E:\__test\_source/modpublic.h C:/ICC/include/iom16v.h C:/ICC/include/macros.h
modpublic.o:	E:\__test\_source\modpublic.c
	$(CC) -c $(CFLAGS) E:\__test\_source\modpublic.c
24CxxMain.o: C:/ICC/include/iom16v.h C:/ICC/include/macros.h E:\__test\_source/xd.h E:\__test\_source/xdprj.h E:\__test\_source/7920.h C:/ICC/include/iom16v.h C:/ICC/include/macros.h E:\__test\_source/usart.h E:\__test\_source/delay.h
24CxxMain.o:	E:\__test\_source\24CxxMain.c
	$(CC) -c $(CFLAGS) E:\__test\_source\24CxxMain.c
