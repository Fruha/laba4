#include "Tower.h"
#include "Tiles/Field.h"
#include "GameInfo.h"
#include "Vector/MyVector.h"

namespace game 
{
	Tower::Tower(Point t_position, Point scale, MyVector<GameObject> t_partOfTower, Type t_type) :
		GameObject("", t_position, scale),
		partOfTower(t_partOfTower),
		type(t_type)
	{
		switch (type)
		{
		case Tower::CLASSIC_TOWER:
			priceBuilt = CLASSIC_TOWER_PRICE_BUILD;
			range = CLASSIC_TOWER_START_RANGE;
			reload = CLASSIC_TOWER_START_RELOAD;
			damage = CLASSIC_TOWER_START_DAMAGE;
			break;
		case Tower::MAGIC_TOWER:
			priceBuilt = MAGIC_TOWER_PRICE_BUILD;
			range = MAGIC_TOWER_START_RANGE;
			reload = MAGIC_TOWER_START_RELOAD;
			damage = MAGIC_TOWER_START_DAMAGE;
			effect = new Effect
			(
				MAGIC_TOWER_EFFECT_TYPE,
				MAGIC_TOWER_EFFECT_TIMELEFT,
				MAGIC_TOWER_EFFECT_POWER
			);
			break;
		}
	}

	void Tower::show(MainScene* hw, int show_level)
	{
		setIsShow(1);
		for (int i = 0; i < partOfTower.size(); i += 1)
		{
			partOfTower[i].show(hw, show_level);
		}
	}

	void Tower::hide(MainScene* hw)
	{
		if (getIsShow() == 1)
		{
			hideArea(hw);
			for (int i = 0; i < partOfTower.size(); i += 1)
			{
				partOfTower[i].hide(hw);
			}
			if (circle != nullptr)
			{
				delete(circle);
				circle = nullptr;
			}
			if (effect != nullptr)
			{
				delete(effect);
				effect = nullptr;
			}
		}
	}

	bool Tower::pointInArea(MainScene* hw, Point point)
	{
		Point center = partOfTower.front().getSprite()->getPosition() - Point(0, 15.f);
		Point temp = point - center;
		return (Point(temp.x, temp.y * hw->getField()->getTileSize().x / hw->getField()->getTileSize().y).length() < hw->getField()->getTileSize().x * sqrt(2) * range);
	};

	int Tower::getPriceLevelUp()
	{
		return (priceBuilt * (level + 1));
	}

	void Tower::fire(MainScene* hw, Enemy* target, cocos2d::Color4B) 
	{
		if (target == nullptr)
		{
			return;
		}
		if (pointInArea(hw, target->getSprite()->getPosition()) && (hw->currentTime > (lastFire + reload)))
		{
			lastFire = hw->currentTime;
			if (effect != nullptr)
			{
				target->addEffect(hw, (*effect));
			}
			target->getDamage(hw, damage);
			auto line = DrawNode::create();
			line->drawSegment(partOfTower.back().getSprite()->getPosition(), target->getSprite()->getPosition(), 2.f, Color4F::RED);
			hw->addChild(line, 2);
			auto sec = Sequence::create(FadeOut::create(1.0f), RemoveSelf::create(), nullptr);
			line->runAction(sec);
		}
	};

	void Tower::showArea(MainScene* hw, int show_level) 
	{
		if (areaIsShow == 0) 
		{
			circle = DrawNode::create();
			circle->drawCircle(
				partOfTower.front().getSprite()->getPosition() - Point(0, 15.f),
				hw->getField()->getTileSize().x * sqrt(2) * range,
//				Point(Field::tile_size.x/sqrt(2), Field::tile_size.x/sqrt(2)* Field::tile_size.y / Field::tile_size.x).length() * range,
				0, 
				100, 
				false, 
				1, 
				hw->getField()->getTileSize().y / hw->getField()->getTileSize().x,
				Color4F::RED);
			hw->addChild(circle);
			areaIsShow = 1;
		}
	}

	void Tower::hideArea(MainScene* hw)
	{
		if (areaIsShow == 1)
		{
			hw->removeChild(circle);
			circle = nullptr;
			areaIsShow = 0;
		}
	};

	void Tower::levelUp() 
	{
		damage += (damage / level);
		range += 0.5;
		if (effect != nullptr)
		{
			effect->setPower(effect->getPower() + effect->getPower() / level);
			effect->setTimeLeft(effect->getTimeLeft() + 1);
		}
		level += 1;
	};

	Enemy* Tower::findCloseEnemy(MainScene* hw)
	{
		Point startEnemies = hw->getField()->getStartEnemy();
		std::list<Enemy*> enemies = hw->getField()->getLair()->getEnemies();
		
		Enemy* ansEnemy = nullptr;
		float ans = INT_MAX;
		float t_float;
		std::list<Enemy*>::iterator it;

		for (it = enemies.begin(); it != enemies.end(); it++) {
			if ((t_float = hw->getField()->mapDistance(partOfTower.front().getSprite()->getPosition(), (*it)->getSprite()->getPosition())) < ans)
			{
				ans = t_float;
				ansEnemy = (*it);
			}
		}
		return ansEnemy;
	}
	Enemy* Tower::findCloseEnemyToCastle(MainScene* hw)
	{
		Point startEnemies = hw->getField()->getStartEnemy();
		std::list<Enemy*> enemies = hw->getField()->getLair()->getEnemies();

		Enemy* ansEnemy = nullptr;
		std::list<Enemy*>::iterator it;

		for (it = enemies.begin(); it != enemies.end(); it++) {
			if (this->pointInArea(hw, (*it)->getSprite()->getPosition()))
			{
				ansEnemy = (*it);
				break;
			}
		}
		return ansEnemy;

	}
}
