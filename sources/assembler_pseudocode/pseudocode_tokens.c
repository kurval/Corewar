#include "../../includes/op.h"

/* Start reading from the bottom function */

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

typedef struct	s_cursor
{
	int		row;
	int		col;
}				t_cursor;

typedef struct	s_token
{
	int		type;
	char	*content;
	int		col_location; //could also be t_cursor type
	struct s_token *next;
}				t_token;

t_token		*create_direct_token(char *line, t_cursor *cursor)
{
	t_token *token;
	int		temporary_col;

	token = malloc(sizeof token);
	token->col_location = cursor->col; // Save the token location for later error handling
	cursor->col++;
	if (line[cursor->col] == LABEL_CHAR)
	{
		token->type = DIRECT_LABEL;
		temporary_col = cursor->col; //Save start of token content for later
		cursor->col++;
		if (line[cursor->col] != label chars) //handle cases like "%: label"
			handle_lexical_error(cursor);
		while (line[cursor->col] != whitespaces/separator/comment/label_char)
		{
			if (line[cursor->col] != label chars)
				handle_lexical_error(cursor);
			cursor->col++;
		}
		token->content = substr(line, temporary_col, characters until cursor->col);
	}
	else if (isdigit(line[cursor->col]))
	{
		token->type = DIRECT;
		// handle same way as the LABEL_CHAR case, but a non-digit character will result in
		// lexical error
	}
	else
		handle_lexical_error(cursor);
	return (token);
}

t_token		*create_registry_token(char *line, t_cursor *cursor)
{
	Check create_direct_token.
	Need to check that r is followed by digits, and that
	the token content will be at most 3 characters (max is r99).
	token content will end in usual end characters (label char,
	separator char, whitespaces. comment char).
	If content length is not 2 or 3 characters (for example "r", "r1000",
	create INSTRUCTION type token instead);
	Invalid characters will result in lexical error.
}

t_token		*create_indirect_token(char *line, t_cursor *cursor)
{
	Check create_direct_token.
	If the first character is label char, make sure the
	characters after that are valid label characters.
	Token content will end with whitespaces/separator/comment/label_char.

	If the first character is a digit, token content will end with any
	non-digit character.

	in both cases an invalid character (not defined as valid label characters)
	will result in lexical error.
}

t_token		*create_instruction_or_label(char *line, t_cursor *cursor)
{
	Check create_direct_token.
	Check if the last character before comment char/newline is a LABEL_CHAR.
	If yes, make LABEL type token. If no, make INSTRUCTION token. Usual rules
	about ending characters and invalid characters apply.
}

t_token		*make_token(char *line, t_cursor *cursor)
{
	t_token *token;

	//Could also add champion-related things here as their own token types
	if (line[cursor->col] == SEPARATOR_CHAR)
	{
		token = malloc(size of token);
		token->content = make_a_string_that_has_separator_char;
		token->type = SEPARATOR;
		token->next = NULL;
	}
	else if (line[cursor->col] == DIRECT_CHAR)
		token = create_direct_token(line, cursor)
	else if (line[cursor->col] == 'r')
		token = create_registry_token(line, cursor);
	else if (line[cursor->col] == LABEL_CHAR || is_digit(line[col]))
		token = create_indirect_token(line, cursor);
	else if (line[cursor->col] == '\n')
		token = create_endline_token(line, cursor); //A simple token of type ENDLINE, col location will be the index of \n 
												   //(or the length of line, one or the other, need to check)
	else
		token == create_instruction_or_label(line, cursor);
	return (token);
}

t_token		*tokenize(char *line, t_cursor cursor)
{
	t_token *token;
	t_token *head;

	cursor.col = 0;
	head = NULL;
	while (line[cursor.col)
	{
		cursor.col = skip_whitespaces_except_newline_and_handle_error_if_invalid_char(line);
		if (!head)
		{
			token = make_token(line, &cursor);
			head = token;
		}
		else
		{
			token->next = make_token(line, &cursor);
			token = token->next;
		}
	}
	return (head);
}

int		check_token_order()
{
	Check that tokens follow one of these orders:
	// ARGUMENTS = any argument type token, like INDIRECT, DIRECT_LABEL, REGISTRY etc
	1. LABEL -> INSTRUCTION -> ARGUMENTS (-> SEPARATOR -> ARGUMENTS -> SEPARATOR -> ARGUMENTS) -> ENDLINE
	2. LABEL -> create_endline_token
	//Could have other valid ones too, need to make sure
	In case the wrong type of token is found, create a syntax error that prints
	the current row number and the col location of the invalid token.
}

int		check_if_tokens_are_valid()
{
	Check that tokens are valid (right amount of arguments, instruction is an existing one etc).
	Can use the op table to determine the validity.
}


void			parse_file()
{
	char	*line;
	t_cursor	cursor; //Our current place in the file (row/col)
	t_token		*tokens;
	t_statement *statement;

	cursor->row = 0;
	while (get_next_line(&line))
	{
		cursor->col = 0;
		tokens = tokenize(line, cursor);
		check_token_order(tokens, cursor);
		check_if_tokens_are_valid(tokens, cursor);
		statement->next = save_statement(tokens); // save statements into a struct.
		statement = statement->next;
		delete_tokens(tokens);
		free(line);
		cursor->row++;
	}
}