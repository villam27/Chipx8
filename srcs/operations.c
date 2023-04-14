#include <operations.h>

t_op_status	op_clear(t_components *cpts)
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			cpts->diplay[i][j] = BLACK;
	//printf("clear\n");
	return (OP_SUCCESS);
}

t_op_status	op_return(t_components *cpts)
{
	int			i;

	i = 0;
	while (i < TOTAL_STACK && cpts->stack[i + 1] != 0)
		i++;
	cpts->op_code = cpts->stack[i];
	cpts->stack[i] = 0;
	return (OP_SUCCESS);
}

t_op_status	op_jump_to(t_components *cpts)
{
	cpts->pc = (u_int16_t)(GET_ADDRESS(cpts->op_code) + cpts->vreg[0]);
	return (OP_SUCCESS);
}

t_op_status	op_jump(t_components *cpts)
{
	cpts->pc = (u_int16_t)(GET_ADDRESS(cpts->op_code));
	//printf(">>>>JUMP to %d\n", cpts->pc);
	return (OP_SUCCESS);
}

t_op_status	op_call(t_components *cpts)
{
	int			i;
	uint16_t	op_code;

	i = 0;
	op_code = cpts->op_code;
	while (i < TOTAL_STACK && cpts->stack[i] != 0)
		i++;
	if (i == TOTAL_STACK)
		return (OP_FAIL);
	cpts->stack[i] = op_code;
	cpts->op_code = GET_ADDRESS(op_code);
	return (OP_SUCCESS);
}

t_op_status	op_display(t_components *cpts)
{
	int			x;
	int			y;
	u_int8_t	len;
	u_int8_t	px;
	u_int16_t	op_code;

	op_code = cpts->op_code;
	x = cpts->vreg[GET_VX(op_code)];
	y = cpts->vreg[GET_VY(op_code)];
	cpts->vreg[VF] = 0;
	len = GET_N(op_code);
	for (int i = 0; i < len; i++)
	{
		px = cpts->ram[cpts->index_reg + i];
		for (int j = 0; j < 8; j++)
		{
			if (y + i < HEIGHT && x + j < WIDTH && (px & (0x80 >> j)))
			{
				if (cpts->diplay[y + i][x + j] == WHITE)
				{
					cpts->vreg[VF] = 1;
					cpts->diplay[y + i][x + j] = BLACK;
				}
				else
					cpts->diplay[y + i][x + j] = WHITE;
			}
		}
	}
	return (OP_SUCCESS);
}

t_op_status	op_bcd(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_save(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_load(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

/*
	Skip if VX and NN are not equal
*/
t_op_status	op_equal(t_components *cpts)
{
	uint16_t	x;
	uint16_t	NN;
	uint16_t	op_code;

	op_code = cpts->op_code;
	x = GET_VX(op_code);
	NN = GET_NN(op_code);
	if (x != NN)
		NEXT_OP(cpts->op_code);
	return (OP_SUCCESS);
}

/*
	Skip if VX and NN are equal
*/
t_op_status	op_no_equal(t_components *cpts)
{
	uint16_t	x;
	uint16_t	NN;
	uint16_t	op_code;

	op_code = cpts->op_code;
	x = GET_VX(op_code);
	NN = GET_NN(op_code);
	if (x == NN)
		NEXT_OP(cpts->op_code);
	return (OP_SUCCESS);
}

/*
	Skip if VX and VY are not equal
*/
t_op_status	op_reg_equal(t_components *cpts)
{
	uint16_t	x;
	uint16_t	y;
	uint16_t	op_code;

	op_code = cpts->op_code;
	x = GET_VX(op_code);
	y = GET_VY(op_code);
	if (x != y)
		NEXT_OP(cpts->op_code);
	return (OP_SUCCESS);
}

/*
	Skip if VX and VY are equal
*/
t_op_status	op_reg_no_equal(t_components *cpts)
{
	uint16_t	x;
	uint16_t	y;
	uint16_t	op_code;

	op_code = cpts->op_code;
	x = GET_VX(op_code);
	y = GET_VY(op_code);
	if (x == y)
		NEXT_OP(cpts->op_code);
	return (OP_SUCCESS);
}

t_op_status	op_key_press(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_no_key_press(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_assign(t_components *cpts)
{
	u_int16_t	op_code;

	op_code = cpts->op_code;
	cpts->vreg[GET_VX(op_code)] = GET_NN(op_code);
	//printf("SET %d to %d\n", (cpts->op_code & 0x0F00) >> 8, (cpts->op_code & 0x00FF));
	return (OP_SUCCESS);
}

t_op_status	op_add(t_components *cpts)
{
	u_int16_t	op_code;

	op_code = cpts->op_code;
	cpts->vreg[GET_VX(op_code)] += GET_NN(op_code);
	//printf("ADD %d to %d is %d\n", (cpts->op_code & 0x00ff),(cpts->op_code & 0x0F00) >> 8, cpts->vreg[(cpts->op_code & 0x0F00) >> 8]);
	return (OP_SUCCESS);
}

t_op_status	op_assign_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	cpts->vreg[vx] = cpts->vreg[vy];
	return (OP_SUCCESS);
}

t_op_status	op_add_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	cpts->vreg[vx] += cpts->vreg[vy];
	return (OP_SUCCESS);
}

t_op_status	op_left_sub_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	cpts->vreg[vx] -= cpts->vreg[vy];
	return (OP_SUCCESS);
}

t_op_status	op_right_sub_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	cpts->vreg[vx] = (cpts->vreg[vy] - cpts->vreg[vx]);
	return (OP_SUCCESS);
}

t_op_status	op_rand_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	NN;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	NN = GET_NN(op_code);
	cpts->vreg[vx] = ((rand() % NN) & NN);
	return (OP_SUCCESS);
}

