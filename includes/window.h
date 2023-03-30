#ifndef	WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <SDL2/SDL.h>
#define WIDTH 64
#define HEIGHT 32
#define DEFAULT_SCALE 5
#define MIN_SCALE 1
#define MAX_SCALE 20
#define	TITLE "Chipx8"
#define CENTERED SDL_WINDOWPOS_CENTERED

typedef struct s_win_data
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_bool		run;
}	t_win_data;

t_win_data	*init_window(const int scale);
void		loop(t_win_data *data);
void		destroy_window(t_win_data	*data);

#endif //WINDOW_H