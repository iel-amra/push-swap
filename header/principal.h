#ifndef PRINCIPAL_H
# define PRINCIPAL_H

# include "../libft/libft.h"
t_list *create_stack(int i, char **argv);
int				indice(char *str, int i, char **argv);
int				parse(int argc, char **argv);

#endif
