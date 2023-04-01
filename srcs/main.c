#include <window.h>
#include <components.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <tasks.h>

int	get_scale(const int argc, char **argv)
{
	int	i;
	int	scale;

	i = 0;
	while (i < argc)
	{
		if (!strncmp(argv[i], "SCALE=", 6))
			scale = (int)strtol(argv[i] + 6, NULL, 10);
		i++;
	}
	if (scale < MIN_SCALE || scale > MAX_SCALE)
		return (DEFAULT_SCALE);
	else
		return (scale);
}

int	main(int argc, char **argv)
{
	t_win_data		*data;
	t_components	*cpts;
	int				scale;
	FILE			*rom;
	struct stat		rom_stat;

	rom = fopen("roms/IBMlogo.ch8", "rb");
	stat("roms/IBMlogo.ch8", &rom_stat);
	scale = get_scale(argc, argv);
	cpts = init_components();
	fread(cpts->ram + START_ADDRESS, rom_stat.st_size, 1, rom);
	if (!cpts)
		return (1);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (free(cpts), 1);
	data = init_window(scale);
	data->scale = scale;
	if (!data)
		return (free(cpts), SDL_Quit(), 1);
	for (int i = START_ADDRESS; i < TOTAL_RAM; i += 2)
	{
		if ((cpts->ram[i] != 0 || cpts->ram[i + 1] != 0))
			printf("(%i)|\x1b[31m%X %X\x1b[0m|", i, cpts->ram[i], cpts->ram[i + 1]);
		//else
		//	printf("|%X %X|", cpts->ram[i], cpts->ram[i + 1]);
	}
	loop(data, cpts);
	free(cpts);
	destroy_window(data);
	SDL_Quit();
	fclose(rom);
	return (0);
}