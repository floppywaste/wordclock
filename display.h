#ifndef DISPLAY_H
#define DISPLAY_H

/*
 * shift register bit masks for output leds
 */
#define D_HFVE ((uint32_t)1)<<8
#define D_SEVN ((uint32_t)1)<<9
#define D_NINE ((uint32_t)1)<<10
#define D_ELVN ((uint32_t)1)<<11
#define D_OCLK ((uint32_t)1)<<12
#define D_SIX ((uint32_t)1)<<13
#define D_EGHT ((uint32_t)1)<<14
#define D_HTEN ((uint32_t)1)<<15
#define D_ONE ((uint32_t)1)<<16
#define D_THRE ((uint32_t)1)<<17
#define D_TO ((uint32_t)1)<<18
#define D_QUAR ((uint32_t)1)<<19
#define D_TWLV ((uint32_t)1)<<20
#define D_TWO ((uint32_t)1)<<21
#define D_FOUR ((uint32_t)1)<<22
#define D_PAST ((uint32_t)1)<<23
#define D_MTEN ((uint32_t)1)<<24
#define D_MFVE ((uint32_t)1)<<25
#define D_AB ((uint32_t)1)<<26
#define D_AC ((uint32_t)1)<<27
#define D_HALF ((uint32_t)1)<<28
#define D_TWTY ((uint32_t)1)<<29
#define D_ITIS ((uint32_t)1)<<30
#define D_AA ((uint32_t)1)<<31

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
 * sets the bit masks of the shift registers
 */
void setRegister(uint32_t word);

#endif //DISPLAY_H
