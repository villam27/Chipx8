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
	data->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED);
	if (!data->renderer)
		return (SDL_DestroyWindow(data->window), free(data), NULL);
	return (data);
}

void	loop(t_main *main_data)
{	
	t_win_data		*window;
	t_components	*cpts;

	window = main_data->window;
	cpts = main_data->cpts;
	while (window->run)
	{
		fetch(cpts);
		decode(cpts);
		event(window);
		render(window, cpts);
		update(window);
	}
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