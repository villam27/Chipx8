#include <tasks.h>
#include <stdio.h>
#include <stdlib.h>
#include <operations.h>

u_int16_t	op_id[MAX_OPERATIONS] = 
{
	0x0000,
	0x1000,
	0x2000,
	0x3000,
	0x4000,
	0x5000,
	0x6000,
	0x7000,
	0x8000,
	0x9000,
	0xA000,
	0xB000,
	0xC000,
	0xD000,
	0xE000,
	0xF000
};

char	*op_str[MAX_OPERATIONS] = 
{
	"0x0000",
	"0x1000",
	"0x2000",
	"0x3000",
	"0x4000",
	"0x5000",
	"0x6000",
	"0x7000",
	"0x8000",
	"0x9000",
	"0xA000",
	"0xB000",
	"0xC000",
	"0xD000",
	"0xE000",
	"0xF000"
};

char	*op_comment[MAX_OPERATIONS] = 
{
	"Operation 0",
	"Operation jump",
	"Operation call",
	"Operation diff",
	"Operation equal",
	"Operation diff reg",
	"Operation assign",
	"Operation add",
	"Operation 8",
	"Operation equal reg",
	"Operation assign i",
	"Operation jump to",
	"Operation rand",
	"Operation draw",
	"Operation E",
	"Operation F"
};

t_op_status	(*operations[MAX_OPERATIONS])(t_components *cpts) =
{
	op_operation_0,
	op_jump,
	op_call,
	op_no_equal,
	op_equal,
	op_reg_no_equal,
	op_assign,
	op_add,
	op_operation_8,
	op_reg_equal,
	op_assign_index,
	op_jump_to,
	op_rand_reg,
	op_display,
	op_operation_E,
	op_operation_F
};

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