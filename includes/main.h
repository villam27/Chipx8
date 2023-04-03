#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <enum.h>
#include <defines.h>
#include <string.h>


typedef struct stat	t_stat;

typedef struct s_win_data
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_bool		run;
	int				scale;
}	t_win_data;

/*
	https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#specifications
	The t_components struct contains
		Memory: 4kilobytes of ram (4096 bytes)
		Display: 64*32 pixels monochrome
		PC: 16-bit program counter => curent instruction of the memory
		Stack: 16-bit stack
		Index Register: 16-bit point to a location in memory
		Delay Timer and Sound Timer: 8-bit
		Variable register: 16bytes
*/
typedef struct s_components
{
	u_int8_t	ram[TOTAL_RAM];
	u_int8_t	vreg[16];
	u_int8_t	delay_timer;
	u_int8_t	sound_timer;
	u_int16_t	stack[TOTAL_STACK];
	u_int16_t	pc;
	u_int16_t	op_code;
	u_int16_t	index_reg;
	t_display	diplay[HEIGHT][WIDTH];
}	t_components;

typedef struct s_rom_data
{
	char	*name;
	FILE	*file;
	t_stat	attributes;
}	t_rom_data;

typedef struct s_args
{
	int			scale;
	SDL_bool	debug;
}	t_args;

typedef struct s_main
{
	t_win_data		*window;
	t_components	*cpts;
	t_rom_data		*rom;
	t_args			args;
}	t_main;

t_rom_data	*load_rom(const char *file);
void		destroy_rom(t_rom_data *rom);

t_main		*init_main(void);
t_main		*load_main(const int argc, char **argv);
void		destroy_main(t_main *main_data);

#endif //MAIN_H