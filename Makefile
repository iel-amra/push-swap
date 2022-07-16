NAME = push_swap
SRC_DIR = src
OBJ_DIR = obj
HEADER_DIR = header
SRC = $(wildcard ${SRC_DIR}/*.c)
OBJ = $(SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o)
HEADER = $(wildcard ${HEADER_DIR}/*.h)
LIBFT = libft/libft.a 

all : checkLibft ${NAME}

${NAME} : ${OBJ} ${LIBFT}
	gcc $(OBJ) ${LIBFT} -o $(NAME)	

checkLibft :
	make -C libft

${OBJ_DIR}/%.o : ${SRC_DIR}/%.c ${HEADER}
	gcc -include "header/principal.h" -Wall -Wextra -Werror -c $< -o $@

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean ${NAME}

.PHONY : clean fclean re checkLibft
