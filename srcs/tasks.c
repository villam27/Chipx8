#include <tasks.h>
#include <stdio.h>
#include <stdlib.h>
#include <operations.h>

char	*op_str[MAX_OPERATIONS] = 
{
	"0000",
	"1000",
	"2000",
	"3000",
	"4000",
	"5000",
	"6000",
	"7000",
	"8000",
	"9000",
	"A000",
	"B000",
	"C000",
	"D000",
	"E000",
	"F000"
};

t_op_status	(*operations[MAX_OPERATIONS])(t_components *cpts) =
{
	//	0 => op
	/*op_clear,
	op_return,*/
	op_call,
	op_jump,
	op_no_equal,
	op_equal,
	op_reg_no_equal,
	op_assign,
	op_add,

	// 8 => op
	/*op_assign_reg,
	op_bitwise_or,
	op_bitwise_and,
	op_bitwise_xor,
	op_add_reg,
	op_left_sub_reg,
	op_bitwise_rshift,
	op_right_sub_reg,
	op_bitwise_lshift*/

	op_reg_equal,
	op_assign_index,
	op_jump_to,
	op_rand_reg,
	op_display,

	// E => op
	/*op_no_key_press,
	op_key_press,*/

	// F => op
	/*op_assign_delay,
	op_wait_key,
	op_assign_delay_reg,
	op_assign_buzzer,
	op_add_index,
	op_set_index,
	op_bcd,
	op_save,
	op_load,*/
};

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
	(void)cpts;
	/*size_t	i;

	while (i < MAX_OPERATIONS)
	{
		code
	}*/
}

void	execute(t_components *cpts)
{
	(void)cpts;
}