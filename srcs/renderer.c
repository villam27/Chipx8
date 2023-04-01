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

void	draw_lines(t_win_data *data)
{
	SDL_SetRenderDrawColor(data->renderer, 100, 100, 100, 255);
	for(int i = 0; i < HEIGHT; i++)
		SDL_RenderDrawLine(data->renderer, 0, data->scale * i, WIDTH * data->scale, data->scale * i);
	for(int i = 0; i < WIDTH; i++)
		SDL_RenderDrawLine(data->renderer, data->scale * i, 0, data->scale * i, HEIGHT * data->scale);
	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 255);
}

void	render(t_win_data *data, t_components *cpts)
{
	SDL_Rect	rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = data->scale;
	rect.h = data->scale;
	//draw_lines(data);
	for (int i = 0; i < HEIGHT; i++)
	{
		rect.y = i * data->scale;
		for (int j = 0; j < WIDTH; j++)
		{
			rect.x = j * data->scale;
			SDL_SetRenderDrawColor(data->renderer, 255, 255, 255, 255);
			if (cpts->diplay[i][j] == WHITE)
			{
				//printf("OK");
				SDL_RenderFillRect(data->renderer, &rect);
			}
			SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 255);
		}
	}
	SDL_RenderPresent(data->renderer);
	SDL_RenderClear(data->renderer);
}

void	update(t_win_data *data)
{
	(void)data;
}
