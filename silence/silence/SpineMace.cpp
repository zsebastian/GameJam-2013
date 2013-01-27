#include "SpineMace.h"
#include "Animation.h"
#include "ResourceManager.h"
#include "BulletSpineMace.h"

SpineMace::SpineMace(std::shared_ptr<Entity> player): 
	Weapon(player),
	mAttackSpeed(0.5)
{

	ResourceManager* r = ResourceManager::getInstance();

	r->loadTexture("spinemaceIdle", "bonemace_idle_png.png", sf::IntRect(0,0,256,256));
	r->loadTexture("spinemaceAttack", "paint_spinemace.png", sf::IntRect(0,0,256,256));

	mAnimIdle = new Animation("spinemaceIdle", 150, 1);
	mAnimAttack = new Animation("spinemaceAttack", 100, 10);
	mCurrentAnimation = mAnimIdle;
}

SpineMace::~SpineMace()
{
	delete mAnimIdle;
	delete mAnimAttack;
}

std::shared_ptr<Entity> SpineMace::shoot(){
	if(mAttackTimer.getElapsedTime().asSeconds() > mAttackSpeed){
		mCurrentAnimation = mAnimAttack;
		mAttackTimer.restart();
		return std::make_shared<BulletSpineMace>(getPlayer()->getPos(), getPlayer()); //<------- kolla upp dennna ?


	}else{
		mCurrentAnimation = mAnimIdle;
		return nullptr;
	}
}


sf::Sprite& SpineMace::getSprite(){
	int pX = getPlayer()->getXpos();
	int pY = getPlayer()->getYpos();

	mCurrentAnimation->getSprite().setPosition(
		pX - mCurrentAnimation->getSprite().getTextureRect().width / 2,
		pY - mCurrentAnimation->getSprite().getTextureRect().height / 2);
	mCurrentAnimation->update();
	return mCurrentAnimation->getSprite();
}

sf::FloatRect SpineMace::getColBox(){
	return mCurrentAnimation->getSprite().getGlobalBounds();
}