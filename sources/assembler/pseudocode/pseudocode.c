

/* THIS CODE IS NOT MEANT TO BE RUN,
** IT'S JUST A DEMONSTRATION
*/

typedef struct	s_champion
{
	char	*name;
	char	*message;
	int		done; // Indicates if champion values have been saved
	char	*code;
}				t_champion;

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

void		save_champion_info(t_champion *champ, int fd)
{
	char *line;
	char *needle;

	//gnl should be modified to have a \n in the end if it doesn't already
	// Comments handling needs to be included - not yet in this pseudocode
	while (get_next_line(&line) && champ->done != 3);
	{
		if ((needle = strstr(line, NAME_CMD_STRING))) //pointer to where the command starts
		{
			if (champ->done & 1)
				handle_error_double_name();
			if (!(needle = strchr(needle, '"')); // Pointer to where the first " is found
				handle_error_no_name_string();
			while (needle[namesize] != '"' && needle[namesize] != '\n')
				namesize++;
			//handle in case the 2nd " is not found (name will continue over multiple rows,
			// check "Lexical analysis" in the manual)
			champ->name = strsub(&needle[1], 0, namesize);
			champ->done = (champ->done | 1); // only save if both " are found
		}
		if ((needle = strstr(line, COMMENT_CMD_STRING)))
		{
			if (champ->done & 2)
				handle_error_double_comment();
			if (!(needle = strchr(needle, '"')); // Pointer to where the first " is found
				handle_error_no_comment_string();
			while (needle[commentsize] != '"' && needle[commentsize] != '\n')
				commentsize++;
			//handle in case the 2nd " is not found (comment will continue over multiple rows,
			// check "Lexical analysis" in the manual)
			champ->name = strsub(&needle[1], 0, commentsize);
			champ->done = (champ->done | 2); // only save if both " are found
		}
	}
}

t_statement *handle_statements(char *line)
{
	int i;
	t_statement *current;
	t_statement *head;
	t_label *labels;
	
	i = 0;
	head = NULL;
	while (get_next_line(&line))
	{
		if (line is empty)
			continue ;
		if (label found)
        {
			check_if_label_already_exists();
		  	labels->next = make_label(i, label name);
			labels = labels->next; // remember to handle the first one correctly and set head
		}
		check_if_valid_statement(line);
		//obviously handle the first statement differently + set head
		statement->next = make_statement(line, i); //set statement->place to be i
		statement = statement->next;
		i = i + statement->size;
	}
	return (head);
}

int main(int argc, char **argv)
{
	int 		i;
	char 		*line;
	t_champion 	champ;
	t_statement *statements;
	char		*exec_code;

	champ.done = 0;
	fd = open(s-file);
	save_champion_info(&champ, fd); // Make sure champion info can't be in the middle of
									   // the file
	statements = handle_statements(line);
	champ->code = convert_champion_code(champ);
	exec_code = convert_statements(statements);
	create_cor_file(argv[1]); //create a file where .s s replace by .cor, check that it's vald
	insert_magic_header(); //Add the magic header in the file
	insert_champion(champ.code);
	insert_exec_code(exec_code);
	close(s-file);
}