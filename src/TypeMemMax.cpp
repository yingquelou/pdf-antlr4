#include <type_traits>
#include <typeinfo>
#include <windows.h>
template <typename... T>
struct MaxType
{
};
template <typename T>
struct MaxType<T>
{
public:
    using type = std::remove_cv_t<T>;
};
template <typename T1, typename T2>
struct MaxType<T1, T2>
{
public:
    using type = std::conditional_t<(sizeof(std::remove_cv_t<T1>) > sizeof(std::remove_cv_t<T2>)), std::remove_cv_t<T1>, std::remove_cv_t<T2>>;
};
template <typename T, typename... Rest>
struct MaxType<T, Rest...>
{
public:
    using type = typename MaxType<T, typename MaxType<Rest...>::type>::type;
};
class Config
{
public:
    Config()
    {
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);
    }
};
static Config conf;
#include <iostream>
int msgbox(LPCSTR lpText)
{
    return MessageBoxA(NULL, lpText, "Message", MB_OK);
}
int main(int argc, char const *argv[])
{
    auto f = []()
    {
        static auto &os = std::cout;

        MaxType<unsigned int, int, void *>::type s;
        switch (MessageBoxA(NULL, typeid(s).name(), "Type", MB_CANCELTRYCONTINUE))
        {
        case IDABORT:
            msgbox("ABORT");
            break;

        case IDCANCEL:
            msgbox("CANCEL");
            break;

        case IDCONTINUE:
            msgbox("CONTINUE");
            break;

        case IDIGNORE:
            msgbox("IGNORE");
            break;

        case IDNO:
            msgbox("NO");
            break;

        case IDOK:
            msgbox("OK");
            break;

        case IDRETRY:
            msgbox("RETRY");
            break;

        case IDTRYAGAIN:
            msgbox("TRYAGAIN");
            break;

        case IDYES:
            msgbox("YES");
            break;
        default:
            msgbox("Nothing!");
            break;
        }
    };
    f();
    return 0;
}