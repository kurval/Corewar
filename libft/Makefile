# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 09:34:51 by vkurkela          #+#    #+#              #
#    Updated: 2020/04/10 19:43:38 by vkurkela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLS = incls/

LIBFT_FILES = ft_isprint.c ft_memmove.c ft_putstr.c ft_strdup.c ft_strmapi.c \
		ft_strsplit.c ft_itoa.c ft_memset.c ft_putstr_fd.c ft_strequ.c \
		ft_strncat.c ft_strstr.c ft_atoi.c ft_memalloc.c ft_putchar.c \
		ft_strcat.c ft_striter.c ft_strncmp.c ft_strsub.c ft_bzero.c \
		ft_memccpy.c ft_putchar_fd.c ft_strchr.c ft_striteri.c ft_strncpy.c \
		ft_strtrim.c ft_isalnum.c ft_memchr.c ft_putendl.c ft_strclr.c \
		ft_strjoin.c ft_strnequ.c ft_tolower.c ft_isalpha.c ft_memcmp.c \
		ft_putendl_fd.c ft_strcmp.c ft_strlcat.c ft_strnew.c ft_toupper.c \
		ft_isascii.c ft_memcpy.c ft_putnbr.c ft_strcpy.c ft_strlen.c \
		ft_strnstr.c ft_numlen.c ft_isdigit.c ft_memdel.c ft_putnbr_fd.c \
		ft_strdel.c ft_strmap.c ft_strrchr.c ft_lstnew.c ft_lstdelone.c \
		ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_itoa_base.c ft_putnbrb.c \
		ft_putstrb.c ft_atoi_base.c ft_iswhitespace.c ft_putnbru.c \
		ft_itoa_baseb.c ft_numlenu.c ft_itoa_baseul.c ft_strsub_b.c \
		ft_put_zeros.c ft_put_spaces.c ft_put_plus.c ft_ftoa.c ft_put_space.c \
		ft_putcharb.c ft_strncmp_end.c ft_atoi_err.c ft_tab_size.c \
		get_next_line.c

FT_PRINTF_FILES = ft_printf.c parser.c type_f.c type_c.c type_p.c \
		flag_percent.c parse_length.c width.c precision.c type_id.c type_o.c \
		type_u.c type_x.c type_s.c typecast.c type_a.c type_n.c

SRCS = $(addprefix srcs/, $(LIBFT_FILES)) \
		$(addprefix srcs/ft_printf/, $(FT_PRINTF_FILES))

OBJS = $(LIBFT_FILES:.c=.o) $(FT_PRINTF_FILES:.c=.o)


all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror -I $(INCLS) -c $(SRCS)
	@ar rc $(NAME) $(OBJS)
	@mkdir objs/
	@mv $(OBJS) objs/

clean:
	@/bin/rm -f $(OBJS) -r objs/

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
