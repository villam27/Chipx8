#include <window.h>
#include <string.h>

int	get_scale(int argc, char **argv)
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
	t_win_data	*data;
	int			scale;

	scale = get_scale(argc, argv);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (1);
	data = init_window(scale);
	if (!data)
		return (SDL_Quit(), 1);
	loop(data);
	destroy_window(data);
	SDL_Quit();
	return (0);
}