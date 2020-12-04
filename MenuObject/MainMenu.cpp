#include "MenuObject/MainMenu.h"

namespace game 
{
	MainMenu::MainMenu(Point t_position) :
		GameObject(t_position)
	{};

	void MainMenu::show(MainScene* hw, MenuObject::Type type)
	{
		if (getIsShow() == 0) 
		{
			setIsShow(1);
			setIsShowType(type);
			menu[type] = new MenuObject(hw, getPosition(), type);
			menu[type]->show(hw);
		}
	};

	void MainMenu::hide(MainScene* hw)
	{
		if (getIsShow() == 1)
		{
			((GameObject*)this)->hide(hw);
			if (getMenu() != nullptr)
			{
				getMenu()->hide(hw);
				delete(getMenu());
				menu[getIsShowType()] = nullptr;
			}
		}
	};
}