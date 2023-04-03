#include <window.h>

void	get_args(const int argc, char **argv, t_args *args)
{
	int	i;
	int	scale;
	int	debug;

	i = 0;
	debug = 0;
	args->scale = DEFAULT_SCALE;
	while (i < argc)
	{
		if (!strncmp(argv[i], "SCALE=", 6))
			scale = (int)strtol(argv[i] + 6, NULL, 10);
		if (!strncmp(argv[i], "DEBUG=", 6))
			debug = (int)strtol(argv[i] + 6, NULL, 10);
		i++;
	}
	if (scale >= MIN_SCALE && scale <= MAX_SCALE)
		args->scale = scale;
	args->debug = debug;
}

t_main	*init_main(void)
{
	t_main	*main_data;

	main_data = malloc(sizeof(t_main));
	if (!main_data)
		return (NULL);
	main_data->window = NULL;
	main_data->cpts = NULL;
	main_data->rom = NULL;
	return (main_data);
}

t_main	*load_main(const int argc, char **argv)
{
	t_main	*main_data;

	main_data = init_main();
	if (!main_data)
		return (NULL);
	main_data->rom = load_rom(argv[1]);
	if (!main_data->rom)
		return (destroy_main(main_data), NULL);
	main_data->cpts = init_components();
	if (!main_data->cpts)
		return (destroy_main(main_data), NULL);
	fread(main_data->cpts->ram + START_ADDRESS,
			main_data->rom->attributes.st_size, 1, main_data->rom->file);
	if (SDL_Init(SDL_INIT_EVERYTHING))
		return (destroy_main(main_data), NULL);
	get_args(argc, argv, &main_data->args);
	main_data->window = init_window(main_data->args.scale);
	if (!main_data->window)
		return (SDL_Quit(), NULL);
	return (main_data);
}

void	destroy_main(t_main *main_data)
{
	free(main_data->cpts);
	destroy_window(main_data->window);
	SDL_Quit();
	destroy_rom(main_data->rom);
	free(main_data);
}