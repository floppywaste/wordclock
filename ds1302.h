#define DS1302_RST_1 (PORTB|=PB0)
#define DS1302_RST_0 (PORTB&=~PB0)
#define DS1302_CLK_1 (PORTB|=PB1)
#define DS1302_CLK_0 (PORTB&=~PB1)
#define DS1302_IO_1 (PORTB|=PB2)
#define DS1302_IO_0 (PORTB&=~PB2)
#define DS1302_IO_DIR_OUT (DDRB|=DDB2)
#define DS1302_IO_DIR_IN (DDRB&=~DDB2)
#define DS1302_IO_IN (PINB&=DDB2)
#define DS1302_CLK_DIR_OUT (DDRB|=DDB1)
#define DS1302_RST_DIR_OUT (DDRB|=DDB0)

void ds1302_write(unsigned char reg,unsigned char data);
unsigned char ds1302_read(unsigned char reg);
void gettime(unsigned char *nowtime);
void settime(unsigned char *settime);
void ds1302_init(void);
