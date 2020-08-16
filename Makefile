# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/02 15:57:46 by bkonjuha          #+#    #+#              #
#    Updated: 2020/08/22 16:45:32 by bkonjuha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
COREWAR = corewar

VM_SRC_PATH = ./sources/vm/
SRC_FILES = ft_errno.c init_vm.c parse_input.c validate_champions.c \
			run_cycles.c print_arena.c get_op.c validate_encoding.c \
			operations/op_add.c operations/op_aff.c operations/op_and.c \
			operations/op_fork.c operations/op_ld.c operations/op_ldi.c \
			operations/op_lfork.c operations/op_live.c operations/op_lld.c \
			operations/op_lldi.c operations/op_or.c operations/op_st.c \
			operations/op_sti.c operations/op_sub.c operations/op_xor.c \
			operations/op_zjmp.c free_all.c assign_opfunctions.c load_champions.c \
			get_addr.c get_args.c testing.c proc_functions.c operations/utils.c \
			winner.c init_processes.c
SRC = $(addprefix $(VM_SRC_PATH), $(SRC_FILES))

MAIN_PATH = ./sources/vm/
# ASM_MAIN = .c
C_MAIN = corewar.c
# A = $(addprefix $(MAIN_PATH), $(PS_MAIN))
C = $(addprefix $(MAIN_PATH), $(C_MAIN))

INCLUDES = -I ./includes/
HEADER_PATH = ./includes/
HEADER_FILES = corewar.h corewar_error.h asm.h op.h
HEADERS = $(addprefix $(HEADER_PATH), $(HEADER_FILES))
COMPILE = gcc -Wall -Werror -Wextra -g # remove g flag before turning the assignment in

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

all: $(COREWAR)

$(COREWAR): $(HEADERS) $(LIBFT) $(PRINTF)
		@$(COMPILE) $(C) $(SRC) $(LIBFT) $(PRINTF) -o $(COREWAR)
		# @$(COMPILE) $(A) $(SRC) $(LIBFT) $(PRINTF) -o $(ASM)
		@echo "[$(COLOR_PENDING)Putting everything togeather$(COLOR_RESET)]"
		@echo "[$(COLOR_SUCCESS)Executable $(COREWAR) created$(COLOR_RESET)]"
		# @echo "[$(COLOR_SUCCESS)Executable $(ASM) created$(COLOR_RESET)]"

$(LIBFT) $(PRINTF): $(PRINTF_SRCS)*.c $(LIBFT_PATH)*.c
		@echo "Recompiling libraries"
		@make -C $(LIBFT_PATH)

exec:
		@$(COMPILE) $(C) $(SRC) $(LIBFT) $(PRINTF) -o $(COREWAR)
clean:
		@make clean -C libft/ >/dev/null

fclean: clean
		@rm -fv $(COREWAR) > /dev/null
		# @rm -fv $(ASM) > /dev/null
		@make fclean -C libft/ >/dev/null

re: fclean all

.PHONY = all clean fclean re
