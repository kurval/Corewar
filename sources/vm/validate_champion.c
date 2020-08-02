/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:45:03 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/02 16:56:58 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static int	ends_with_cor(char *s)
{
	int i;

	i = 0;
	while(s[i])
		i++;
	if (!ft_strequ(s + i - 4, ".cor"))
		return (0);
	return (1);
}

static int	is_valid_length(char *s)
{
	int fd;

	fd = open(s, O_RDONLY);

}

char		*validate_chapion(char *s)
{
	if (!(ends_with_cor(s) || is_valid_length(s)))
		ft_errno(INPUT_ERROR);
}
