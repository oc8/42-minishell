NAME			= minishell
LST_SRCS		= \
	main.c \
	cmd/others/execve.c \
	cmd/cmd_exec.c \
	cmd/echo/echo.c \
	cmd/pwd/pwd.c \
	cmd/cd/cd.c \
	cmd/export/export.c \
	cmd/unset/unset.c \
	cmd/env/env.c \
	cmd/exit/exit.c \
	parsing/get_operator_command.c \
	parsing/pars_line.c \
	parsing/lexer.c \
	parsing/manage_var_env.c \
	parsing/reconize_type.c \
	utils/quit_prog.c \
	utils/ft_strncmp_minishell.c \
	utils/ft_strdup_no_list.c \
	utils/free_lexer.c \
	utils/init.c
SRCS_DIR		= srcs
OBJS_DIR		= objs
SRCS			= $(addprefix $(SRCS_DIR)/,$(LST_SRCS))
OBJS			= $(LST_SRCS:%.c=$(OBJS_DIR)/%.o) $(OBJS_SHARED)
CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
# CFLAGS			= -Wall -Werror -Wextra -fsanitize=address -g3
CFLAGS			= -fsanitize=address -g3
INCLUDE			= -Iinc -I${LIBFT}/inc
RM				= rm -rf
MKDIR			= mkdir -p
LIBFT			= libft

all:			libft $(NAME)

$(OBJS_DIR):
				$(MKDIR) $@

libft:
				printf "$(ERASE)${GREEN}--> LIBFT <--${END}"
				make -C ${LIBFT} > SILENT
				$(RM) SILENT
				printf "$(ERASE)"

${NAME}:		${OBJS_DIR} ${OBJS}
				${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -L ${LIBFT} -lft -o ${NAME}
				echo "$(BOLD)${GREEN}$(ERASE)--> minishell generated <--${END}"


$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c inc/*.h
				$(MKDIR) $(dir $@)
				${CC} ${CFLAGS} $(INCLUDE) -c  $< -o $@
				printf "$(ERASE)--> [$(GREEN)$<$(END)] <--"

clean:
				${RM} $(OBJS)
				make clean -C $(LIBFT) > SILENT
				$(RM) SILENT

fclean:			clean
				${RM} $(OBJS_DIR) $(NAME)
				printf "$(ERASE)${GREEN}--> CLEAN LIBFT <--${END}"
				make fclean -C $(LIBFT) > SILENT
				$(RM) SILENT
				printf "$(ERASE)${GREEN}--> CLEAN MINISHELL <--${END}"

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
