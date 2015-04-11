#include "Star.h"
#include "StarMatrix.h"
#include "GameResource.h"
#include "GameData.h"

USING_NS_CC;

Star* Star::create()
{
	auto star = new Star();

	StarColor color = Star::generateColor();
	if (star && star->initWithColor(color))
	{
		return star;
	}
	CC_SAFE_DELETE(star);
	return nullptr;
}

Star* Star::create(StarColor color)
{
	auto star = new Star();
	if (star && star->initWithColor(color))
	{
		return star;
	}
	CC_SAFE_DELETE(star);
	return nullptr;
}

std::string Star::getImage(StarColor color)
{
	switch (color)
	{
	case Star::RED:
		return "star_r.png";
	case Star::GREEN:
		return "star_g.png";
	case Star::YELLOW:
		return "star_y.png";
	case Star::BLUE:
		return "star_b.png";
	case Star::PURPLE:
		return "star_p.png";
	default:
		return "star_y.png";
	}
}

Star::StarColor Star::generateColor()
{
	return (Star::StarColor)random<int>(Star::RED, Star::PURPLE);
}

bool Star::initWithColor(StarColor color)
{
	this->setStarColor(color);

	return this->init();
}

bool Star::init()
{
	if (GameData::getInstance()->getPlayType() == GameData::PlayType::NEW)
	{
		_starcolor = generateColor();
	}
	
	if (!Sprite::initWithSpriteFrameName(getImage(_starcolor)))
	{
		return false;
	}
	this->setStatus(false);
	this->setXOffset(0);
	this->setYOffset(0);
	this->setBoomDelay(0);

	//加入点击事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t, Event *e){
		if (this->getBoundingBox().containsPoint(t->getLocation()))
		{
			//CCLOG("click %d -- %d", this->getX(), this->getY());
			StarMatrix* matrix = (StarMatrix*)this->getParent();
			if (!this->getStatus())
			{
				this->setStatus(true);
				this->setBoomDelay(0);
				GameAudio::getInstance()->PlaySelect();
				matrix->consumeSelectedStar(this);
			}
			else
			{
				matrix->deleteSelectedStar();
			}
			
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Star::playParticleEffect()
{
	ParticleExplosion* effect = ParticleExplosion::create();
	//effect->setTexture(this->getTexture());
	effect->setTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName(getImage(_starcolor))->getTexture());
	//模式，重力模式，半径模式
	effect->setEmitterMode(ParticleSystem::Mode::RADIUS);
	//数量
 	effect->setTotalParticles(3000);
	//颜色
 	effect->setStartColor(getColor4F());
 	effect->setStartColorVar(Color4F(0, 0, 0, 1));
 	effect->setEndColor(getColor4F());
 	effect->setEndColorVar(Color4F(0, 0, 0, 1));
	//大小变化
 	effect->setStartSize(6.0f);
	effect->setStartSizeVar(10.0f);
	effect->setEndSize(25.0f);
	effect->setEndSizeVar(0);
	//旋转--测试是整体旋转
	effect->setRotatePerSecond(0);
	effect->setRotatePerSecond(60.0f);
	//生命周期
 	effect->setLife(0.3f);
	effect->setLifeVar(0.1f);
	//范围
	effect->setEndRadius(this->getContentSize().width * 2.0f);
	effect->setEndRadiusVar(this->getContentSize().width * 1.5f);
	
 	effect->setPosition(this->getPosition());
	effect->setAutoRemoveOnFinish(true);
	this->getParent()->addChild(effect, 10);

	auto callfunc = CallFunc::create([this]{
		//爆炸的同时移除自己
		GameAudio::getInstance()->PlayBoom();
		this->removeFromParent();
	});

	this->runAction(Sequence::create(DelayTime::create(_boomdelay), callfunc, nullptr));
}

cocos2d::Color4F Star::getColor4F()
{
	switch (_starcolor)
	{
	case Star::StarColor::PURPLE:
		return Color4F(0.74f, 0.30f, 0.99f, 1);
		//return Color4F(189,78,253,1);
	case Star::StarColor::BLUE:
		return Color4F(84 / 255.0f, 203 / 255.0f, 254 / 255.0f, 1);
	case Star::StarColor::RED:
		return Color4F(253 / 255.0f, 80 / 255.0f, 126 / 255.0f, 1);
	case Star::StarColor::YELLOW:
		return Color4F(253 / 255.0f, 234 / 255.0f, 84 / 255.0f, 1);
	case Star::StarColor::GREEN:
		return Color4F(132 / 255.0f, 226 / 255.0f, 111 / 255.0f, 1);
	default:
		break;
	}
	return Color4F(1, 1, 1, 0);
}


