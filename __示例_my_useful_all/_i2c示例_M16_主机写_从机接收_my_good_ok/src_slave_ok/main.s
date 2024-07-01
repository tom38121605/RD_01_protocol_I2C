	.module main.c
	.area data(ram, con, rel)
_RX_data::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.blkb 11
	.area idata
	.word 0,0,0,0,0
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source2\main.c
	.dbsym e RX_data _RX_data A[12:12]c
_RX_data2::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source2\main.c
	.blkb 11
	.area idata
	.word 0,0,0,0,0
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source2\main.c
	.dbsym e RX_data2 _RX_data2 A[12:12]c
_main_tmp::
	.blkb 1
	.area idata
	.byte 0
	.area data(ram, con, rel)
	.dbfile E:\__test\source2\main.c
	.dbsym e main_tmp _main_tmp c
	.area text(rom, con, rel)
	.dbfile E:\__test\source2\main.c
	.dbfunc e twi_slave_init _twi_slave_init fV
;            add -> R16
	.even
_twi_slave_init::
	.dbline -1
	.dbline 80
; //twi �ӻ�
; 
; #include <string.h>
; 
; #include <iom16v.h>
; #include <macros.h>
; 
; //----����------
; #define  B9600  47	//������ 7.3728MHz clock
; #define  B19200 23
; #define  B38400 11
; #define  B57600 7
; #define  BAUD B57600
; 
; #define RX_BUFFER_SIZE 12 
; 
; void UART_Init(void);               //���ڳ�ʼ������
; void UART_Receive(void);            //���ڽ��պ���
; void UART_PutChar(unsigned char c); //��������ַ�
; void UART_Puts(unsigned char *s);   //��������ַ���
; void UART_PutBytes(unsigned char *s, unsigned char ilen);  //��������ֽ�
; 
; unsigned char RX_data[RX_BUFFER_SIZE]={0};   //���ڽ��ջ�����
; unsigned char RX_data2[RX_BUFFER_SIZE]={0};
; 
; void twi_slave_init(unsigned char add);
; void twi_isr(void);
; 
; //�ӻ�����״̬��
; #define TW_SR_SLA_ACK             0x60   //�Լ���SLA+W �Ѿ�������ACK�ѷ���
; #define TW_SR_ARB_LOST_SLA_ACK    0x68   //SLA+R/W ��Ϊ�������ٲ�ʧ�ܣ��Լ���SLA+W �Ѿ�������ACK �ѷ���
; #define TW_SR_GCALL_ACK           0x70   //���յ��㲥��ַACK �ѷ���
; #define TW_SR_ARB_LOST_GCALL_ACK  0x78   //SLA+R/W ��Ϊ�������ٲ�ʧ�ܣ����յ��㲥��ַACK�ѷ���
; #define TW_SR_DATA_ACK            0x80   //��ǰ���Լ���SLA+W��Ѱַ�������Ѿ�������ACK�ѷ���
; #define TW_SR_DATA_NACK           0x88   //��ǰ���Լ���SLA+W��Ѱַ�������Ѿ�������NOT ACK�ѷ���
; #define TW_SR_GCALL_DATA_ACK      0x90   //��ǰ�Թ㲥��ʽ��Ѱַ�������Ѿ�������ACK�ѷ���
; #define TW_SR_GCALL_DATA_NACK     0x98   //��ǰ�Թ㲥��ʽ��Ѱַ�������Ѿ�������NOT ACK�ѷ���
; #define TW_SR_STOP                0xA0   //���Դӻ�����ʱ���յ�STOP���ظ�START
;  
;  
; //�ӷ���״̬��
; #define TW_ST_SLA_ACK             0xA8   //�Լ���SLA+R �Ѿ�������ACK �ѷ���
; #define TW_ST_ARB_LOST_SLA_ACK    0xB0   //SLA+R/W ��Ϊ�������ٲ�ʧ�ܣ��Լ���SLA+R �Ѿ�������ACK �ѷ���
; #define TW_ST_DATA_ACK            0xB8   //TWDR �������Ѿ����ͽ��յ�ACK
; #define TW_ST_DATA_NACK           0xC0   //TWDR �������Ѿ����ͽ��յ�NOT ACK
; #define TW_ST_LAST_DATA           0xC8   //TWDR ��һ�ֽ������Ѿ�����(TWAE = ��0��);���յ�ACK
;  
; 
; /***********************************************/
; //����TWI����(��ģʽд�ʹ�ģʽ��)
; /***********************************************/
; 
; // defines and constants 
; #define TWCR_CMD_MASK     0x0F 
; #define TWSR_STATUS_MASK  0xF8 
; 
; //����״̬��
; #define TW_NO_INFO   0xF8   //û����ص�״̬��Ϣ��TWINT = ��0��
; #define TW_BUS_ERROR 0x00   //���ڷǷ���START ��STOP ��������ߴ���
; 
; 
; //TWSR--Twi_״̬�Ĵ���,���TWI״̬,Ӧ�ý�Ԥ��Ƶλ����(����λ�Ǳ���λ)
; #define Test_Twsr() (TWSR&0xf8)                                               //��ѯģʽ�µȴ��жϷ���
; #define Twi_WaitForComplete() {while(!(TWCR&(1<<TWINT)));}                    //����жϱ�־λ,ʹ��TWI����,����TWI�ж�,�����ؽ���״̬�¶�SDA����Ӧ��
; #define Twi_Ack()   {TWCR=TWCR&TWCR_CMD_MASK|(1<<TWEA)|(1<<TWINT);}           //����жϱ�־λ,ʹ��TWI����,����TWI�ж�,�����ؽ���״̬�²���SDA����Ӧ��
; #define Twi_NoAcK() {TWCR=TWCR&TWCR_CMD_MASK|(1<<TWINT);}                     //д��8λ���ݵ����ݼĴ�����,ͬʱ����жϱ�־λ��ʹ��TWI����
; #define Twi_SendByte(x)  {TWDR=(x);TWCR=TWCR&TWCR_CMD_MASK|(1<<TWINT);}       //����жϱ�־λ���������Ϸ�����ֹ�źţ�����TWI���ܣ�
; #define Twi_Stop()   TWCR=TWCR&TWCR_CMD_MASK|(1<<TWINT)|(1<<TWEA)|(1<<TWSTO)  //����жϱ�־λ���������Ϸ�����ʼ�źţ�����TWI���ܣ�����TWI�ж�    ע���Ƿ��Զ�����ACK ��TWEA��
; #define Twi_Start()  TWCR=TWCR&TWCR_CMD_MASK|(1<<TWINT)|(1<<TWSTA)            //���ñ�����ַ(�ӻ���ʽ)
; #define Twi_SetLocalDeviceAddr(deviceAddr, genCallEn)   TWAR=((deviceAddr)&0xFE)|((genCallEn)&0x01) //��������:��������״̬
; #define Twi_GetState()    Twi_State
; 
; 
; volatile unsigned char main_tmp=0;
; 
; 
; //TWI slave initialize
; // bit rate:100
; void twi_slave_init(unsigned char add)
; {
	.dbline 81
;  TWCR= 0x00; //disable twi
	clr R2
	out 0x36,R2
	.dbline 82
;  TWBR= 1;//50;//0x64; //set bit rate
	ldi R24,1
	out 0x0,R24
	.dbline 83
;  TWSR= 0x00; //set prescale
	out 0x1,R2
	.dbline 84
;  TWAR= add; //set slave address 
	out 0x2,R16
	.dbline 86
;  
;  TWCR= (1<<TWEN)|(1<<TWEA)|(1<<TWIE); //enable twi
	ldi R24,69
	out 0x36,R24
	.dbline -2
L1:
	.dbline 0 ; func end
	ret
	.dbsym r add 16 c
	.dbend
	.area vector(rom, abs)
	.org 68
	jmp _twi_isr
	.area text(rom, con, rel)
	.dbfile E:\__test\source2\main.c
	.dbfunc e twi_isr _twi_isr fV
	.even
_twi_isr::
	xcall push_lset
	xcall push_gset1
	.dbline -1
	.dbline 93
;  //TWEN������λ��ʹ��TWI�ӿڡ�TWEAҲҪ��λ��ʹ����Ѱַ���Լ�(�ӻ���ַ��㲥) ʱ����ȷ����ϢACK
; 
; }
; 
; #pragma interrupt_handler twi_isr:18
; void twi_isr(void)
; {
	.dbline 95
;    //twi event
;    switch (TWSR&0xF8)
	in R20,0x1
	clr R21
	andi R20,248
	andi R21,0
	cpi R20,144
	ldi R30,0
	cpc R21,R30
	brne X4
	xjmp L9
X4:
	ldi R24,144
	ldi R25,0
	cp R24,R20
	cpc R25,R21
	brge X5
	xjmp L17
X5:
L16:
	cpi R20,112
	ldi R30,0
	cpc R21,R30
	brne X6
	xjmp L7
X6:
	ldi R24,112
	ldi R25,0
	cp R24,R20
	cpc R25,R21
	brlt L19
L18:
	cpi R20,96
	ldi R30,0
	cpc R21,R30
	brne X7
	xjmp L6
X7:
	ldi R24,96
	ldi R25,0
	cp R24,R20
	cpc R25,R21
	brlt L21
L20:
	cpi R20,0
	cpc R20,R21
	brne X8
	xjmp L15
X8:
X0:
	xjmp L4
L21:
	cpi R20,104
	ldi R30,0
	cpc R21,R30
	brne X9
	xjmp L7
X9:
	xjmp L4
L19:
	cpi R20,128
	ldi R30,0
	cpc R21,R30
	brne X10
	xjmp L8
X10:
	ldi R24,128
	ldi R25,0
	cp R24,R20
	cpc R25,R21
	brlt L23
L22:
	cpi R20,120
	ldi R30,0
	cpc R21,R30
	brne X11
	xjmp L7
X11:
	xjmp L4
L23:
	cpi R20,136
	ldi R30,0
	cpc R21,R30
	brne X12
	xjmp L8
X12:
	xjmp L4
L17:
	cpi R20,176
	ldi R30,0
	cpc R21,R30
	brne X13
	xjmp L4
X13:
	ldi R24,176
	ldi R25,0
	cp R24,R20
	cpc R25,R21
	brlt L25
L24:
	cpi R20,160
	ldi R30,0
	cpc R21,R30
	brne X14
	xjmp L10
X14:
	ldi R24,160
	ldi R25,0
	cp R24,R20
	cpc R25,R21
	brlt L27
L26:
	cpi R20,152
	ldi R30,0
	cpc R21,R30
	brne X15
	xjmp L9
X15:
	xjmp L4
L27:
	cpi R20,168
	ldi R30,0
	cpc R21,R30
	brne X16
	xjmp L4
X16:
	xjmp L4
L25:
	cpi R20,192
	ldi R30,0
	cpc R21,R30
	brne X17
	xjmp L13
X17:
	ldi R24,192
	ldi R25,0
	cp R24,R20
	cpc R25,R21
	brlt L29
L28:
	cpi R20,184
	ldi R30,0
	cpc R21,R30
	brne X18
	xjmp L4
X18:
	xjmp L4
L29:
	cpi R20,200
	ldi R30,0
	cpc R21,R30
	breq L13
	cpi R20,200
	ldi R30,0
	cpc R21,R30
	brlt L4
L30:
	cpi R20,248
	ldi R30,0
	cpc R21,R30
	breq L4
	xjmp L4
X1:
	.dbline 96
;    {
L6:
	.dbline 99
;       //�ӽ���
;       case TW_SR_SLA_ACK:
;            UART_PutChar(0x80);
	ldi R16,128
	xcall _UART_PutChar
	.dbline 100
;            Twi_Ack();  //����ACK
	.dbline 100
	in R24,0x36
	andi R24,15
	ori R24,192
	out 0x36,R24
	.dbline 100
	.dbline 100
	.dbline 101
;            break;
	xjmp L4
L7:
	.dbline 106
;            
;       case TW_SR_ARB_LOST_SLA_ACK:
;       case TW_SR_GCALL_ACK:
;       case TW_SR_ARB_LOST_GCALL_ACK:
;            Twi_Ack();  //����ACK
	.dbline 106
	in R24,0x36
	andi R24,15
	ori R24,192
	out 0x36,R24
	.dbline 106
	.dbline 106
	.dbline 107
;            break;          
	xjmp L4
L8:
	.dbline 112
;            
;       case TW_SR_DATA_ACK:
;       
;        case TW_SR_DATA_NACK:  //��ǰ���Լ���SLA+W��Ѱַ�������Ѿ�������NOT ACK�ѷ���
;            main_tmp = TWDR;
	in R2,0x3
	sts _main_tmp,R2
	.dbline 113
;            UART_PutChar(main_tmp);
	lds R16,_main_tmp
	xcall _UART_PutChar
	.dbline 115
;            //PORTA = ~ TWDR; //�������ݲ���ʾ
;            Twi_Ack();  //����ACK
	.dbline 115
	in R24,0x36
	andi R24,15
	ori R24,192
	out 0x36,R24
	.dbline 115
	.dbline 115
	.dbline 116
;            break;
	xjmp L4
L9:
	.dbline 119
;       case TW_SR_GCALL_DATA_ACK:
;       case TW_SR_GCALL_DATA_NACK:
;            Twi_Ack();  //����ACK 
	.dbline 119
	in R24,0x36
	andi R24,15
	ori R24,192
	out 0x36,R24
	.dbline 119
	.dbline 119
	.dbline 120
;            break;
	xjmp L4
L10:
	.dbline 122
;       case TW_SR_STOP:
;            Twi_Ack();
	.dbline 122
	in R24,0x36
	andi R24,15
	ori R24,192
	out 0x36,R24
	.dbline 122
	.dbline 122
	.dbline 123
;            break;
	xjmp L4
X2:
	.dbline 132
; 
;       //�ӷ���*****************************
;       
;       case TW_ST_SLA_ACK:               // 0xA8: �Լ���SLA+R �Ѿ������գ�ACK �ѷ���
;       case TW_ST_ARB_LOST_SLA_ACK:// 0xB0: SLA+R/W ��Ϊ�������ٲ�ʧ�ܣ��Լ���SLA+R �Ѿ������գ�ACK �ѷ���
;            // ��ѡ��Ϊ�Ӷ��� (���ݽ��Ӵ�������)
;            //TWDR=main_tmp;  //����ȫ�ֱ�����ֵ
;            //Twi_Ack();
;            break;
	.dbline 136
;       case TW_ST_DATA_ACK:            // 0xB8: TWDR �������Ѿ����ͣ����յ�ACK
;            //��������λ
;            //TWDR=main_tmp;
;            break;
L13:
	.dbline 141
;       case TW_ST_DATA_NACK:            // 0xC0: TWDR �������Ѿ����ͽ��յ�NOT ACK
;       case TW_ST_LAST_DATA:            // 0xC8: TWDR ��һ�ֽ������Ѿ�����(TWAE = ��0��);���յ�ACK
;            // ȫ�����
;            // �ӷ�ʽ����
;            Twi_NoAcK();
	.dbline 141
	in R24,0x36
	andi R24,15
	ori R24,128
	out 0x36,R24
	.dbline 141
	.dbline 141
	.dbline 142
;            twi_slave_init(0x5A);        //���»ص���ʼ��״̬���ȴ�����ģʽ�ĵ���
	ldi R16,90
	xcall _twi_slave_init
	.dbline 143
;            break;
	xjmp L4
X3:
	.dbline 146
;       case TW_NO_INFO:                 // 0xF8: û����ص�״̬��Ϣ��TWINT = ��0��
;            // �޲���
;            break;
L15:
	.dbline 149
	in R24,0x36
	andi R24,15
	ori R24,208
	out 0x36,R24
	.dbline 150
	.dbline 152
L4:
	.dbline -2
L2:
	xcall pop_gset1
	xcall pop_lset
	.dbline 0 ; func end
	reti
	.dbend
	.dbfunc e UART_Init _UART_Init fV
	.even
_UART_Init::
	.dbline -1
	.dbline 160
;       case TW_BUS_ERROR:               // 0x00: ���ڷǷ���START ��STOP ��������ߴ���
;            // �ڲ�Ӳ����λ���ͷ�����
;            TWCR=TWCR&TWCR_CMD_MASK|(1<<TWINT)|(1<<TWSTO)|(1<<TWEA);
;            break;
;       default:
;            break;
;    }
;    
; 
; }
; 
; //���ڳ�ʼ������
; void UART_Init(void)
; {
	.dbline 161
;    UCSRB = (1<<RXCIE)| (1<<RXEN) |(1<<TXEN);   //�����ڷ��ͺͽ��գ�����Ӧ��������ж�
	ldi R24,152
	out 0xa,R24
	.dbline 162
;    UBRR = BAUD;
	ldi R24,7
	out 0x9,R24
	.dbline 163
;    UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);   //8λ���ݣ�1λstopλ
	ldi R24,134
	out 0x20,R24
	.dbline -2
