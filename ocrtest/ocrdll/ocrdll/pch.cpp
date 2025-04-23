// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
#include <Python.h>
#include <stdio.h>
#include <string>

#pragma warning(disable: 4996)
// 当使用预编译的头时，需要使用此源文件，编译才能成功。

char* extract_ocr_text(char* text)
{
    std::string result;
    char* pResult = new char[4096]{ '\0' };

    Py_SetPythonHome(L"C:\\Users\\21242\\AppData\\Local\\Programs\\Python\\Python312\\");

    Py_Initialize();

    if (!Py_IsInitialized())
    {
        printf("初始化失败\n");
        Py_Finalize();
    }

    PyObject* pModule;
    PyObject* pFunc = NULL;
    PyObject* pArg = NULL;
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    pModule = PyImport_ImportModule("test");
    if (!pModule)
    {
        printf("py文件导入失败\n");
        Py_Finalize();
        return NULL;
    }
    else
    {
        pFunc = PyObject_GetAttrString(pModule, "extract_ocr_text");
        if (!pFunc)
        {
            printf("函数导入失败");
            Py_Finalize();
            return NULL;
        }

        PyObject* pyParamsA = PyUnicode_FromString(text);

        PyObject* pArgs = PyTuple_Pack(1, pyParamsA);
        PyObject* pValue = PyObject_CallObject(pFunc, pArgs);

        if (pValue != NULL) {
            // 处理不同类型的返回值
            if (PyUnicode_Check(pValue)) {
                // 处理 Unicode 字符串
                Py_ssize_t size;
                const char* str = PyUnicode_AsUTF8AndSize(pValue, &size);
                if (str) {
                    result.assign(str, size);
                }
            }
            else if (PyBytes_Check(pValue)) {
                // 处理 bytes 对象
                char* str = PyBytes_AsString(pValue);
                if (str) {
                    result = str;
                }
            }
            else {
                // 尝试将其他类型转换为字符串
                PyObject* strObj = PyObject_Str(pValue);
                if (strObj) {
                    Py_ssize_t size;
                    const char* str = PyUnicode_AsUTF8AndSize(strObj, &size);
                    if (str) {
                        result.assign(str, size);
                    }
                    Py_DECREF(strObj);
                }
            }
            Py_DECREF(pValue);
        }
        else {
            PyErr_Print();
        }

        Py_DECREF(pModule);
        Py_DECREF(pArgs);
        Py_DECREF(pValue);

        Py_Finalize();

       

        snprintf(pResult, 4096, "%s", result.c_str());


    }
    return pResult;
}