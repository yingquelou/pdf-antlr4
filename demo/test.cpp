#include <iostream>
#include <fstream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

int main() {
    // 创建一个输出文件流
    std::ofstream file("example.txt.gz", std::ios_base::out | std::ios_base::binary);

    // 创建一个 Boost.IOStreams 的 filtering_stream 对象
    boost::iostreams::filtering_ostream out;
    out.push(boost::iostreams::gzip_compressor());
    out.push(file);

    // 写入数据到 filtering_stream
    out << "Hello, World! This is a test message.";

    // 关闭 filtering_stream
    out.reset();
    file.close();

    // 创建一个输入文件流
    std::ifstream input("example.txt.gz", std::ios_base::in | std::ios_base::binary);

    // 创建一个 Boost.IOStreams 的 filtering_stream 对象
    boost::iostreams::filtering_istream in;
    in.push(boost::iostreams::gzip_decompressor());
    in.push(input);

    // 从 filtering_stream 中读取数据
    std::string message;
    std::getline(in, message);

    // 输出读取的数据
    std::cout << "Decompressed message: " << message << std::endl;

    return 0;
}
