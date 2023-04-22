#include <operations.h>
#include <global.h>

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
	while (i < TOTAL_STACK && cpts->stack[i] != 0)
		i++;
	cpts->pc = cpts->stack[i - 1];
	cpts->stack[i - 1] = 0;
	//NEXT_OP(cpts->pc);
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
	cpts->stack[i] = cpts->pc;
	cpts->pc = GET_ADDRESS(op_code);
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
	//cpts->vreg[VF] = 0;
	len = GET_N(op_code);
	for (int i = 0; i < len; i++)
	{
		px = cpts->ram[cpts->index_reg + i];
		for (int j = 0; j < SPRITE_SIZE; j++)
		{
			if (y + i < HEIGHT && x + j < WIDTH && (px & (0x80 >> j)))
			{
				if (cpts->diplay[y + i][x + j] == WHITE)
				{
					cpts->vreg[VF] = !cpts->vreg[VF];
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
	uint8_t		vx;
	uint16_t	op_code;
	u_int16_t	i;

	i = cpts->index_reg;
	if (i > TOTAL_RAM - 2)
		return (OP_FAIL);
	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vx = cpts->vreg[vx];
	cpts->ram[i + 2] = vx % 10;
	vx /= 10;
	cpts->ram[i + 1] = vx % 10;
	vx /= 10;
	cpts->ram[i] = vx % 10;
	return (OP_SUCCESS);
}

t_op_status	op_save(t_components *cpts)
{
	uint8_t		vx;
	uint16_t	op_code;
	uint16_t	I;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	I = cpts->index_reg;
	for (size_t i = 0; i <= vx; i++)
	{
		if (I + i >= TOTAL_RAM)
			return (OP_FAIL);
		cpts->ram[I + i] = cpts->vreg[i];
	}
	return (OP_SUCCESS);
}

t_op_status	op_load(t_components *cpts)
{
	uint8_t		vx;
	uint16_t	op_code;
	uint16_t	I;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	I = cpts->index_reg;
	for (size_t i = 0; i <= vx; i++)
	{
		if (I + i >= TOTAL_RAM)
			return (OP_FAIL);
		cpts->vreg[i] = cpts->ram[I + i]; 
	}
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
	x = cpts->vreg[x];
	NN = GET_NN(op_code);
	if (x != NN)
		NEXT_OP(cpts->pc);
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
	x = cpts->vreg[x];
	NN = GET_NN(op_code);
	if (x == NN)
		NEXT_OP(cpts->pc);
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
	x = cpts->vreg[x];
	y = cpts->vreg[y];
	if (x != y)
		NEXT_OP(cpts->pc);
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
	x = cpts->vreg[x];
	y = cpts->vreg[y];
	if (x == y)
		NEXT_OP(cpts->pc);
	return (OP_SUCCESS);
}

t_op_status	op_key_press(t_components *cpts)
{
	uint8_t		vx;
	uint16_t	op_code;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vx = cpts->vreg[vx];
	if (!cpts->key_state[keys[vx]])
		NEXT_OP(cpts->pc);
	return (OP_SUCCESS);
}

t_op_status	op_no_key_press(t_components *cpts)
{
	uint8_t		vx;
	uint16_t	op_code;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vx = cpts->vreg[vx];
	if (cpts->key_state[keys[vx]])
		NEXT_OP(cpts->pc);
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
	u_int16_t	temp;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	temp = cpts->vreg[vx] + cpts->vreg[vy];
	cpts->vreg[vx] = temp;
	if (temp > 255)
		cpts->vreg[VF] = 1;
	else
		cpts->vreg[VF] = 0;
	return (OP_SUCCESS);
}

t_op_status	op_left_sub_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;
	int16_t		temp;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	temp = cpts->vreg[vx] - cpts->vreg[vy];
	cpts->vreg[vx] = (u_int16_t)temp;
	if (temp < 0)
		cpts->vreg[VF] = 0;
	else
		cpts->vreg[VF] = 1;
	return (OP_SUCCESS);
}

t_op_status	op_right_sub_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	vy;
	int16_t		temp;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	vy = GET_VY(op_code);
	temp = cpts->vreg[vy] - cpts->vreg[vx];
	cpts->vreg[vx] = (u_int16_t)temp;
	if (temp < 0)
		cpts->vreg[VF] = 0;
	else
		cpts->vreg[VF] = 1;
	return (OP_SUCCESS);
}

t_op_status	op_rand_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;
	u_int8_t	NN;
	u_int16_t	random;

	random = 0;
	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	NN = GET_NN(op_code);
	random = rand() % 255;
	cpts->vreg[vx] = (random & NN);
	return (OP_SUCCESS);
}

