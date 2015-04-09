#include "StarMatrix.h"
#include "GameScene.h"
#include "GameData.h"

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

			//一维是x 二维是y
			_star[i][j] = star;
		}
	}
}

void StarMatrix::onEnter()
{
	Layer::onEnter();

	//CCLOG("StarMatrix OnEnter");

	auto delay = DelayTime::create(0.5f);
	auto callfunc = CallFunc::create([this](){
		this->createMatrix();
	});
	auto delay2 = DelayTime::create(3.0f);
	auto callfunc2 = CallFunc::create([this](){
		this->schedule(schedule_selector(StarMatrix::updateCheck), 0.5f);
	});
	auto action = Sequence::create(delay,callfunc, delay2, callfunc2, nullptr);
	this->runAction(action);
}

void StarMatrix::consumeSelectedStar(Star* original)
{
	//先将所有的其它选中项清除
	for (int j = 0; j < ROW_NUM; j++)
	{
		for (int i = 0; i < COL_NUM; i++)
		{
			if (_star[i][j] != nullptr && 
				_star[i][j] != original && 
				_star[i][j]->getStatus())
			{
				_star[i][j]->setStatus(false);
			}
		}
	}

	selectedCount = 1;
	//CCLOG("first %d --- %d", star->getX(), star->getY());
	findOtherSelectedStar(original);
	
	if (selectedCount <= 1)
	{
		original->setStatus(false);
		selectedCount = 0;
		return;
	}
}

void StarMatrix::findOtherSelectedStar(Star* original)
{
	if (original == nullptr)
	{
		return;
	}
	int x = original->getX();
	int y = original->getY();
	//左
	if (x > 0)
	{
		findOneDirection(original, x - 1, y);
	}
	//右
	if (x < COL_NUM - 1)
	{
		findOneDirection(original, x + 1, y);
	}
	//上
	if (y < ROW_NUM - 1)
	{
		findOneDirection(original, x, y + 1);
	}
	//下
	if (y > 0)
	{
		findOneDirection(original, x, y - 1);
	}
}

void StarMatrix::findOneDirection(Star* original, int x, int y)
{
	Star* star = _star[x][y];
	if (star != nullptr && star->getStarColor() == original->getStarColor())
	{
		if (!star->getStatus())
		{
			//CCLOG("match %d --- %d", x, y);
			selectedCount++;
			star->setStatus(true);
			findOtherSelectedStar(star);
		}
	}
}

void StarMatrix::deleteSelectedStar()
{
	if (selectedCount <= 1)
	{
		return;
	}
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
	//更新剩余星星的位置
	updateLeftStarPosition();
	//计算分数以及通关状态
	updateScore();
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
						//+1代表要往下移1格
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

void StarMatrix::updateScore()
{
	//分数 = 数量 * 数量 * 5
	int score = selectedCount * selectedCount * 5;
	GameData::getInstance()->setScore(score);
}

bool StarMatrix::checkEnded()
{
	for (int x = 0; x < COL_NUM; x++)
	{
		for (int y = 0; y < ROW_NUM; y++)
		{
			if (_star[x][y] != nullptr)
			{
				if (checkOne(x, y))
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool StarMatrix::checkOne(int x, int y)
{
	//左
	if (x > 0)
	{
		if (_star[x - 1][y] != nullptr && _star[x - 1][y]->getStarColor() == _star[x][y]->getStarColor())
		{
			return true;
		}
	}
	//右
	if (x < COL_NUM - 1)
	{
		if (_star[x + 1][y] != nullptr && _star[x + 1][y]->getStarColor() == _star[x][y]->getStarColor())
		{
			return true;
		}
	}
	//下
	if (y > 0)
	{
		if (_star[x][y - 1] != nullptr && _star[x][y - 1]->getStarColor() == _star[x][y]->getStarColor())
		{
			return true;
		}
	}
	//上
	if (y < ROW_NUM - 1)
	{
		if (_star[x][y + 1] != nullptr && _star[x][y + 1]->getStarColor() == _star[x][y]->getStarColor())
		{
			return true;
		}
	}

	return false;
}

int StarMatrix::getLeftCount()
{
	int count = 0;
	for (int x = 0; x < COL_NUM; x++)
	{
		for (int y = 0; y < ROW_NUM; y++)
		{
			if (_star[x][y] != nullptr)
			{
				count++;
			}
		}
	}
	return count;
}

void StarMatrix::updateCheck(float delta /*= 0*/)
{
	if (checkEnded())
	{
		CCLOG("no more star can be cleared!");
		int leftCount = getLeftCount();
		//剩余分数 = 2000 - 剩余数量 * 剩余数量 * 5
		int leftScore = 2000 - leftCount * leftCount * 5;
		if (leftScore > 0)
		{
			GameData::getInstance()->setScore(leftScore);
		}
		GameScene* scene = (GameScene *)this->getParent();
		scene->TongGuan();
	}
}

