NAME		= push_swap
BONUS_NAME	= checker

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes -I libft
RM			= rm -f

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

HEADER		= includes/push_swap.h

# files shared by push_swap and checker (everything except main.c)
COMMON		= srcs/01_stack.c srcs/02_flags.c srcs/03_parsing.c \
			  srcs/04_parsing_utils.c srcs/05_index.c srcs/06_disorder.c \
			  srcs/07_sort_adaptive.c srcs/08_sort_small.c srcs/09_sort_simple.c \
			  srcs/10_sort_medium.c srcs/11_sort_complex.c srcs/12_sort_utils.c \
			  srcs/13_ops_swap.c srcs/14_ops_push.c srcs/15_ops_rotate.c \
			  srcs/16_ops_rev_rotate.c srcs/17_bench.c

SRCS		= srcs/00_main.c $(COMMON)
BONUS_SRCS	= bonus/checker_bonus.c bonus/checker_utils_bonus.c $(COMMON)

OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
