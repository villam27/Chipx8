#ifndef INSTRUCTION_H
#define INSTRUCTION_H

//https://johnearnest.github.io/Octo/docs/chip8ref.pdf

/*
	System
*/
#define CLEAR				0x00E0
#define RETURN 				0x00EE
#define JUMP_TO				0xB000
#define JUMP				0x1000
#define CALL				0x2000
#define DISPLAY				0xD000
#define BCD					0xF033
#define SAVE				0xF055
#define LOAD				0xF064

/*
	Conditions
*/
#define iF_EQUAL			0x4000
#define IF_NO_EQUAL			0x3000
#define IF_REG_EQUAL		0x9000
#define IF_REG_NO_EQUAL		0x5000
#define IF_NO_KEY_PRESS		0xE09E
#define IF_KEY_PRESS		0xE0A1

/*
	Operations
*/
#define ASSIGN				0x6000
#define ADDITION			0x7000
#define ASSIGN_REG			0x8000
#define ADDITION_REG		0x8004
#define LSUBSTRACT_REG		0x8005
#define RSUBSTRACT_REG		0x8007
#define ASSIGN_RAND_REG		0xC000
#define ASSIGN_DELAY_REG	0xF007
#define ASSIGN_ID_REG		0xA000
#define SET_ID_REG			0xF029
#define DELAY_ASSIGN		0xF015
#define WAIT_KEY			0xE00A
#define BUZZER_ASSIGN		0xF018
#define ADDITION_ID_REG		0xF01E

/*
	Bitwise
*/
#define BITWISE_OR			0x8001
#define BITWISE_AND			0x8002
#define BITWISE_XOR			0x8003
#define BITWISE_RSHIFT		0x8006
#define BITWISE_LSHIT		0x800E

#endif //INSTRUCTION_H