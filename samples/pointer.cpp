// Declare a function pointer to a function that returns an integer and takes an integer parameter
int (*p1)(int);

// Define a function pointer to a function that returns a float and takes a float and an integer parameter, and point it to a function named `func1`
float (*p2)(float, int);

// Declare a function pointer to a function that returns a pointer to a char and takes a pointer to a char and an integer parameter
char *(*p3)(char *, int);

// Define a function pointer to a function that returns a pointer to void and takes two pointers to void parameters, and point it to a function named `func2`
int *(*p4)(void *, void *);

// Declare a function pointer to a function that returns a function pointer that returns an integer and takes an integer parameter and a function pointer that returns an integer and takes an integer parameter
int (*(*p5)(int, int (*)(int)))(int);

// Function 1: a float-returning function that takes a float and an integer parameter
float func1(float f, int n)
{
  return f * n;
}

// Function 2: a char pointer-returning function that takes a char pointer and an integer parameter
char *func2(char *str, int n)
{
  return str;
}

// Function 3: a void pointer-returning function that takes two pointers to void parameters
int *func3(void *p1, void *p2)
{
  return 0;
}

// Function: an integer-returning function that takes an integer parameter
int func(int n)
{
  return n;
}

// Function 4: a function pointer-returning function that takes an integer parameter and a function pointer that returns an integer and takes an integer parameter
int (*func4(int n, int (*f)(int)))(int)
{
  return f;
}

int main()
{
  // Initialize the function pointers
  p1 = func;
  p2 = &func1;
  p3 = &func2;
  p4 = &func3;
  p5 = &func4;

  // local
  float (*fptr)(float, int) = func1;

  // Use the function pointers to call the functions
  fptr(0.1,123);

  // `func_ptr();`
  int res1 = p1(10);

  // `(*func_ptr)();`
  float res2 = (*p2)(3.14, 2);

  char *s;
  char *res3 = (*p3)(s, 3);

  void *res4 = (*p4)(0, 0);

  int (*f)(int) = (*p5)(20, &func);
  int res5 = (*f)(5);

  return 0;
}
