CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LIBFT = libft.a
LIBFT_DIR = libft
HEADER_DIR = include
READLINE = -lreadline

NAME = minishell

PARSE = ./src/parse/parse.c ./src/parse/data_struct_.c ./src/parse/data_struct_free.c
BUILTIN = ./src/builtin/ft_cd.c ./src/builtin/ft_echo.c ./src/builtin/ft_env.c ./src/builtin/ft_export.c ./src/builtin/ft_pwd.c ./src/builtin/ft_unset.c

SRCS = 	./src/main.c \
		$(PARSE) \
		$(DATA) \
		$(BUILTIN) \

OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
		make -C $(LIBFT_DIR)
		cp $(LIBFT_DIR)/$(LIBFT) .
		$(CC) $(CFLAGS) -I $(HEADER_DIR) $(OBJS) $(LIBFT) -o $(NAME) $(READLINE)

clean :
		make clean -C $(LIBFT_DIR)
		${RM} ${OBJS}
		${RM} ${BOBJS}

fclean : clean
		make fclean -C $(LIBFT_DIR)
		${RM} $(NAME)
		${RM} $(BONUS_NAME)
		${RM} $(LIBFT)

re : fclean all

.PHONY:		all bonus clean fclean re
