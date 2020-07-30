/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:05:18 by jmetelin          #+#    #+#             */
/*   Updated: 2020/07/29 17:05:22 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** Header file used by open
*/

# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"
# include "printf.h"
# include "op.h"

# define INSTRUCTION 1
# define LABEL 2
# define REGISTER 4
# define SEPARATOR 8
# define DIRECT 16
# define DIRECT_LABEL 32
# define INDIRECT 64
# define INDIRECT_LABEL 128
# define STRING 256

/*
** T_champ
** Done: Indicates if champion values have been saved
*/

typedef struct	s_champ
{
	char	*name;
	char	*message;
	int		done;
	char	*code;
}				t_champ;

/*
** T_argument
** Type: Either T_REG, T_IND or T_DIR
** Content: Might have to change this later - not sure if it works
** Size: Size of argument in bytes
*/

typedef struct	s_argument
{
	int		type;
	void	*content;
	int		size;
}				t_argument;

/*
** T_statement
** Name: Command name, for example "live" or "sti"
** Args: Args[0] will be the first argument, args[MAX_ARGS_NUMBER - 1] is null.
**       If there are less than MAX_ARGS_NUMBER -1 arguments, pad with null.
** Size: Statement code size + argument sizes in bytes
** Place: Iterator place. For example for the first stament, this value will be
**        0. If the 1st statement size is 7, this value will be 7 for the second
**        argument.
*/

typedef struct	s_statement
{
	int					code;
	char				*name;
	t_argument			args[MAX_ARGS_NUMBER];
	int					size;
	int					place;
	struct s_statement	*next;
}				t_statement;

/*
** T_label
** Place: The statement location the label points to
*/

typedef struct	s_label
{
	char			*name;
	int				place;
	struct s_label	*next;
}				t_label;

typedef struct	s_cursor
{
	int	row;
	int	col;
}				t_cursor;

typedef struct	s_token
{
	int				type;
	char			*content;
	t_cursor		*cursor;
	struct s_token	*next;
}				t_token;

void			parse_file(int fd);
int				is_valid_char(char c);
int				skip_whitespaces(char *line, int i);
t_token			*tokenize(char *line, t_cursor cursor);
int				find_first_char(char *str, int start, char *chars);
int				find_last_char(char *str, int start, char *chars);
char			*merge_strs(char *s1, char *s2);
void			handle_error(char *msg);
void			check_params(int ac, char **av);

#endif
