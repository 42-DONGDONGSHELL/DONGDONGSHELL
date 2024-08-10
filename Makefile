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

BUILTIN = ./src/builtin/ft_cd.c \
		./src/builtin/ft_echo.c \
		./src/builtin/ft_env.c \
		./src/builtin/ft_exit.c \
		./src/builtin/ft_export.c \
		./src/builtin/ft_pwd.c \
		./src/builtin/ft_unset.c \

EXECUTE = ./src/execute/execute.c \
		./src/execute/heredoc.c \
		./src/execute/redirect.c \
		./src/execute/run_builtin.c \
		./src/execute/run_cmd.c \

SIGNAL = ./src/signal/set_signal.c \
		./src/signal/signal_handler.c \
		./src/signal/signal_util.c \

ERR = ./src/error/error.c \

SRCS =	./src/main.c \
		./src/utils.c \
		$(PARSE) \
		$(DATA) \
		$(DATA_STRUCT) \
		$(BUILTIN) \
		$(EXECUTE) \
		$(SIGNAL) \
		$(ERR) \

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
