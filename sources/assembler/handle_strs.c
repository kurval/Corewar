/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_strs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmetelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:39:03 by jmetelin          #+#    #+#             */
/*   Updated: 2020/08/06 17:39:03 by jmetelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		del_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		ft_strdel(&array[i++]);
	free(array);
}

char		*join_free_strs(char *s1, char *s2)
{
	char	*joined;

	joined = NULL;
	if (!s2)
		handle_error(MALLOC_ERROR);
	else if (s1)
	{
		if (!(joined = ft_strjoin(s1, s2)))
			handle_error(MALLOC_ERROR);
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	else
		return (s2);
	return (joined);
}

/*
** Add_strs_to_str
** Loops str until the pattern, "%s", or the end of the string is found. Adds a
** string from strs to the position.
*/

char		*add_strs_to_str(char *str, char **strs)
{
	char	*merged;
	int		start;
	int		end;
	int		i;

	merged = NULL;
	start = 0;
	i = 0;
	while ((end = find_first_str(str, start, "%s")) != -1)
	{
		if (end - start)
			merged = join_free_strs(merged, ft_strsub(str, start, end - start));
		if (strs[i])
			merged = join_free_strs(merged, ft_strdup(strs[i++]));
		start = end + 2;
	}
	if ((end = ft_strlen(str)) - start)
		merged = join_free_strs(merged, ft_strsub(str, start, end - start));
	return (merged);
}

/*
** Add_str_to_str
** 1. Count the len of s1 without "%" and "%s".
** 2. Allocate memory for merged of size: the counted len of s1 + the len of s2.
** 3. Copy s1 to merged char by char until '%' is found.
** 4. A) '%' is found: If the next char is 's', copy s2 to merged. If the char
**                     is NOT 's', copy the char to merged. If there is s1 left,
**                     copy the rest of s1 to merged.
**    B) '%' is NOT found: Copy s2 to the end of merged.
*/

static int	count_s1_len(char *s1)
{
	int	s1_len;

	s1_len = 0;
	while (s1 && *s1)
	{
		if (*s1 == '%')
		{
			if (++s1 && *s1 == 's')
				s1++;
		}
		else
		{
			s1_len++;
			s1++;
		}
	}
	return (s1_len);
}

char		*add_str_to_str(char *s1, char *s2)
{
	char	*merged;
	int		i;

	if (!(merged = (char *)malloc(sizeof(char *) * (count_s1_len(s1) +
	ft_strlen(s2) + 1))))
		handle_error("Malloc error");
	i = 0;
	while (s1 && *s1)
	{
		if (*s1 == '%' && ++s1 && *s1 == 's')
		{
			while (s2 && *s2)
				merged[i++] = *s2++;
			s1++;
		}
		else if (*s1)
			merged[i++] = *s1++;
	}
	while (s2 && *s2)
		merged[i++] = *s2++;
	merged[i] = '\0';
	return (merged);
}
