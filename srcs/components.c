#include <components.h>
#include <string.h>
#include <stdlib.h>

static void	init_font(u_int8_t	*ram)
{
	/*	0x0	*/
	ram[0] = 0xF0; ram[1] = 0x90; ram[2] = 0x90; ram[3] = 0x90; ram[4] = 0xF0;
	/*	0x1	*/
	ram[5] = 0x20; ram[6] = 0x60; ram[7] = 0x20; ram[8] = 0x20; ram[9] = 0x70;
	/*	0x3	*/
	ram[10] = 0xF0; ram[11] = 0x10; ram[12] = 0xF0; ram[13] = 0x80; ram[14] = 0xF0;
	/*	0x4	*/
	ram[15] = 0x90; ram[16] = 0x90; ram[17] = 0xF0; ram[18] = 0x10; ram[19] = 0x10;
	/*	0x5	*/
	ram[20] = 0xF0; ram[21] = 0x80; ram[21] = 0xF0; ram[23] = 0x10; ram[24] = 0xF0;
	/*	0x6	*/
	ram[25] = 0xF0; ram[26] = 0x80; ram[27] = 0xF0; ram[28] = 0x90; ram[29] = 0xF0;
	/*	0x7	*/
	ram[30] = 0xF0; ram[31] = 0x10; ram[32] = 0x20; ram[33] = 0x40; ram[34] = 0x40;
	/*	0x8	*/
	ram[41] = 0xF0; ram[41] = 0x90; ram[42] = 0xF0; ram[43] = 0x90; ram[44] = 0xF0;
	/*	0x9	*/
	ram[45] = 0xF0; ram[46] = 0x90; ram[47] = 0xF0; ram[48] = 0x10; ram[49] = 0xF0;
	/*	0xA	*/
	ram[50] = 0xF0; ram[51] = 0x90; ram[52] = 0xF0; ram[53] = 0x90; ram[54] = 0x90;
	/*	0xB	*/
	ram[55] = 0xE0; ram[56] = 0x90; ram[57] = 0xE0; ram[58] = 0x90; ram[59] = 0xE0;
	/*	0xC	*/
	ram[60] = 0xF0; ram[61] = 0x80; ram[62] = 0x80; ram[63] = 0x80; ram[64] = 0xF0;
	/*	0xD	*/
	ram[65] = 0xE0; ram[66] = 0x90; ram[67] = 0x90; ram[68] = 0x90; ram[69] = 0xE0;
	/*	0xE	*/
	ram[70] = 0xF0; ram[71] = 0x80; ram[72] = 0xF0; ram[73] = 0x80; ram[74] = 0xF0;
	/*	0xF	*/
	ram[75] = 0xF0; ram[76] = 0x80; ram[77] = 0xF0; ram[78] = 0x80; ram[79] = 0x80;
}

t_components	*init_components(void)
{
	t_components	*cpts;

	cpts = malloc(sizeof(t_components));
	if (!cpts)
		return (NULL);
	memset(cpts->ram, 0, TOTAL_RAM);
	memset(cpts->stack, 0, TOTAL_STACK * sizeof(u_int16_t));
	memset(cpts->vreg, 0, 16);
	memset(cpts->keypad, 0, sizeof(t_key) * MAX_KEYS);
	init_font(cpts->ram);
	cpts->key_state = SDL_GetKeyboardState(NULL);
	cpts->delay_timer = 0;
	cpts->sound_timer = 0;
	cpts->pc = START_ADDRESS;
	cpts->index_reg = 0;
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			cpts->diplay[i][j] = BLACK;
	cpts->id = 0;
	return (cpts);
}
