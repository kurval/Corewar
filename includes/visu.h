/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:48:50 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/03 13:50:02 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <ncurses.h>
# include <locale.h>

# define HEIGHT 68
# define WIDTH  197

# define ESC    27
# define SPACE  32

# define LIVE_ON    50
# define NEW_MEM    50

# define GRAY_B         0
# define G_B            1
# define B_B            2
# define R_B            3
# define C_B            4
# define M_B            5
# define W_B            6
# define Y_B            7
# define GRAY_CURSOR    10
# define G_CURSOR       11
# define B_CURSOR       12
# define R_CURSOR       13
# define C_CURSOR       14
# define G_LIVE         21
# define B_LIVE         22
# define R_LIVE         23
# define C_LIVE         24
# define GRAY           15
# define WHITE          16
# define FRAME          17

# define L1  L" ▄████▄   ▒█████   ██▀███  ▓█████  █     █░ ▄▄▄       ██▀███  "
# define L2  L"▒██▀ ▀█  ▒██▒  ██▒▓██ ▒ ██▒▓█   ▀ ▓█░ █ ░█░▒████▄    ▓██ ▒ ██▒"
# define L3  L"▒▓█    ▄ ▒██░  ██▒▓██ ░▄█ ▒▒███   ▒█░ █ ░█ ▒██  ▀█▄  ▓██ ░▄█ ▒"
# define L4  L"▒▓▓▄ ▄██▒▒██   ██░▒██▀▀█▄  ▒▓█  ▄ ░█░ █ ░█ ░██▄▄▄▄██ ▒██▀▀█▄  "
# define L5  L"▒ ▓███▀ ░░ ████▓▒░░██▓ ▒██▒░▒████▒░░██▒██▓  ▓█   ▓██▒░██▓ ▒██▒"
# define L6  L"░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░░░ ▒░ ░░ ▓░▒ ▒   ▒▒   ▓▒█░░ ▒▓ ░▒▓░"
# define L7  L"  ░  ▒     ░ ▒ ▒░   ░▒ ░ ▒░ ░ ░  ░  ▒ ░ ░    ▒   ▒▒ ░  ░▒ ░ ▒░"
# define L8  L"░        ░ ░ ░ ▒    ░░   ░    ░     ░   ░    ░   ▒     ░░   ░ "
# define L9  L"░ ░          ░ ░     ░        ░  ░    ░          ░  ░   ░     "
# define L10  L"░                                                             "

# define PL1_1  L"   ___  __   _____  _________    ___"
# define PL1_2  L"  / _ \\/ /  / _ \\ \\/ / __/ _ \\  <  /"
# define PL1_3  L" / ___/ /__/ __ |\\  / _// , _/  / / "
# define PL1_4  L"/_/  /____/_/ |_|/_/___/_/|_|  /_/  "

# define PL2_1  L"   ___  __   _____  _________    ___ "
# define PL2_2  L"  / _ \\/ /  / _ \\ \\/ / __/ _ \\  |_  |"
# define PL2_3  L" / ___/ /__/ __ |\\  / _// , _/ / __/ "
# define PL2_4  L"/_/  /____/_/ |_|/_/___/_/|_| /____/ "

# define PL3_1  L"   ___  __   _____  _________    ____"
# define PL3_2  L"  / _ \\/ /  / _ \\ \\/ / __/ _ \\  |_  /"
# define PL3_3  L" / ___/ /__/ __ |\\  / _// , _/ _/_ < "
# define PL3_4  L"/_/  /____/_/ |_|/_/___/_/|_| /____/ "

# define PL4_1  L"   ___  __   _____  _________    ____"
# define PL4_2  L"  / _ \\/ /  / _ \\ \\/ / __/ _ \\  / / /"
# define PL4_3  L" / ___/ /__/ __ |\\  / _// , _/ /_  _/"
# define PL4_4  L"/_/  /____/_/ |_|/_/___/_/|_|   /_/  "

# define B1  L"    ____  ___  ______________    ______   _____   ____________ "
# define B2  L"   / __ )/   |/_  __/_  __/ /   / ____/  /  _/ | / / ____/ __ \\"
# define B3  L"  / __  / /| | / /   / / / /   / __/     / //  |/ / /_  / / / /"
# define B4  L" / /_/ / ___ |/ /   / / / /___/ /___   _/ // /|  / __/ / /_/ / "
# define B5  L"/_____/_/  |_/_/   /_/ /_____/_____/  /___/_/ |_/_/    \\____/  "

# define WIN1  L"██╗    ██╗██╗███╗   ██╗███████╗"
# define WIN2  L"██║    ██║██║████╗  ██║██╔════╝"
# define WIN3  L"██║ █╗ ██║██║██╔██╗ ██║███████╗"
# define WIN4  L"██║███╗██║██║██║╚██╗██║╚════██║"
# define WIN5  L"╚███╔███╔╝██║██║ ╚████║███████║"
# define WIN6  L" ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝"

# define S1 L"█ █ █ █ █ █ █ █ █ █ █ MAX"
# define S2 L"█ █ █ █ █ █ █ █ █ █   MAX"
# define S3 L"█ █ █ █ █ █ █ █ █     MAX"
# define S4 L"█ █ █ █ █ █ █ █       MAX"
# define S5 L"█ █ █ █ █ █ █         MAX"
# define S6 L"█ █ █ █ █ █           MAX"
# define S7 L"█ █ █ █ █             MAX"
# define S8 L"█ █ █ █               MAX"
# define S9 L"█ █ █                 MAX"
# define S10 L"█ █                   MAX"
# define S11 L"█                     MAX"

#endif
