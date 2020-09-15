# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atuomine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/29 15:17:12 by atuomine          #+#    #+#              #
#    Updated: 2020/07/29 15:17:14 by atuomine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm
INC = ../../libft/
INC2 = ../../includes/
INC3 = ../../libft/printf/includes/
SRC = asm.c check_args.c set_flags.c handle_error.c handle_d_and_f_flags.c \
find.c handle_strs.c get_op.c parse_file.c asm_gnl_utils.c tokenize.c \
validate_characters.c check_for_lexical_error.c handle_error_msg.c \
handle_tokens.c copy.c check_tokens.c set_champ.c parse_file_utils.c \
make_cor_file.c insert_bytes_number.c insert_statements.c get_arg_code.c \
write_hexdump.c free_memory.c
OBJECT = $(SRC:%.c=%.o)
LIBRARY = ../../libft/libft.a

all:		$(NAME)

$(LIBRARY):
			make -C ../../libft/

$(NAME):	$(LIBRARY)
			gcc -g -I $(INC) -I $(INC2) -I $(INC3) -c $(SRC)
			gcc -g $(OBJECT) $(LIBRARY) -o $(NAME)

clean:
			/bin/rm -f $(OBJECT)
			make -C ../../libft/ clean

fclean:		clean
			/bin/rm -f $(NAME)
			make -C ../../libft/ fclean

re:			fclean all

.PHONY: 	all clean fclean re
