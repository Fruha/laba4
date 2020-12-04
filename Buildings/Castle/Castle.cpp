#include "Castle.h"
#include <string.h>

namespace game 
{
	Castle::Castle(std::string t_path, Point t_position, int t_life, int t_gold, Point t_scale) :
		GameObject(t_path, t_position, t_scale),
		life(t_life),
		gold(t_gold)
	{
		goldObject = new GameObject(
			"Isometric Tower defence pack/Sprites/Castle/Coin.png",
			Point(61, 835),
			std::to_string(gold),
			Point(140, 835),
			40,
			Point(0.1, 0.1),
			Point(1, 1)
		);

		lifeObject = new GameObject(
			"Isometric Tower defence pack/Sprites/Castle/heart.png",
			Point(61, 746),
			std::to_string(life),
			Point(140, 746),
			40,
			Point(0.03, 0.03),
			Point(1, 1)
		);
	};
	
	void Castle::changeLife(MainScene* hw, int change)
	{
		life += change;
		lifeObject->getLabel()->setString(std::to_string(life));
		if (life <= 0)
		{
			setIsAlive(0);
			GameObject gameOver = GameObject("Game Over", MainScene::windowSize / 2, 100);
			gameOver.getLabel()->enableOutline(Color4B::BLACK, 5);
			gameOver.show(hw, 10);
			Director::getInstance()->pause();
		}
	};

	void Castle::changeGold(int change)
	{
		if (change + gold < 0)
			throw ("Negative Gold");
		gold += change;
		goldObject->getLabel()->setString(std::to_string(gold));
	};
	
	void Castle::hide(MainScene* hw)
	{
		if (getIsShow() == 1)
		{
			((GameObject*)this)->hide(hw);
			if (getLifeObject() != nullptr)
			{
				getLifeObject()->hide(hw);
			}
			if (getGoldObject() != nullptr)
			{
				getGoldObject()->hide(hw);
			}
		}
	};
}