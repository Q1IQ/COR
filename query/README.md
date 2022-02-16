1. search for all function pointers
```
clang-query>  m declRefExpr(hasType(pointerType(pointee(ignoringParens(functionType())))))
```
[result1](result1.md)

2. only for pointers have global storage 
- exclude ReturnStmt `return f`
- exclude Local Var `fptr`
```
clang-query>  m declRefExpr(hasType(pointerType(pointee(ignoringParens(functionType())))),to(varDecl(hasGlobalStorage())))
```
[result2](result2.md)