// 实现对pdf文件stream与endstream之间的内容的解析

// 1. 读取文件内容到std::string
// 2. 能解析pdf常见的编码的stream内容
// 3. 输出解析后的内容

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <antlr4-runtime.h>
#include "pdfLexer.h"
#include "pdfParser.h"
#include "pdfBaseVisitor.h"
#include "pdfBaseListener.h"
#include "format.h"

using namespace antlr4;

std::string read_file(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs)
    {
        std::cerr << "open file " << filename << " failed\n";
        return "";
    }
    std::string content;
    ifs.seekg(0, std::ios::end);
    content.resize(ifs.tellg());
    ifs.seekg(0, std::ios::beg);
    ifs.read(&content[0], content.size());
    return content;
}

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " filename\n";
        return 1;
    }
    std::string content = read_file(argv[1]);
    if (content.empty())
    {
        return 1;
    }
    ANTLRInputStream input(content);
    pdfLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    pdfParser parser(&tokens);
    tree::ParseTree *tree = parser.start();
    format fmt(std::cout);
    fmt.visit(tree);
    return 0;
}