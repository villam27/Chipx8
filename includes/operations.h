#ifndef OPERATION_H
#define OPERATION_H

#include <main.h>

typedef enum e_op_status
{
	OP_SUCCESS,
	OP_FAIL
}	t_op_status;

t_op_status	op_clear(t_components *cpts);
t_op_status	op_return(t_components *cpts);
t_op_status	op_jump_to(t_components *cpts);
t_op_status	op_jump(t_components *cpts);
t_op_status	op_call(t_components *cpts);
t_op_status	op_display(t_components *cpts);
t_op_status	op_bcd(t_components *cpts);
t_op_status	op_save(t_components *cpts);
t_op_status	op_load(t_components *cpts);

t_op_status	op_equal(t_components *cpts);
t_op_status	op_no_equal(t_components *cpts);
t_op_status	op_reg_equal(t_components *cpts);
t_op_status	op_reg_no_equal(t_components *cpts);
t_op_status	op_key_press(t_components *cpts);
t_op_status	op_no_key_press(t_components *cpts);

t_op_status	op_assign(t_components *cpts);
t_op_status	op_add(t_components *cpts);
t_op_status	op_assign_reg(t_components *cpts);
t_op_status	op_add_reg(t_components *cpts);
t_op_status	op_left_sub_reg(t_components *cpts);
t_op_status	op_right_sub_reg(t_components *cpts);
t_op_status	op_rand_reg(t_components *cpts);
t_op_status	op_assign_delay_reg(t_components *cpts);
t_op_status	op_assign_index(t_components *cpts);
t_op_status	op_set_index(t_components *cpts);
t_op_status	op_assign_delay(t_components *cpts);
t_op_status	op_wait_key(t_components *cpts);
t_op_status	op_assign_buzzer(t_components *cpts);
t_op_status	op_add_index(t_components *cpts);

t_op_status	op_bitwise_or(t_components *cpts);
t_op_status	op_bitwise_and(t_components *cpts);
t_op_status	op_bitwise_xor(t_components *cpts);
t_op_status	op_bitwise_rshift(t_components *cpts);
t_op_status	op_bitwise_lshift(t_components *cpts);

t_op_status	op_operation_0(t_components *cpts);
t_op_status	op_operation_8(t_components *cpts);
t_op_status	op_operation_E(t_components *cpts);
t_op_status	op_operation_F(t_components *cpts);

#endif