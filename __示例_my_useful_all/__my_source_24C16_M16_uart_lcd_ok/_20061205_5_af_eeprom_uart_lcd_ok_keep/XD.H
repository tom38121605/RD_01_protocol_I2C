#ifndef MCU_MODEL
	#define  MCU_MODEL avr		//<----在此设定mcu类型, 51代表51系列; avr代表avr系列
#endif


#if MCU_MODEL==51
    typedef unsigned char uchar;            //无符号字符型
    typedef unsigned char idata iuchar;     //间接访问无符号字符型
    typedef signed char schar;              //有符号字符型
    typedef signed char idata ischar;       //间接访问有符号字符型
    typedef unsigned int uint;              //无符号整型
    typedef unsigned int idata iuint;       //间接访问无符号整型
    typedef signed int sint;                //有符号整型
    typedef signed int idata isint;         //间接访问有符号整型
    typedef unsigned long ulong;            //无符号长整型
    typedef unsigned long idata iulong;     //间接访问无符号长整型
    typedef signed long slong;              //有符号长整型
    typedef signed long idata islong;       //间接访问有符号长整型
    
    #define _NOP() _nop_()
    
    //------定义程序存储器说明符----
	#define CHAR_CODE uchar code
	
#elif MCU_MODEL==avr
	typedef unsigned char uchar;            //无符号字符型
	typedef signed char schar;              //有符号字符型
	typedef unsigned int uint;              //无符号整型
	typedef signed int sint;                //有符号整型
	typedef unsigned long ulong;            //无符号长整型
	typedef signed long slong;              //有符号长整型
	
	//------定义程序存储器说明符----
	#define CHAR_CODE const uchar
	
#endif

/*
typedef struct
{   unsigned bit0 : 1 ;
    unsigned bit1 : 1 ;
    unsigned bit2 : 1 ;
    unsigned bit3 : 1 ;
    unsigned bit4 : 1 ;
    unsigned bit5 : 1 ;
    unsigned bit6 : 1 ;
    unsigned bit7 : 1 ;
}bit_field;

#define GET_BITFIELD(addr) (*((volatile  bit_field *) (addr)))
*/

struct datetime {uchar year, month, day, hour, minute, second;};    //定义一个日期时间结构类型,年月日时分秒
struct date {uchar year, month, day;};                              //定义一个日期结构类型,年月日
struct timeHMS {uchar hour, minute, second;};	//时间结构类型,时分秒
struct timeHM {uchar hour, minute;};			//时间结构类型,时分
struct timeMS {uchar minute, second;};      	//时间结构类型,分秒

#define TRUE 1
#define FALSE 0
#define HIGH 1
#define LOW 0

#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15
#define G 16
#define H 17
#define I 18
#define J 19
#define K 20
#define L 21
#define M 22
#define N 23
#define O 24
#define P 25
#define Q 26
#define R 27
#define S 28
#define T 29
#define U 30
#define V 31
#define W 32
#define X 33
#define Y 34
#define Z 35
#define HEN 36
#define DEN 37
#define BLACK 38
//uchar code duan_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x3d,0x76,0x05,0x0d,0x7a,0x38,0x55,0x54,0x5c,0x73,0x67,0x70,0x6d,0x78,0x3e,0x62,0x6a,0x57,0x6e,0x1b,0x40,0x48,0x00};
                         // 0    1    2    3    4    5    6    7    8    9    A    b    C    d    E    F    G    H    i    j    k    L    m    n    o    p    q    r    S    t    U    v    w    x    y    z    -    =    黑   
                         //                                                   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38
/*
uchar code duan_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x3d,0x76,0x05,0x0d,
				       // 0    1    2    3    4    5    6    7    8    9    A    b    C    d    E    F    G    H    i    j
				       //                                                   10   11   12   13   14   15   16   17   18   19
               	       0x7a,0x38,0x55,0x54,0x5c,0x73,0x67,0x70,0x6d,0x78,0x3e,0x62,0x6a,0x57,0x6e,0x1b,0x40,0x48,0x00};
                      // k    L    m    n    o    p    q    r    S    t    U    v    w    x    y    z    -    =    黑   
                      // 20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38
*/


