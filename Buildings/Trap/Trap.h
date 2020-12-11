#pragma once
#include "Abstract/GameObject.h"
#include "Buildings/Lair/Enemy.h"
#include "Effect/Effect.h"
#include "cocos2d.h"

namespace game
{
	class Tile;
	class Trap : public GameObject
	{
	private:
		float lastFire = -1000;
		float reload;
		Tile* tile = nullptr;
		float damage;
		int priceBuilt;
		int level = 1;
		Effect* effect = nullptr;
	protected:
	public:
		enum Type { POISON_TRAP };
		Type type;

		Trap(Point t_position, Type t_type, Tile* t_tile);

		void levelUp();
		int getPriceLevelUp();
		void fire(MainScene* hw, Enemy* enemy);
		void show(MainScene* hw);
		void hide(MainScene* hw);
		Enemy* findCloseEnemyToCastle(MainScene* hw);

		float getLastFire() { return lastFire; };
		float getReload() { return reload; };
		float getDamage() { return damage; };
		int getPriceBuilt() { return priceBuilt; };
		int getLevel() { return level; };
		Effect* getEffect() { return effect; };
		Tile* getTile() { return tile; };
	};
}