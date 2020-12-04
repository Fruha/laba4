#pragma once
#include "Abstract/GameObject.h"
#include "MenuObject/MenuObject.h"


namespace game 
{
	class MainMenu : public GameObject 
	{
	private:
		MenuObject::Type isShowType;
		std::map <MenuObject::Type, MenuObject*> menu;
	protected:
	public:

		MainMenu(Point t_position);

		void show(MainScene* hw, MenuObject::Type type);
		void hide(MainScene* hw);

		MenuObject::Type getIsShowType() { return isShowType; };
		MenuObject* getMenu() { return menu[isShowType]; };

		void setIsShowType(MenuObject::Type t_isShowType) { isShowType = t_isShowType; };
	};
}