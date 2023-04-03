# Get Next Line

Reading a line on a fd is way too tedious

## 概要

ファイル記述子を受け取って、ファイルの内容を一行ずつ取得します。  
ファイルを読み込む際のバッファサイズを指定する場合は、  
"-D BUFFER_SIZE=buffer_size"オプションを付けてコンパイルしてください。  
動的に確保された文字列がlineに格納されるので、使用後は解放してください。  

返り値はマクロで定義した以下の定数が返されます。  
| マクロ | 定数 | 内容         |
| ------ | ---- | ------------ |
| READ   | 1    | 一行読み込み |
| END    | 0    | EOF          |
| ERROR  | -1   | エラー       |

## コンパイル例

```Shell
gcc main.c get_next_line.c get_next_line_utils.c -D BUFFER_SIZE=512
```

## 使用例

```c
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
```
