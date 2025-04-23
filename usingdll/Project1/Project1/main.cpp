#include <iostream>
#include <tchar.h>
#include <Windows.h>
using namespace std;

int main()
{
    // ����DLL�ļ�
    HINSTANCE hDllInst;
    hDllInst = LoadLibrary(L"./ocrdll.dll"); //����DLL
    if (hDllInst) {
        typedef char* (*EXTRACT_OCR_TEXT)(const char *text); //���Ϊ������ǰ��Ϊ����ֵ
        EXTRACT_OCR_TEXT extract = (EXTRACT_OCR_TEXT)GetProcAddress(hDllInst, "extract_ocr_text"); //GetProcAddressΪ��ȡ�ú����ĵ�ַ
        char* text = extract("./test.png");
        cout << text;
    }
    else {
        DWORD error = GetLastError();
        LPTSTR errorText = NULL;

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            error,
            0,
            (LPTSTR)&errorText,
            0,
            NULL);

        printf("���ؿ�ʧ��: %s\n�������: %d\n������Ϣ: %s\n",
            "./ocrdll.dll", error, errorText);

        LocalFree(errorText);
    }

    return 0;
}