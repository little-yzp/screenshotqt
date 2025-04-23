#include <iostream>
#include <tchar.h>
#include <Windows.h>
using namespace std;

int main()
{
    // 加载DLL文件
    HINSTANCE hDllInst;
    hDllInst = LoadLibrary(L"./ocrdll.dll"); //调用DLL
    if (hDllInst) {
        typedef char* (*EXTRACT_OCR_TEXT)(const char *text); //后边为参数，前面为返回值
        EXTRACT_OCR_TEXT extract = (EXTRACT_OCR_TEXT)GetProcAddress(hDllInst, "extract_ocr_text"); //GetProcAddress为获取该函数的地址
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

        printf("加载库失败: %s\n错误代码: %d\n错误信息: %s\n",
            "./ocrdll.dll", error, errorText);

        LocalFree(errorText);
    }

    return 0;
}