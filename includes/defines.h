#ifndef DEFINE_H
#define DEFINE_H

#include <insctruction.h>

#define GET_OP(CODE)		((CODE) & 0xF000)
#define GET_VX(CODE)		(((CODE) & 0x0F00) >> 8)
#define GET_VY(CODE)		(((CODE) & 0x00F0) >> 4)
#define GET_N(CODE)			((CODE) & 0x000F)
#define GET_NN(CODE)		((CODE) & 0x00FF)
#define GET_ADDRESS(CODE)	((CODE) & 0x0FFF)
#define GET_FUNC(CODE)		((CODE) & 0x000F)
#define GET_FUNC2(CODE)		((CODE) & 0x00FF)

#define NEXT_OP(CODE)		((CODE) += 2)

#define VF					0xF

#define START_ADDRESS		0x0200
#define TOTAL_RAM			4096
#define TOTAL_STACK			16

#define MASK_ONE			0xF000
#define MASK_TWO			0x0F00
#define MASK_THREE			0x00F0
#define MASK_FOUR			0x000F

#define WIDTH				64
#define HEIGHT				32

#endif //DEFINE_H