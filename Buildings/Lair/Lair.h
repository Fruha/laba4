#pragma once
#include "Abstract/GameObject.h"
#include "Enemy.h"
#include "cocos2d.h"
#include "GameInfo.h"

namespace game
{
	class Field;
	class cocos2d::FiniteTimeAction;
	class Lair : public GameObject
	{
	private:
		void backWay(Point tile, Point previousStep, Field* field, std::vector < std::vector <int> >& pathLen, cocos2d::Vector<FiniteTimeAction*>& tempWay);
		void minWay(Point tile, Field* field, std::vector < std::vector <int> >& pathLen);
		void findWay(Point tile, Field* field, std::vector < std::vector <int> >& pathLen);
		FiniteTimeAction* createWayOneTile(Point start, Point end, Point tile, Field* field);
		float speed = 0.5;
		float height = 15;
		float rate = 4;
		Sequence* way = nullptr;
		Sequence* wayWithDamage = nullptr;
		std::list<Enemy*> enemies;
	protected:
	public:

		Lair(std::string t_path, Point t_position, Point t_scale = { 1,1 });
		void createWay(Field* field);
		void addEnemy(MainScene* hw, Field* field, int t_life);

		float getSpeed() { return speed; };
		float getHeight() { return height; };
		float getRate() { return rate; };
		Sequence* getWay() { return way; };
		Sequence* getWayWithDamage() { return wayWithDamage; };
		std::list<Enemy*>& getEnemies() { return enemies; };

		void setSpeed(float t_speed) { speed = t_speed; };
		void setHeight(float t_height) { height = t_height; };
		void setRate(float t_rate) { rate = t_rate; };

		void hide(MainScene* hw);
		
	};
}