#include "MainScene.h"
#include "TestAll.h"
#include "TestGameObject.h" 

namespace unitTest
{
	void TestAll::testAll(game::MainScene* hw)
	{
		TestGameObject testGameObject = TestGameObject();
		testGameObject.testAll(hw);
	};
}