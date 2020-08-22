#include <sys/stat.h> 
#include <fcntl.h>
#include "../../../libft/libft.h"
#include "../../../libft/printf/includes/printf.h"

#define GREEN 0
#define RED 1
#define YELLOW 2

void	set_print_colour(int colour)
{
	if (colour == RED)
		ft_printf("\033[0;31m");
	else if (colour == YELLOW)
		ft_printf("\033[0;33m");
	else
		ft_printf("\033[0;32m");
}

int		check_diff_type(char *line_ours, char *line_orig)
{
	int i;

	if (ft_atoi(line_ours) != ft_atoi(line_orig))
	{
		set_print_colour(RED);
		return (2);
	}
	i = 0;
	while (ft_isdigit(line_ours[i]))
		i++;
	if (ft_strequ(&line_ours[i + 1], "abort"))
	{
		set_print_colour(RED);
		return (3);
	}
	if (ft_strequ(&line_orig[i + 1], "abort"))
	{
		set_print_colour(YELLOW);
		return (4);
	}
	if (ft_strncmp(&line_ours[i + 1], "Writing output program to", 25) == 0 ||
	ft_strncmp(&line_orig[i + 1], "Writing output program to", 25) == 0)
	{
		set_print_colour(YELLOW);
		return (1);
	}
	else
	{
		set_print_colour(GREEN);
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
		ft_printf(" likely segfault or other similar error ");
		ft_printf("in the test before the first line number error\n");
	}
	if (result == 3)
		ft_printf("Warning! Segfault or something similar\n");
	if (result == 4)
		ft_printf("Original asm segfault or something similar\n");
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
		if (!ft_strequ(line_ours, line_orig) || ft_strequ(line_ours, "abort"))
		{
			ft_printf("------------------------------------------------------------------------------\n");
			result = check_diff_type(line_ours, line_orig);
			print_line_heading(i, result);
			ft_printf("Ours > %s\nOrig > %s\n", line_ours, line_orig);
		}
		i++;
	}
	ft_printf("------------------------------------------------------------------------------\n");
	close(fd_ours);
	close(fd_orig);
	return (0);
}