t_op_status	op_assign_delay_reg(t_components *cpts)
{
	u_int16_t	op_code;
	u_int8_t	vx;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	cpts->vreg[vx] = cpts->delay_timer;
	return (OP_SUCCESS);
}

t_op_status	op_assign_index(t_components *cpts)
{
	cpts->index_reg = GET_ADDRESS(cpts->op_code);
	return (OP_SUCCESS);
}

t_op_status	op_set_index(t_components *cpts)
{
	uint8_t		vx;
	uint16_t	op_code;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	cpts->index_reg = GET_HEX_CHAR(vx);
	return (OP_SUCCESS);
}

t_op_status	op_assign_delay(t_components *cpts)
{
	uint8_t		vx;
	uint16_t	op_code;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	cpts->delay_timer = cpts->vreg[vx];
	return (OP_SUCCESS);
}

t_op_status	op_wait_key(t_components *cpts)
{
	uint8_t			vx;
	uint16_t		op_code;
	static int16_t	pressed_key = -1;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	cpts->pc -= 2;
	if (pressed_key == -1)
	{
		for (size_t i = 0; i < MAX_KEYS; i++)
		{
			if (cpts->key_state[keys[i]])
			{
				mvprintw(2, 60, "ok");
				pressed_key = keys[i];
			}
		}
	}
	else
	{
		if (!cpts->key_state[pressed_key])
		{
			NEXT_OP(cpts->pc);
			cpts->vreg[vx] = pressed_key;
			pressed_key = -1;
		}
	}
	return (OP_SUCCESS);
}

t_op_status	op_assign_buzzer(t_components *cpts)
{
	uint8_t		vx;
	uint16_t	op_code;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	cpts->sound_timer = cpts->vreg[vx];
	return (OP_SUCCESS);
}

t_op_status	op_add_index(t_components *cpts)
{
	uint8_t		vx;
	uint16_t	op_code;

	op_code = cpts->op_code;
	vx = GET_VX(op_code);
	cpts->index_reg += cpts->vreg[vx];
	if (cpts->index_reg >= TOTAL_RAM)
		return (OP_FAIL);
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
	cpts->vreg[vx] = (cpts->vreg[vx] >> 1);
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
	
	function = GET_FUNC(cpts->op_code);
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
			return (op_bitwise_rshift(cpts));
			break;
		case RSUBST_FUNC:
			return (op_right_sub_reg(cpts));
			break;
		case RSHIFT_FUNC:
			return (op_bitwise_lshift(cpts));
			break;
		default:
			return (OP_FAIL);
			break;
	}
}

t_op_status	op_operation_E(t_components *cpts)
{	
	u_int8_t	function;
	
	function = GET_FUNC(cpts->op_code);
	switch (function)
	{
		case NKEY_PRESS_FUNC:
			return (op_no_key_press(cpts));
			break;
		case KEY_PRESS_FUNC:
			return (op_key_press(cpts));
			break;
		default:
			return (OP_FAIL);
			break;
	}
}

t_op_status	op_operation_F(t_components *cpts)
{	
	u_int8_t	function;
	
	function = GET_FUNC2(cpts->op_code);
	switch (function)
	{
		case ASSSIGN_DELAY_FUNC:
			return (op_assign_delay(cpts));
			break;
		case WAIT_KEY_FUNC:
			return (op_wait_key(cpts));
			break;
		case DELAY_ASSIGN_FUNC:
			return (op_assign_delay_reg(cpts));
			break;
		case BUZZER_ASSIGN_FUNC:
			return (op_assign_buzzer(cpts));
			break;
		case ADD_ID_REG_FUNC:
			return (op_add_index(cpts));
			break;
		case SET_HEX_FUNC:
			return (op_set_index(cpts));
			break;
		case BCD_FUNC:
			return (op_bcd(cpts));
			break;
		case SAVE_FUNC:
			return (op_save(cpts));
			break;
		case LOAD_FUNC:
			return (op_load(cpts));
			break;
		default:
			return (OP_FAIL);
			break;
	}
	return (OP_SUCCESS);
}
