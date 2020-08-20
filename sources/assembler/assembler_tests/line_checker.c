#include <sys/stat.h> 
#include <fcntl.h>
#include "../../../libft/libft.h"
#include "../../../libft/printf/includes/printf.h"

void	set_print_colour(int colour)
{
	if (colour == 1)
		ft_printf("\033[0;31m");
	else
		ft_printf("\033[0;32m");
}

int		check_diff_type(char *line_ours, char *line_orig)
{
	int i;

	if (ft_atoi(line_ours) != ft_atoi(line_orig))
		return (2);
	i = 0;
	while (ft_isdigit(line_ours[i]))
		i++;
	if (ft_strncmp(&line_ours[i + 1], "Writing output program to", 25) == 0 ||
	ft_strncmp(&line_orig[i + 1], "Writing output program to", 25) == 0)
	{
		set_print_colour(1);
		return (1);
	}
	else
	{
		set_print_colour(0);
		return (0);
	}	
}

void	print_line_heading(int i, int result)
{
	ft_printf("line %d - ", i);
	if (result == 0)
		ft_printf("Ok, both are errors\n");
	if (result == 1)
		ft_printf("Warning! One got an error, one created cor file\n");
	if (result == 2)
	{
		ft_printf("Warning! Test numbers differ -");
		ft_printf(" likely segfault or other similar error\n");
	}
	ft_printf("\033[0m");
}

int	main(int argc, char **argv)
{
	int 	fd_ours;
	int		fd_orig;
	char	*line_ours;
	char	*line_orig;
	int		i;
	int		result;

	fd_ours = open(argv[1], O_RDONLY);
	fd_orig = open(argv[2], O_RDONLY);
	i = 1;
	while (get_next_line(fd_ours, &line_ours) && get_next_line(fd_orig, &line_orig))
	{
		if (!ft_strequ(line_ours, line_orig))
		{
			result = check_diff_type(line_ours, line_orig);
			print_line_heading(i, result);
			ft_printf("Ours > %s\nOrig > %s\n", line_ours, line_orig);
		}
		i++;
	}
	close(fd_ours);
	close(fd_orig);
	return (0);
}