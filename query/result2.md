```
clang-query> m declRefExpr(hasType(pointerType(pointee(ignoringParens(functionType())))),to(varDecl(hasGlobalStorage())))

Match #1:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:49:3: note: "root" binds here
  p1 = func;
  ^~

Match #2:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:50:3: note: "root" binds here
  p2 = &func1;
  ^~

Match #3:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:51:3: note: "root" binds here
  p3 = &func2;
  ^~

Match #4:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:52:3: note: "root" binds here
  p4 = &func3;
  ^~

Match #5:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:53:3: note: "root" binds here
  p5 = &func4;
  ^~

Match #6:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:61:14: note: "root" binds here
  int res1 = p1(10);
             ^~

Match #7:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:63:18: note: "root" binds here
  float res2 = (*p2)(3.14, 2);
                 ^~

Match #8:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:65:18: note: "root" binds here
  char *res3 = (*p3)("hello", 3);
                 ^~

Match #9:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:67:18: note: "root" binds here
  void *res4 = (*p4)(0, 0);
                 ^~

Match #10:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:69:21: note: "root" binds here
  int (*f)(int) = (*p5)(20, &func);
                    ^~
10 matches.
clang-query> m declRefExpr(hasType(pointerType(pointee(ignoringParens(functionType())))),to(varDecl(hasLocalStorage())))

Match #1:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:43:10: note: "root" binds here
  return f;
         ^

Match #2:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:59:3: note: "root" binds here
  fptr(0.1,123);
  ^~~~

Match #3:

/Users/apple/Downloads/COR2/build/../samples/pointer.cpp:70:16: note: "root" binds here
  int res5 = (*f)(5);
               ^
3 matches.
```