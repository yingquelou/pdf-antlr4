#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/copy.hpp>
#include <fstream>
#include <iostream>
#include <string>
int main(int argc, char const *argv[])
{
    using namespace boost;
    for (int i = 1; argv[i]; ++i)
    {
        std::cout << argv[i] << std::endl;
        iostreams::filtering_istream in;
        in.push(iostreams::zlib_decompressor());
        // 载入pdf文件的stream...endstream之间的数据流
        in.push(iostreams::file_source(argv[i], std::ios_base::in | std::ios_base::binary));
        in.seekg(0, std::ios_base::end);
        std::streampos length = in.tellg();
        in.seekg(0, std::ios_base::beg);
        std::string buffer;
        buffer.resize(length);
        in.read(&buffer[0], length);
        std::cout << buffer << std::endl;
        std::ofstream out("test.txt");
        out << buffer;
        out.close();
    }
    return 0;
}
