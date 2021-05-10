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

# NAME		= minishell
# INCLUDES	= ./inc/*.h
# CC			= clang
# RM			= rm -rf
# # FLAGS		= -Wall -Wextra -Werror
# # FLAGS		= -Wall -Wextra -Werror -Ofast
# # FLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
# # FLAGS		= -Wall -Wextra -Werror -g #(lldb)
# CFLAGS		= -I./inc -I./libft/inc
# AR			= ar
# ARFLAGS		= rcs
# PATH_SRCS	= srcs
# PATH_OBJS	= objs
# LST_SRCS	=	main.c \
# 				parsing/get_operator_command.c \
# 				utils/fail.c
# LST_OBJS	= ${LST_SRCS:.c=.o}
# DIRS		= cmd pars utils cmd/cd cmd/echo cmd/env cmd/exit cmd/export cmd/pwd cmd/unset
# DIRS_OBJS	= $(addprefix $(PATH_OBJS)/,$(DIRS))
# SRCS		= $(addprefix $(PATH_SRCS)/,$(LST_SRCS))
# OBJS		= $(addprefix $(PATH_OBJS)/,$(LST_OBJS))
# MKDIR		= mkdir -p

# $(NAME):	compilation $(OBJS)
# 			$(CC) $(FLAGS) -L./libft -lft -o $@ $(OBJS)
# 			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)ok$(END)\n"

# $(PATH_OBJS)/%.o:	$(PATH_SRCS)/%.c $(INCLUDES) libft/libft.a
# 			mkdir -p $(DIRS_OBJS)
# 			$(CC) $(CFLAGS) -c $< -o $@
# 			printf "$(ERASE)$(CYAN)⤖ $(NAME) : $(RED)[$<]"

# # $(PATH_OBJS)/%.o:$(PATH_SRCS)/%.c $(INCLUDES)
# # 				$(MKDIR) $(dir $@)
# # 				${CC} ${CFLAGS} $(INCLUDE) -c  $< -o $@

# all:		$(NAME)

# compilation:
# 			make -C ./Libft/

# clean:		
# 			$(RM) $(OBJS) $(BONUS)

# fclean:		clean
# 			$(RM) $(NAME)
# 			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)clean$(END)\n"
# 			make fclean -C ./Libft/

# re:			fclean all

# .PHONY:		all clean fclean re compilation
# .SILENT:	fclean clean $(OBJS) re $(NAME) all compilation

NAME			= minishell
SRCS			=	srcs/main.c \
					srcs/parsing/get_operator_command.c \
					srcs/utils/fail.c \
					srcs/utils/ft_strncmp_minishell.c
OBJS			= $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o) $(OBJS_SHARED)
OBJS_DIR		= objs
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


$(OBJS_DIR)/%.o:srcs/%.c inc/*.h
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