#if MCU_MODEL==51
    #define b00000000 0x00
    #define b00000001 0x01
    #define b00000010 0x02
    #define b00000011 0x03
    #define b00000100 0x04
    #define b00000101 0x05
    #define b00000110 0x06
    #define b00000111 0x07
    #define b00001000 0x08
    #define b00001001 0x09
    #define b00001010 0x0A
    #define b00001011 0x0B
    #define b00001100 0x0C
    #define b00001101 0x0D
    #define b00001110 0x0E
    #define b00001111 0x0F
    
    #define b00010000 0x10
    #define b00010001 0x11
    #define b00010010 0x12
    #define b00010011 0x13
    #define b00010100 0x14
    #define b00010101 0x15
    #define b00010110 0x16
    #define b00010111 0x17
    #define b00011000 0x18
    #define b00011001 0x19
    #define b00011010 0x1A
    #define b00011011 0x1B
    #define b00011100 0x1C
    #define b00011101 0x1D
    #define b00011110 0x1E
    #define b00011111 0x1F
    
    #define b00100000 0x20
    #define b00100001 0x21
    #define b00100010 0x22
    #define b00100011 0x23
    #define b00100100 0x24
    #define b00100101 0x25
    #define b00100110 0x26
    #define b00100111 0x27
    #define b00101000 0x28
    #define b00101001 0x29
    #define b00101010 0x2A
    #define b00101011 0x2B
    #define b00101100 0x2C
    #define b00101101 0x2D
    #define b00101110 0x2E
    #define b00101111 0x2F
    
    #define b00110000 0x30
    #define b00110001 0x31
    #define b00110010 0x32
    #define b00110011 0x33
    #define b00110100 0x34
    #define b00110101 0x35
    #define b00110110 0x36
    #define b00110111 0x37
    #define b00111000 0x38
    #define b00111001 0x39
    #define b00111010 0x3A
    #define b00111011 0x3B
    #define b00111100 0x3C
    #define b00111101 0x3D
    #define b00111110 0x3E
    #define b00111111 0x3F
    
    #define b01000000 0x40
    #define b01000001 0x41
    #define b01000010 0x42
    #define b01000011 0x43
    #define b01000100 0x44
    #define b01000101 0x45
    #define b01000110 0x46
    #define b01000111 0x47
    #define b01001000 0x48
    #define b01001001 0x49
    #define b01001010 0x4A
    #define b01001011 0x4B
    #define b01001100 0x4C
    #define b01001101 0x4D
    #define b01001110 0x4E
    #define b01001111 0x4F
    
    #define b01010000 0x50
    #define b01010001 0x51
    #define b01010010 0x52
    #define b01010011 0x53
    #define b01010100 0x54
    #define b01010101 0x55
    #define b01010110 0x56
    #define b01010111 0x57
    #define b01011000 0x58
    #define b01011001 0x59
    #define b01011010 0x5A
    #define b01011011 0x5B
    #define b01011100 0x5C
    #define b01011101 0x5D
    #define b01011110 0x5E
    #define b01011111 0x5F
    
    #define b01100000 0x60
    #define b01100001 0x61
    #define b01100010 0x62
    #define b01100011 0x63
    #define b01100100 0x64
    #define b01100101 0x65
    #define b01100110 0x66
    #define b01100111 0x67
    #define b01101000 0x68
    #define b01101001 0x69
    #define b01101010 0x6A
    #define b01101011 0x6B
    #define b01101100 0x6C
    #define b01101101 0x6D
    #define b01101110 0x6E
    #define b01101111 0x6F
    
    #define b01110000 0x70
    #define b01110001 0x71
    #define b01110010 0x72
    #define b01110011 0x73
    #define b01110100 0x74
    #define b01110101 0x75
    #define b01110110 0x76
    #define b01110111 0x77
    #define b01111000 0x78
    #define b01111001 0x79
    #define b01111010 0x7A
    #define b01111011 0x7B
    #define b01111100 0x7C
    #define b01111101 0x7D
    #define b01111110 0x7E
    #define b01111111 0x7F
    
    #define b10000000 0x80
    #define b10000001 0x81
    #define b10000010 0x82
    #define b10000011 0x83
    #define b10000100 0x84
    #define b10000101 0x85
    #define b10000110 0x86
    #define b10000111 0x87
    #define b10001000 0x88
    #define b10001001 0x89
    #define b10001010 0x8A
    #define b10001011 0x8B
    #define b10001100 0x8C
    #define b10001101 0x8D
    #define b10001110 0x8E
    #define b10001111 0x8F
    
    #define b10010000 0x90
    #define b10010001 0x91
    #define b10010010 0x92
    #define b10010011 0x93
    #define b10010100 0x94
    #define b10010101 0x95
    #define b10010110 0x96
    #define b10010111 0x97
    #define b10011000 0x98
    #define b10011001 0x99
    #define b10011010 0x9A
    #define b10011011 0x9B
    #define b10011100 0x9C
    #define b10011101 0x9D
    #define b10011110 0x9E
    #define b10011111 0x9F
    
    #define b10100000 0xA0
    #define b10100001 0xA1
    #define b10100010 0xA2
    #define b10100011 0xA3
    #define b10100100 0xA4
    #define b10100101 0xA5
    #define b10100110 0xA6
    #define b10100111 0xA7
    #define b10101000 0xA8
    #define b10101001 0xA9
    #define b10101010 0xAA
    #define b10101011 0xAB
    #define b10101100 0xAC
    #define b10101101 0xAD
    #define b10101110 0xAE
    #define b10101111 0xAF
    
    #define b10110000 0xB0
    #define b10110001 0xB1
    #define b10110010 0xB2
    #define b10110011 0xB3
    #define b10110100 0xB4
    #define b10110101 0xB5
    #define b10110110 0xB6
    #define b10110111 0xB7
    #define b10111000 0xB8
    #define b10111001 0xB9
    #define b10111010 0xBA
    #define b10111011 0xBB
    #define b10111100 0xBC
    #define b10111101 0xBD
    #define b10111110 0xBE
    #define b10111111 0xBF
    
    #define b11000000 0xC0
    #define b11000001 0xC1
    #define b11000010 0xC2
    #define b11000011 0xC3
    #define b11000100 0xC4
    #define b11000101 0xC5
    #define b11000110 0xC6
    #define b11000111 0xC7
    #define b11001000 0xC8
    #define b11001001 0xC9
    #define b11001010 0xCA
    #define b11001011 0xCB
    #define b11001100 0xCC
    #define b11001101 0xCD
    #define b11001110 0xCE
    #define b11001111 0xCF
    
    #define b11010000 0xD0
    #define b11010001 0xD1
    #define b11010010 0xD2
    #define b11010011 0xD3
    #define b11010100 0xD4
    #define b11010101 0xD5
    #define b11010110 0xD6
    #define b11010111 0xD7
    #define b11011000 0xD8
    #define b11011001 0xD9
    #define b11011010 0xDA
    #define b11011011 0xDB
    #define b11011100 0xDC
    #define b11011101 0xDD
    #define b11011110 0xDE
    #define b11011111 0xDF
    
    #define b11100000 0xE0
    #define b11100001 0xE1
    #define b11100010 0xE2
    #define b11100011 0xE3
    #define b11100100 0xE4
    #define b11100101 0xE5
    #define b11100110 0xE6
    #define b11100111 0xE7
    #define b11101000 0xE8
    #define b11101001 0xE9
    #define b11101010 0xEA
    #define b11101011 0xEB
    #define b11101100 0xEC
    #define b11101101 0xED
    #define b11101110 0xEE
    #define b11101111 0xEF
    
    #define b11110000 0xF0
    #define b11110001 0xF1
    #define b11110010 0xF2
    #define b11110011 0xF3
    #define b11110100 0xF4
    #define b11110101 0xF5
    #define b11110110 0xF6
    #define b11110111 0xF7
    #define b11111000 0xF8
    #define b11111001 0xF9
    #define b11111010 0xFA
    #define b11111011 0xFB
    #define b11111100 0xFC
    #define b11111101 0xFD
    #define b11111110 0xFE
    #define b11111111 0xFF
