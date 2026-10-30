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
COMMON		= srcs/parsing.c srcs/parsing_utils.c srcs/stack.c \
			  srcs/flags.c \
			  srcs/ops_swap.c srcs/ops_push.c srcs/ops_rotate.c \
			  srcs/ops_rev_rotate.c srcs/sort_utils.c \
			  srcs/sort_simple.c srcs/sort_medium.c srcs/bench.c \
			  srcs/index.c srcs/disorder.c srcs/sort_small.c \
			  srcs/sort_complex.c srcs/sort_adaptive.c

SRCS		= srcs/main.c $(COMMON)
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
