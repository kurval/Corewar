// Pseudocode, not meant to be executed as is

#include "../../libft/libft.h"
#include "../../libft/get_next_line.h"
#include "../../includes/op.h"

typedef struct	s_champ
{
	char	*name;
	char	*comment;
	char	*code;
}				t_champ;

void	handle_error(void)
{
	// Print error message
	exit(EXIT_FAILURE);
}

// There can be comments at the end of line so handle this as well

t_champ	*get_champ(int fd)
{
	t_champ	*champ;
	char	*line;

	// Read comments
	while (get_next_line(fd, &line) == 1 && line[0] == COMMENT_CHAR)
		ft_strdel(&line);
	if (!line)
		handle_error();
	// Allocate memory for champ
	if (!(champ = (t_champ *)malloc(sizeof(t_champ))))
		handle_error();
	// Read and save name
		// Check that line starts with NAME_CMD_STRING
		// Check that NAME_CMD_STRING is followed by a name in quotation marks
		// ('"')
		// If name is in multiple lines, handle it
		// Check that name is no longer than PROG_NAME_LENGTH
		// Save name to champ->name
	// Read comments
	while (get_next_line(fd, &line) == 1 && line[0] == COMMENT_CHAR)
		ft_strdel(&line);
	if (!line)
		handle_error();
	// Read and save comment
		// Check that line starts with COMMENT_CMD_STRING
		// Check that COMMENT_CMD_STRING is followed by a name in quotation
		// marks ('"')
		// If comment is in multiple lines, handle it
		// Check that comment is no longer than COMMENT_LENGTH
		// Save comment to champ->comment
	return (champ);
}

char	*get_file_name(int ac, char **av)
{
	char	*file_name;

	// Check that there is only two arguments (./asm champ.s)
	if (ac > 2)
		handle_error();
	// Check that file has extencion .s
	// Return file name without extencion .s
	return (file_name);
}

int		main(int ac, char **av)
{
	t_champ		champ;
	t_statement	*statements;
	char		*exec_code;
	char		*file_name;
	int			fd;

	file_name = get_file_name(ac, av);
	if ((fd = open(file_name)) == -1)
		handle_error();
	champ = get_champ(fd);	// Make sure champion info can't be in the
							// middle of the file
	statements = handle_statements();
	champ->code = convert_champion_code(champ);
	exec_code = convert_statements(statements);
	create_cor_file(file_name);	// Create a file where .s s replace by .cor,
								// check that it's vald
	// Open created file, get fd
	insert_magic_header(fd);	// Add the magic header in the file
	insert_champion(fd, champ.code);
	insert_exec_code(fd, exec_code);
	// Close created .cor file with the fd
	if (close(file_name) == -1)
		handle_error();
}
