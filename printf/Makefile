NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = ft_print_char.c ft_print_ptr.c ft_unsigned_int.c ft_printf.c ft_print_int.c \
ft_print_str.c ft_putnbr_hex.c
OBJ = $(SRCS:.c=.o)
AR = ar rcs
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	@make bonus -C $(LIBFT_DIR)
	@cp $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJ)

%.o : %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ)

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re