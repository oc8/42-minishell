NAME			= minishell
LST_SRCS		= \
	main.c \
	cmd/others/others.c \
	cmd/cmd_exec.c \
	cmd/cmd_call.c \
	cmd/echo/echo.c \
	cmd/pwd/pwd.c \
	cmd/cd/cd.c \
	cmd/export/export.c \
	cmd/export/print_export.c \
	cmd/unset/unset.c \
	cmd/env/env.c \
	cmd/exit/exit.c \
	redirection/redirection.c \
	redirection/in.c \
	redirection/out.c \
	redirection/here_doc.c \
	redirection/pipe.c \
	redirection/fd.c \
	parsing/get_operator_command.c \
	parsing/tokenization.c \
	parsing/check_caracter_lex.c \
	parsing/quotes_backslash_dollar.c \
	parsing/create_param_cmd.c \
	parsing/manage_var_env.c \
	parsing/manage_here_doc.c \
	parsing/reconize_type.c \
	parsing/verify_syntax.c \
	parsing/fill_struct_param_cmd.c \
	utils/quit_prog.c \
	utils/cpy_env.c \
	utils/var_utils.c \
	utils/env_utils.c \
	utils/reset_var.c \
	utils/init.c \
	utils/prompt.c \
	utils/ft_atoi_redirection.c \
	utils/save_path_home.c \
	utils/ft_strncmp_minishell.c \
	utils/ft_strdup_no_list.c \
	utils/free_lexer.c \
	utils/free_param_cmd.c \
	utils/print_struct_cmd.c \
	utils/print_lexer.c \
	utils/here_document.c \
	utils/error.c \
	utils/error_syntax.c
SRCS_DIR		= srcs
OBJS_DIR		= objs
SRCS			= $(addprefix $(SRCS_DIR)/,$(LST_SRCS))
OBJS			= $(LST_SRCS:%.c=$(OBJS_DIR)/%.o)
CC				= clang
# CFLAGS			= -Wall -Werror -Wextra
# CFLAGS			= -g
# CFLAGS			= -Wall -Werror -Wextra -fsanitize=address -g3
CFLAGS			= -fsanitize=address -g3
INCLUDE			= -Iinc -I${LIBFT}/inc -I/Users/$(USER)/.brew/opt/readline/include
RM				= rm -rf
MKDIR			= mkdir -p
LIBFT			= libft
LIB_RL			= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
# LIB_RL			= -lreadline
LIBFT_AR		= libft/libft.a

all:			libft $(NAME)

$(OBJS_DIR):
				$(MKDIR) $@

libft:
				printf "$(ERASE)${GREEN}--> LIBFT <--${END}"
				make -C ${LIBFT} > SILENT
				$(RM) SILENT
				printf "$(ERASE)"

${NAME}:		$(LIBFT_AR) ${OBJS_DIR} ${OBJS}
				${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -L ${LIBFT} $(LIB_RL) -lft -o ${NAME}
				echo "$(BOLD)${GREEN}$(ERASE)--> minishell generated <--${END}"

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c inc/*.h
				$(MKDIR) $(dir $@)
				${CC} ${CFLAGS} $(INCLUDE) -c  $< -o $@
				printf "$(ERASE)--> [$(GREEN)$<$(END)] <--\n"

clean:
				${RM} $(OBJS)
				make clean -C $(LIBFT) > SILENT
				$(RM) SILENT

fclean:			clean
				${RM} $(OBJS_DIR) $(NAME)
				printf "$(ERASE)${GREEN}--> LIBFT CLEAN<--${END}"
				make fclean -C $(LIBFT) > SILENT
				$(RM) SILENT
				printf "$(ERASE)${GREEN}--> MINISHELL CLEAN <--${END}"

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
