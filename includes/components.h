#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <sys/types.h>
#include <enum.h>
#define START_ADDRESS 0x200
#define TOTAL_RAM 4096
#define TOTAL_STACK 8

#define MASK_ONE 0xF000
#define MASK_TWO 0x0F00
#define MASK_THREE 0x00F0
#define MASK_FOUR 0x000F

#define CLEAR 0x00E0
#define JUMP 0x1000
#define DISPLAY 0xD000
#define ANNN 0xA000
#define SET_VREG 0x6000
#define ADD_VREG 0x7000

#define WIDTH 64
#define HEIGHT 32

/*
	https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#specifications
	The t_components struct contains
		Memory: 4kilobytes of ram (4096 bytes)
		Display: 64*32 pixels monochrome
		PC: 16-bit program counter => curent instruction of the memory
		Stack: 16-bit stack
		Index Register: 16-bit point to a location in memory
		Delay Timer and Sound Timer: 8-bit
		Variable register: 16bytes
*/
typedef struct s_components
{
	u_int8_t	ram[TOTAL_RAM];
	u_int8_t	vreg[16];
	u_int8_t	delay_timer;
	u_int8_t	sound_timer;
	u_int16_t	stack[TOTAL_STACK];
	u_int16_t	pc;
	u_int16_t	op_code;
	u_int16_t	index_reg;
	t_display	diplay[HEIGHT][WIDTH];
}	t_components;

t_components	*init_components(void);

#endif //COMPONENTS_H