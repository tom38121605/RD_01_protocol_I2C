CC = iccavr
CFLAGS =  -Id:\ICC\include\ -e -DATMEGA -DATMega16  -l -g -Mavr_enhanced 
ASFLAGS = $(CFLAGS)  -Wa-g
LFLAGS =  -Ld:\ICC\lib\ -g -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:16 -beeprom:1.512 -fihx_coff -S2
FILES = main.o 

prj1:	$(FILES)
	$(CC) -o prj1 $(LFLAGS) @prj1.lk   -lcatmega
main.o: d:/ICC/include/iom16v.h d:/ICC/include/macros.h d:/ICC/include/string.h d:/ICC/include/_const.h
main.o:	main.c
	$(CC) -c $(CFLAGS) main.c
