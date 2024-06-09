#pragma once
#include <iostream>
#include <algorithm>
#include <execution>
#include <antlr4-runtime.h>
namespace antlr4
{
    class format : tree::AbstractParseTreeVisitor
    {
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
                visit(tree->xStr());
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
                auto &&vec = tree->obj();
                std::div_t &&d = std::div(vec.size(), 2);
                visit(tree->Ld());
                size_t i = 0;
                for (; i < d.quot; i++)
                {
                    os << '\n';
                    visit(vec[i * 2]);
                    os << ' ';
                    visit(vec[i * 2 + 1]);
                }
                if (d.rem)
                {
                    os << '\n';
                    visit(vec[i * 2]);
                }
                if (d.quot + d.rem)
                    os << '\n';
                visit(tree->Rd());
            }
            return 0;
        }
        std::any visit(pdfParser::ArrayContext *tree)
        {
            if (tree)
            {
                visit(tree->La());
                auto &&vec = tree->obj();
                auto &&sz = vec.size();
                if (sz)
                {
                    visit(vec[0]);
                    for (size_t i = 1; i < sz; ++i)
                    {
                        os << ' ';
                        visit(vec[i]);
                    }
                }
                visit(tree->Ra());
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
                    os << ' ';
                }
                visit(tree->R());
            }
            return 0;
        }
        std::any visit(pdfParser::PdfContext *tree)
        {
            if (tree)
            {
                auto &&vec = tree->pdfObj();
                static auto comparePdfObjContext = [](pdfParser::PdfObjContext *const &lhs, pdfParser::PdfObjContext *const &rhs)
                {
                    std::string &&l = lhs->Int(0)->getText();
                    std::string &&r = rhs->Int(0)->getText();
                    if (l > r)
                        return false;
                    else if (l < r)
                        return true;
                    std::string &&l1 = lhs->Int(1)->getText();
                    std::string &&r1 = rhs->Int(1)->getText();
                    if (l1 > r1)
                        return false;
                    return true;
                };
                std::set<pdfParser::PdfObjContext *, decltype(comparePdfObjContext)> set(vec.begin(), vec.end(), comparePdfObjContext);
                bool newline = false;
                static auto visitnode = [&](auto &&node)
                { if (newline)
                        os << '\n';
                    else
                        newline = true;
                    visit(node); };
                std::for_each(set.begin(), set.end(), visitnode);
                auto &&xref = tree->xref();
                std::for_each(xref.begin(), xref.end(), visitnode);
                auto &&trailer = tree->trailer();
                std::for_each(trailer.begin(), trailer.end(), visitnode);
                auto &&startxref = tree->startxref();
                std::for_each(startxref.begin(), startxref.end(), visitnode);
            }
            return 0;
        }
        std::any visit(pdfParser::StartxrefContext *tree)
        {
            if (tree)
            {
                visit(tree->Startxref());
                os << '\n';
                visit(tree->Int());
            }
            return 0;
        }
        std::any visit(pdfParser::StrContext *tree)
        {
            if (tree)
                os << tree->getText();
            return 0;
        }
        std::any visit(pdfParser::StreamContext *tree)
        {
            if (tree)
            {
                visit(tree->Stream());
                os << '\n';
                visit(tree->EndStream());
            }
            return 0;
        }
        std::any visit(pdfParser::TrailerContext *tree)
        {
            if (tree)
            {
                visit(tree->Trailer());
                os << '\n';
                visit(tree->dict());
            }
            return 0;
        }
        std::any visit(pdfParser::SubXrefContext *subXref)
        {
            if (subXref)
            {
                visit(subXref->Int(0));
                os << ' ';
                visit(subXref->Int(1));
                for (auto &&entry : subXref->subXrefEntry())
                {
                    os << '\n';
                    visit(entry);
                }
            }
            return 0;
        }
        std::any visit(pdfParser::SubXrefEntryContext *entry)
        {
            if (entry)
            {
                for (auto &&node : entry->Int())
                {
                    visit(node);
                    os << ' ';
                }
                os << (entry->F() ? 'f' : 'n');
            }
            return 0;
        }
        std::any visit(pdfParser::XrefContext *tree)
        {
            if (tree)
            {
                visit(tree->Xref());
                for (auto &&subXref : tree->subXref())
                {
                    os << '\n';
                    visit(subXref);
                }
            }
            return 0;
        }
        std::any visit(pdfParser::XStrContext *tree)
        {
            if (tree)
                os << tree->getText();
            return 0;
        }
        std::any visit(pdfParser::PdfObjContext *tree)
        {
            if (tree)
            {
                visit(tree->Int(0));
                os << ' ';
                visit(tree->Int(1));
                os << ' ';
                visit(tree->Obj());
                for (auto &&node : tree->obj())
                {
                    os << '\n';
                    visit(node);
                }
                os << '\n';
                visit(tree->EndObj());
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
                    if (antlrcpp::is<pdfParser::PdfContext *>(tree))
                        visit(dynamic_cast<pdfParser::PdfContext *>(tree));
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
                    else if (antlrcpp::is<pdfParser::StartxrefContext *>(tree))
                        visit(dynamic_cast<pdfParser::StartxrefContext *>(tree));
                    else if (antlrcpp::is<pdfParser::StrContext *>(tree))
                        visit(dynamic_cast<pdfParser::StrContext *>(tree));
                    else if (antlrcpp::is<pdfParser::XStrContext *>(tree))
                        visit(dynamic_cast<pdfParser::XStrContext *>(tree));
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
        static std::string trim(std::string &&str)
        {
            while (::isspace(str.front()))
                str.erase(str.begin());
            while (::isspace(str.back()))
                str.pop_back();
            return str;
        }
        std::any visitTerminal(tree::TerminalNode *node) override
        {
            os << trim(node->getText());
            return 0;
        }
    };
} // namespace antlr4
