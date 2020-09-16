# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/02 15:57:46 by bkonjuha          #+#    #+#              #
#    Updated: 2020/09/15 15:16:25 by vkurkela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
COREWAR = corewar

ASM_SRC_PATH = ./sources/assembler/
COREWAR_SRC_PATH = ./sources/vm/
ASM_SRC_FILES = check_args.c set_flags.c handle_error.c handle_d_and_f_flags.c \
			find.c handle_strs.c get_op.c parse_file.c asm_gnl_utils.c \
			tokenize.c validate_characters.c check_for_lexical_error.c \
			handle_error_msg.c handle_tokens.c copy.c check_tokens.c \
			set_champ.c parse_file_utils.c make_cor_file.c \
			insert_bytes_number.c insert_statements.c get_arg_code.c \
			write_hexdump.c free_memory.c validate_file.c dasm.c dasm2.c dasm3.c
COREWAR_SRC_FILES = ft_errno.c initialize.c parse_input.c validate_champions.c \
			run_cycles.c print_arena.c validate_encoding.c operations/op_add.c \
			operations/op_aff.c operations/op_and.c operations/op_fork.c \
			operations/op_ld.c operations/op_ldi.c operations/op_lfork.c \
			operations/op_live.c operations/op_lld.c operations/op_lldi.c \
			operations/op_or.c operations/op_st.c operations/op_sti.c \
			operations/op_sub.c operations/op_xor.c operations/op_zjmp.c \
			load_champions.c parse_input2.c get_addr.c get_args.c \
			proc_functions.c operations/utils.c winner.c \
			visual/start_visualizer.c visual/create_color_pairs.c \
			visual/draw_arena.c visual/get_attribute.c visual/print_winner.c \
			visual/init_visualizer.c visual/draw_footer.c \
			visual/draw_player_info.c visual/draw_players.c visual/draw_logo.c \
			visual/draw_battle_info.c visual/debugger.c

ASM_SRC = $(addprefix $(ASM_SRC_PATH), $(ASM_SRC_FILES))
COREWAR_SRC = $(addprefix $(COREWAR_SRC_PATH), $(COREWAR_SRC_FILES))

A_MAIN_PATH = ./sources/assembler/
C_MAIN_PATH = ./sources/vm/
A_MAIN = asm.c
C_MAIN = corewar.c
A = $(addprefix $(A_MAIN_PATH), $(A_MAIN))
C = $(addprefix $(C_MAIN_PATH), $(C_MAIN))

INCLUDES = -I ./includes/ -I ./libft/incls/
HEADER_PATH = ./includes/
HEADER_FILES = asm.h corewar.h corewar_error.h visu.h op.h
HEADERS = $(addprefix $(HEADER_PATH), $(HEADER_FILES))
COMPILE = gcc -Wall -Wextra -Werror -g # remove g flag before turning the assignment in
NCURSES = -lncurses

LIBFT_SRCS = ./libft/srcs/
LIBFT_PATH = ./libft/
LIBFT_FILE = libft.a
LIBFT = $(addprefix $(LIBFT_PATH), $(LIBFT_FILE))
FT_PRINTF_SRCS = ./libft/srcs/ft_printf/

ASM_MANPAGE = ./sources/asm
COREWAR_MANPAGE = ./sources/corewar
ASM_MAN_LOCATION = /usr/local/share/man/man8/asm.8
COREWAR_MAN_LOCATION = /usr/local/share/man/man8/corewar.8
GZIP = gzip
CP = cp

COLOR_RESET = \033[0m
COLOR_PENDING = \033[0;33m
COLOR_SUCCESS = \033[0;32m
COLOR_DEFAULT = \033[1;34m

all: $(ASM) $(COREWAR)

$(ASM): $(LIBFT) $(HEADERS) $(A) $(ASM_SRC)
		@$(COMPILE) $(INCLUDES) $(A) $(ASM_SRC) $(LIBFT) -o $(ASM)
		@$(CP) -f $(ASM_MANPAGE) $(ASM_MAN_LOCATION)
		@$(GZIP) -f $(ASM_MAN_LOCATION)
		@echo "[$(COLOR_PENDING)Putting everything together$(COLOR_RESET)]"
		@echo "[$(COLOR_SUCCESS)Executable $(ASM) created$(COLOR_RESET)]"

$(COREWAR): $(LIBFT) $(HEADERS) $(C) $(COREWAR_SRC)
		@$(COMPILE) $(NCURSES) $(INCLUDES) $(C) $(COREWAR_SRC) $(LIBFT) -o $(COREWAR)
		@$(CP) -f $(COREWAR_MANPAGE) $(COREWAR_MAN_LOCATION)
		@$(GZIP) -f $(COREWAR_MAN_LOCATION)
		@echo "[$(COLOR_PENDING)Putting everything together$(COLOR_RESET)]"
		@echo "[$(COLOR_SUCCESS)Executable $(COREWAR) created$(COLOR_RESET)]"

$(LIBFT): $(LIBFT_SRCS)*.c $(FT_PRINTF_SRCS)*.c
		@echo "Recompiling library"
		@make -C libft/

exec: $(LIBFT)
		@$(COMPILE) $(INCLUDES) $(A) $(ASM_SRC) $(LIBFT) -o $(ASM)
		@$(COMPILE) $(NCURSES) $(INCLUDES) $(C) $(COREWAR_SRC) $(LIBFT) -o $(COREWAR)

clean:
		@make clean -C libft/ > /dev/null

mclean:
		@rm $(ASM_MAN_LOCATION).gz
		@rm $(COREWAR_MAN_LOCATION).gz

fclean: clean mclean
		@rm -fv $(ASM) > /dev/null
		@rm -fv $(COREWAR) > /dev/null
		@make fclean -C libft/ > /dev/null

re: fclean all

.PHONY = all exec clean mclean fclean re
