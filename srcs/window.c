#include <window.h>
#include <renderer.h>

t_win_data	*init_window(const int scale)
{
	t_win_data	*data;

	data = malloc(sizeof(t_win_data));
	if (!data)
		return (NULL);
	data->run = SDL_TRUE;
	data->window = SDL_CreateWindow(TITLE, CENTERED, CENTERED,
				WIDTH * scale, HEIGHT * scale, SDL_WINDOW_MINIMIZED);
	if (!data->window)
		return (free(data), NULL);
	data->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED);
	if (!data->renderer)
		return (SDL_DestroyWindow(data->window), free(data), NULL);
	return (data);
}

void	loop(t_win_data *data)
{
	while (data->run)
	{
		event(data);
		render(data);
		update(data);
	}
}

void	destroy_window(t_win_data	*data)
{
	SDL_DestroyRenderer(data->renderer);
	SDL_DestroyWindow(data->window);
	free(data);
}