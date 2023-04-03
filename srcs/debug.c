#include <debug.h>

void	print_memory(t_components *cpts)
{
	for (int i = 0; i < TOTAL_RAM; i += 2)
	{
		if ((cpts->ram[i] != 0 || cpts->ram[i + 1] != 0))
			printf("\x1b[31m%X %X\x1b[0m|", cpts->ram[i], cpts->ram[i + 1]);
		/*else
			printf("0 0|");*/
	}
	printf("\n");
}