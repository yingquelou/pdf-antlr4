#include <boost/spirit/include/qi.hpp>
#include <iostream>
#include <iterator>

namespace qi = boost::spirit::qi;

int main()
{
    std::cout << "Enter a number: ";

    // 创建std::istreambuf_iterator，从标准输入流中读取数据
    std::istream_iterator<char> begin(std::cin), end;

    int number;

    // 使用qi::parse解析输入数据
    // bool success = qi::parse(begin, end, qi::int_, number);

    // if (success) {
    //     std::cout << "Parsed number: " << number << std::endl;
    // } else {
    //     std::cout << "Parsing failed. Please enter a valid number." << std::endl;
    // }
    std::cout << *begin;
    std::cout << *++begin;
    return 0;
}
