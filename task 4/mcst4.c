#include <stdio.h>
#include <stdlib.h>
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
}; //разрешенные аргументы для опции elbrus

int elbrusvalid(const char* arg) //проверка валидности аргументов всех использований elbrus
{
	for (size_t i = 0; i < sizeof(ElbrusAllowed) / sizeof(ElbrusAllowed[0]); i++)
	{
		if (!strcmp(ElbrusAllowed[i], arg))
			return 1;
	}
	return 0;
}

int main (int argc, char **argv) {
    int c; //переменная, куда сохраняется возвращаемое функцией значение
    int optionIndex = 0; //указывает на переменную с индексом длинной опции в LongOptions либо на NULL
	
	static struct option LongOptions[] = 
	{
		{"elbrus=", 1, 0, 1000}, //ставим 1000, чтобы в switch точно не перепутать опцию ни с какой другой (короткой)
		{0, 0, 0, 0}
	}; //массив разрешенных длинных опций; обязательно ноль-терминирован

	while ((c = getopt_long (argc, argv, "mcst", LongOptions, &optionIndex)) >= 0)
	{
		if (c == -1) //завершение работы при достижении конца
			break;

		switch (c) {
			case 'm':
				printf ("valid option: param m\n");
				break;

			case 's':
				printf ("valid option: param s\n");
				break;

			case 'c':
				printf ("valid option: param c\n");
				break;

			case 't':
				printf ("valid option: param t\n");
				break;
			
			case 1000:
				if (elbrusvalid(optarg))
				{	
					printf("valid option: elbrus=%s\n", optarg);
				}
				else
				{
					printf(">>invalid elbrus argument: elbrus=%s\n", optarg);
					return -2;
				}
				break;
			case '?': //неразрешенная в optstring опция/неправильное толкование параметра
				printf(">>invalid option: %s\n", argv[optind - 1]);
				return -1;

			default: //сюда программа не должна зайти...
				printf ("GETOPT RETURNED UNEXPECTED VALUE %o\n", c);
				return -3;
        }
    }

    if (optind < argc) //вывод non-options
	{
        printf ("non params: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }

    return 0;
}