#pragma once
#include "Abstract/GameObject.h"
#include "PartOfTower.h"
#include "Buildings/Lair/Enemy.h"
#include "Effect/Effect.h"
#include "Vector/MyVector.h"

namespace game
{
	class Tower : public GameObject
	{
	private:
		float lastFire = -1000;
		float range;
		float reload;
		DrawNode* circle = nullptr;
		bool areaIsShow = 0;
		float damage;
		int priceBuilt;
		int level = 1;
		MyVector<GameObject> partOfTower;
		Effect* effect = nullptr;
	protected:
	public:
		enum Type { CLASSIC_TOWER, MAGIC_TOWER };
		Type type;

		Tower(Point t_position, Point scale, MyVector<GameObject> t_partOfTower, Type t_type);
		void levelUp();
		bool pointInArea(MainScene* hw, Point point);
		void fire(MainScene* hw, Enemy* enemy, cocos2d::Color4B);
		void show(MainScene* hw, int show_level);
		void hide(MainScene* hw);
		void showArea(MainScene* hw, int show_level);
		void hideArea(MainScene* hw);
		Enemy* findCloseEnemy(MainScene* hw);
		Enemy* findCloseEnemyToCastle(MainScene* hw);

		int getPriceLevelUp();
		float getLastFire() { return lastFire; };
		float getRange() { return range; };
		float getReload() { return reload; };
		DrawNode* getCircle() { return circle; };
		bool getAreaIsShow() { return areaIsShow; };
		float getDamage() { return damage; };
		int getPriceBuilt() { return priceBuilt; };
		int getLevel() { return level; };
		MyVector<GameObject>& getPartOfTower() { return partOfTower; };
		Effect* getEffect() { return effect; };
	};
}