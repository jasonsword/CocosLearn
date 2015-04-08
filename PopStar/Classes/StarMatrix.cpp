#include "StarMatrix.h"

USING_NS_CC;

static cocos2d::Size starSize(0.0f, 0.0f);

bool StarMatrix::init()
{
	if (!Layer::init())
	{
		return false;
	}

	memset(_star, 0, sizeof(_star));

	return true;
}

void StarMatrix::createMatrix()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float width = visibleSize.width / COL_NUM;
	starSize = Size(width, width);

	for (int j = 0; j < COL_NUM; j++)
	{
		for (int i = 0; i < ROW_NUM; i++)
		{
			auto star = Star::createStar();
			star->setXY(i, j);
			star->setContentSize(starSize);
			//这里添加下落的动作 直到终点
			Vec2 dest = Vec2((i + 0.5f) * width, (j + 0.5f) * width);
			star->setPosition(dest + Vec2(0, width * (j + 1)));
			star->runAction(MoveTo::create(0.25, dest));
			this->addChild(star);

			//一维是行 二维是列
			_star[i][j] = star;
		}
	}
}

void StarMatrix::update(float delta)
{
	genSelectedStar();
}

void StarMatrix::onEnter()
{
	Layer::onEnter();

	CCLOG("StarMatrix OnEnter");

	auto delay = DelayTime::create(0.5f);
	auto callfunc = CallFunc::create([this](){
		this->createMatrix();
	});
	auto delay2 = DelayTime::create(3.0f);
	auto callfunc2 = CallFunc::create([this](){
		this->scheduleUpdate();
	});
	auto action = Sequence::create(delay,callfunc, delay2, callfunc2, nullptr);
	this->runAction(action);
}

Star* StarMatrix::getFirstSelectedStar()
{
	for (int j = 0; j < COL_NUM; j++)
	{
		for (int i = 0; i < ROW_NUM; i++)
		{
			if (_star[j][i] != nullptr && _star[j][i]->getStatus())
			{
				return _star[j][i];
			}
		}
	}
	return nullptr;
}

void StarMatrix::genSelectedStar()
{
	Star* star = getFirstSelectedStar();
	if (star == nullptr)
	{
		//CCLOG("selected star not found");
		selectedCount = 0;
		return;
	}
	selectedCount = 1;
	//CCLOG("first %d --- %d", star->getX(), star->getY());
	findOtherSelectedStar(star);
	
	if (selectedCount <= 1)
	{
		star->setStatus(false);
		selectedCount = 0;
		return;
	}

	deleteSelectedStar();
	updateLeftStarPosition();

}

void StarMatrix::findOtherSelectedStar(Star* original)
{
	if (original == nullptr)
	{
		return;
	}
	Star::StarColor color = original->getStarColor();
	int x = original->getX();
	int y = original->getY();
	//左
	if (x > 0)
	{
		findOneDirection(color, x - 1, y);
	}
	//右
	if (x < COL_NUM - 1)
	{
		findOneDirection(color, x + 1, y);
	}
	//上
	if (y < ROW_NUM - 1)
	{
		findOneDirection(color, x, y + 1);
	}
	//下
	if (y > 0)
	{
		findOneDirection(color, x, y - 1);
	}
}

void StarMatrix::findOneDirection(Star::StarColor color, int x, int y)
{
	Star* star = _star[x][y];
	if (star != nullptr && star->getStarColor() == color)
	{
		if (!star->getStatus())
		{
			CCLOG("match %d --- %d", x, y);
			selectedCount++;
			star->setStatus(true);
			findOtherSelectedStar(star);
		}
	}
}

void StarMatrix::deleteSelectedStar()
{
	for (int j = 0; j < ROW_NUM; j++)
	{
		for (int i = 0; i < COL_NUM; i++)
		{
			Star* star = _star[i][j];
			if (star != nullptr && star->getStatus())
			{
				this->removeChild(star);
				_star[i][j] = nullptr;
			}
		}
	}
}

void StarMatrix::updateLeftStarPosition()
{
	//x轴，每列单独检查
	for (int x = 0; x < COL_NUM; x++)
	{
		//对y轴上对每个进行判断，有空的，则其上面每个都+1
		bool columnExists = false;//检查此列是否已被删完
		for (int y = 0; y < ROW_NUM; y++)
		{
			if (_star[x][y] == nullptr)
			{
				for (int i = y + 1; i < ROW_NUM; i++)
				{
					if (_star[x][i] != nullptr)
					{
						_star[x][i]->setYOffset(_star[x][i]->getYOffset() + 1);
					}
				}
			}
			else
			{
				columnExists = true;
			}
		}

		//此列被删完之后，右侧的所有列都左移1格
		if (!columnExists)
		{
			for (int i = x + 1; i < COL_NUM; i++)
			{
				for (int j = 0; j < ROW_NUM; j++)
				{
					if (_star[i][j] != nullptr)
					{
						_star[i][j]->setXOffset(_star[i][j]->getXOffset() + 1);
					}
				}
			}
		}
	}

	//对有偏移的星星创建动作，同时更新数组
	int xoffset = 0;
	int yoffset = 0;
	for (int x = 0; x < COL_NUM; x++)
	{
		for (int y = 0; y < ROW_NUM; y++)
		{
			if (_star[x][y] != nullptr)
			{
				xoffset = _star[x][y]->getXOffset();
				yoffset = _star[x][y]->getYOffset();
				if (xoffset > 0 || yoffset > 0)
				{
					_star[x][y]->runAction(MoveTo::create(0.5f, _star[x][y]->getPosition() - Vec2(starSize.width * xoffset, starSize.height * yoffset)));
					_star[x][y]->setXOffset(0);
					_star[x][y]->setYOffset(0);

					_star[x][y]->setX(x - xoffset);
					_star[x][y]->setY(y - yoffset);
					_star[x - xoffset][y - yoffset] = _star[x][y];
					_star[x][y] = nullptr;
				}
			}
		}
	}
	
}

