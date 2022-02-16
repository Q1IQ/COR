#include "FindFunctionPointer.h"
#include <sstream>
#include <string>
using namespace clang;
using namespace clang::ast_matchers;
using namespace cor;

MyASTVisitor::MyASTVisitor(clang::Rewriter &R) : TheRewriter(R) {}
bool MyASTVisitor::VisitStmt(clang::Stmt *s)
{
    // Only care about If statements.
    if (clang::isa<clang::IfStmt>(s))
    {
        clang::IfStmt *IfStatement = cast<clang::IfStmt>(s);
        clang::Stmt *Then = IfStatement->getThen();

        TheRewriter.InsertText(Then->getBeginLoc(), "// the 'if' part\n", true,
                               true);

        clang::Stmt *Else = IfStatement->getElse();
        if (Else)
            TheRewriter.InsertText(Else->getBeginLoc(), "// the 'else' part\n",
                                   true, true);
    }

    return true;
}

bool MyASTVisitor::VisitFunctionDecl(clang::FunctionDecl *f)
{
    // Only function definitions (with bodies), not declarations.
    if (f->hasBody())
    {
        clang::Stmt *FuncBody = f->getBody();

        // Type name as string
        clang::QualType QT = f->getReturnType();
        std::string TypeStr = QT.getAsString();

        // Function name
        clang::DeclarationName DeclName = f->getNameInfo().getName();
        std::string FuncName = DeclName.getAsString();

        // Add comment before
        std::stringstream SSBefore;
        SSBefore << "// Begin function " << FuncName << " returning " << TypeStr << "\n";
        clang::SourceLocation ST = f->getSourceRange().getBegin();
        TheRewriter.InsertText(ST, SSBefore.str(), true, true);

        // And after
        std::stringstream SSAfter;
        SSAfter << "\n// End function " << FuncName;
        ST = FuncBody->getEndLoc().getLocWithOffset(1);
        TheRewriter.InsertText(ST, SSAfter.str(), true, true);
    }

    return true;
}

bool ParmVisitor::VisitParmVarDecl(clang::ParmVarDecl *d)
{
    if (d->getFunctionScopeDepth() != 0)
        return true;
    names.push_back(d->getName().str());
    return true;
}

bool MyASTVisitor::VisitFieldDecl(clang::Decl *d)
{
    if (!d->getFunctionType())
    {
        // not a function pointer
        return true;
    }
    ParmVisitor pv;
    pv.TraverseDecl(d);
    auto names = std::move(pv.names);
    // now you get the parameter names...
    return true;
}

// Implementation of the ASTConsumer interface for reading an AST produced
// by the Clang parser.
MyASTConsumer::MyASTConsumer(clang::Rewriter &R) : Visitor(R) {}

// Override the method that gets called for each parsed top-level
// declaration.
bool MyASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef DR)
{
    for (clang::DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b)
    {
        // Traverse the declaration using our AST visitor.
        Visitor.TraverseDecl(*b);
        (*b)->dump();
    }
    return true;
}

MyFrontendAction::MyFrontendAction() {}
std::unique_ptr<clang::ASTConsumer> MyFrontendAction::CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef file)
{
    llvm::errs() << "\033[33m"
                 << "Creating AST matcher for: "
                 << "\033[0m" << file << "\n";
    // auto m = CI.getDiagnostics().getNumWarnings();
    // llvm::outs() << m;

    // Global Function Pointer
    auto GlobalFuncPointerMatcher =
        declRefExpr(
            hasType(
                pointerType(
                    pointee(
                        ignoringParens(functionType())))),
            to(varDecl(hasGlobalStorage())))
            .bind("GlobalFuncPointerCall");

    // Local Function Pointer
    auto LocalFuncPointerMatcher =
        declRefExpr(
            hasType(
                pointerType(
                    pointee(
                        ignoringParens(functionType())))),
            to(varDecl(hasLocalStorage())))
            .bind("LocalFuncPointerCall");

    Finder.addMatcher(GlobalFuncPointerMatcher, &FuncCall);
    Finder.addMatcher(LocalFuncPointerMatcher, &FuncCall);
    return Finder.newASTConsumer();
}
void MyFrontendAction::EndSourceFileAction()
{
    auto m = getCompilerInstance().getDiagnostics().getNumWarnings();
    llvm::outs() << "Warning: " << m << "\n";
    // clang::SourceManager &SM = TheRewriter.getSourceMgr();
    // llvm::errs() << "** EndSourceFileAction for: "
    //              << SM.getFileEntryForID(SM.getMainFileID())->getName() << "\n";

    // // Now emit the rewritten buffer.
    // TheRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
}

void Func_Call::run(const clang::ast_matchers::MatchFinder::MatchResult &Result)
{
    std::string classname;
    std::string functionname;
    std::string functionparms;
    std::string callexprname;
    std::string callexprparms;

    clang::LangOptions LangOpts;
    LangOpts.CPlusPlus = true;
    clang::PrintingPolicy Policy(LangOpts);

    if (auto const *E = Result.Nodes.getNodeAs<clang::DeclRefExpr>("GlobalFuncPointerCall"))
    {
        llvm::outs() << "\033[32m"
                     << "GlobalFuncPointerCall:  "
                     << "\033[0m";
        llvm::outs() << "Name: " << E->getNameInfo().getAsString() << "  Type: " << E->getType().getAsString();

        const SourceManager &SM = *Result.SourceManager;
        const SourceLocation Loc = E->getLocation();
        if (Loc.isValid())
        {
            const unsigned Line = SM.getSpellingLineNumber(Loc);
            // llvm::outs() << "  Location: " << SM.getFilename(Loc) << ":" << Line << "\n";
            llvm::outs() << "  Line: " << Line << "\n";
        }
        else
        {
            llvm::outs() << "\n";
        }
        // const NamedDecl *ND = E->getDecl();
        // if (const ValueDecl *VD = dyn_cast<ValueDecl>(ND))
        // {
        //     llvm::outs() << "  ValueDecl:\n";
        //     // llvm::outs() << "    Kind: " << VD->getKindName() << "\n";
        //     llvm::outs() << "    Name: " << VD->getNameAsString() << "    Type: " << VD->getType().getAsString() << "\n";
        // }
    }

    if (auto const *E = Result.Nodes.getNodeAs<clang::DeclRefExpr>("LocalFuncPointerCall"))
    {
        llvm::outs() << "\033[36m"
                     << "LocallFuncPointerCall:  "
                     << "\033[0m";
        llvm::outs() << "Name: " << E->getNameInfo().getAsString() << "  Type: " << E->getType().getAsString();

        const SourceManager &SM = *Result.SourceManager;
        const SourceLocation Loc = E->getLocation();
        if (Loc.isValid())
        {
            const unsigned Line = SM.getSpellingLineNumber(Loc);
            // llvm::outs() << "  Location: " << SM.getFilename(Loc) << ":" << Line << "\n";
            llvm::outs() << "  Line: " << Line << "\n";
        }
        else
        {
            llvm::outs() << "\n";
        }
        // const NamedDecl *ND = E->getDecl();
        // if (const ValueDecl *VD = dyn_cast<ValueDecl>(ND))
        // {
        //     llvm::outs() << "  ValueDecl:\n";
        //     // llvm::outs() << "    Kind: " << VD->getKindName() << "\n";
        //     llvm::outs() << "    Name: " << VD->getNameAsString() << "    Type: " << VD->getType().getAsString() << "\n";
        // }
    }
}
