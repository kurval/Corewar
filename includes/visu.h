/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:48:50 by vkurkela          #+#    #+#             */
/*   Updated: 2020/09/02 12:49:26 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <ncurses.h>
# include <locale.h>

# define HEIGHT (MEM_SIZE / 64 + 4)
# define WIDTH ((MEM_SIZE / 64) * 3 + 4)

# define ESC    27
# define SPACE  32

# define GREEN	1
# define B_B	2
# define Y_B	3
# define R_B	4
# define M_B	5
# define G_B	6
# define W_B	7
# define GREEN_CURSOR 8
# define B_CURSOR 9
# define Y_CURSOR 10
# define R_CURSOR 11
# define G_CURSOR 12
# define GRAY	13
# define WHITE	14
# define FRAME	15

# define LOGO1  L" ▄████▄   ▒█████   ██▀███  ▓█████  █     █░ ▄▄▄       ██▀███  "
# define LOGO2  L"▒██▀ ▀█  ▒██▒  ██▒▓██ ▒ ██▒▓█   ▀ ▓█░ █ ░█░▒████▄    ▓██ ▒ ██▒"
# define LOGO3  L"▒▓█    ▄ ▒██░  ██▒▓██ ░▄█ ▒▒███   ▒█░ █ ░█ ▒██  ▀█▄  ▓██ ░▄█ ▒"
# define LOGO4  L"▒▓▓▄ ▄██▒▒██   ██░▒██▀▀█▄  ▒▓█  ▄ ░█░ █ ░█ ░██▄▄▄▄██ ▒██▀▀█▄  "
# define LOGO5  L"▒ ▓███▀ ░░ ████▓▒░░██▓ ▒██▒░▒████▒░░██▒██▓  ▓█   ▓██▒░██▓ ▒██▒"
# define LOGO6  L"░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒▓ ░▒▓░░░ ▒░ ░░ ▓░▒ ▒   ▒▒   ▓▒█░░ ▒▓ ░▒▓░"
# define LOGO7  L"  ░  ▒     ░ ▒ ▒░   ░▒ ░ ▒░ ░ ░  ░  ▒ ░ ░    ▒   ▒▒ ░  ░▒ ░ ▒░"
# define LOGO8  L"░        ░ ░ ░ ▒    ░░   ░    ░     ░   ░    ░   ▒     ░░   ░ "
# define LOGO9  L"░ ░          ░ ░     ░        ░  ░    ░          ░  ░   ░     "
# define LOGO10  L"░                                                             "

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

# define BI1  L"    ____  ___  ______________    ______   _____   ____________ "
# define BI2  L"   / __ )/   |/_  __/_  __/ /   / ____/  /  _/ | / / ____/ __ \\"
# define BI3  L"  / __  / /| | / /   / / / /   / __/     / //  |/ / /_  / / / /"
# define BI4  L" / /_/ / ___ |/ /   / / / /___/ /___   _/ // /|  / __/ / /_/ / "
# define BI5  L"/_____/_/  |_/_/   /_/ /_____/_____/  /___/_/ |_/_/    \\____/  "

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
                                                                                                                                              