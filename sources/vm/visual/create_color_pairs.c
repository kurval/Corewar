/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_color_pairs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 11:20:24 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/02 15:11:56 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/visu.h"

void define_colors(void)
{
    start_color();
    init_color(GRAY, 300, 300, 300);
    init_color(WHITE, 1000, 1000, 1000);
    init_pair(FRAME, COLOR_BLACK, COLOR_RED);
    init_pair(R_B, COLOR_RED, COLOR_BLACK);
    init_pair(M_B, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(Y_B, COLOR_YELLOW, COLOR_BLACK);
    init_pair(C_B, COLOR_CYAN, COLOR_BLACK);
    init_pair(B_B, COLOR_BLUE, COLOR_BLACK);
    init_pair(G_B, GRAY, COLOR_BLACK);
    init_pair(W_B, WHITE, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(GREEN_CURSOR, COLOR_BLACK, COLOR_GREEN);
    init_pair(B_CURSOR, COLOR_BLACK, COLOR_BLUE);
    init_pair(C_CURSOR, COLOR_BLACK, COLOR_CYAN);
    init_pair(R_CURSOR, COLOR_BLACK, COLOR_RED);
    init_pair(G_CURSOR, COLOR_BLACK, GRAY);
}