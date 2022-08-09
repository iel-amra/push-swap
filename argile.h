#ifndef PRINCIPAL_H
# define PRINCIPAL_H

# include "../libft/libft.h"

# define A_TO_B 1
# define B_TO_A 2
# define FIRST_P 4
# define SECOND_P 8
# define LAST 16

typedef struct s_stacks
{
	t_list	*a;
	t_list	*b;
	int	diff;
	int	nb;
	int	total;
}	t_stacks;

enum {PA, RA, RB, RR, PB, RRA, RRB, RRR, SA, SB, SS, SORTED};
