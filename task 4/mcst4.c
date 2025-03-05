#include <stdio.h>     /* для printf */
#include <stdlib.h>    /* для exit */
#include <getopt.h>
#include <string.h>

const char* ElbrusAllowed[] = 
{
	"1c+",
	"2c+",
	"2c3",
	"4c" ,
	"8c" ,
	"16c",
};

int elbrusvalid(const char* arg)
{
	for (size_t i = 0; i < sizeof(ElbrusAllowed) / sizeof(ElbrusAllowed[0]); i++)
	{
		if (!strcmp(ElbrusAllowed[i], arg))
			return 1;
	}
	return 0;
}

int main (int argc, char **argv) {
    int c;
    int optionIndex = 0;
	char* elbrusMode = NULL;
	
	static struct option LongOptions[] = {
		{"elbrus=", 1, 0, 1000},
		{0, 0, 0, 0}
	};

	while ((c = getopt_long (argc, argv, "m::c::s::t::", LongOptions, &optionIndex)) >= 0)
	{
		if (c == -1)
			break;

		switch (c) {
			case 'm':
				printf ("param m with value `%s'\n", optarg);
				break;

			case 's':
				printf ("param s with value `%s'\n", optarg);
				break;

			case 'c':
				printf ("param c with value `%s'\n", optarg);
				break;

			case 't':
				printf ("param t with value `%s'\n", optarg);
				break;
			
			case 1000:
				if (elbrusvalid(optarg))
				{	
					printf("elbrus= %s\n", optarg);
				}
				else
				{
					printf("ERROR: elbrus wrong option\n");
				}
			case '?':
				break;

			default:
				printf ("?? getopt возвратило код символа 0%o ??\n", c);
        }
    }

    if (optind < argc) {
        printf ("элементы ARGV, не paramы: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }

    exit (0);
}