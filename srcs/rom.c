#include <main.h>
#include <fcntl.h>
#include <unistd.h>

static t_rom_data	*init_rom(void)
{
	t_rom_data	*rom;

	rom = malloc(sizeof(t_rom_data));
	if (!rom)
		return (NULL);
	rom->file = NULL;
	rom->name = NULL;	
	return (rom);
}

t_rom_data	*load_rom(const char *file)
{
	t_rom_data	*rom;

	if (access(file, W_OK) != 0)
		return (NULL);
	rom = init_rom();
	if (!rom)
		return (NULL);
	rom->file = fopen(file, "rb");
	if (!rom->file)
		return (destroy_rom(rom), NULL);	
	if (stat(file, &rom->attributes) == -1)
		return (destroy_rom(rom), NULL);
	rom->name = SDL_strdup(file);
	if (!rom->name)
		return (destroy_rom(rom), NULL);
	return (rom);
}

void		destroy_rom(t_rom_data *rom)
{
	if (!rom)
		return ;
	fclose(rom->file);
	free(rom->name);
	rom->file = NULL;
	rom->name = NULL;
	free(rom);
	rom = NULL;
}