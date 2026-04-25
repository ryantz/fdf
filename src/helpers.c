#include "fdf.h"

// 0xffffff
char	*convert_string_to_lower(char **str);

int	hex_to_dec(char *str)
{
	int	converted;
	int	i;
	char	*range;

	range = "0123456789abcdef";
	convert_string_to_lower(&str);
	i = 2;
	while (str[i])
	{
		i++;
	}
	converted = 0;
	return (converted);
}

char	*convert_string_to_lower(char **str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		ft_tolower(str[i]);
		i++;
	}
	return (str);
}
