ERASE	= \033[2K\r
GREY	= \033[30m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
PINK	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
END		= \033[0m
BOLD	= \033[1m
UNDER	= \033[4m
SUR		= \033[7m

NAME		= minishell
INCLUDES	= ./inc/*.h
CC			= clang
RM			= rm -rf
# FLAGS		= -Wall -Wextra -Werror
# FLAGS		= -Wall -Wextra -Werror -Ofast
# FLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
# FLAGS		= -Wall -Wextra -Werror -g #(lldb)
CFLAGS		= -I./inc -I./libft/inc
AR			= ar
ARFLAGS		= rcs
PATH_SRCS	= srcs
PATH_OBJS	= objs
LST_SRCS	= main.c
LST_OBJS	= ${LST_SRCS:.c=.o}
DIRS		= cmd pars utils cmd/cd cmd/echo cmd/env cmd/exit cmd/export cmd/pwd cmd/unset
DIRS_OBJS	= $(addprefix $(PATH_OBJS)/,$(DIRS))
SRCS		= $(addprefix $(PATH_SRCS)/,$(LST_SRCS))
OBJS		= $(addprefix $(PATH_OBJS)/,$(LST_OBJS))

$(NAME):	compilation $(OBJS)
			$(CC) $(FLAGS) -L./libft -lft -o $@ $(OBJS)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)ok$(END)\n"

$(PATH_OBJS)/%.o:	$(PATH_SRCS)/%.c $(INCLUDES) libft/libft.a
			mkdir -p $(DIRS_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@
			printf "$(ERASE)$(CYAN)⤖ $(NAME) : $(RED)[$<]"

all:		$(NAME)

compilation:
			make -C ./Libft/

clean:		
			$(RM) $(OBJS) $(BONUS)

fclean:		clean
			$(RM) $(NAME)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)clean$(END)\n"
			make fclean -C ./Libft/

re:			fclean all

.PHONY:		all clean fclean re compilation
.SILENT:	fclean clean $(OBJS) re $(NAME) all compilation
