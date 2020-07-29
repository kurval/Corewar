#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include "printf.h"
# include "get_next_line.h"

# define INSTRUCTION 1
# define LABEL 2
# define REGISTER 4
# define SEPARATOR 8
# define DIRECT 16
# define DIRECT_LABEL 32
# define INDIRECT 64
# define INDIRECT_LABEL 128
# define STRING 256

typedef struct	s_champ
{
	char	*name;
	char	*message;
	int		done; // Indicates if champion values have been saved
	char	*code;
}				t_champ;

typedef struct	s_argument
{
	int		type; //Either T_REG, T_IND r T_DIR
	void	*content; // Might have to change this later - not sure if it works
	int		size; //size of argument in bytes
}				t_argument;

typedef struct	s_statement
{
	int			code;
	char		*name; //command name, for example "live" or "sti"
	t_argument 	args[MAX_ARGS_NUMBER]; //args[0] will be the first argument, args[MAX_ARGS_NUMBER - 1] is null.
						// If there are less than MAX_ARGS_NUMBER -1 arguments, pad with null.
	int			size; //Statement code size + argument sizes in bytes
	int			place; 	// Iterator place. For example for the first stament, this
						//value will be 0. If the 1st statement size is 7, this value will be 7 for
						// the second argument.
	struct s_statement *next;
}				t_statement;

typedef struct	s_label
{
	char	*name;
	int		place; //the statement location the label points to
	struct s_label *next;
}				t_label;

typedef struct	s_cursor
{
	int		row;
	int		col;
}				t_cursor;

typedef struct	s_token
{
	int			type;
	char		*content;
	t_cursor	*cursor;
	struct s_token *next;
}				t_token;

void	parse_file(int fd);
int		is_valid_char(char c);
int		skip_whitespaces(char *line, int i);
t_token	*tokenize(char *line, t_cursor cursor);

# endif