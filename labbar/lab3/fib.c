#include <stdio.h>
#include <stdlib.h>

/// Den intressanta delen av programmet
int fib(int num)
{
    /*
  int ppf = 0; // the two given fib values
  int pf  = 1;

  for (int i = 1; i < num; ++i)
  {
    int tmp = pf;
    pf = ppf + pf;
    ppf = tmp;
  }

  return pf;
  */

    if (num == 2 || num == 1) {
        return 1;
    } else if (num == 0) {
        return 0;
    } else {
        return fib(num - 1) + fib(num - 2);
    }
}

/// Den ointressanta main()-funktionen
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s >=0 number\n", argv[0]);
  }
  else
  {
    int n = atoi(argv[1]);
    if (n < 2)
    {
      printf("fib(%d) = %d\n", n, n);
    }
    else
    {
      printf("fib(%s) = %d\n", argv[1], fib(n));
    }
  }
  return 0;
}