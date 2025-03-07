#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		printf("program only takes 2 arguments: executable file name and name of the file we give to stat.\n");
		return -1;
	}
	
	struct stat fileStats;
	
	if (stat(argv[1], &fileStats) == -1)
	{
		printf("ERROR: stat returned -1.\n");
		return -2;
	}
	
	 if (S_ISREG(fileStats.st_mode))
        printf("  Type: Regular file\n");
    else if (S_ISDIR(fileStats.st_mode))
        printf("  Type: Directory\n");

    printf("  Size: %lld bytes\n", (long long)fileStats.st_size);
    printf("  Permissions: %o\n", fileStats.st_mode & 0777);
	
	return 0;
}
