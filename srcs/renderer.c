#include <renderer.h>

void	event(t_win_data *data)
{
	if (SDL_PollEvent(&(data->event)))
	{
		if (data->event.type == SDL_QUIT)
			data->run = SDL_FALSE;
		if (data->event.type == SDL_KEYDOWN)
			if (data->event.key.keysym.sym == SDLK_ESCAPE)
				data->run = SDL_FALSE;
	}
}

void	render(t_win_data *data)
{
	SDL_RenderClear(data->renderer);
	SDL_RenderPresent(data->renderer);
}

void	update(t_win_data *data)
{
	(void)data;
}
