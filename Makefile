NAME			= minishell
LST_SRCS		=	main.c \
					cmd/cmd_exec.c \
					cmd/echo/echo.c \
					cmd/exit/exit.c \
					parsing/get_operator_command.c \
					parsing/pars_line.c \
					parsing/lexer.c \
					utils/fail.c \
					utils/ft_strncmp_minishell.c \
					utils/ft_strdup_no_list.c \
					utils/free_lexer.c
SRCS_DIR		= srcs
OBJS_DIR		= objs
SRCS			= $(addprefix $(PATH_SRCS)/,$(LST_SRCS))
OBJS			= $(LST_SRCS:%.c=$(OBJS_DIR)/%.o) $(OBJS_SHARED)
CC				= gcc
# CFLAGS			= -Wall -Werror -Wextra
CFLAGS			= -Wall -Werror -Wextra -fsanitize=address -g3
INCLUDE			= -Iinc -I${LIBFT}/inc
RM				= rm -rf
MKDIR			= mkdir -p
LIBFT			= libft

all:			libft $(NAME)

$(OBJS_DIR):
				$(MKDIR) $@

libft: 
				make -C ${LIBFT}

${NAME}:		${OBJS_DIR} ${OBJS}
				${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -L ${LIBFT} -lft -o ${NAME}
				echo "$(BOLD)${GREEN}--> minishell generated <--${END}"


$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c inc/*.h
				$(MKDIR) $(dir $@)
				${CC} ${CFLAGS} $(INCLUDE) -c  $< -o $@

clean:
				${RM} $(OBJS)
				make clean -C $(LIBFT)

fclean:			clean
				${RM} $(OBJS_DIR) $(NAME)
				make fclean -C $(LIBFT)
				echo "${RED}XXXXX CLEAN XXXXX${END}"

re:				fclean all

.PHONY: 		clean fclean all re compil libft
.SILENT:		clean fclean all re compil libft $(OBJS) $(NAME) $(OBJS_DIR)

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
