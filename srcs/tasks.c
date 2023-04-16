#include <tasks.h>
#include <stdio.h>
#include <stdlib.h>
#include <operations.h>
#include <global.h>

void	fetch(t_components *cpts)
{
	u_int8_t	first_byte;
	u_int8_t	second_byte;

	first_byte = cpts->ram[cpts->pc];
	second_byte = cpts->ram[cpts->pc + 1];
	cpts->op_code = ((u_int16_t)first_byte << 8) | second_byte;
	NEXT_OP(cpts->pc);
}

void	decode(t_components *cpts, FILE *debug_file)
{
	size_t		id;
	uint16_t	op_code;
	uint16_t	op;
	static int	col = 3;
	static int	line = 0;

	op_code = cpts->op_code;
	op = GET_OP(op_code);
	id = 0;
	while (id < MAX_OPERATIONS)
	{
		if (op == op_id[id])
			break;
		id++;
	}
	mvprintw(col, 1, "Current op: %X => %s", op_code, op_str[id]);
	for (int i = 0; i <= VF; i++)
		mvprintw(i + 3, 60, "register [%d]:[%d]", i, cpts->vreg[i]);
	col++;
	if (col > 25)
		col = 3;
	(void)debug_file;
	if (line < 500)
		fprintf(debug_file, "Current op: (%d) %X => %s: %s\n", cpts->pc - 2, op_code, op_str[id], op_comment[id]);
	line++;
	operations[id](cpts);
}

void	execute(t_components *cpts)
{
	(void)cpts;
}