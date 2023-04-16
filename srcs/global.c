#include <global.h>

const u_int16_t	op_id[MAX_OPERATIONS] = 
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

const char	*op_str[MAX_OPERATIONS] = 
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

const char	*op_comment[MAX_OPERATIONS] = 
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
