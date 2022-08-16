#ifndef PRINCIPAL_H
# define PRINCIPAL_H

# include "../libft/libft.h"
# include <limits.h>

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

static const char str_move[11][4] = {"pa", "ra", "rb", "rr", "pb", "rra", "rrb", "rrr", "sa", "sb", "ss"};
int				brute_recur(char *brute, t_stacks *stacks, int nb, int restricted);
int				prepare_brute(int nb, char **brute, t_stacks *stacks);
char			*brute_force(int nb, int restricted);
int				reader(t_stacks *stacks);
void			p_putnbr(void *nb);
void			put_stacks(void *src);
void			print_tab(int *tab, int nb);
void			px(t_list **stack_x, t_list **stack_y);
void			sx(t_list **stack);
void			rx(t_list **stack);
void			rrx(t_list **stack);
int				is_in_tab(int *tab, int nb, int len);
int				*tab_int_copy(int *line, int len);
int				*int_copy(int *nb);
int nb_digit(unsigned int nb);
int				overflow(char *str, unsigned int nb, int len);
int				score_line(t_stacks *stacks, int nb, int **line);
int				score_recur(t_stacks *stacks, int step, int nb, int **line);
int				stop_recur(t_stacks *stacks, int **line, int nb);
int				score_tab(int *line, int nb);
int				choose_best_score(int *score, int **line, int **new);
void			line_first_step(t_stacks *stacks, int *data, int *line, int best_sa);
void			line_second(t_stacks *stacks, int *data, int *line, int moved);
void			line_third_step(t_stacks *stacks, int *data, int *line);
int				best_line_solve(t_stacks *stacks, int nb);
int				line_solve(t_stacks *stacks, int nb, int verbose);
int				prep_second_step(t_stacks *stacks, int *data, int *line);
void			move_downward(t_stacks *stacks, int verbose, int *line, int *moved);
int				get_smallest(int *tab, int nb);
int				get_best_correc(t_stacks *stacks, int nb);
int				ft_factoriel(int nb);
int				ft_pow(int nb, int exp);
int				get_nb_bit(int nb);
int				true_bits(int x);
void			move(t_stacks *stacks, int action, int verbose);
void			move_rotations(t_stacks *stacks, int action, int verbose);
int				get_opposite_move(int i);
int				is_sorted(t_stacks *stacks);
int				fit_in_int(char *str);
int				parse(int argc, char **argv);
int				indice(char *str, int i, char **argv);
t_list			*stack_from_argv(int argc, char **argv);
void			radix(int bit, t_stacks *stacks, int len, int mode);
void			radix_push(t_stacks *stacks, int mode);
void			radix_reverse_push(t_stacks *stacks, int mode);
void			get_best_sa(t_stacks *stacks, int nb, int **line, int *best_sa);
void			move_sa_binary(t_stacks *stacks, int nb, int byte, int mode);
int				solve_brute(t_stacks *stacks, int nb);
int				solve(t_stacks *stacks);
t_list			*create_stack(int nb);
int				int_content(t_list *stack);
t_stacks			*copy_stacks(t_stacks *stacks);
void			free_stacks(t_stacks *stacks);
int				forbidden_move(t_stacks *stacks, int action, int restricted);
int				try_moves(char *brute, t_stacks *stacks, int circle, int restricted);
char			*get_best_move(t_stacks *stacks, char *brute);

#endif
