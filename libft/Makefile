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

LST_OBJS	= \
	chain_list/ft_lstadd_back.o \
	chain_list/ft_lstadd_front.o \
	chain_list/ft_lstclear.o \
	chain_list/ft_lstdelone.o \
	chain_list/ft_lstiter.o \
	chain_list/ft_lstlast.o \
	chain_list/ft_lstmap.o \
	chain_list/ft_lstnew.o \
	chain_list/ft_lstsize.o \
	chain_list/ft_lstdel_content.o \
	checker/ft_isalnum.o \
	checker/ft_isalpha.o \
	checker/ft_isascii.o \
	checker/ft_isdigit.o \
	checker/ft_isduplicate.o \
	checker/ft_isprint.o \
	conversion/ft_atoi.o \
	conversion/ft_atoi_l.o \
	conversion/ft_atoi_ll.o \
	conversion/ft_itoa.o \
	conversion/ft_tolower.o \
	conversion/ft_toupper.o \
	gnl/get_next_line.o \
	memory/ft_bzero.o \
	memory/ft_calloc_lst.o \
	memory/ft_calloc_secure.o \
	memory/ft_calloc.o \
	memory/ft_memccpy.o \
	memory/ft_memchr.o \
	memory/ft_memcmp.o \
	memory/ft_memcpy.o \
	memory/ft_memmove.o \
	memory/ft_memset.o \
	memory/ft_memadd.o \
	memory/ft_switch.o \
	memory/ft_freedoublestr.o \
	print/ft_putchar_fd.o \
	print/ft_putendl_fd.o \
	print/ft_putnbr_fd.o \
	print/ft_putstr_fd.o \
	strings/ft_split.o \
	strings/ft_strchr.o \
	strings/ft_strdup.o \
	strings/ft_strdup_secure.o \
	strings/ft_strjoin.o \
	strings/ft_strlcat.o \
	strings/ft_strlcpy.o \
	strings/ft_strlen.o \
	strings/ft_doublestrlen.o \
	strings/ft_strmapi.o \
	strings/ft_strncmp.o \
	strings/ft_strnstr.o \
	strings/ft_strrchr.o \
	strings/ft_strtrim.o \
	strings/ft_substr.o \
	math/sort/ft_sort_ascending.o \
	math/ft_median.o \
	len/ft_doublelen.o
LST_SRCS	= ${SRCS:.o=.c}
INCLUDES	= inc/libft.h
NAME		= libft.a
CC			= clang
RM			= rm -rf
# CFLAGS		= -Wall -Wextra -Werror -Ofast -I ./inc -fPIE
CFLAGS		= -Wall -Wextra -Werror -I ./inc -fPIE
AR			= ar
ARFLAGS		= rcs
PATH_SRCS	= srcs
PATH_OBJS	= objs
DIRS		= checker chain_list conversion gnl memory print strings math math/sort len
DIRS_OBJS	= $(addprefix $(PATH_OBJS)/,$(DIRS))
SRCS		= $(addprefix $(PATH_SRCS)/,$(LST_SRCS))
OBJS		= $(addprefix $(PATH_OBJS)/,$(LST_OBJS))

$(NAME):	$(OBJS)
			$(AR) $(ARFLAGS) $(NAME) $?
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)ok$(END)\n"

$(PATH_OBJS)/%.o:	$(PATH_SRCS)/%.c $(INCLUDES)
			mkdir -p $(DIRS_OBJS)
			$(CC) $(CFLAGS) -c $< -o $@
			printf "$(ERASE)$(CYAN)⤖ $(NAME) : $(RED)[$<]"

all:		$(NAME)

clean:		
			$(RM) $(OBJS) $(BONUS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(PATH_OBJS)
			printf "$(ERASE)$(GREEN)⤖ $(CYAN)$(NAME) : $(GREEN)clean$(END)\n"

re:			fclean all

n:
			NORM_ERR=$$(/usr/bin/norminette | grep -e Error\: | wc -l \
				| sed "s/ //g"); \
			if [ "$$NORM_ERR" = "0" ]; then \
				printf "Everything seems normed!\n"; \
			else \
				NORM_FIL=$$(/usr/bin/norminette | grep -e Error\! \
					| wc -l | sed "s/ //g"); \
				printf "\n\t$$NORM_ERR norme error(s) found in $$NORM_FIL \
file(s):\n\n"; \
				printf "$$(/usr/bin/norminette | grep -e Error)\n"; \
			fi

.PHONY:		all clean fclean re n
.SILENT:	fclean clean $(OBJS) re $(NAME) all n
