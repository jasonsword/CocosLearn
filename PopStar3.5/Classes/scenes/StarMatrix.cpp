#include "StarMatrix.h"
#include "GameScene.h"
#include "GameData.h"
#include "GameResource.h"

USING_NS_CC;

static cocos2d::Size starSize(0.0f, 0.0f);

bool StarMatrix::init()
{
	if (!Layer::init())
	{
		return false;
	}

	memset(_star, 0, sizeof(_star));
	_stageClearPlayed = false;
	selectedCount = 0;

	return true;
}

void StarMatrix::createMatrix()
{
	_initcomplete = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float width = visibleSize.width / COL_NUM;
	starSize = Size(width, width);

	Star::StarColor color = Star::generateColor();

	for (int y = 0; y < COL_NUM; y++)
	{
		for (int x = 0; x < ROW_NUM; x++)
		{
			auto star = Star::create();
			star->setXY(x, y);
			star->setContentSize(starSize);
			//这里添加下落的动作 直到终点
			Vec2 dest = Vec2((x + 0.5f) * width, (y + 0.5f) * width);
			star->setPosition(dest + Vec2(0, width * (y + 1)));
			star->runAction(MoveTo::create(0.25, dest));
			this->addChild(star);

			//一维是x 二维是y
			_star[x][y] = star;

			color = Star::generateColor();
		}
	}
}

void StarMatrix::createMatrixByHistory()
{
	_initcomplete = false;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	float width = visibleSize.width / COL_NUM;
	starSize = Size(width, width);

	for (int y = 0; y < COL_NUM; y++)
	{
		for (int x = 0; x < ROW_NUM; x++)
		{
			if (!GameData::getInstance()->getStar(x, y))
			{
				_star[x][y] = nullptr;
				continue;
			}
			auto star = Star::create(GameData::getInstance()->getStarColor(x, y));
			star->setStarColor(GameData::getInstance()->getStarColor(x, y));
			star->setXY(x, y);
			star->setContentSize(starSize);
			//这里添加下落的动作 直到终点
			Vec2 dest = Vec2((x + 0.5f) * width, (y + 0.5f) * width);
			star->setPosition(dest + Vec2(0, width * (y + 1)));
			star->runAction(MoveTo::create(0.25, dest));
			this->addChild(star);

			//一维是x 二维是y
			_star[x][y] = star;
		}
	}
}

void StarMatrix::onEnter()
{
	Layer::onEnter();

	//CCLOG("StarMatrix OnEnter");

	auto delay = DelayTime::create(0.5f);
	auto callfunc = CallFunc::create([this](){
		if (GameData::getInstance()->getPlayType() == GameData::PlayType::NEW)
		{
			this->createMatrix();
		}
		else if (GameData::getInstance()->getPlayType() == GameData::PlayType::LAST)
		{
			this->createMatrixByHistory();
		}
	});
	auto delay2 = DelayTime::create(3.0f);
	auto callfunc2 = CallFunc::create([this](){
		this->setInitState(true);
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
			star->setBoomDelay(original->getBoomDelay() + 0.1f);
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
	//先禁用定时检查，防止冲突
	//this->unschedule(schedule_selector(StarMatrix::updateCheck));
	float maxDelay = 0;// 最大延迟时间，防止和移动Action冲突
	for (int j = 0; j < ROW_NUM; j++)
	{
		for (int i = 0; i < COL_NUM; i++)
		{
			if (_star[i][j] != nullptr && _star[i][j]->getStatus())
			{
				maxDelay = maxDelay > _star[i][j]->getBoomDelay() ? maxDelay : _star[i][j]->getBoomDelay();
				_star[i][j]->playParticleEffect();
				_star[i][j] = nullptr;
			}
		}
	}


	//important 序列动作的回调函数需要使用CallFunc来封装lambda
	auto callfunc = CallFunc::create([this]{
		//更新剩余星星的位置
		this->updateLeftStarPosition();
		//播放Combo特效
		this->playComboEffect();
		//计算分数以及通关状态
		this->updateScore();
		//重新启用定时检查
		//this->schedule(schedule_selector(StarMatrix::updateCheck), 0.5f);
	});

	this->runAction(Sequence::create(DelayTime::create(maxDelay), callfunc, nullptr));
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
					_star[x][y]->setXYOffset(0, 0);
					_star[x][y]->setXY(x - xoffset, y - yoffset);
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

	if (GameData::getInstance()->getTongGuanState() && !_stageClearPlayed)
	{
		_stageClearPlayed = true;
		GameAudio::getInstance()->PlayStageClear();
	}
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

		this->unschedule(schedule_selector(StarMatrix::updateCheck));
		
		GameScene* scene = (GameScene *)this->getParent();
		scene->TongGuan();
	}
}

void StarMatrix::playComboEffect()
{
	if (selectedCount < 5)
	{
		return;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* comboSprite;
	if (selectedCount >= 10)
	{
		comboSprite = Sprite::create("images/combo_3.png");
	}
	else if (selectedCount >= 7)
	{
		comboSprite = Sprite::create("images/combo_2.png");
	}
	else
	{
		comboSprite = Sprite::create("images/combo_1.png");
	}
	if (comboSprite == nullptr)
	{
		CCLOG("combo resource not found!");
		return;
	}
	comboSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(comboSprite);

	Blink* blink = Blink::create(1.0f, 5);
	CallFunc* remove = CallFunc::create([=](){comboSprite->removeFromParent(); });
	Sequence* action = Sequence::create(blink, remove, nullptr);
	comboSprite->runAction(action);

	GameAudio::getInstance()->PlayFire();
}

void StarMatrix::saveGameData()
{
	if (!this->getInitState())
	{
		return;
	}

	for (int x = 0; x < COL_NUM; x++)
	{
		for (int y = 0; y < ROW_NUM; y++)
		{
			if (_star[x][y] != nullptr)
			{
				GameData::getInstance()->setStarInfo(x, y, true, _star[x][y]->getStarColor());
			}
			else
			{
				GameData::getInstance()->setStarInfo(x, y, false);
			}
		}
	}
}

