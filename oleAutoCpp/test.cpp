#include <iostream>
#include <atlcomcli.h>
#define IFSUCCEEDED(exp) if (SUCCEEDED(exp))
int main(int argc, char const *argv[])
{

    // ���� spDispatch �Ѿ���һ����Ч�� IDispatch ָ��
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
                // ��������
                for (UINT i = 0; i < pTypeAttr->cFuncs; ++i)
                {
                    FUNCDESC *funcDesc = nullptr;
                    IFSUCCEEDED(spTypeInfo->GetFuncDesc(i, &funcDesc))
                    {
                        // ��ȡ������
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
                        // ����������������ǩ��
                        // for (UINT iParam = 0; iParam < funcDesc.cParams; iParam++)
                        // {
                        //     TYPEDESC &paramTypeDesc = funcDesc.lprgelemdescParam[iParam].tdesc;

                        //     // ������Ҫ�ݹ����Ƕ������
                        //     ParseTypeDescription(paramTypeDesc);

                        //     // ��ӡ���¼��������
                        // }

                        // // ��ȡ��������ǩ��
                        // TYPEDESC &returnTypeDesc = funcDesc.tdescResult;
                        // ParseTypeDescription(returnTypeDesc);

                        // // ��ӡ���¼�������Ƽ�����ǩ��
                        // // ע���ͷ�BSTR��FUNCDESC�ṹ
                        // SysFreeString(methodName);
                        // spTypeInfo->ReleaseFuncDesc(&funcDesc);
                    }
                }

                // �������������ԣ�
                // for (UINT iVar = 0; iVar < pTypeAttr->cVars; iVar++)
                // {
                //     VARDESC varDesc;
                //     hr = spTypeInfo->GetVarDesc(iVar, &varDesc);

                //     if (SUCCEEDED(hr))
                //     {
                //         // ��ȡ������
                //         BSTR varName;
                //         hr = spTypeInfo->GetDocumentation(varDesc.memid, &varName, nullptr, nullptr, nullptr);

                //         // ��ȡ��������ǩ��
                //         TYPEDESC &varTypeDesc = varDesc.elemdescVar.tdesc;
                //         ParseTypeDescription(varTypeDesc);

                //         // ��ӡ���¼�������Ƽ�����
                //         SysFreeString(varName);
                //         spTypeInfo->ReleaseVarDesc(&varDesc);
                //     }
                // }

                // �ͷ�TYPEATTR�ṹ
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
// �������������������ĸ�������
// void ParseTypeDescription(TYPEDESC &typeDesc)
// {
//     switch (typeDesc.vt)
//     {
//     case VT_I2:
//         // ������
//         break;
//     case VT_I4:
//         // ����
//         break;
//     // ������������...
//     case VT_PTR:
//         // ָ�����ͣ����������ڲ���������
//         ParseTypeDescription(typeDesc.lptdesc);
//         break;
//     case VT_USERDEFINED:
//         // �û��������ͣ���Ҫ��һ����ȡ�����Ϣ
//         GUID guid;
//         HREFTYPE hRefType;
//         spTypeInfo->GetRefTypeInfo(typeDesc.hreftype, &spTempTypeInfo);
//         // ʹ��spTempTypeInfo��ȡ������Ϣ...
//         break;
//     // ��������...
//     default:
//         break;
//     }
// }