#include "path.h"
#ifdef __MINGW32__
#include <windows.h>
char *pwd()
{
    static CHAR buffer[PATH_MAX];
    
    DWORD ln = GetCurrentDirectory(PATH_MAX, buffer)+1;
    char *str = (char *)malloc(ln);
    memmove(str, buffer, ln);
    return str;
}
#else
#include <filesystem>
char *pwd()
{
    auto &&path = std::filesystem::current_path().string();
    char *str = (char *)malloc(path.size() + 1);
    path.copy(str, path.length());
    str[path.length()] = '\0';
    ;
    return str;
}
#endif