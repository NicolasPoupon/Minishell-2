##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## compile lib with project
##

SRC	=	sources/main_minishell.c	\
		sources/minishell.c	\
		sources/do_prog.c	\
		sources/do_comm.c	\
		sources/where_is_comm.c	\
		sources/linked_env.c	\
		sources/set_env.c	\
		sources/linked_list_to_array.c	\
		sources/unset_env.c	\
		sources/do_cd.c	\
		sources/line_clear_in_array.c	\
		sources/fill_comm.c	\
		sources/fill_comm_help.c	\
		sources/change_std.c	\
		sources/do_pipe.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	mysh

CPPFLAGS	=	-I./include/

LDFLAGS	=	-L ./libmy -lmy

all:    $(NAME)

$(NAME):	$(OBJ)
	make -C libmy
	gcc $(OBJ) -L libmy/ -o $(NAME) -lmy

clean:
	$(RM) $(OBJ)
	make clean -C libmy

fclean:	clean
	$(RM) $(NAME)
	make fclean -C libmy

re:	fclean all

tests_run:
	make
	./tests/mytest.sh

debug:		$(OBJ)
	make -C libmy
	gcc $(OBJ) -L libmy/ -o $(NAME) -lmy -Wall -Wextra -g3

.PHONY : all clean fclean re tests_run debug
