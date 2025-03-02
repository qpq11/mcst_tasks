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
	char name[]="try.fifo";
	char buf[9] = "";
	fgets(buf, 8, stdin);
	
	if ((fd = open(name, O_WRONLY))< 0)
		{
		 /** Если открыть FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
		 printf("Can\'t open FIFO for writing\n");
		 exit(-1);
		}

	size = write(fd, buf, strlen(buf) + 1);

	if(size != (strlen(buf) + 1))
		{
		 printf("Can\'t write all string to FIFO\n");
		 exit(-1);
		}

	close(fd);
	return 0;
}