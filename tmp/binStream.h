#include <antlr4-runtime.h>
#include <pdfParserBaseListener.h>
namespace antlr4
{
    class binStream : public antlr4::CharStream
    {
    private:
    public:
        void consume() override;
        size_t LA(ssize_t i) override;
        ssize_t mark() override;
        void release(ssize_t marker) override;
        size_t index() override;
        void seek(size_t index) override;
        size_t size() override;
        std::string getSourceName() const override;
        std::string getText(const misc::Interval &interval) override;
        std::string toString() const override;
    };
    class listen : pdfParserBaseListener
    {
    private:
        /* data */
    public:
        void exitStartxref(pdfParser::StartxrefContext *sc) override
        {
            std::cout << sc->Int()->getText();
        }
    };
} // namespace antlr4
