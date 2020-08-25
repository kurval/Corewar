/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:45:03 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/25 17:32:12 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	ends_with_cor(char *s)
{
	int i;

	i = 0;
	while(s[i])
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
	if((fd = open(s, O_RDONLY)) < 0)
		ft_errno(OPEN_ERROR);
	else if((num = lseek(fd, 0, SEEK_END) - sizeof(header_t)) > CHAMP_MAX_SIZE)
		ft_errno(CHAMP_ERROR);
	close(fd);
	return (1);
}

void			validate_chapions(char **s)
{
	int i;

	i = 0;
	while (s[++i])
	{
		if ((ft_strequ(s[i], "-a")) || ((ft_strequ(s[i], "-n")
			|| ft_strequ(s[i], "-dump")) && i++))
			continue ;
		if (!ends_with_cor(s[i]) || !is_valid_length(s[i]))
			ft_errno(INPUT_ERROR);
	}
}