#endif


#define ERR_1 1
#define ERR_2 2
#define ERR_3 3
#define ERR_4 4
#define ERR_5 5
#define ERR_6 6
#define ERR_7 7
#define ERR_8 8
#define ERR_9 9
#define ERR_10 10
#define ERR_11 11
#define ERR_12 12
#define ERR_13 13
#define ERR_14 14
#define ERR_15 15
#define ERR_16 16
#define ERR_17 17
#define ERR_18 18
#define ERR_19 19
#define ERR_20 20
#define ERR_21 21
#define ERR_22 22
#define ERR_23 23
#define ERR_24 24
#define ERR_25 25
#define ERR_26 26
#define ERR_27 27
#define ERR_28 28
#define ERR_29 29
#define ERR_30 30
#define ERR_31 31
#define ERR_32 32
#define ERR_33 33
#define ERR_34 34
#define ERR_35 35
#define ERR_36 36
#define ERR_37 37
#define ERR_38 38
#define ERR_39 39
#define ERR_40 40
#define ERR_41 41
#define ERR_42 42
#define ERR_43 43
#define ERR_44 44
#define ERR_45 45
#define ERR_46 46
#define ERR_47 47
#define ERR_48 48
#define ERR_49 49
#define ERR_50 50
#define ERR_51 51
#define ERR_52 52
#define ERR_53 53
#define ERR_54 54
#define ERR_55 55
#define ERR_56 56
#define ERR_57 57
#define ERR_58 58
#define ERR_59 59
#define ERR_60 60
#define ERR_61 61
#define ERR_62 62
#define ERR_63 63
#define ERR_64 64
#define ERR_65 65
#define ERR_66 66
#define ERR_67 67
#define ERR_68 68
#define ERR_69 69
#define ERR_70 70
#define ERR_71 71
#define ERR_72 72
#define ERR_73 73
#define ERR_74 74
#define ERR_75 75
#define ERR_76 76
#define ERR_77 77
#define ERR_78 78
#define ERR_79 79
#define ERR_80 80
#define ERR_81 81
#define ERR_82 82
#define ERR_83 83
#define ERR_84 84
#define ERR_85 85
#define ERR_86 86
#define ERR_87 87
#define ERR_88 88
#define ERR_89 89
#define ERR_90 90
#define ERR_91 91
#define ERR_92 92
#define ERR_93 93
#define ERR_94 94
#define ERR_95 95
#define ERR_96 96
#define ERR_97 97
#define ERR_98 98
#define ERR_99 99