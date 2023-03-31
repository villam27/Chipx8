#include <tasks.h>
#include <stdio.h>

void	fetch(t_components *cpts)
{
	u_int8_t	first_byte;
	u_int8_t	second_byte;

	first_byte = cpts->ram[cpts->pc];
	second_byte = cpts->ram[cpts->pc + 1];
	cpts->op_code = ((u_int16_t)first_byte << 8) | second_byte;
	cpts->pc += 2;
	//printf("\nOpCode:%x\n", cpts->op_code);
}

void	decode(t_components *cpts)
{
	if (cpts->op_code == CLEAR)
	{
		printf("clear\n");
	}
	else if ((cpts->op_code & MASK_ONE) == JUMP)
	{
		cpts->pc = cpts->op_code & 0x0FFF;
		printf("jump to %X\n", cpts->op_code & 0x0FFF);
	}
	else if ((cpts->op_code & MASK_ONE) == DISPLAY)
		printf("display\n");
	else if ((cpts->op_code & MASK_ONE) == ANNN)
		printf("index equal %X\n", cpts->op_code & 0x0FFF);
}

void	execute(t_components *cpts)
{
	(void)cpts;
}