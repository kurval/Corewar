/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:45:03 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/04 20:50:42 by bkonjuha         ###   ########.fr       */
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
	long long num;

	if((fd = open(s, O_RDONLY)) < 0)
		ft_errno(INPUT_ERROR);
	else if((num = lseek(fd, 0, SEEK_END) - COREWAR_EXEC_MAGIC) > CHAMP_MAX_SIZE)
		ft_errno(INPUT_ERROR);
	ft_printf("It's fine\n");
	close(fd);
	return (1);
}

void			validate_chapions(char **s)
{
	int i;

	i = 0;
	while (s[++i])
	{
		if (!ends_with_cor(s[i]) || !is_valid_length(s[i]))
			ft_errno(INPUT_ERROR);
	}
}
