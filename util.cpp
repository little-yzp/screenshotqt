#include "util.h"
using namespace std;

OCR_HANDLE MYOCR::Init(const char* DET_MODEL, const char* CLS_MODEL, const char* REC_MODEL, const char* KEY_FILE)
{
	try
	{
		int THREAD_NUM = 3;
		OCR_HANDLE handle = OcrInit(DET_MODEL, CLS_MODEL, REC_MODEL, KEY_FILE, THREAD_NUM);
		return handle;
	}
	catch (const std::exception&)
	{
		return NULL;
	}
	catch (...)
	{
		return NULL;
	}
}

char* MYOCR::Detect(OCR_HANDLE handle, const char*imagePath, const char*imageName, OCR_PARAM*params)
{
	if (handle == NULL) return {'\0'};
	OCR_BOOL ret = OcrDetect(handle, imagePath, imageName, params);
	if (ret)
	{
		int nLen = OcrGetLen(handle);
		if (nLen > 0)
		{
			char* szinfo = (char*)malloc(nLen);
			if (szinfo)
			{
				if (OcrGetResult(handle, szinfo, nLen))
				{
					return szinfo;
				}
			}
		}
	}
}
