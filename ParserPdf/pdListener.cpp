#include "pdListener.h"

void pdListener::exitXref(pdfParser::XrefContext *ctx)
{
    // for (auto &&sub : ctx->subXref())
    // {
    //     std::cout << sub->Int(0)->getText() << ' ' << sub->Int(1)->getText() << '\n';
    //     for (auto &&entry : sub->subXrefEntry())
    //         std::cout << entry->Int(0)->getText() << ' ' << entry->Int(1)->getText() << ' ' << (entry->F() ? 'f' : 'n') << '\n';
    // }
}

void pdListener::exitPdfObj(pdfParser::PdfObjContext *ctx)
{
    // std::cout << ctx->Int(0)->getText() <<' '<< ctx->Int(1)->getText() << '\n';
}

void pdListener::visitErrorNode(antlr4::tree::ErrorNode *node)
{
    // std::cout << "Error: " << node->getText() << '\n';
}

void pdListener::visitTerminal(antlr4::tree::TerminalNode *node)
{
    // std::cout << "Terminal: " << node->getText() << '\n';
}

void pdListener::exitStream(pdfParser::StreamContext *ctx)
{
    // std::cout << ctx << '\n';
}
