#pragma once
#include "Abstract/GameObject.h"
#include "Abstract/ClickableObject.h"
#include "Tiles/Tile.h"
#include "Vector/MyVector.h"

namespace game
{
	class MenuObject : public GameObject
	{
	private:
		MyVector<ClickableObject> menuSelections;
		MyVector<GameObject> objects;
		MyVector<GameObject> stats;
		MyVector<int> prices;
		MyVector<std::function<void(MainScene*, game::Tile*)>> action;
	protected:
	public:
		enum Type { MENU_SHOP_TOWERS, MENU_TOWER, MENU_SHOP_TRAPS, MENU_TRAP };
		Type type;



		MenuObject(MainScene* hw, Point t_position, Type t_type);

		void show(MainScene* hw);
		void hide(MainScene* hw);


		MyVector<ClickableObject>& getMenuSelections() { return menuSelections; };
		MyVector<GameObject>& getObjects() { return objects; };
		MyVector<GameObject>& getStats() { return stats; };
		MyVector<int>& getPrices() { return prices; };
		MyVector<std::function<void(MainScene*, game::Tile*)>>& getAction() { return action; };
	};
}