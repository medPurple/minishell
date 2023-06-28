#include "../../include/libft.h"

char *ft_limited_strdup(char *str, int begin, int end)
{
	char *new_str;
	int i;

	i = 0;
	if (end - begin < 0)
		return (NULL);
	new_str = ft_malloc(end - begin, "char");
	while(begin <= end)
	{
		new_str[i] = str[begin];
		begin++;
		i++;
	}
	return (new_str);
}
