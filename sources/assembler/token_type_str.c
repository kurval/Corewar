/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atuomine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:17:19 by atuomine          #+#    #+#             */
/*   Updated: 2020/07/29 15:17:21 by atuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

char			*token_type_str(int type)
{
	if (type == REGISTER)
		return ("REGISTER");
	if (type == DIRECT)
		return ("DIRECT");
	if (type == INDIRECT)
		return ("INDIRECT");
	if (type == INSTRUCTION)
		return ("INSTRUCTION");
	if (type == LABEL)
		return ("LABEL");
	if (type == SEPARATOR)
		return ("SEPARATOR");
	if (type == STRING)
		return ("STRING");
	if (overlap(type, CMD_STR))
		return (type == COMMAND_NAME ? "COMMAND_NAME" : "COMMAND_COMMENT");
	if (type == DIRECT_LABEL)
		return ("DIRECT_LABEL");
	if (type == INDIRECT_LABEL)
		return ("INDIRECT_LABEL");
	if (type == INDIRECT)
		return ("INDIRECT");
	if (overlap(type, ENDLINE))
		return (type == ENDLINE ? "ENDLINE" : "END");
	return (NULL);
}
