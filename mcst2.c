#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

const int FifoNameLen = 9;
const int BufSize = 15;

int main(const int argc, const char *argv[]) 
{
	if (argc != 2)
	{
		printf("The program only takes 2 arguments: .out file name and either 1 or 2 as a number.");
		return -1;
	}
	
	int fd = 0;
	size_t size = 0;
	
	char* name1 = (char*) calloc(FifoNameLen, sizeof(char));
	name1 ="try1.fifo";
	char* name2 = (char*) calloc(FifoNameLen, sizeof(char));
	name2 ="try2.fifo";
	char* temp   = (char*) calloc(FifoNameLen, sizeof(char));
	
	if (!strcmp(argv[1], "1"))
	{
		printf("argument: 1\n");
	}
	else if (!strcmp(argv[1], "2"))
	{
		printf("argument: 2\n");
		temp = name1;
		name1 = name2;
		name2 = temp;
	}
	else
	{
		printf("only 1 and 2 are accepted as arguments.");
		return 0;
	}
	
	char resstring[16];
	char buf[16] = "";

	// if ((fd = open(name, O_WRONLY))< 0)
	// {
		 // /* Если открыть FIFO не удалось, печатаем об этом сообщение и прекращаем работу */
		 // printf("Can\'t open FIFO for writing\n");
		 // exit(-1);
	// }
	
	(void)umask(0);

	if (access(name1, F_OK) == 0) 
	{
	       printf("FIFO already exists: %s\n", name1);
	} 
	else 
	{
	       if (mknod(name1, S_IFIFO | 0666, 0) == -1) {
	           puts("mknod err");
	           exit(EXIT_FAILURE);
	       }
	       printf("FIFO created: %s\n", name1);
	}
	
	if (access(name2, F_OK) == 0) 
	{
	       printf("FIFO already exists: %s\n", name2);
	} 
	else 
	{
	       if (mknod(name2, S_IFIFO | 0666, 0) == -1) {
	           puts("mknod err");
	           exit(EXIT_FAILURE);
	       }
	       printf("FIFO created: %s\n", name2);
	}
	
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
		if ((fd = open(name1, O_WRONLY))< 0)
			{
			 printf("Can\'t open FIFO for writing\n");
			 exit(-1);
			}
        while (1)
		{
            //printf(">>>Enter message: \n");
            fflush(stdout);
			fgets(buf, BufSize, stdin);
			
			if(!strcmp(buf, "##\n"))
			{
				close(fd);
				free(temp);
				free(name1);
				free(name2);
				exit(0);
				return 0;
			}

			size = write(fd, buf, strlen(buf) + 1);

			if(size != (strlen(buf) + 1))
			{
				 printf("Can\'t write all string to FIFO\n");
				 exit(-1);
			}
        }
		close(fd);
		free(temp);
		free(name1);
		free(name2);
    } 
	
	else 
	{
		if((fd = open(name2, O_RDONLY)) < 0)
		{
			 printf("Can\'t open FIFO for reading\n");
			 exit(-1);
		}
			
        while (1) {
			memset(resstring, 0, BufSize + 1);
			size = read(fd, resstring, BufSize);
			
			if(!strcmp(resstring, "##\n"))
			{
				close(fd);
				free(temp);
				free(name1);
				free(name2);
				exit(0);
				return 0;
			}
			
			if(size < 0)
			{
			  printf("Can\'t read string\n");
			  exit(-1);
			}
			printf("<<<Received message: %s\n>>>Enter message: \n", resstring);
        }
		close(fd);
		free(temp);
		free(name1);
		free(name2);
    }

    return 0;
}