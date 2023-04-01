#include <tasks.h>
#include <stdio.h>
#include <stdlib.h>

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
	//if ((cpts->op_code & MASK_ONE) != JUMP)
	//printf("\n++\nFor opcode %X pc => %d/%d:\n", cpts->op_code, (cpts->pc - 2 - START_ADDRESS), cpts->pc - 2);
	if (cpts->op_code == CLEAR)
	{
		for (int i = 0; i < HEIGHT; i++)
			for (int j = 0; j < WIDTH; j++)
				cpts->diplay[i][j] = BLACK;
		printf("clear\n");
	}
	else if ((cpts->op_code & MASK_ONE) == JUMP)
	{
		cpts->pc = (u_int16_t)(cpts->op_code & 0x0FFF);
		//printf(">>>>JUMP to %d\n", cpts->pc);
		//exit (1);
	}
	else if ((cpts->op_code & MASK_ONE) == SET_VREG)
	{
		cpts->vreg[(cpts->op_code & 0x0F00) >> 8] = (cpts->op_code & 0x00FF);
		printf("SET %d to %d\n", (cpts->op_code & 0x0F00) >> 8, (cpts->op_code & 0x00FF));
	}
	else if ((cpts->op_code & MASK_ONE) == ADD_VREG)
	{
		cpts->vreg[(cpts->op_code & 0x0F00) >> 8] += (cpts->op_code & 0x00ff);
		printf("ADD %d to %d is %d\n", (cpts->op_code & 0x00ff),(cpts->op_code & 0x0F00) >> 8, cpts->vreg[(cpts->op_code & 0x0F00) >> 8]);
	}
	else if ((cpts->op_code & MASK_ONE) == DISPLAY)
	{
		int			x;
		int			y;
		u_int8_t	len;
		u_int8_t	px;

		x = (cpts->op_code & 0x0F00) >> 8;
		y = (cpts->op_code & 0x00F0) >> 4;
		x = cpts->vreg[x];
		y = cpts->vreg[y];
		cpts->vreg[0xF] = 0;
		len = cpts->op_code & 0x000F;
		for (int i = 0; i < len; i++)
		{
			px = cpts->ram[cpts->index_reg + i];
			for (int j = 0; j < 8; j++)
			{
				printf("%X ", px);
				if (y + i < HEIGHT && x + j < WIDTH && (px & (0x80 >> j)))
				{
					if (cpts->diplay[y + i][x + j] == WHITE)
					{
						cpts->vreg[0xF] = 1;
						cpts->diplay[y + i][x + j] = BLACK;
					}
					else
					{
						cpts->diplay[y + i][x + j] = WHITE;
					}
				}
			}
			printf("\n");
		}
		printf("display %d, %x\n", x, y);
	}
	else if ((cpts->op_code & MASK_ONE) == ANNN)
	{
		cpts->index_reg = cpts->op_code & 0x0FFF;
		printf("index equal %X, %d => %X\n", cpts->index_reg - START_ADDRESS, cpts->index_reg, cpts->ram[cpts->index_reg]);
	}
}

void	execute(t_components *cpts)
{
	(void)cpts;
}