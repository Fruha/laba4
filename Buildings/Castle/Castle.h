#pragma once
#include "Abstract/GameObject.h"

namespace game 
{
	class Castle : public GameObject 
	{
	private:
		bool isAlive = 1;
		GameObject* lifeObject = nullptr;
		int life;
		GameObject* goldObject = nullptr;
		int gold;
	protected:
	public:


		Castle(std::string t_path, Point t_position, int t_life, int t_gold, Point scale = { 1,1 });

		void changeLife(MainScene* hw, int change);
		void changeGold(int change);

		bool getIsAlive() { return isAlive; };
		GameObject* getLifeObject() { return lifeObject; };
		GameObject* getGoldObject() { return goldObject; };
		int getLife() { return life; };
		int getGold() { return gold; };

		void setIsAlive(bool t_isAlive) { isAlive = t_isAlive; };
		
		void hide(MainScene* hw);

	};
}