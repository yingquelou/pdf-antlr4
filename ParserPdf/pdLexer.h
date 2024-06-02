#pragma once
#include <pdfLexer.h>
#include "PdfObjIndexEntryVector.h"
class pdLexer : public pdfLexer
{
private:
    std::string index, gen;
    long long count;
    std::ofstream out;
    PdfObjIndexEntryVector<std::string, 2> indexEntryVector;

public:
    using pdfLexer::pdfLexer;
    antlr4::Token *emit() override;
};