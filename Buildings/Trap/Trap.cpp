#include "Buildings/Trap/Trap.h"
#include "Tiles/Tile.h"
#include "cocos2d.h"
#include "MainScene.h"
#include "Tiles/Field.h"
#include "GameInfo.h"

namespace game 
{
	Trap::Trap(Point t_position, Type t_type, Tile* t_tile) :
		GameObject(t_position),
		type(t_type),
		tile(t_tile)
	{
		switch (type)
		{
		case POISON_TRAP:
			reload = POISON_TRAP_START_RELOAD;
			damage = POISON_TRAP_START_DAMAGE;
			priceBuilt = POISON_TRAP_PRICE_BUILD;
			effect = new Effect
			(
				POISON_TRAP_EFFECT_TYPE,
				POISON_TRAP_EFFECT_TIMELEFT,
				POISON_TRAP_EFFECT_POWER
			);
			break;
		}
	}
	void Trap::show(MainScene* hw)
	{
		setIsShow(1);
		tile->getSprite()->runAction(TintTo::create(0.f, 0.f, 100.f, 0.f));
	}

	void Trap::hide(MainScene* hw)
	{
		if (getIsShow() == 1)
		{
			tile->getSprite()->runAction(TintTo::create(0.f, 255.f, 255.f, 255.f));
			((GameObject*)this)->hide(hw);
			if (effect != nullptr) 
			{
				delete(effect);
				effect = nullptr;
			}
		}
	}

	int Trap::getPriceLevelUp()
	{
		return (priceBuilt * (level + 1));
	}

	void Trap::fire(MainScene* hw, Enemy* target)
	{
		if (target == nullptr)
		{
			return;
		}
		if (tile->PointInPolygon(target->getSprite()->getPosition() - Point(0, ENEMY_HEIGHT)) && (hw->currentTime > (lastFire + reload)))
		{
			lastFire = hw->currentTime;
			target->addEffect(hw, *(effect));
			target->getDamage(hw, damage);
		}
	};


	void Trap::levelUp()
	{
		damage += (damage / level);
		if (effect != nullptr)
		{

			effect->setPower(effect->getPower() + effect->getPower() / level);
			effect->setTimeLeft(effect->getTimeLeft() + 1);
		}
		level += 1;
	};

	Enemy* Trap::findCloseEnemyToCastle(MainScene* hw)
	{
		Point startEnemies = hw->getField()->getStartEnemy();
		std::list<Enemy*> enemies = hw->getField()->getLair()->getEnemies();

		Enemy* ansEnemy = nullptr;
		std::list<Enemy*>::iterator it;

		for (it = enemies.begin(); it != enemies.end(); it++) {
			if (tile->PointInPolygon((*it)->getSprite()->getPosition() - Point(0, ENEMY_HEIGHT)))
			{
				ansEnemy = (*it);
				break;
			}
		}
		return ansEnemy;
	}
}