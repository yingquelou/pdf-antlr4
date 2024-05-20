#include <iostream>
// #import "stdole2.tlb" auto_search
// #import "C:/Program Files/Microsoft Office/root/Office16/MSACC.OLB" auto_search
// #import "C:/Program Files/Microsoft Office/root/Office16/MSWORD.OLB" auto_search
#include <atlcomcli.h>
#define ifSUCCEEDED(exp) if (SUCCEEDED(exp))
void print(ATL::CComVariant &var)
{
    switch (var.vt)
    {
    case VT_BSTR:
        std::wcout << var.bstrVal;
        break;
    case VT_I4:
        std::cout << var.intVal;
        break;
    default:
        std::cout << "Unimpliments:" << var.vt;
    }
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    // using namespace ATL;
    auto &os = std::cout;
    auto &wos = std::wcout;
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    CComPtr<IDispatch> WordApp;
    CComVariant var;
    ifSUCCEEDED(WordApp.CoCreateInstance(OLESTR("Word.Application"), nullptr, CLSCTX_LOCAL_SERVER))
    {
        // os << "ok";
        ifSUCCEEDED(WordApp.GetPropertyByName(OLESTR("Documents"), &var))
        {
            if (var.vt == VT_DISPATCH)
            {
                CComPtr<IDispatch> Documents(var.pdispVal);
                // New
                ifSUCCEEDED(Documents.Invoke0(OLESTR("Add"), &var))
                {
                    if (var.vt == VT_DISPATCH)
                    {
                        CComPtr<IDispatch> doc(var.pdispVal);

                        ifSUCCEEDED(doc.Invoke0(OLESTR("Range"), &var))
                        {
                            if (var.vt == VT_DISPATCH)
                            {
                                CComPtr<IDispatch> range(var.pdispVal);
                                var = OLESTR("ÄãºÃ!");
                                range.Invoke1(OLESTR("InsertAfter"), &var);
                                var = OLESTR("ATL");
                                range.Invoke1(OLESTR("InsertAfter"), &var);
                                var = OLESTR("ok");
                                range.Invoke1(OLESTR("InsertAfter"), &var);
                            }
                        }
                        // Save
                        var = OLESTR("aaa.docx");
                        ifSUCCEEDED(doc.Invoke1(OLESTR("SaveAs"), &var))
                        {
                            os << "save successfully!";
                        }
                    }
                }
            }
        }

        var = 0;
        ifSUCCEEDED(WordApp.Invoke1(OLESTR("Quit"), &var))
        {
            os << "\nQuit";
        }
    }
    CoUninitialize();
    return 0;
}
