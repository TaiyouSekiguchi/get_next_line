#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char *argv[])
{
	char*	line;
	int		fd;
	int		ret;
	int		cnt;

	if (argc != 2)
		return (1);

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);

	cnt = 1;
	while (1)
	{
		ret = get_next_line(fd, &line);
		if (ret == ERROR)
		{
			close(fd);
			return (1);
		}
		if (ret == END)
			break;
		printf("%03d  %s\n", cnt, line);
		free(line);
		line = NULL;
		cnt++;
	}
	free(line);
	line = NULL;

	close(fd);

	return (0);
}
