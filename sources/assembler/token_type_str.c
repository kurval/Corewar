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

char			*token_type_str(t_type type)
{
	if (type == reg)
		return ("REGISTER");
	if (type == direct)
		return ("SIRECT");
	if (type == indirect)
		return ("INDIRECT");
	if (type == instruction)
		return ("INSTRUCTION");
	if (type == label)
		return ("LABEL");
	if (type == separator)
		return ("SEPARATOR");
	if (type == string)
		return ("STRING");
	if (overlap(type, cmd_str))
		return (type == command_name ? "COMMAND_NAME" : "COMMAND_COMMENT");
	if (type == direct_label)
		return ("DIRECT_LABEL");
	if (type == indirect_label)
		return ("INDIRECT_LABEL");
	if (type == indirect)
		return ("INDIRECT");
	if (type == endline)
		return ("ENDLINE");
	return (NULL);
}
