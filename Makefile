NAME = push_swap
NAME_BONUS = checker
SRC_DIR = src
OBJ_DIR = obj
HEADER_DIR = includes
SRC_FILES = brute.c display.c instructions.c int_utils.c line_algo.c line_solve.c line_solve_utils.c main.c maths.c move.c parsing.c radix.c radix_utils.c sa.c solve.c stack.c try_moves.c line_algo_utils.c
SRC_FILES_BONUS = checker_bonus.c move.c instructions.c parsing.c stack.c maths.c int_utils.c
SRC = $(addprefix ${SRC_DIR}/,${SRC_FILES})
SRC_BONUS = $(addprefix ${SRC_DIR}/,${SRC_FILES_BONUS})
OBJ = $(SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
OBJ_BONUS = $(SRC_BONUS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
HEADER = ${HEADER_DIR}/principal.h
LIBFT = libft/libft.a 
FLAGS = -Wall -Wextra -Werror

all : ${NAME} ${NAME_BONUS}

${NAME} : ${OBJ}
	gcc $(FLAGS) $(OBJ) ${LIBFT} -o $(NAME)	

${NAME_BONUS} : ${OBJ_BONUS} 
	gcc $(FLAGS) $(OBJ_BONUS) ${LIBFT} -o checker

${OBJ_DIR}/%.o : ${SRC_DIR}/%.c ${HEADER} Makefile ${LIBFT} | ${OBJ_DIR}
	gcc -include ${HEADER} $(FLAGS) -c $< -o $@

${LIBFT} : FORCE
	make -C libft

FORCE :

${OBJ_DIR} : 
	mkdir $@

clean :
	rm -f ${OBJ}
	make -C libft clean

fclean : clean
	rm -f ${NAME}
	rm -f checker
	rm -f ${OBJ}
	make -C libft fclean

re : fclean all

.PHONY : clean fclean re checkLibft bonus FORCE
