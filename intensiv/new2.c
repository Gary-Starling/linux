/*Напишите программу, которая принимает сначала число - количество элементов последовательности, а потом сами элементы, 
разделенные пробелом. Необходимо записать числа в массив, а затем удалить из него все нечётные значения,
 а чётные поделить на два. Полученный массив необходимо вывести, разделяя элементы пробелом*/

#include <stdio.h>
#include <stdlib.h>

int main()
{

    int number = 0;

    scanf("%d", &number);

    int *mass = NULL;

    mass = (int *)malloc(number * (sizeof(int)));

    int i = 0;

    for (i = 0; i < number; i++)
    {
        scanf("%d", mass);
        mass++;
    }

    /* Вернём указатель в начало */
    mass = mass - number;

    for (i = 0; i < number; i++)
    {
        if (mass[i] % 2 != 0) //нечётное
        {
            mass[i] = 0;//
        }
        else
        {
            mass[i] = mass[i] / 2;
            printf("%d ", mass[i]);
        }

        
    }
    //printf("\n");

    return 0;
}