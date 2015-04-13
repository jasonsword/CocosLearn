#include "GameResource.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static GameAudio* _gameAudio = nullptr;

void GameResource::Load()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("star_packer.plist");
	GameAudio::getInstance()->PreLoad();
}


GameAudio* GameAudio::getInstance()
{
	if (!_gameAudio)
	{
		_gameAudio = new GameAudio();
	}
	return _gameAudio;
}

GameAudio::GameAudio()
{
}

GameAudio::~GameAudio()
{
	CC_SAFE_DELETE(_gameAudio);
}

void GameAudio::PreLoad()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/broken.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/fire.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/gameover.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/select.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/stageclear.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/win.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.3f);
}

void GameAudio::PlayWin()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/win.mp3", false);
}

void GameAudio::PlayClick()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/click.mp3", false);
}

void GameAudio::PlaySelect()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/select.mp3", false);
}

void GameAudio::PlayGameOver()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/gameover.mp3", false);
}

void GameAudio::PlayStageClear()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/stageclear.mp3", false);
}

void GameAudio::PlayBoom()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/broken.mp3", false);
}

void GameAudio::PlayFire()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/fire.mp3", false);
}
