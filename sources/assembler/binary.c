#include "asm.h"

int			convert_dec(char *binary, int size)
{
	int multiplier;
	int i;
	int result;

	multiplier = 1;
	i = size - 1;
	result = 0;
	while (i >= 0)
	{
		if (binary[i] == '1')
			result = result + multiplier;
		i--;
		multiplier = multiplier * 2;
	}
	ft_strdel(&binary);
	return (result);
}

char	*make_rev_binary_str(int nbr)
{
	char	*binary;
	int		i;

	binary = ft_strnew(16);
	i = 15;
	while (i >= 0)
	{
		binary[i] = (nbr % 2 ? '0' : '1');
		i--;
		nbr = nbr / 2;
	}
	return (binary);
}