t_op_status	op_assign_delay_reg(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_assign_index(t_components *cpts)
{
	cpts->index_reg = GET_ADDRESS(cpts->op_code);
	//printf("index equal %X, %d => %X\n", cpts->index_reg - START_ADDRESS, cpts->index_reg, cpts->ram[cpts->index_reg]);
	return (OP_SUCCESS);
}

t_op_status	op_set_index(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_assign_delay(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_wait_key(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_assign_buzzer(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_add_index(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_bitwise_or(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	cpts->vreg[vx] = (cpts->vreg[vx] | cpts->vreg[vy]);
	return (OP_SUCCESS);
}

t_op_status	op_bitwise_and(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	cpts->vreg[vx] = (cpts->vreg[vx] & cpts->vreg[vy]);
	return (OP_SUCCESS);
}

t_op_status	op_bitwise_xor(t_components *cpts)
{	
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	cpts->vreg[vx] = (cpts->vreg[vx] ^ cpts->vreg[vy]);
	return (OP_SUCCESS);
}

t_op_status	op_bitwise_rshift(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	cpts->vreg[VF] = (cpts->vreg[vx] & 0x1);
	cpts->vreg[vx] = (cpts->vreg[vx] >> 0x0001);
	return (OP_SUCCESS);
}

t_op_status	op_bitwise_lshift(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	cpts->vreg[VF] = (cpts->vreg[vx] & 0x80);
	cpts->vreg[vx] = (cpts->vreg[vx] << 1);
	return (OP_SUCCESS);
}

t_op_status	op_operation_0(t_components *cpts)
{	
	u_int8_t	function;
	
	function = GET_FUNC2(cpts->op_code);
	switch (function)
	{
		case CLEAR_FUNC:
			return (op_clear(cpts));
			break;
		case RETURN_FUNC:
			return (op_return(cpts));
			break;
		default:
			return (OP_FAIL);
			break;
	}
}

t_op_status	op_operation_8(t_components *cpts)
{
	u_int8_t	function;
	
	function = GET_FUNC2(cpts->op_code);
	switch (function)
	{
		case ASSIGN_FUNC:
			return (op_assign_reg(cpts));
			break;
		case OR_FUNC:
			return (op_bitwise_or(cpts));
			break;
		case AND_FUNC:
			return (op_bitwise_and(cpts));
			break;
		case XOR_FUNC:
			return (op_bitwise_xor(cpts));
			break;
		case ADD_FUNC:
			return (op_add_reg(cpts));
			break;
		case LSUBST_FUNC:
			return (op_left_sub_reg(cpts));
			break;
		case LSHIFT_FUNC:
			return (op_bitwise_lshift(cpts));
			break;
		case RSUBST_FUNC:
			return (op_right_sub_reg(cpts));
			break;
		case RSHIFT_FUNC:
			return (op_bitwise_rshift(cpts));
			break;
		default:
			return (OP_FAIL);
			break;
	}
}

t_op_status	op_operation_E(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}

t_op_status	op_operation_F(t_components *cpts)
{
	(void)cpts;
	return (OP_SUCCESS);
}
