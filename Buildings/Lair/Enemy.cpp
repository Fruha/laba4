#include "Enemy.h"
#include "Lair.h"
#include <algorithm>
#include "MainScene.h"
#include "Tiles/Field.h"
#include "Buildings/Castle/Castle.h"
#include "Effect/Effect.h"
#include "Abstract/GameObject.h"

namespace game 
{
	void Enemy::getDamage(MainScene* hw, float damage) 
	{
		if (lifeObject == nullptr)
		{
			return;
		}
		life = std::max(life - damage, 0.f);
		std::string temp = std::to_string(life);
		lifeObject->getLabel()->setString(temp.substr(0, temp.size() - 4));
		if (life <= 0.001)
		{
			Lair* lair = hw->getField()->getLair();
			lair->getEnemies().remove(this);
			this->hide(hw);
			Castle* castle = hw->getField()->getCastle();
			castle->changeGold(getGold());
		}
	}

	void Enemy::addEffect(MainScene* hw, Effect effect)
	{
		effects.push_back(new Effect(effect));
	}

	void Enemy::updateEffects(MainScene* hw, float dt)
	{
		std::list<Effect*>::iterator it;
		for (it = effects.begin(); it != effects.end() ; it++)
		{
			if ((*it)->type == (*it)->POISONING && life >= 0)
			{
				this->getDamage(hw, std::min(dt, (*it)->getTimeLeft()) * (*it)->getPower());
				if ((*it) == nullptr)
				{
					return;
				}
			}
			(*it)->setTimeLeft((*it)->getTimeLeft() - dt);
			if ((*it)->getTimeLeft() <= 0)
			{
				delete(*it);
				(*it) = nullptr;
			}
		}
		effects.remove(nullptr);
	}

	void Enemy::moveAllPath() 
	{
		if (getWay() == nullptr)
			throw("Error way");
		getWay()->setDuration(200);
		getSprite()->runAction(wayWithDamage->clone());
		lifeObject->getLabel()->runAction(way);
	}
	void Enemy::show(MainScene* hw, int showLevel)
	{
		GameObject* tempG = (GameObject*)this;
		tempG->show(hw, 1);
		std::string temp = std::to_string(life);
		lifeObject->getLabel()->setString(temp.substr(0, temp.size() - 4));
		lifeObject->show(hw, 1);
	}
	void Enemy::hide(MainScene* hw)
	{
		if (getIsShow() == 1) 
		{
			((GameObject*)this)->hide(hw);
			lifeObject->hide(hw);
			delete(lifeObject);
			lifeObject = nullptr;
			std::list<Effect*>::iterator it;
			for (it = effects.begin(); it != effects.end(); it++)
			{
				delete(*it);
				(*it) = nullptr;
			}
		}
	}

	int Enemy::getGold()
	{
		return ((int)std::pow(maxLife / 5, 3.f/4.f));
	}
}