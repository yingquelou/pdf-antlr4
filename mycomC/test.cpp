#include <zlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#define CHUNK 16384
struct pair
{
    Bytef *buffer;
    std::streampos len;
};
pair readBin(const char *filename)
{
    std::ifstream ifs(filename);
    ifs.seekg(0, std::ifstream::end);
    std::streamoff end = ifs.tellg();
    Bytef *ok = (Bytef *)calloc(1, end + 1);
    ifs.read((char *)ok, end);
    ifs.close();
    return {ok, end};
}

int main()
{
    // 读取PDF文件中的二进制数据，存储到source数组中
    // 假设source和sourceLen是已知的

    // 分配用于存储解压缩数据的缓冲区
    Bytef *dest = (Bytef *)malloc(CHUNK);
    uLongf destLen = CHUNK;
    auto re = readBin("C:/Users/26951/AppData/Local/Temp/scik.0-3-0z.txt");
    // 初始化zlib解压缩流
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = re.len;
    stream.next_in = re.buffer;
    stream.avail_out = CHUNK;
    stream.next_out = dest;

    // 初始化zlib解压缩环境
    int ret = inflateInit(&stream);
    if (ret != Z_OK)
    {
        printf("初始化解压缩环境失败\n");
        return 1;
    }

    // 循环解压缩数据
    do
    {
        ret = inflate(&stream, Z_NO_FLUSH);
        if (ret < 0)
        {
            printf("解压缩失败，错误码：%d\n", ret);
            inflateEnd(&stream);
            return 1;
        }

        // 如果输出缓冲区已满，扩展缓冲区并继续解压缩
        if (stream.avail_out == 0)
        {
            dest = (Bytef *)realloc(dest, destLen + CHUNK);
            stream.next_out = dest + destLen;
            stream.avail_out = CHUNK;
            destLen += CHUNK;
        }
    } while (ret != Z_STREAM_END);

    // 完成解压缩
    inflateEnd(&stream);

    // 输出解压缩后的数据
    printf("解压缩后的数据大小：%lu\n", destLen - stream.avail_out);

    // 处理解压缩后的数据

    // 释放内存
    free(dest);
    free(re.buffer);
    return 0;
}
