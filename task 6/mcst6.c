#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 2) //ровно 2 аргмента разрешены
	{
		printf("program only takes 2 arguments: executable file name and name of the file we give to stat.\n");
		return -1;
	}
	
	struct stat fileStats; //структура со статистикой о файле
	
	if (stat(argv[1], &fileStats) == -1)
	{
		printf("ERROR: stat returned -1.\n");
		return -2;
	}
	printf("INPUT FILE STATS\n\n");
	printf("  NAME                   |  %s\n", argv[1]);
	printf("-----------------------------------------------------------------\n");
	//тип файла
	 if (S_ISREG(fileStats.st_mode))
        printf("  TYPE                   |  Regular file\n");
    else if (S_ISDIR(fileStats.st_mode))
        printf("  TYPE                   |  Directory\n");
    else if (S_ISFIFO(fileStats.st_mode))
        printf("  TYPE                   |  FIFO (named pipe)\n");
    else if (S_ISLNK(fileStats.st_mode))
        printf("  TYPE                   |  Symbolic link\n");
    else if (S_ISLNK(fileStats.st_mode))
        printf("  TYPE                   |  Socket\n");
	else if (S_ISCHR(fileStats.st_mode))
        printf("  TYPE                   |  Character device\n");
    else if (S_ISBLK(fileStats.st_mode))
        printf("  TYPE                   |  Block device\n");
    else
		printf("  TYPE                   |  Unknown\n");
	//размер, разрешения, время последнего изменения с начала Unix(?)
    printf("  SIZE                   |  %lld bytes\n", (long long)fileStats.st_size);
    printf("  PERMITS                |  %o\n", fileStats.st_mode & 0777);
    printf("  LAST MODIFIED          |  %ld\n\n", (long)fileStats.st_mtime);
	
	return 0;
}
