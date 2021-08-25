FOLDER_UTILS		= Utils

SRCS				= pipex.c pipex_utils.c pipex_utils_bis.c

#SRCS_UTILS			= ${addprefix ${FOLDER_UTILS}/,}

OBJS				= ${SRCS:.c=.o}

INCLUDES			= pipex.h

NAME				= pipex

CC					= gcc

CFLAGS				= -g3 -fsanitize=address -Wall -Wextra -Werror

all:		MAKELIBFT ${NAME}

%.o:		%.c
			${CC} ${CFLAGS} -o $@ -c $<

${NAME}:	${OBJS}
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ./libft/libft.a
				@echo compilation complete !
			

${OBJS}:	${INCLUDES}

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