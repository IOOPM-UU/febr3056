typedef int int_fold_func(int, int);

int add(int a, int b)
{
  return a + b;
}

int foldl_int_int(int numbers[], int numbers_siz, int_fold_func *f) {
    int result = 0;

    for (int i = 0; i < numbers_siz; ++i) {
        result = f(result, numbers[i]);
    }

    return result;
}
long sum(int numbers[], int numbers_siz)
{
    return foldl_int_int(numbers[], numbers_siz, add);
}