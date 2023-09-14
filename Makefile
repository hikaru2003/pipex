NAME = pipex

SRCS	=	./error.c				\
			./free.c				\
			./ft_print_conv.c		\
			./ft_printf.c			\
			./ft_put.c				\
			./ft_split.c			\
			./ft_strjoin.c			\
			./get_next_line_utils.c	\
			./get_next_line.c		\
			./here_doc.c			\
			./path.c				\
			./pipe_tool.c			\
			./to_hexa.c				\
			./tool.c				\

M_SRCS	= 	./pipex.c				\

B_SRCS	=	./pipex_bonus.c			\

OBJS = $(SRCS:%.c=%.o)
M_OBJS = $(M_SRCS:%.c=%.o)
B_OBJS = $(B_SRCS:%.c=%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

ifdef WITH_BONUS
OBJS += $(B_OBJS)
$(NAME): $(OBJS) $(M_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
endif

all: $(NAME)

ifndef WITH_BONUS
$(NAME): $(OBJS) $(M_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(M_OBJS)
endif

clean:
	rm -f $(OBJS) $(M_OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

bonus:	$(OBJS) $(B_OBJS)
	@make WITH_BONUS=1

re: fclean all

.PHONY: all clean fclean bonus re