#include "pdListener.h"

void pdListener::exitXref(pdfParser::XrefContext *ctx)
{
    // std::cout
    //     << ctx->Xref()->getText() << '\n';
    //     for (auto &&i : ctx->Int())
    //     {
    //         std::cout << i->getText() << '\n';
    //     }
        
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
