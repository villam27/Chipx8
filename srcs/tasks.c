#include <tasks.h>
#include <stdio.h>
#include <stdlib.h>
#include <operations.h>
#include <global.h>
#include <debug.h>

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
	cpts->id = id;
	if (line < 2000)
		fprintf(debug_file, "OP: (%d) %X => %s: %s\n", cpts->pc - 2, op_code, op_str[id], op_comment[id]);
	line++;
}

void	execute(t_components *cpts, FILE *debug_file)
{
	//print_memory(cpts);
	print_last_op(cpts, 1, 0, 30);
	print_registers(cpts, 35, 0);
	if (operations[cpts->id](cpts) == OP_FAIL)
		fprintf(debug_file, "WARNING: LAST OP FAIL\n");
}