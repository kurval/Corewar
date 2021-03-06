/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:45:03 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/09/22 08:26:09 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int			ends_with_cor(char *s)
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
		ft_errno(OPEN_ERROR, s);
	num = lseek(fd, 0, SEEK_END);
	if ((num - sizeof(t_header)) > CHAMP_MAX_SIZE
			|| num < (int)sizeof(t_header))
		ft_errno(CHAMP_ERROR, s);
	close(fd);
	return (1);
}

static int	valid_n_input(char **s, int i)
{
	if (!s[i + 1] || !s[i + 2] || !ft_isdigit(s[i + 1][0])
		|| !ends_with_cor(s[i + 2]) || s[i + 1][1])
		ft_errno(N_FLAG_INPUT, "check your -n flag");
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
		if ((ft_strequ(s[i], "-a") || ft_strequ(s[i], "-v") ||
			(ft_strequ(s[i], "-l"))) || (((ft_strequ(s[i], "-n")
			&& valid_n_input(s, i)) || ft_strequ(s[i], "-dump")
			|| ft_strequ(s[i], "-d")) && i++))
			continue ;
		count += ends_with_cor(s[i]);
		count > 4 ? ft_errno(CHAMP_NUM_ERROR, s[i]) : 0;
		is_valid_length(s[i]);
		has_magic_header(s[i]);
	}
	count ? 0 : ft_errno(MISSING_CHAMP, "No chapmion found");
	return (count);
}
