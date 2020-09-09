/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_gnl_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkurkela <vkurkela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 10:26:05 by vkurkela          #+#    #+#             */
/*   Updated: 2020/02/27 15:33:29 by vkurkela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** This function checks if it finds linebreak and stores
** the line ending '\n' to *line variable and sets *s
** variable to right location. If there is no linebreak
** it copies the end and frees the *s variable. If it reach
** the end of a file we can free the memory of *s beacause.
*/

static int	get_line_len(char **s)
{
	int str_char_count;
	int len;

	len = 0;
	str_char_count = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
	{
		if ((*s)[len] == '"')
			str_char_count++;
		len++;
		while ((*s)[len] == '\n' && str_char_count % 2 != 0)
			len++;
	}
	return (len);
}

static int	get_line(char **s, char **line)
{
	int		len;
	char	*temp;

	len = get_line_len(s);
	if ((*s)[len] == '\n')
	{
		if ((!(*line = ft_strsub(*s, 0, len + 1))) ||\
		!(temp = ft_strdup(&((*s)[len + 1]))))
			return (-1);
		ft_strdel(s);
		*s = temp;
		if ((*s)[0] == '\0')
			ft_strdel(s);
	}
	else
	{
		if (!(*line = ft_strdup(*s)))
			return (-1);
		ft_strdel(s);
	}
	return (1);
}

/*
** Returns a value 1 if line has been read,
** 0 when the reading has been completed or
** -1 if an error has happened respectively.
*/

int			ret_value(char **s, char **line, int ret, int fd)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && s[fd] == NULL)
		return (0);
	else
		return (get_line(&s[fd], line));
}

static int	count_string_chars(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count);
}

/*
** Gnl checks if static variable is empty and then allocates
** memory for it using buff and see if it contains line break
** character. Next iterations will store the data from fd and
** stores it after the previous data. Then it  must free
** the memory and copy temp andress so it won't loose the data.
** If line break occurs then function breaks and calls next function.
*/

int			store_line(char *buff, char **s, int *ret, int fd)
{
	char		*temp;

	buff[*ret] = '\0';
	if (s[fd] == NULL)
	{
		if (!(s[fd] = ft_strdup(buff)))
			return (-1);
	}
	else
	{
		if (!(temp = ft_strjoin(s[fd], buff)))
			return (-1);
		free(s[fd]);
		s[fd] = temp;
	}
	if (ft_strchr(s[fd], '\n'))
	{
		if (count_string_chars(s[fd]) % 2 == 0)
			return (0);
	}
	return (1);
}
