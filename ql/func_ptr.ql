// `func_ptr` is a global function pointer defined like `void (*func_ptr) ( void ) = NULL;`
import cpp
from ExprCall c
where
  // `func_ptr();`
  c.(VariableCall).getVariable() instanceof GlobalVariable
  or
  // `(*func_ptr)();`
  (not c instanceof VariableCall and c.getExpr().getAChild().(VariableAccess).getTarget() instanceof GlobalVariable)
select c, "This is function pointer type "+c.getAPrimaryQlClass()