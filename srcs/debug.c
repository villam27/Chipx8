#include <debug.h>
#include <global.h>

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

void	print_last_op(t_components *cpts, int x, int y, int max)
{
	uint16_t	op_code;
	static int	col = 0;

	op_code = cpts->op_code;
	mvprintw(col + y, x, "Current op: %X => %s", op_code, op_str[cpts->id]);
	col++;
	if (col >= max)
		col = 0;
}

void	print_registers(t_components *cpts, int x, int y)
{
	for (int i = 0; i <= VF; i++)
		mvprintw(i + y, x, "register [%d]:[%d]", i, cpts->vreg[i]);
	for (int i = 0; i < TOTAL_STACK; i++)
		mvprintw(i + y, x + 25, "stack [%d]:[%d]", i, cpts->stack[i]);
	/*printw("\n");
	printw("\n");
	print_memory(cpts);*/
}