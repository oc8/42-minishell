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
FLAGS		= -Wall -Wextra -Werror
# FLAGS		= -Wall -Wextra -Werror -Ofast
# FLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
# FLAGS		= -Wall -Wextra -Werror -g #(lldb)
CFLAGS		= -I./inc -I./libft/inc
AR			= ar
ARFLAGS		= rcs
PATH_SRCS	= srcs
PATH_OBJS	= objs
LST_SRCS	= main.c
LST_OBJS	= ${SRCS:.c=.o}
SRCS		= $(addprefix $(PATH_SRCS)/,$(LST_SRCS))
OBJS		= $(addprefix $(PATH_OBJS)/,$(LST_OBJS))
