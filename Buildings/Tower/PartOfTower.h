#pragma once
#include "Abstract/GameObject.h"

namespace game 
{
	class PartOfTower : public GameObject 
	{
	private:
	protected:
	public:
		PartOfTower(std::string t_path, Point t_position, Point scale = { 1,1 }) :
			GameObject(t_path, t_position, scale)
		{}
	};
}