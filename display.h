#ifndef DISPLAY_H
#define DISPLAY_H

/*
 * bitmasks for shift register 1
 */
#define D1_HFVE 0b00000001
#define D1_SEVN 0b00000010
#define D1_NINE 0b00000100
#define D1_ELVN 0b00001000
#define D1_OCLK 0b00010000
#define D1_SIX 0b00100000
#define D1_EGHT 0b01000000
#define D1_HTEN 0b10000000

/*
 * bitmasks for shift register 2
 */
#define D2_ONE 0b00000001
#define D2_THRE 0b00000010
#define D2_TO 0b00000100
#define D2_QUAR 0b00001000
#define D2_TWLV 0b00010000
#define D2_TWO 0b00100000
#define D2_FOUR 0b01000000
#define D2_PAST 0b10000000

/*
 * bitmasks for shift register 3
 */
#define D3_MTEN 0b00000001
#define D3_MFVE 0b00000010
#define D3_AB 0b00000100
#define D3_AC 0b00001000
#define D3_HALF 0b00010000
#define D3_TWTY 0b00100000
#define D3_ITIS 0b01000000
#define D3_AA 0b10000000


#define D_HFVE 2^0
#define D_SEVN 2^1
#define D_NINE 2^2
#define D_ELVN 2^3
#define D_OCLK 2^4
#define D_SIX 2^5
#define D_EGHT 2^6
#define D_HTEN 2^7
#define D_ONE 2^8
#define D_THRE 2^9
#define D_TO 2^10
#define D_QUAR 2^11
#define D_TWLV 2^12
#define D_TWO 2^13
#define D_FOUR 2^14
#define D_PAST 2^15
#define D_MTEN 2^16
#define D_MFVE 2^17
#define D_AB 2^18
#define D_AC 2^19
#define D_HALF 2^20
#define D_TWTY 2^21
#define D_ITIS 2^22
#define D_AA 2^23

/*
 * enable output pins
 */
#define SHIFTREG_ENABLE_OUTPUTS DDRD |= ((1 << DDD3) | (1 << DDD4) | (1 << DDD5));

/*
 * output pin state switches
 */
#define SHIFTREG_CLK_0 CLR(PORTD, PD5)
#define SHIFTREG_CLK_1 SET(PORTD, PD5)
#define SHIFTREG_DATA_0 CLR(PORTD, PD3);
#define SHIFTREG_DATA_1 SET(PORTD, PD3)
#define SHIFTREG_STRB_0 CLR(PORTD, PD4);
#define SHIFTREG_STRB_1 SET(PORTD, PD4)

/*
 * enables output pins
 */
void initOutput();

/*
 * sets the bitmasks of the shift registers
 */
void setTime(char reg1, char reg2, char reg3);

void setR(uint32_t word);

#endif //DISPLAY_H
