#ifndef TASK_H
#define TASK_H

#include <components.h>

void	fetch(t_components *cpts);
void	decode(t_components *cpts, FILE *debug_file);
void	execute(t_components *cpts);

#endif //TASK_H