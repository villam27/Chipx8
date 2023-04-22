#include <window.h>
#include <components.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <tasks.h>
#include <debug.h>
#include <ncurses.h>

int	main(int argc, char **argv)
{
	t_main			*main_data;

	srand(time(NULL));
	if (argc < 2)
		return (1);
	initscr();
	main_data = load_main(argc, argv);
	if (!main_data)
		return (endwin(), perror(argv[1]), 1);
	loop(main_data);
	destroy_main(main_data);
	endwin();
	return (0);
}