#include <window.h>
#include <renderer.h>

t_win_data	*init_window(const int scale)
{
	t_win_data	*data;

	data = malloc(sizeof(t_win_data));
	if (!data)
		return (NULL);
	data->run = SDL_TRUE;
	data->scale = scale;
	data->window = SDL_CreateWindow(TITLE, CENTERED, CENTERED,
				WIDTH * scale, HEIGHT * scale, SDL_WINDOW_MINIMIZED);
	if (!data->window)
		return (free(data), NULL);
	data->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!data->renderer)
		return (SDL_DestroyWindow(data->window), free(data), NULL);
	return (data);
}

void	loop(t_main *main_data)
{	
	t_win_data		*window;
	t_components	*cpts;
	FILE			*debug_file;

	debug_file = fopen("opcode.log", "w+");
	window = main_data->window;
	cpts = main_data->cpts;
	while (window->run)
	{
		for (int i = 0; i < CYCLES; i++)
		{
			fetch(cpts);
			decode(cpts, debug_file);
			execute(cpts, debug_file);
			event(window);
			//SDL_Delay(25);
		}
		if (cpts->delay_timer > 0)
			cpts->delay_timer--;
		if (cpts->sound_timer > 0)
			cpts->sound_timer--;
		refresh();
		render(window, cpts);
		update(window);
	}
	fclose(debug_file);
}

void	destroy_window(t_win_data	*data)
{
	if (!data)
		return ;
	SDL_DestroyRenderer(data->renderer);
	SDL_DestroyWindow(data->window);
	data->renderer = NULL;
	data->window = NULL;
	free(data);
	data = NULL;
}