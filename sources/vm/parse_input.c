/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkonjuha <bkonjuha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:35:39 by bkonjuha          #+#    #+#             */
/*   Updated: 2020/08/02 16:46:07 by bkonjuha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static void	get_player(char *s)
{


}

void		parse_input(char **av)
{
	if (ft_strstr(av[1], ".cor"))
		ft_get_player(av[1]);
	else
		ft_errno(INPUT_ERROR);

}
