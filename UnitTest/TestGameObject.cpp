#include "MainScene.h"
//#include "TestsMain.h"
#include <assert.h>
#include "TestGameObject.h" 
#include "GameObject.h"

namespace unitTest
{
	void TestGameObject::testAll(game::MainScene* hw)
	{
		constructorDefault(hw);
		constructor1(hw);
		constructor2(hw);
		constructor3(hw);
		getersSeters(hw);
	};

	void TestGameObject::constructorDefault(game::MainScene* hw)
	{
		game::GameObject gameObject = game::GameObject();
		assert(gameObject.getIsShow() == 0);
		assert(gameObject.getLabel() == nullptr);
		assert(gameObject.getPath() == "");
		assert(gameObject.getPosition() == Point(0, 0));
		assert(gameObject.getSprite() == nullptr);
	}
	void TestGameObject::constructor1(game::MainScene* hw)
	{
		game::GameObject gameObject = game::GameObject(Point(100, 200), Point(0.5, 0.5));
		assert(gameObject.getIsShow() == 0);
		assert(gameObject.getLabel() == nullptr);
		assert(gameObject.getPath() == "");
		assert(gameObject.getPosition() == Point(100, 200));
		assert(gameObject.getSprite() == nullptr);
	}
	void TestGameObject::constructor2(game::MainScene* hw)
	{
		game::GameObject gameObject = game::GameObject("Isometric Tower defence pack/Sample.png" ,Point(100, 200), Point(0.5, 0.5));
		assert(gameObject.getIsShow() == 0);
		assert(gameObject.getPath() == "Isometric Tower defence pack/Sample.png");
		assert(gameObject.getPosition() == Point(100, 200));
		assert(gameObject.getSprite() != nullptr);
		assert(Point(gameObject.getSprite()->getScaleX(), gameObject.getSprite()->getScaleY()) == Point(0.5, 0.5));
	}
	void TestGameObject::constructor3(game::MainScene* hw)
	{
		game::GameObject gameObject = game::GameObject("Text", Point(100, 200), 12, Point(0.5, 0.5));
		assert(gameObject.getIsShow() == 0);
		assert(gameObject.getLabel() != nullptr);
		assert(gameObject.getLabel()->getString() == "Text");
		assert(gameObject.getPosition() == Point(100, 200));
	}
	void TestGameObject::getersSeters(game::MainScene* hw)
	{
		game::GameObject gameObject = game::GameObject();
		gameObject.setPosition(Point(100, 200));
		assert(gameObject.getPosition() == Point(100,200));
	}
}