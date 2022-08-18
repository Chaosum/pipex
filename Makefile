SRCS				= pipex.c pipex_utils.c pipex_utils_bis.c

OBJS				= ${SRCS:.c=.o}

INCLUDES			= pipex.h

NAME				= pipex

CC					= gcc

CFLAGS				= -g3 -fsanitize=address -Wall -Wextra -Werror

all:		MAKELIBFT ${NAME}

bonus:		all

%.o:		%.c ${INCLUDES}
			@${CC} ${CFLAGS} -o $@ -c $<

${NAME}:	${OBJS}
				@gcc ${CFLAGS} -o ${NAME} ${OBJS} ./libft/libft.a
				@echo compilation complete !

MAKELIBFT:
			@make -C ./libft

clean:
			@rm -f *.o
			@echo files cleaned !
			@make clean -C ./libft

fclean:		clean
			@rm -f ${NAME}
			@make fclean -C ./libft

re:			fclean all

.PHONY: all clean fclean re MAKELIBFT