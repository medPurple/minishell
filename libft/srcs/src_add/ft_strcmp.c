
#include "../../include/libft.h"

int	ft_strcmp(char *s1, char *s2) {
	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}