
#include "map.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int	count_tabsizemap()
{
	int	i = 0;
	int	fd = open("map.txt", O_RDONLY);
	if (!fd)
		return (write(1, "error fd\n", 10));

	while (get_next_line(fd))
		i++;
	return (i + 1);
}

char**	createmap(void)
{

	int fd_map = open("map.txt", O_RDONLY);
	if (!fd_map)
		return (NULL);

	char **map = malloc(sizeof(char *) * count_tabsizemap());
	if (!map)
		return (NULL);
	char **memmap = map;
	char *bufline = get_next_line(fd_map);
	if (!bufline)
		return (NULL);
	while (bufline)
	{
		// printf("%s", bufline);
		*map = ft_strdup(bufline);
		map++;
		bufline = get_next_line(fd_map);
	}
	*map = NULL;
	return (memmap);
	
}

int	main(void)
{
	char **map = createmap();
	if (!map)
		return (1);
	printf("fin\n");
	printf("%s", *map);
	while (*map)
	{
		printf("%s", *map);
		map++;
	}
	return (0);
}