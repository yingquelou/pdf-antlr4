#pragma once
#include "pdfParser.h"

namespace antlr4
{
    class pdfFormatVisitor : tree::AbstractParseTreeVisitor
    {
        std::ostream &os;
        bool split;
        std::string index, gen;
        int count = 1;

    public:
        pdfFormatVisitor(std::ostream &_os, bool split = false) : os(_os), split(split) {}
        std::any visit(pdfParser::ObjContext *tree);
        std::any visit(pdfParser::DictContext *tree);
        std::any visit(pdfParser::ArrayContext *tree);

        std::any visit(pdfParser::ObjRefContext *tree);

        std::any visit(pdfParser::PdfContext *tree);

        std::any visit(pdfParser::StartxrefContext *tree);

        std::any visit(pdfParser::StrContext *tree);

        std::any visit(pdfParser::StreamContext *tree);

        std::any visit(pdfParser::TrailerContext *tree);

        std::any visit(pdfParser::SubXrefContext *subXref);

        std::any visit(pdfParser::SubXrefEntryContext *entry);

        std::any visit(pdfParser::XrefContext *tree);

        std::any visit(pdfParser::XStrContext *tree);

        std::any visit(pdfParser::PdfObjContext *tree);

        std::any visit(tree::ParseTree *tree) override;

        std::any visitTerminal(tree::TerminalNode *node) override;
    };
} // namespace antlr4
