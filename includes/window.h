#ifndef	WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <tasks.h>
#include <main.h>
#define WIDTH 64
#define HEIGHT 32
#define DEFAULT_SCALE 5
#define MIN_SCALE 1
#define MAX_SCALE 20
#define	TITLE "Chipx8"
#define CENTERED SDL_WINDOWPOS_CENTERED

t_win_data	*init_window(const int scale);
void		loop(t_main *main);
void		destroy_window(t_win_data	*data);

#endif //WINDOW_H