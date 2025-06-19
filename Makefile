NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = pipex.c splited_commands.c path.c errors.c utils.c
OBJS = $(SRCS:.c=.o)
PRINTF_DIR = printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(NAME) : $(OBJS)
	@echo -n "\033[32mcompilando $(NAME)...\n"
	@make --no-print-directory -C $(PRINTF_DIR) > /dev/null
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PRINTF_LIB)

%.o:%.c 
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@echo -n "\033[34mclean...\n"
	@make --no-print-directory clean -C $(PRINTF_DIR)
	@rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	@echo -n "\033[34mfclean...\n"
	@make --no-print-directory fclean -C $(PRINTF_DIR)
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re