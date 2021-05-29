#include <stdio.h>
#include <string.h>

int
main ()
{
  char str[100] = "aHhhna";

  int len = strlen (str);
  int iter = 0;


  printf ("%d\n", len);


  iter = len / 2;

  for (int i = 0; i < iter; i++)
    {
      if (str[i] == str[len-1])
	len--;
      else
	return 0;
    }



  return 1;
}