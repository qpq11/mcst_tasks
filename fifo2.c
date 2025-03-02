#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd;
	size_t size;
	char resstring[16];
	char name[]="try.fifo";

	/** Открываем FIFO на чтение.*/
	if((fd = open(name, O_RDONLY)) < 0)
	{
	  printf("Can\'t open FIFO for reading\n");
	  exit(-1);
	}

	size = read(fd, resstring, 15);
	if(size < 0)
	{
	  /** Если прочитать не смогли, сообщаем об ошибке и завершаем работу */
	  printf("Can\'t read string\n");
	  exit(-1);
	}

	int n = atoi(resstring);
	n *= n;

	printf("Resstring: %d\n", n);
	close(fd);
	return 0;
} 