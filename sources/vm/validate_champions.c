/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:45:03 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/28 21:50:52 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	ends_with_cor(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	if (!(ft_strequ(s + i - 4, ".cor")))
		return (0);
	return (1);
}

static int	is_valid_length(char *s)
{
	int fd;
	int num;

	num = -1;
	if ((fd = open(s, O_RDONLY)) < 0)
		ft_errno(OPEN_ERROR);
	else if ((num = lseek(fd, 0, SEEK_END) - sizeof(t_header)) > CHAMP_MAX_SIZE)
		ft_errno(CHAMP_ERROR);
	close(fd);
	return (1);
}

int			validate_chapions(char **s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[++i])
	{
		if ((ft_strequ(s[i], "-a") || ft_strequ(s[i], "-v")) ||
		((ft_strequ(s[i], "-n") || ft_strequ(s[i], "-dump")) && i++))
			continue ;
		count += ends_with_cor(s[i]);
		is_valid_length(s[i]);
	}
	return (count);
}
