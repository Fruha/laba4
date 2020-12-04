#pragma once
#include "Abstract/GameObject.h"
#include "Abstract/ClickableObject.h"
#include "Tiles/Tile.h"

namespace game
{
	class MenuObject : public GameObject
	{
	private:
		std::vector<ClickableObject> menuSelections;
		std::vector<GameObject> objects;
		std::vector<GameObject> stats;
		std::vector<int> prices;
		std::vector<std::function<void(MainScene*, game::Tile*)>> action;
	protected:
	public:
		enum Type { MENU_SHOP_TOWERS, MENU_TOWER, MENU_SHOP_TRAPS, MENU_TRAP };
		Type type;



		MenuObject(MainScene* hw, Point t_position, Type t_type);

		void show(MainScene* hw);
		void hide(MainScene* hw);


		std::vector<ClickableObject>& getMenuSelections() { return menuSelections; };
		std::vector<GameObject>& getObjects() { return objects; };
		std::vector<GameObject>& getStats() { return stats; };
		std::vector<int>& getPrices() { return prices; };
		std::vector<std::function<void(MainScene*, game::Tile*)>>& getAction() { return action; };
	};
}