#pragma once
#ifndef __STATICDATA_H__
#define __STATICDATA_H__
#include <QRect>
#include"picview.h"
#include "util.h"

class StaticData 
{
private:
	StaticData()
	{

	}
public:
	static StaticData& Instance()
	{
		static StaticData data;
		return data;
	}
	QRect s_rect;
	QScreen* s_curScreenPtr;
	QList<PicView>s_picViewList;
	OCR_HANDLE handle;
};
#endif

