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

#define CLEAR_FUNC			0xE0
#define RETURN_FUNC			0xEE

#define ASSIGN_FUNC			0x0
#define OR_FUNC				0x1
#define AND_FUNC			0x2
#define XOR_FUNC			0x3
#define ADD_FUNC			0x4
#define LSUBST_FUNC			0x5
#define LSHIFT_FUNC			0x6
#define RSUBST_FUNC			0x7
#define RSHIFT_FUNC			0xE

#define NEXT_OP(CODE)		((CODE) += 2)

#define VF					0xF

#define START_ADDRESS		0x0200
#define TOTAL_RAM			4096
#define TOTAL_STACK			16

#define MASK_ONE			0xF000
#define MASK_TWO			0x0F00
#define MASK_THREE			0x00F0
#define MASK_FOUR			0x000F

#define	MAX_OPERATIONS		16
#define CYCLES				8

#define WIDTH				64
#define HEIGHT				32

#endif //DEFINE_H