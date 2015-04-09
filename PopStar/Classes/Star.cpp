#include "Star.h"
#include "StarMatrix.h"

USING_NS_CC;

Star* Star::createStar()
{
	auto star = Star::create();
	StarColor color = generateColor();
	star->setXOffset(0);
	star->setYOffset(0);
	star->setStarColor(color);
	star->setStatus(false);
	star->initWithSpriteFrameName(getImage(color));
	return star;
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

bool Star::init()
{
	if (!Sprite::init())
	{
		return false;
	}

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


