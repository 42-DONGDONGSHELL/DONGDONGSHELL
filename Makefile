CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
LIBFT = libft.a
LIBFT_DIR = libft
HEADER_DIR = include
READLINE = -lreadline

NAME = minishell

DATA_STRUCT =	./src/data_struct/data_struct_.c \
				./src/data_struct/data_struct_utils.c \

PARSE =	./src/parse/parse.c \
		./src/parse/envp.c \
		./src/parse/envsubst.c \
		./src/parse/parse_operator.c \
		./src/parse/quote.c \
		./src/parse/token.c \
		./src/parse/free_token.c \
		./src/print_token.c \

SRCS =	./src/main.c \
		./src/utils.c \
		$(PARSE) \
		$(DATA) \
		$(DATA_STRUCT) \

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
