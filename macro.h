#ifndef MACRO_H
#define MACRO_H

//×àñòîòà ãåíåðàòîðà ÌÊ
//#define F_CPU 7372800

//Ìàêðîñû äëÿ ðàáîòû ñ áèòàìè
#define ClearBit(reg, bit)  (reg &= (~(1 << (bit))))
#define SetBit(reg, bit)    (reg |= (1 << (bit)))

//Ìàêðîñû äëÿ çàäåðæåê
//#define _delay_us(us)   __delay_cycles((F_CPU / 1000000) * (us));
//#define _delay_ms(ms)   __delay_cycles((F_CPU / 1000) * (ms));

#endif
