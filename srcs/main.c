#include <stdio.h>
#include <SDL2/SDL.h>

int	main(int argc, char **argv)
{
	SDL_version	version;

	(void)argc;
	(void)argv;
	SDL_GetVersion(&version);
	printf("%d.%d\n",version.major, version.minor);
	return (0);
}