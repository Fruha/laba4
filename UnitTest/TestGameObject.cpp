#include "MainScene.h"
#include "TestAll.h"
#include "TestGameObject.h" 
#include "GameObject.h"

namespace unitTest
{
	void TestGameObject::testAll(game::MainScene* hw)
	{
		constructorDefault(hw);
		constructor1(hw);
		constructor2(hw);
	};

	void TestGameObject::constructorDefault(game::MainScene* hw)
	{
		game::GameObject gameObject = game::GameObject();
		if (gameObject.getIsShow() != 0)
			throw ("Error: getIsShow");
		if (gameObject.getLabel() != nullptr)
			throw ("Error: getLabel");
		if (gameObject.getPath() != "")
			throw ("Error: getPath");
		if (gameObject.getPosition() != Point(0, 0))
			throw ("Error: getPosition");
		if (gameObject.getSprite() != nullptr)
			throw ("Error: getSprite");
	}
	void TestGameObject::constructor1(game::MainScene* hw)
	{
		game::GameObject gameObject = game::GameObject(Point(100, 200), Point(0.5, 0.5));
		if (gameObject.getIsShow() != 0)
			throw ("Error: getIsShow");
		if (gameObject.getLabel() != nullptr)
			throw ("Error: getLabel");
		if (gameObject.getPath() != "")
			throw ("Error: getPath");
		if (gameObject.getPosition() != Point(100, 200))
			throw ("Error: getPosition");
		if (gameObject.getSprite() != nullptr)
			throw ("Error: getSprite");

	}
	void TestGameObject::constructor2(game::MainScene* hw)
	{
		game::GameObject gameObject = game::GameObject("Isometric Tower defence pack/Sample.png" ,Point(100, 200), Point(0.5, 0.5));
		if (gameObject.getIsShow() != 0)
			throw ("Error: getIsShow");
		if (gameObject.getLabel() != nullptr)
			throw ("Error: getLabel");
		if (gameObject.getPath() != "Isometric Tower defence pack/Sample.png")
			throw ("Error: getPath");
		if (gameObject.getPosition() != Point(100, 200))
			throw ("Error: getPosition");
		if (gameObject.getSprite() == nullptr)
			throw ("Error: getSprite");
		if (Point(gameObject.getSprite()->getScaleX(), gameObject.getSprite()->getScaleY()) != Point(0.5, 0.5))
			throw ("Error: getScale");

	}
}