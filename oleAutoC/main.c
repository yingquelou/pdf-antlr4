#include <Windows.h>
#include <stdio.h>
#include <oaidl.h>
void show(LPCSTR lpText)
{
    MessageBoxEx(NULL, lpText, "Message", MB_OK, LANG_CHINESE);
}
void showW(LPCWSTR lpText)
{
    MessageBoxExW(NULL, lpText, L"MessageW", MB_OK, LANG_CHINESE);
}
HRESULT showHresult(HRESULT code)
{
    switch (code)
    {
    case S_OK:
        printf("%s\n", "S_OK");
        break;
    case REGDB_E_CLASSNOTREG:
        printf("%s\n", "REGDB_E_CLASSNOTREG");
        break;
    case E_NOINTERFACE:
        printf("%s\n", "E_NOINTERFACE");
        break;
    case REGDB_E_READREGDB:
        printf("%s\n", "REGDB_E_READREGDB");
        break;
    case CO_E_DLLNOTFOUND:
        printf("%s\n", "CO_E_DLLNOTFOUND");
        break;
    case CO_E_APPNOTFOUND:
        printf("%s\n", "CO_E_APPNOTFOUND");
        break;
    case E_ACCESSDENIED:
        printf("%s\n", "E_ACCESSDENIED");
        break;
    case CO_E_ERRORINDLL:
        printf("%s\n", "CO_E_ERRORINDLL");
        break;
    case CO_E_APPDIDNTREG:
        printf("%s\n", "CO_E_APPDIDNTREG");
        break;
    case DISP_E_BADINDEX:
        printf("%s\n", "DISP_E_BADINDEX");
        break;
    case E_INVALIDARG:
        printf("%s\n", "E_INVALIDARG");
        break;
    case E_OUTOFMEMORY:
        printf("%s\n", "E_OUTOFMEMORY");
        break;
    default:
        printf("%ld\n", code);
        break;
    }
    return code;
}
#define Show(Message) _Generic((Message), char *: show(Message), wchar_t *: showW(Message), default: show("UnImplements"))
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    freopen("D:\\projects\\c\\demo\\log.txt", "w", stdout);
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    CLSID clsid;
    if (SUCCEEDED(CLSIDFromProgID(OLESTR("Word.Application"), &clsid)))
    {
        IDispatch *pWordApp = NULL;
        if (SUCCEEDED(showHresult(CoCreateInstance(&clsid, NULL, CLSCTX_LOCAL_SERVER, &IID_IDispatch, (void **)&pWordApp))))
        {
            // 假设 spDispatch 是一个指向实现了 IDispatch 的 COM 对象的指针
            ITypeInfo *pTypeInfo;
            HRESULT hr = pWordApp->lpVtbl->GetTypeInfo(pWordApp, 0, LOCALE_SYSTEM_DEFAULT, &pTypeInfo); // 获取类型信息

            BSTR bstrName = SysAllocString(L""); // 用于存放成员名
            if (SUCCEEDED(hr))
            {
                // 初始化一些辅助变量
                MEMBERID memId;
                TYPEATTR *pTypeAttr;
                // 获取类型描述符
                hr = pTypeInfo->lpVtbl->GetTypeAttr(pTypeInfo, &pTypeAttr);
                if (SUCCEEDED(hr))
                {
                    // 遍历方法和属性
                    for (UINT i = 0; i < pTypeAttr->cFuncs; ++i)
                    {
                        // 获取方法
                        if (i < pTypeAttr->cFuncs)
                        {
                            FUNCDESC *pFuncDesc;
                            hr = pTypeInfo->lpVtbl->GetFuncDesc(pTypeInfo, i, &pFuncDesc);
                            if (SUCCEEDED(hr))
                            {
                                // 提取方法信息
                                pTypeInfo->lpVtbl->GetDocumentation(pTypeInfo, pFuncDesc->memid, &bstrName, NULL, NULL, NULL);
                                // 打印或处理方法名
                                // MEMBERID *pMemId = malloc(sizeof(MEMBERID) * pFuncDesc->cParams);
                                BSTR *rgBstrNames = malloc(sizeof(BSTR) * (pFuncDesc->cParams+1));
                                UINT ct=0;
                                pTypeInfo->lpVtbl->GetNames(pTypeInfo, pFuncDesc->memid,rgBstrNames,pFuncDesc->cParams + 1,&ct);
                                wprintf(L"Method: %s ", bstrName);
                                for (size_t j = 1; j < ct; j++)
                                {
                                    // wprintf(L"%#x ", pMemId[j]);
                                    wprintf(L"%s ",rgBstrNames[j]);
                                }
                                wprintf(L"\n");
                                SysFreeString(bstrName);
                                pTypeInfo->lpVtbl->ReleaseFuncDesc(pTypeInfo, pFuncDesc);
                                // free(pMemId);
                                free(rgBstrNames);
                            }
                        }
                    }
                    // 获取属性
                    for (UINT i = 0; i < pTypeAttr->cVars; ++i)
                    {
                        VARDESC *pVarDesc = NULL;
                        hr = pTypeInfo->lpVtbl->GetVarDesc(pTypeInfo, (i - pTypeAttr->cFuncs), &pVarDesc);
                        if (SUCCEEDED(hr))
                        {
                            // 提取属性信息
                            pTypeInfo->lpVtbl->GetDocumentation(pTypeInfo, pVarDesc->memid, &bstrName, NULL, NULL, NULL);
                            // 打印或处理属性名
                            wprintf(L"Property: %s\n", bstrName);
                            SysFreeString(bstrName);
                            pTypeInfo->lpVtbl->ReleaseVarDesc(pTypeInfo, pVarDesc);
                        }
                    }

                    // 释放类型描述符
                    pTypeInfo->lpVtbl->ReleaseTypeAttr(pTypeInfo, pTypeAttr);
                }

                // 释放类型信息接口
                pTypeInfo->lpVtbl->Release(pTypeInfo);
            }
            else
            {
                // 处理获取类型信息失败的情况
            }

            // 清理BSTR
            SysFreeString(bstrName);
            pWordApp->lpVtbl->Release(pWordApp);
        }
    }
    CoUninitialize();
    fclose(stdout);
    return 0;
}