# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omansour <omansour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/25 01:34:48 by omansour          #+#    #+#              #
#    Updated: 2023/07/31 11:21:27 by omansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARSE		=	minishell_parse
RED			=	redirections

SRC			=	main.c ${PARSE}/functions.c ${PARSE}/helpers.c \
				${PARSE}/lst_fcts.c ${PARSE}/remove_quotes.c \
				${PARSE}/split_line.c ${PARSE}/split_proc.c \
				${PARSE}/split_proc_fcts.c ${PARSE}/syntax_check.c \
				${PARSE}/syntax_error.c ${PARSE}/expand_data/expand_data.c ${PARSE}/expand_data/expand_utils.c \
				${RED}/exec_heredoc.c ${RED}/open_files.c ${RED}/open_utils.c \
				minishell_exec/minishel.c \
				minishell_exec/excepath.c \
				minishell_exec/expath.c \
				minishell_exec/expth.c \
				minishell_exec/execution.c \
				minishell_exec/utils1.c \
				minishell_exec/utils2.c \
				minishell_exec/builtin/env.c \
				minishell_exec/builtin/echo.c \
				minishell_exec/builtin/exit.c \
				minishell_exec/builtin/pwd.c \
				minishell_exec/builtin/unset.c \
				minishell_exec/builtin/cd.c \
				minishell_exec/builtin/cdex.c \
				minishell_exec/builtin/export.c \
				minishell_exec/builtin/exportex.c \
				minishell_exec/builtin/exportex1.c \
				minishell_exec/builtin/exportetup.c

OBJS		=	${SRC:.c=.o}

CFLAGS		=	-Wall -Werror -Wextra #-fsanitize=address -g3

LIBFT		=	libft/libft.a

NAME		=	minishell

CC			=	cc

RM			=	rm -rf

all : ${NAME}

${LIBFT} :
	make -C libft

${NAME} : ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LIBFT} -lreadline

clean :
	make clean -C libft
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME} ${LIBFT}

re : fclean all
