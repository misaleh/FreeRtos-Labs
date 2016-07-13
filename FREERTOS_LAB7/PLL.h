#ifndef PLL_H
#define PLL_H
#include "Types.h"

#define USERCC2 0x80000000
#define BYPASS  0x00000800
#define PLLNormal 0x00002000
#define NoDiv   0x40000000
#define PLLIRS 0x00000040
#define XTAL 0x000007C0
#define PLL_16MHZ 0x00000540
void PLL_Init(void);
void PLL_SetClock(uint32);

void PLL_Set80(void);

#endif
