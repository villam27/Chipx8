#include <tasks.h>
#include <stdio.h>
#include <stdlib.h>
#include <operations.h>

void	fetch(t_components *cpts)
{
	u_int8_t	first_byte;
	u_int8_t	second_byte;

	first_byte = cpts->ram[cpts->pc];
	second_byte = cpts->ram[cpts->pc + 1];
	cpts->op_code = ((u_int16_t)first_byte << 8) | second_byte;
	cpts->pc += 2;
}

void	decode(t_components *cpts)
{
	if (cpts->op_code == CLEAR)
		op_clear(cpts);
	else if ((cpts->op_code & MASK_ONE) == JUMP)
		op_jump(cpts);
	else if ((cpts->op_code & MASK_ONE) == ASSIGN)
		op_assign(cpts);
	else if ((cpts->op_code & MASK_ONE) == ADDITION)
		op_add(cpts);
	else if (GET_OP(cpts->op_code) == DISPLAY)
		op_display(cpts);
	else if ((cpts->op_code & MASK_ONE) == ASSIGN_ID_REG)
		op_assign_index(cpts);
}

void	execute(t_components *cpts)
{
	(void)cpts;
}