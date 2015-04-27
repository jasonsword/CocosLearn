#ifndef __XML_DATA_H__
#define __XML_DATA_H__

#include "cocos2d.h"
#include "tinyxml2/tinyxml2.h"
#include "StarMatrix.h"

typedef struct
{
	int x;
	int y;
	Star::StarColor color;
	bool exists;
}StarInfo;

class XmlData
{
public:
	void init();

	void reset();

	Star::StarColor getStarColor(int x, int y){ return _starinfo[x][y].color; };
	bool getStar(int x, int y){ return _starinfo[x][y].exists; };
	void setStarInfo(int x, int y, bool exists, Star::StarColor color = Star::StarColor::RED);

	void XmlData::parseStarInfo();
	void XmlData::saveStarInfo();

	static XmlData* getInstance();
	virtual ~XmlData();

protected:
	XmlData();

private:
	tinyxml2::XMLDocument* _doc;

	StarInfo _starinfo[COL_NUM][ROW_NUM];
};

#endif // __XML_DATA_H__
