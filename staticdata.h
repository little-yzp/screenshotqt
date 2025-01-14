#pragma once
#ifndef __STATICDATA_H__
#define __STATICDATA_H__
#include<QRect>
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
};
#endif

