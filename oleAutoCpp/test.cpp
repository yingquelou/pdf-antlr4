#include <iostream>
#include <atlcomcli.h>
#define IFSUCCEEDED(exp) if (SUCCEEDED(exp))
int main(int argc, char const *argv[])
{

    // 假设 spDispatch 已经是一个有效的 IDispatch 指针
    CoInitialize(nullptr);
    CComPtr<IDispatch> spDispatch;
    CComVariant var;
    HRESULT hr;
    IFSUCCEEDED(spDispatch.CoCreateInstance(OLESTR("Word.Application"), nullptr, CLSCTX_LOCAL_SERVER))
    {
        ITypeInfo *spTypeInfo = nullptr;
        IFSUCCEEDED(spDispatch->GetTypeInfo(0, LOCALE_SYSTEM_DEFAULT, &spTypeInfo))
        {
            TYPEATTR *pTypeAttr = nullptr;
            IFSUCCEEDED(spTypeInfo->GetTypeAttr(&pTypeAttr))
            {
                // 遍历方法
                for (UINT i = 0; i < pTypeAttr->cFuncs; ++i)
                {
                    FUNCDESC *funcDesc = nullptr;
                    IFSUCCEEDED(spTypeInfo->GetFuncDesc(i, &funcDesc))
                    {
                        // 获取方法名
                        BSTR methodName;
                        IFSUCCEEDED(spTypeInfo->GetDocumentation(funcDesc->memid, &methodName, nullptr, nullptr, nullptr))
                        {
                            std::wcout << methodName << '\n';
                            SysFreeString(methodName);
                        }
                        // UINT *cNames = (UINT *)malloc(sizeof(UINT)*(funcDesc->cParams + 1));
                        // IFSUCCEEDED(spTypeInfo->GetNames(funcDesc->memid, &methodName, funcDesc->cParams + 1, cNames))
                        // {
                        //     for (INT j = 0; j < funcDesc->cParams + 1; j++)
                        //     {
                        //         std::wcout << methodName[j] << ' ';
                        //     }
                        // }
                        // free(cNames);
                        // 解析方法参数类型签名
                        // for (UINT iParam = 0; iParam < funcDesc.cParams; iParam++)
                        // {
                        //     TYPEDESC &paramTypeDesc = funcDesc.lprgelemdescParam[iParam].tdesc;

                        //     // 可能需要递归解析嵌套类型
                        //     ParseTypeDescription(paramTypeDesc);

                        //     // 打印或记录参数类型
                        // }

                        // // 获取返回类型签名
                        // TYPEDESC &returnTypeDesc = funcDesc.tdescResult;
                        // ParseTypeDescription(returnTypeDesc);

                        // // 打印或记录方法名称及完整签名
                        // // 注意释放BSTR和FUNCDESC结构
                        // SysFreeString(methodName);
                        // spTypeInfo->ReleaseFuncDesc(&funcDesc);
                    }
                }

                // 遍历变量（属性）
                // for (UINT iVar = 0; iVar < pTypeAttr->cVars; iVar++)
                // {
                //     VARDESC varDesc;
                //     hr = spTypeInfo->GetVarDesc(iVar, &varDesc);

                //     if (SUCCEEDED(hr))
                //     {
                //         // 获取变量名
                //         BSTR varName;
                //         hr = spTypeInfo->GetDocumentation(varDesc.memid, &varName, nullptr, nullptr, nullptr);

                //         // 获取变量类型签名
                //         TYPEDESC &varTypeDesc = varDesc.elemdescVar.tdesc;
                //         ParseTypeDescription(varTypeDesc);

                //         // 打印或记录属性名称及类型
                //         SysFreeString(varName);
                //         spTypeInfo->ReleaseVarDesc(&varDesc);
                //     }
                // }

                // 释放TYPEATTR结构
                spTypeInfo->ReleaseTypeAttr(pTypeAttr);
            }
        }
        var = 0;
        IFSUCCEEDED(spDispatch.Invoke1(OLESTR("Quit"), &var))
        {
            std::cout << "\nQuit";
        }
    }
}
// 解析单个类型描述符的辅助函数
// void ParseTypeDescription(TYPEDESC &typeDesc)
// {
//     switch (typeDesc.vt)
//     {
//     case VT_I2:
//         // 短整型
//         break;
//     case VT_I4:
//         // 整型
//         break;
//     // 其他基本类型...
//     case VT_PTR:
//         // 指针类型，继续解析内部的子类型
//         ParseTypeDescription(typeDesc.lptdesc);
//         break;
//     case VT_USERDEFINED:
//         // 用户定义类型，需要进一步获取相关信息
//         GUID guid;
//         HREFTYPE hRefType;
//         spTypeInfo->GetRefTypeInfo(typeDesc.hreftype, &spTempTypeInfo);
//         // 使用spTempTypeInfo获取更多信息...
//         break;
//     // 其他类型...
//     default:
//         break;
//     }
// }