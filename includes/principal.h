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
int				ft_factoriel(int nb);
int				*int_copy(int *nb);
t_stacks			*copy_stacks(t_stacks *stacks);
void			free_stacks(t_stacks *stacks);
int				brute_recur(char *brute, t_stacks *stacks, int nb, int restricted);
char			*brute_force(int nb, int restricted);
int				get_opposite_move(int	i);
int				forbidden_move(t_stacks *stacks, int action, int restricted);
int				try_moves(char *brute, t_stacks *stacks, int circle, int restricted);
char			*get_best_move(t_stacks *stacks, char *brute);
void			px(t_list **stack_x, t_list **stack_y);
void			sx(t_list **stack);
void			rx(t_list **stack);
void			rrx(t_list **stack);
void			p_putnbr(void *nb);
void			put_stacks(void *src);
int				parse(int argc, char **argv);
void			move(t_stacks *stacks, int action, int verbose);
void			radix(int bit, t_stacks *stacks, int len, int mode);
void			radix_push(t_stacks *stacks, int mode);
void			radix_reverse_push(t_stacks *stacks, int mode);
int				ft_pow(int nb, int exp);
int				solve(t_stacks *stacks);
t_list			*stack_from_argv(int argc, char **argv);
t_list			*create_stack(int nb);
int				indice(char *str, int i, char **argv);
int int_content(t_list *stack);

#endif
