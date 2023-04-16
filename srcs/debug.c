#include <debug.h>

void	print_memory(t_components *cpts)
{
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	for (int i = 0; i < TOTAL_RAM; i += 2)
	{
		if ((cpts->ram[i] != 0 || cpts->ram[i + 1] != 0))
			printw("(%d)%X %X|", i, cpts->ram[i], cpts->ram[i + 1]);
	}
	attroff(COLOR_PAIR(1));
	refresh();
}