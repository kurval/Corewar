/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:07 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:10 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/errno.h>

/*
** Main
** 1. Check the params
** 2. Try to open the .s file
** 3. Parse file
** 4. Try to close the .s file
*/

int	main(int ac, char **av)
{
	char	*msg;
	int		fd;

	check_params(ac, av);
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		msg = merge_strs("Can't read source file ", av[1], 23);
		handle_error(msg);
		ft_strdel(&msg);
	}
	parse_file(fd);
	if (close(fd) == -1)
	{
		msg = merge_strs("Can't close source file ", av[1], 23);
		if (errno == EBADF)
			ft_printf("ebadf\n");
		if (errno == EINTR)
			ft_printf("eio\n");
		if (errno == EBADF)
			ft_printf("eio\n");
		handle_error(msg);
		ft_strdel(&msg);
	}
	return (0);
}
