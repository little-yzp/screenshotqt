#pragma once

#include <iostream>
#include "OcrLib/include/OcrLiteCApi.h"

namespace MYOCR {
	OCR_HANDLE Init(const char* DET_MODEL, const char* CLS_MODEL, const char* REC_MODEL, const char* KEY_FILE);
	
	char* Detect(OCR_HANDLE, const char*, const char*, OCR_PARAM*);
}