#include <window.h>
#include <components.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <tasks.h>
#include <debug.h>

int	main(int argc, char **argv)
{
	t_main			*main_data;

	if (argc < 2)
		return (1);
	main_data = load_main(argc, argv);
	if (!main_data)
		return (perror(argv[1]), 1);
	print_memory(main_data->cpts);
	loop(main_data);
	destroy_main(main_data);
	return (0);
}