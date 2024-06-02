// 实现对pdf文件stream与endstream之间的内容的解析

// 1. 读取文件内容到std::string
// 2. 能解析pdf常见的编码的stream内容
// 3. 输出解析后的内容

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <zlib.h>

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
#include <iostream>
#include <zlib.h>

std::string decode_FlateDecode(const std::string &data)
{
    std::string decoded_data;
    z_stream zs;
    zs.zalloc = Z_NULL;
    zs.zfree = Z_NULL;
    zs.opaque = Z_NULL;
    zs.avail_in = 0;
    zs.next_in = Z_NULL;

    int ret = inflateInit(&zs);
    if (ret != Z_OK)
    {
        return "Error: Failed to initialize zlib\n";
    }

    zs.avail_in = data.size();
    zs.next_in = (Bytef *)data.data();

    char buffer[4096];
    do
    {
        zs.avail_out = 4096;
        zs.next_out = (Bytef *)buffer;
        ret = inflate(&zs, Z_NO_FLUSH);
        if (ret < 0)
        {
            inflateEnd(&zs);
            return "Error: Failed to decode FlateDecode stream\n";
        }
        decoded_data.append(buffer, 4096 - zs.avail_out);
    } while (zs.avail_out == 0);

    inflateEnd(&zs);
    return decoded_data;
}

int main(int argc, const char *argv[])
{
    for (size_t i = 1; argv[i]; i++)
    {
        std::cout << "File: " << argv[i] << std::endl;
        std::string content = read_file(argv[1]);
        if (content.empty())
            continue;
        std::cout << decode_FlateDecode(content);
    }

    return 0;
}