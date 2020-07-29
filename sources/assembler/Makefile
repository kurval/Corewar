NAME = asm
INC = ../../libft/
INC2 = ../../includes/
INC3 = ../../libft/printf/includes/
SRC =  main.c parse_file.c utils.c tokenize.c
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
