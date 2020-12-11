#include "MainScene.h"
#include <assert.h>
#include "TestClickableObject.h" 
#include "Abstract/ClickableObject.h"

namespace unitTest
{
	void TestClickableObject::testAll(game::MainScene* hw)
	{
		constructorDefault(hw);
		constructor1(hw);
		constructor2(hw);
		PointInPoligon(hw);
	};
	void TestClickableObject::constructorDefault(game::MainScene* hw)
	{
		game::ClickableObject object = game::ClickableObject();
		assert(object.getClickPoligon().size() == 0);
	}
	void TestClickableObject::constructor1(game::MainScene* hw)
	{
		game::ClickableObject object = game::ClickableObject("Isometric Tower defence pack/Sample.png", Point(1, 0), { Point(0,0), Point(0,1), Point(1,1), Point(1,0) }, Point(1, 1));
		assert(object.getIsShow() == 0);
		assert(object.getPosition() == Point(1, 0));
		assert(object.getIsShow() == 0);
		assert(object.getSprite() != nullptr);
	}

	void TestClickableObject::constructor2(game::MainScene* hw)
	{
		game::ClickableObject object = game::ClickableObject("Text", Point(1, 0), 10, { Point(0,0), Point(0,1), Point(1,1), Point(1,0) }, Point(1, 1));
		assert(object.getIsShow() == 0);
		assert(object.getPosition() == Point(1, 0));
		assert(object.getIsShow() == 0);
		assert(object.getLabel() != nullptr);
	}
	void TestClickableObject::PointInPoligon(game::MainScene* hw)
	{
		game::ClickableObject object = game::ClickableObject("Text", Point(1, 0), 10, { Point(0,0), Point(0,1), Point(1,1), Point(1,0) }, Point(1, 1));
		assert(object.PointInPolygon(Point(0.5, 0.5)) == 1);
		assert(object.PointInPolygon(Point(2, 2)) == 0);
	}
}