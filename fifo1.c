#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
	int fd;
	size_t size;
	char name[]="try.fifo";

	(void)umask(0);

	if (access(name, F_OK) == 0) 
	{
	       printf("FIFO already exists: %s\n", name);
	} 
	else 
	{
	       /**Если файл не существует, создаем FIFO с помощью mknod*/
	       if (mknod(name, S_IFIFO | 0666, 0) == -1) {
	           puts("mknod err");
	           exit(EXIT_FAILURE);
	       }
	       printf("FIFO created: %s\n", name);
	}

	return 0;
}