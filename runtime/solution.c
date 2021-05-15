#include <stdbool.h>
#include <string.h> 
#include <stdio.h>
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>

/* Указатель на ф-ю в библиотеке Shared */
int (*some_func)(int var);

int main(int argc, char **argv) //Тут передаём аргументы
{


	char name_lib[128];
	snprintf(name_lib, sizeof(name_lib), "%s%s", "./", argv[1]);
	

	/* Пробуем открыть библиотеку */
	void *hdl = dlopen(name_lib, RTLD_LAZY);

	/* Не нашли библиотеку */
	if (hdl == NULL)
		exit(1);

	/* Пробуем присвоить указатель на ф-ю, в библиотеке */
	some_func = (int (*)(int))dlsym(hdl, argv[2]);

	if (some_func == NULL)
		exit(1);

	/* Преобразуем в число 3 аргумент */
	int arg_f = atoi(argv[3]);

	/* Переведём число int возращаемое функцией в строку */
	char str[3];
	sprintf(str, "%d", some_func(arg_f));

	strcat( str, "\n");

	fputs(str, stdout);

	return 0;
}