#include "../../include/libft.h"

char *ft_limited_strdup(char *str, int begin, int end)
{
	char *new_str;
	int i;

	i = 0;
	new_str = ft_malloc(end - begin, "char");
	while(begin <= end)
	{
		new_str[i] = str[begin];
		begin++;
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}
