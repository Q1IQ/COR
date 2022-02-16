#include <clang/Frontend/FrontendActions.h>
#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include "clang/AST/Expr.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/raw_ostream.h"
namespace cor
{
    class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor>
    {
    public:
        MyASTVisitor(clang::Rewriter &R);
        bool VisitStmt(clang::Stmt *s);
        bool VisitFunctionDecl(clang::FunctionDecl *f);
        bool VisitFieldDecl(clang::Decl *d);

    private:
        clang::Rewriter &TheRewriter;
    };

    class ParmVisitor : public clang::RecursiveASTVisitor<ParmVisitor>
    {
    public:
        bool VisitParmVarDecl(clang::ParmVarDecl *d);
        std::vector<std::string> names;
    };

    class MyASTConsumer : public clang::ASTConsumer
    {
    public:
        MyASTConsumer(clang::Rewriter &R);
        bool HandleTopLevelDecl(clang::DeclGroupRef DR) override;

    private:
        MyASTVisitor Visitor;
    };

    class Func_Call : public clang::ast_matchers::MatchFinder::MatchCallback
    {
    public:
        void run(const clang::ast_matchers::MatchFinder::MatchResult &Result) override;
    };

    // For each source file provided to the tool, a new FrontendAction is created.
    class MyFrontendAction : public clang::ASTFrontendAction
    {
    public:
        MyFrontendAction();
        void EndSourceFileAction();
        std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef file) override;

    private:
        clang::Rewriter TheRewriter;
        Func_Call FuncCall;
        clang::ast_matchers::MatchFinder Finder;
    };
}
