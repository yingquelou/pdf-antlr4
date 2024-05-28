// 实现对pdf文件stream与endstream之间的内容的解析
#include <zlib.h>
#include <string>
std::string parserStream(std::string &stream)
{
    std::string result;
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = stream.size();
    strm.next_in = (Bytef *)stream.c_str();
    if (inflateInit(&strm) != Z_OK)
    {
        return result;
    }
    char out[1024];
    do
    {
        strm.avail_out = 1024;
        strm.next_out = (Bytef *)out;
        if (inflate(&strm, Z_NO_FLUSH) == Z_STREAM_ERROR)
        {
            return result;
        }
        result.append(out, 1024 - strm.avail_out);
    } while (strm.avail_out == 0);
    inflateEnd(&strm);
    return result;
}
#include <iostream>
#include <fstream>
// 实现读取文件内容到std::string
std::string readFile(const std::string &filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file)
    {
        return "";
    }
    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());

    return content;
}

int main(int argc, char const *argv[])
{
    for (int i = 1; argv[i]; i++)
    {
        std::string stream = readFile(argv[i]);
        std::string result = parserStream(stream);
        std::cout << result.size() << std::endl;
        std::cout << result << std::endl;
    }
    return 0;
}
