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
SRC =  main.c parse_file.c utils.c tokenize.c find_first_char.c check_args.c \
validate.c overlap.c check_for_lexical_error.c asm_gnl.c get_op.c \
make_cor_file.c check_token_order.c add_str_to_str.c error.c insert_bytes.c \
init_champ.c set_champ.c arg_code.c insert_statements.c binary.c \
copy_cursor.c labels_to_rel_adrs.c check_str_len.c token_type_str.c
OBJECT = $(SRC:%.c=%.o)
LIBRARY = ../../libft/libft.a

all:		$(NAME)

$(LIBRARY):
			make -C ../../libft/

$(NAME):	$(LIBRARY)
			gcc -I $(INC) -I $(INC2) -I $(INC3) -c $(SRC)
			gcc $(OBJECT) $(LIBRARY) -o $(NAME)

clean:
			/bin/rm -f $(OBJECT)
			make -C ../../libft/ clean

fclean:		clean
			/bin/rm -f $(NAME)
			make -C ../../libft/ fclean

re:			fclean all

.PHONY: 	all clean fclean re
