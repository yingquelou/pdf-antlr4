#include <Windows.h>
#include <stdio.h>
BSTR VT2BSTR(VARTYPE vt)
{
    switch (vt)
    {
    case VT_EMPTY:
        return OLESTR("VT_EMPTY");
    case VT_NULL:
        return OLESTR("VT_NULL");
    case VT_I2:
        return OLESTR("VT_I2");
    case VT_I4:
        return OLESTR("VT_I4");
    case VT_R4:
        return OLESTR("VT_R4");
    case VT_R8:
        return OLESTR("VT_R8");
    case VT_CY:
        return OLESTR("VT_CY");
    case VT_DATE:
        return OLESTR("VT_DATE");
    case VT_BSTR:
        return OLESTR("VT_BSTR");
    case VT_DISPATCH:
        return OLESTR("VT_DISPATCH");
    case VT_ERROR:
        return OLESTR("VT_ERROR");
    case VT_BOOL:
        return OLESTR("VT_BOOL");
    case VT_VARIANT:
        return OLESTR("VT_VARIANT");
    case VT_UNKNOWN:
        return OLESTR("VT_UNKNOWN");
    case VT_DECIMAL:
        return OLESTR("VT_DECIMAL");
    case VT_I1:
        return OLESTR("VT_I1");
    case VT_UI1:
        return OLESTR("VT_UI1");
    case VT_UI2:
        return OLESTR("VT_UI2");
    case VT_UI4:
        return OLESTR("VT_UI4");
    case VT_I8:
        return OLESTR("VT_I8");
    case VT_UI8:
        return OLESTR("VT_UI8");
    case VT_INT:
        return OLESTR("VT_INT");
    case VT_UINT:
        return OLESTR("VT_UINT");
    case VT_VOID:
        return OLESTR("VT_VOID");
    case VT_HRESULT:
        return OLESTR("VT_HRESULT");
    case VT_PTR:
        return OLESTR("VT_PTR");
    case VT_SAFEARRAY:
        return OLESTR("VT_SAFEARRAY");
    case VT_CARRAY:
        return OLESTR("VT_CARRAY");
    case VT_USERDEFINED:
        return OLESTR("VT_USERDEFINED");
    case VT_LPSTR:
        return OLESTR("VT_LPSTR");
    case VT_LPWSTR:
        return OLESTR("VT_LPWSTR");
    case VT_RECORD:
        return OLESTR("VT_RECORD");
    case VT_INT_PTR:
        return OLESTR("VT_INT_PTR");
    case VT_UINT_PTR:
        return OLESTR("VT_UINT_PTR");
    case VT_FILETIME:
        return OLESTR("VT_FILETIME");
    case VT_BLOB:
        return OLESTR("VT_BLOB");
    case VT_STREAM:
        return OLESTR("VT_STREAM");
    case VT_STORAGE:
        return OLESTR("VT_STORAGE");
    case VT_STREAMED_OBJECT:
        return OLESTR("VT_STREAMED_OBJECT");
    case VT_STORED_OBJECT:
        return OLESTR("VT_STORED_OBJECT");
    case VT_BLOB_OBJECT:
        return OLESTR("VT_BLOB_OBJECT");
    case VT_CF:
        return OLESTR("VT_CF");
    case VT_CLSID:
        return OLESTR("VT_CLSID");
    case VT_VERSIONED_STREAM:
        return OLESTR("VT_VERSIONED_STREAM");
    // case VT_ILLEGALMASKED:
    //     return OLESTR("VT_ILLEGALMASKED");
    // case VT_TYPEMASK:
    //     return OLESTR("VT_TYPEMASK");
    case VT_BSTR_BLOB:
        return OLESTR("VT_BSTR_BLOB|VT_ILLEGALMASKED|VT_TYPEMASK");
    case VT_VECTOR:
        return OLESTR("VT_VECTOR");
    case VT_ARRAY:
        return OLESTR("VT_ARRAY");
    case VT_BYREF:
        return OLESTR("VT_BYREF");
    case VT_RESERVED:
        return OLESTR("VT_RESERVED");
    case VT_ILLEGAL:
        return OLESTR("VT_ILLEGAL");
    }
    return OLESTR("");
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
#define IFSUCCEEDED(exp) if (SUCCEEDED(exp))
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
int main(int argc, char const *argv[])
{
    if (freopen("stdout.txt", "w", stdout))
    {
        CoInitializeEx(NULL, COINIT_MULTITHREADED);
        CLSID clsid;
        IFSUCCEEDED(CLSIDFromProgID(OLESTR("Word.Application"), &clsid))
        {
            IDispatch *pWordApp = NULL;
            IFSUCCEEDED(CoCreateInstance(&clsid, NULL, CLSCTX_LOCAL_SERVER, &IID_IDispatch, &pWordApp))
            {
                ITypeInfo *pTypeInfo;
                IFSUCCEEDED(pWordApp->lpVtbl->GetTypeInfo(pWordApp, 0, LOCALE_SYSTEM_DEFAULT, &pTypeInfo)) // 获取类型信息
                {
                    // 初始化一些辅助变量
                    TYPEATTR *pTypeAttr;
                    pTypeAttr->typekind;
                    // 获取类型描述符
                    IFSUCCEEDED(pTypeInfo->lpVtbl->GetTypeAttr(pTypeInfo, &pTypeAttr))
                    {
                        // 获取方法
                        FUNCDESC *pFuncDesc = NULL;
                        TYPEDESC pTypeDesc;
                        for (UINT i = 0; i < pTypeAttr->cFuncs; ++i)
                        {
                            IFSUCCEEDED(pTypeInfo->lpVtbl->GetFuncDesc(pTypeInfo, i, &pFuncDesc))
                            {
                                UINT cMaxNames = pFuncDesc->cParams + 1;
                                BSTR *rgBstrNames = malloc(sizeof(BSTR) * cMaxNames);
                                UINT cNames;
                                IFSUCCEEDED(pTypeInfo->lpVtbl->GetNames(pTypeInfo, pFuncDesc->memid, rgBstrNames, cMaxNames, &cNames))
                                {
                                    pTypeDesc = pFuncDesc->elemdescFunc.tdesc;
                                    // pTypeDesc.hreftype
                                    wprintf(L"%s->%s\n\t", rgBstrNames[0], VT2BSTR(pFuncDesc->elemdescFunc.tdesc.vt));
                                    for (UINT j = 1; j < cNames; j++)
                                    {
                                        wprintf(L"%s:%s\n\t", rgBstrNames[j], VT2BSTR(pFuncDesc->lprgelemdescParam[j - 1].tdesc.vt));
                                    }
                                    printf("\n");
                                }
                                pTypeInfo->lpVtbl->ReleaseFuncDesc(pTypeInfo, pFuncDesc);
                                free(rgBstrNames);
                            }
                        }
                        // 获取属性
                        // VARDESC *pVarDesc = NULL;
                        // for (UINT i = 0; i < pTypeAttr->cVars; ++i)
                        // {
                        //     IFSUCCEEDED(pTypeInfo->lpVtbl->GetVarDesc(pTypeInfo, i, &pVarDesc))
                        //     {
                        //         // 提取属性信息
                        //         pTypeInfo->lpVtbl->GetDocumentation(pTypeInfo, pVarDesc->memid, &bstrName, NULL, NULL, NULL);
                        //         pVarDesc->elemdescVar;
                        //         // 打印或处理属性名
                        //         wprintf(L"Property: %s\n", bstrName);
                        //         SysFreeString(bstrName);
                        //         pTypeInfo->lpVtbl->ReleaseVarDesc(pTypeInfo, pVarDesc);
                        //     }
                        // }
                    }
                    // 释放类型描述符
                    pTypeInfo->lpVtbl->ReleaseTypeAttr(pTypeInfo, pTypeAttr);

                    // 释放类型信息接口
                    pTypeInfo->lpVtbl->Release(pTypeInfo);
                }
                else
                {
                    // 处理获取类型信息失败的情况
                }
                pWordApp->lpVtbl->Release(pWordApp);
            }
        }
        CoUninitialize();
        fclose(stdout);
    }
    return 0;
}