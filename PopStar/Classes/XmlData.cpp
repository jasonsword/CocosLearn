#include "XmlData.h"

USING_NS_CC;

static XmlData* _xmlData = nullptr;

XmlData::XmlData()
{
	_doc = nullptr;
}

XmlData* XmlData::getInstance()
{
	if (_xmlData == nullptr)
	{
		_xmlData = new XmlData();
		_xmlData->init();
	}
	return _xmlData;
}

XmlData::~XmlData()
{
	saveStarInfo();
	CC_SAFE_DELETE(_xmlData);
	CC_SAFE_DELETE(_doc);
}

void XmlData::init()
{
	memset(_starinfo, 0, sizeof(_starinfo));
	for (int x = 0; x < COL_NUM; x++)
	{
		for (int y = 0; y < ROW_NUM; y++)
		{
			_starinfo[x][y].x = x;
			_starinfo[x][y].y = y;
			_starinfo[x][y].exists = false;
			_starinfo[x][y].color = Star::StarColor::RED;
		}
	}

	_doc = new tinyxml2::XMLDocument();

}

void XmlData::parseStarInfo()
{
	std::string strPath = FileUtils::getInstance()->getWritablePath() + "data.xml";
	int errorno = _doc->LoadFile(strPath.c_str());
	if (errorno != 0)
	{
		CCLOG("xml doc parse error no:%d", errorno);
		return;
	}
	auto root = _doc->RootElement();
	if (root == 0)
	{
		CCLOG("xml doc parse error root not found!");
		return;
	}
	auto starRoot = root->FirstChildElement("starRoot");
	if (starRoot == 0)
	{
		CCLOG("xml doc parse error starRoot not found!");
		return;
	}

	for (starRoot = root->FirstChildElement("starRoot"); starRoot; starRoot = starRoot->NextSiblingElement("starRoot"))
	{
		for (auto star = starRoot->FirstChildElement(); star; star = star->NextSiblingElement())
		{
			int x = star->IntAttribute("x");
			int y = star->IntAttribute("y");
			_starinfo[x][y].color = (Star::StarColor)star->IntAttribute("color");
			_starinfo[x][y].exists = star->BoolAttribute("exists");
		}
	}
}

void XmlData::saveStarInfo()
{
	if (_doc->NoChildren())
	{
		auto declare = _doc->NewDeclaration();
		_doc->InsertFirstChild(declare);
		auto root = _doc->NewElement("PopStarRoot");
		_doc->InsertEndChild(root);
	}
	auto root = _doc->RootElement();

	auto starRoot = root->FirstChildElement("starRoot");
	if (starRoot != 0)
	{
		root->DeleteChild(starRoot);
	}
	starRoot = _doc->NewElement("starRoot");

	for (int x = 0; x < COL_NUM; x++)
	{
		for (int y = 0; y < ROW_NUM; y++)
		{
			auto star = _doc->NewElement("star");

			star->SetAttribute("x", x);
			star->SetAttribute("y", y);
			star->SetAttribute("color", _starinfo[x][y].color);
			star->SetAttribute("exists", _starinfo[x][y].exists);

			starRoot->InsertEndChild(star);
		}
	}

	root->InsertEndChild(starRoot);

	std::string strPath = FileUtils::getInstance()->getWritablePath() + "data.xml";
	CCLOG("SAVE PATH: %s", strPath.c_str());
	_doc->SaveFile(strPath.c_str());
}

void XmlData::setStarInfo(int x, int y, bool exists, Star::StarColor color /*= Star::StarColor::RED*/)
{
	_starinfo[x][y].color = color;
	_starinfo[x][y].exists = exists;
}
