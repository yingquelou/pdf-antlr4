#pragma once
#include <iostream>
#include <algorithm>
#include <antlr4-runtime.h>
namespace antlr4
{
    class format : tree::AbstractParseTreeVisitor
    {
    private:
        std::ostream &os;

    public:
        format(std::ostream &_os) : os(_os)
        {
        }
        std::any visit(pdfParser::ObjContext *tree)
        {
            if (tree)
            {
                visit(tree->Null());
                visit(tree->Int());
                visit(tree->Boolean());
                visit(tree->Float());
                visit(tree->XStr());
                visit(tree->str());
                visit(tree->Name());
                visit(tree->objRef());
                visit(tree->dict());
                visit(tree->array());
                visit(tree->stream());
            }
            return 0;
        }
        std::any visit(pdfParser::DictContext *tree)
        {
            if (tree)
            {
                visit(tree->Ld());
                for (auto &&node : tree->obj())
                    visit(node);
                visit(tree->Rd());
                os << '\n';
            }
            return 0;
        }
        std::any visit(pdfParser::ArrayContext *tree)
        {
            if (tree)
            {
                visit(tree->La());
                for (auto &&node : tree->obj())
                {
                    visit(node);
                }
                visit(tree->Ra());
                os << '\n';
            }
            return 0;
        }

        std::any visit(pdfParser::ObjRefContext *tree)
        {
            if (tree)
            {
                for (auto &&node : tree->Int())
                {
                    visit(node);
                }
                visit(tree->R());
            }
            return 0;
        }
        std::any visit(pdfParser::StartContext *tree)
        {
            if (tree)
                for (auto &&node : tree->pdfStruct())
                {
                    visit(node);
                }
            return 0;
        }
        std::any visit(pdfParser::PdfStructContext *tree)
        {
            if (tree)
            {
                visit(tree->startxref());
                visit(tree->xref());
                visit(tree->trailer());
                visit(tree->pdfObj());
            }
            return 0;
        }
        std::any visit(pdfParser::StartxrefContext *tree)
        {
            if (tree)
            {
                visit(tree->Startxref());
                visit(tree->Int());
            }
            return 0;
        }
        std::any visit(pdfParser::StrContext *tree)
        {
            if (tree)
                os << tree->getText() << ' ';
            return 0;
        }
        std::any visit(pdfParser::StreamContext *tree)
        {
            if (tree)
            {
                visit(tree->Stream());
                // 根据index,gen采用c++通用方式创建临时文件名
                std::string filename(tmpnam(nullptr));
                filename += "-" + Index + '-' + Gen + ".stream";
                std::ofstream ofs(filename, std::ios::binary);
                for (auto &&node : tree->Any())
                    ofs << node->getText();
                ofs.close();
                // std::cout << "stream data saved to " << filename << '\n';
                visit(tree->EndStream());
            }
            return 0;
        }
        std::any visit(pdfParser::TrailerContext *tree)
        {
            if (tree)
            {
                visit(tree->Trailer());
                visit(tree->dict());
            }
            return 0;
        }
        std::any visit(pdfParser::XrefContext *tree)
        {
            if (tree)
                os << tree->getText() << '\n';
            return 0;
        }
        std::string Index, Gen;
        std::any visit(pdfParser::PdfObjContext *tree)
        {
            if (tree)
            {
                for (auto &&node : tree->Int())
                {
                    visit(node);
                }
                Index = tree->Int(0)->getText();
                Gen = tree->Int(1)->getText();
                visit(tree->Obj());
                for (auto &&node : tree->obj())
                {
                    visit(node);
                }
                visit(tree->EndObj());
                os << '\n';
            }
            return 0;
        }
        std::any visit(tree::ParseTree *tree) override
        {
            if (tree)
                switch (tree->getTreeType())
                {
                case tree::ParseTreeType::TERMINAL:
                    visitTerminal(dynamic_cast<tree::TerminalNode *>(tree));
                    break;
                case tree::ParseTreeType::RULE:
                    if (antlrcpp::is<pdfParser::StartContext *>(tree))
                        visit(dynamic_cast<pdfParser::StartContext *>(tree));
                    else if (antlrcpp::is<pdfParser::ArrayContext *>(tree))
                        visit(dynamic_cast<pdfParser::ArrayContext *>(tree));
                    else if (antlrcpp::is<pdfParser::DictContext *>(tree))
                        visit(dynamic_cast<pdfParser::DictContext *>(tree));
                    else if (antlrcpp::is<pdfParser::ObjContext *>(tree))
                        visit(dynamic_cast<pdfParser::ObjContext *>(tree));
                    else if (antlrcpp::is<pdfParser::ObjRefContext *>(tree))
                        visit(dynamic_cast<pdfParser::ObjRefContext *>(tree));
                    else if (antlrcpp::is<pdfParser::PdfObjContext *>(tree))
                        visit(dynamic_cast<pdfParser::PdfObjContext *>(tree));
                    else if (antlrcpp::is<pdfParser::PdfStructContext *>(tree))
                        visit(dynamic_cast<pdfParser::PdfStructContext *>(tree));
                    else if (antlrcpp::is<pdfParser::StartxrefContext *>(tree))
                        visit(dynamic_cast<pdfParser::StartxrefContext *>(tree));
                    else if (antlrcpp::is<pdfParser::StrContext *>(tree))
                        visit(dynamic_cast<pdfParser::StrContext *>(tree));
                    else if (antlrcpp::is<pdfParser::StreamContext *>(tree))
                        visit(dynamic_cast<pdfParser::StreamContext *>(tree));
                    else if (antlrcpp::is<pdfParser::StreamContext *>(tree))
                        visit(dynamic_cast<pdfParser::StreamContext *>(tree));
                    else if (antlrcpp::is<pdfParser::TrailerContext *>(tree))
                        visit(dynamic_cast<pdfParser::TrailerContext *>(tree));
                    else if (antlrcpp::is<pdfParser::XrefContext *>(tree))
                        visit(dynamic_cast<pdfParser::XrefContext *>(tree));

                    break;
                default:
                    break;
                }
            return 0;
        }
        std::any visitTerminal(tree::TerminalNode *node) override
        {
            os << node->getText() << ' ';
            return 0;
        }
    };
} // namespace antlr4
