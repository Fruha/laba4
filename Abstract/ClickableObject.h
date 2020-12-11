#pragma once
#include <vector>
#include "cocos2d.h"
#include "GameObject.h"
#include "Vector/MyVector.h"

USING_NS_CC;

namespace game 
{
	class ClickableObject : public GameObject
	{
	private:
		MyVector<Point> ClickPoligon;
	public:
		ClickableObject() {};
		ClickableObject(std::string t_path, Point t_position, MyVector<Point> ClickPoligon_t, Point t_scale) :
			GameObject(t_path, t_position, t_scale),
			ClickPoligon(ClickPoligon_t)
		{};
		ClickableObject(std::string t_text, Point t_position, int font, MyVector<Point> ClickPoligon_t, Point t_scale) :
			GameObject(t_text, t_position, font, t_scale),
			ClickPoligon(ClickPoligon_t)
		{};
		bool PointInPolygon(Point point);

		MyVector<Point>& getClickPoligon() { return ClickPoligon; };
	};
}
