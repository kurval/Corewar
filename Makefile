# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkonjuha <bkonjuha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/02 15:57:46 by bkonjuha          #+#    #+#              #
#    Updated: 2020/08/02 16:23:41 by bkonjuha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
COREWAR = COREWAR

VM_SRC_PATH = ./sources/
SRC_FILES =
SRC = $(addprefix $(VM_SRC_PATH), $(SRC_FILES))

MAIN_PATH = ./sources/
# ASM_MAIN = .c
C_MAIN = vm/corewar.c
# A = $(addprefix $(MAIN_PATH), $(PS_MAIN))
C = $(addprefix $(MAIN_PATH), $(C_MAIN))

INCLUDES = -I ./includes/
HEADER_PATH = ./includes/
HEADER_FILES = corewar.h corewar_error.h asm.h
HEADERS = $(addprefix $(HEADER_PATH), $(HEADER_FILES))
COMPILE = gcc -Wall -Werror -Wextra

LIBFT_PATH = ./libft/
LIBFT_FILE = libft.a
LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_FILE))
PRINTF_SRCS = ./libft/printf/src/
PRINTF_PATH = ./libft/printf/
PRINTF_FILE = libftprintf.a
PRINTF = $(addprefix $(PRINTF_PATH), $(PRINTF_FILE))

COLOR_RESET = \033[0m
COLOR_PENDING = \033[0;33m
COLOR_SUCCESS = \033[0;32m
COLOR_DEFAULT = \033[1;34m

all: $(COREWAR) $(ASM)

$(COREWAR): $(HEADERS) $(LIBFT) $(PRINTF)
		@$(COMPILE) $(C) $(SRC) $(LIBFT) $(PRINTF) -o $(COREWAR)
		# @$(COMPILE) $(A) $(SRC) $(LIBFT) $(PRINTF) -o $(ASM)
		@echo "[$(COLOR_PENDING)Putting everything togeather$(COLOR_RESET)]"
		@echo "[$(COLOR_SUCCESS)Executable $(COREWAR) created$(COLOR_RESET)]"
		# @echo "[$(COLOR_SUCCESS)Executable $(ASM) created$(COLOR_RESET)]"

$(LIBFT) $(PRINTF): $(PRINTF_SRCS)*.c $(LIBFT_PATH)*.c
		@echo "Recompiling libraries"
		@make -C $(LIBFT_PATH)

clean:
		@make clean -C libft/ >/dev/null

fclean: clean
		@rm -fv $(COREWAR) > /dev/null
		# @rm -fv $(ASM) > /dev/null
		@make fclean -C libft/ >/dev/null

re: fclean all

.PHONY = all clean fclean re
