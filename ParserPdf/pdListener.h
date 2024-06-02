#include <pdfParserBaseListener.h>
class pdListener : public pdfParserBaseListener
{
public:
    void exitXref(pdfParser::XrefContext *ctx) override;
    void exitPdfObj(pdfParser::PdfObjContext * /*ctx*/) override;
    void visitErrorNode(antlr4::tree::ErrorNode *) override;
    void visitTerminal(antlr4::tree::TerminalNode *) override;
    void exitStream(pdfParser::StreamContext *) override;
};
