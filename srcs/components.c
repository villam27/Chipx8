#include <components.h>
#include <string.h>
#include <stdlib.h>

t_components	*init_components(void)
{
	t_components	*cpts;

	cpts = malloc(sizeof(t_components));
	if (!cpts)
		return (NULL);
	memset(cpts->ram, 0, TOTAL_RAM);
	memset(cpts->stack, 0, TOTAL_STACK * sizeof(u_int16_t));
	memset(cpts->vreg, 0, 16);
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
