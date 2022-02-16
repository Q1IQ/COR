#include "FindFunctionPointer.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/raw_ostream.h"

int main(int argc, const char *argv[])
{
  if ((argc > 3) || (argc < 2))
  {
    llvm::outs() << "You input wrong number arguments!\n";
    return -1;
  }

  FILE *result = fopen(argv[1], "r");
  if (result == NULL)
  {
    llvm::outs() << "Can't open the file: {}.\n"
                 << argv[1];
    return -1;
  }

  static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");
  clang::tooling::CommonOptionsParser OptionsParser(argc, argv, ToolingSampleCategory);
  clang::tooling::ClangTool Tool(OptionsParser.getCompilations(),
                                 OptionsParser.getSourcePathList());
  Tool.run(clang::tooling::newFrontendActionFactory<cor::MyFrontendAction>().get());
}
