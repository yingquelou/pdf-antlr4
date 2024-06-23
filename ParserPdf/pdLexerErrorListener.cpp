#include "pdLexerErrorListener.h"

void pdLexerErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e)
{
    // std::cerr << "line :" << line << ":" << charPositionInLine << " " << msg << std::endl;
}