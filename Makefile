FOLDER_UTILS		= Utils

SRCS				= Pipex_new.c

#SRCS_UTILS			= ${addprefix ${FOLDER_UTILS}/,}

OBJS				= ${SRCS:.c=.o}

INCLUDES			= pipex.h

NAME				= pipex

CC					= gcc

CFLAGS				=  #-g3 -fsanitize=address -Wall -Wextra -Werror

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

fclean:		clean
			@rm -f ${NAME}
			@make fclean -C ./libft

re:			fclean all

.PHONY: all clean fclean re MAKELIBFT