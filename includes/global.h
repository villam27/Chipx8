#ifndef GLOBAL_H
#define GLOBAL_H

#include <operations.h>
#include <components.h>
#include <sys/types.h>

extern const u_int16_t	op_id[MAX_OPERATIONS];
extern const char			*op_str[MAX_OPERATIONS];
extern const char			*op_comment[MAX_OPERATIONS];
extern t_op_status	(*operations[MAX_OPERATIONS])(t_components *cpts);

#endif //GLOBAL_H