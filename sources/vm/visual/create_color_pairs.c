/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_color_pairs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 11:20:24 by vkurkela          #+#    #+#             */
/*   Updated: 2020/08/29 13:08:46 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/corewar.h"

void define_colors(void)
{
    //use_default_colors();
    start_color();
    init_color(GRAY, 300, 300, 300);
    init_color(BLACK, 0, 0, 0);
    init_pair(FRAME, COLOR_BLACK, COLOR_RED);
    init_pair(R_B, COLOR_RED, COLOR_BLACK);
    init_pair(M_B, COLOR_MAGENTA, BLACK);
    init_pair(Y_B, COLOR_YELLOW, BLACK);
    init_pair(B_B, COLOR_BLUE, BLACK);
    init_pair(G_B, GRAY, BLACK);
    init_pair(GREEN, COLOR_GREEN, BLACK);
}