L31:
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e UART_PutChar _UART_PutChar fV
;              c -> R16
	.even
_UART_PutChar::
	.dbline -1
	.dbline 168
; }
; 
; //��������ַ�
; void UART_PutChar(unsigned char c)  
; {
L33:
	.dbline 169
L34:
	.dbline 169
;    while (!(UCSRA&(1 << UDRE)));    //�ж��ϴη�����û�����
	sbis 0xb,5
	rjmp L33
	.dbline 170
;    UDR = c;
	out 0xc,R16
	.dbline -2
L32:
	.dbline 0 ; func end
	ret
	.dbsym r c 16 c
	.dbend
	.dbfunc e UART_Puts _UART_Puts fV
;              s -> R20,R21
	.even
_UART_Puts::
	xcall push_gset1
	movw R20,R16
	.dbline -1
	.dbline 175
; }
; 
; //��������ַ���
; void UART_Puts(unsigned char *s)
; {
	xjmp L38
L37:
	.dbline 177
	.dbline 178
	movw R30,R20
	ld R16,Z+
	movw R20,R30
	xcall _UART_PutChar
	.dbline 179
L38:
	.dbline 176
;    while (*s)
	movw R30,R20
	ldd R2,z+0
	tst R2
	brne L37
	.dbline -2
L36:
	xcall pop_gset1
	.dbline 0 ; func end
	ret
	.dbsym r s 20 pc
	.dbend
	.dbfunc e UART_PutBytes _UART_PutBytes fV
;              i -> R20
;           ilen -> R22
;              s -> R10,R11
	.even
_UART_PutBytes::
	xcall push_gset3
	mov R22,R18
	movw R10,R16
	.dbline -1
	.dbline 184
;    {
;       UART_PutChar(*s++);
;    }
; }
; 
; //��������ֽ�
; void UART_PutBytes(unsigned char *s, unsigned char ilen)
; {
	.dbline 187
; unsigned char i;
; 
;    for(i=0;i<ilen;i++)
	clr R20
	xjmp L44
L41:
	.dbline 188
	.dbline 189
	movw R30,R10
	ld R16,Z+
	movw R10,R30
	xcall _UART_PutChar
	.dbline 190
L42:
	.dbline 187
	inc R20
L44:
	.dbline 187
	cp R20,R22
	brlo L41
	.dbline -2
L40:
	xcall pop_gset3
	.dbline 0 ; func end
	ret
	.dbsym r i 20 c
	.dbsym r ilen 22 c
	.dbsym r s 10 pc
	.dbend
	.dbfunc e main _main fV
	.even
_main::
	.dbline -1
	.dbline 197
;    {
;       UART_PutChar(*s++);
;    }
; }
; 
; 
; 
; 
; void main(void)
; {
	.dbline 199
; 
;    CLI();
	cli
	.dbline 202
; 
; 
;    DDRC&=~(1<<0|1<<1);
	in R24,0x14
	andi R24,252
	out 0x14,R24
	.dbline 203
;    PORTC|=(1<<0|1<<1);   //ʹ���ڲ��������� 
	in R24,0x15
	ori R24,3
	out 0x15,R24
	.dbline 204
;    twi_slave_init(0x5A); //��ʼ��Ϊ�ӻ�
	ldi R16,90
	xcall _twi_slave_init
	.dbline 207
; 
;    
;    UART_Init();
	xcall _UART_Init
	.dbline 210
;    
;    
;    SEI();
	sei
L46:
	.dbline 215
	.dbline 217
	.dbline 219
L47:
	.dbline 214
	xjmp L46
X19:
	.dbline -2
L45:
	.dbline 0 ; func end
	ret
	.dbend
