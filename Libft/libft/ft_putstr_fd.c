#include "../../fractal.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	if (!s || fd == -1)
		return ;
	index = 0;
	while (s[index] != '\0')
	{
		write(fd, &s[index], 1);
		index++;
	}
}