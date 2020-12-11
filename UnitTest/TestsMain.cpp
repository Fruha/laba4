#include "MainScene.h"
#include "TestsMain.h"
#include "TestGameObject.h" 
#include "TestCastle.h"
#include "TestClickableObject.h"
#include "TestLair.h"
#include "TestTower.h"

namespace unitTest
{
	void TestsMain::testAll(game::MainScene* hw)
	{
		TestCastle testCastle;
		testCastle.testAll(hw);
		TestClickableObject testClickableObject;
		testClickableObject.testAll(hw);
		TestGameObject testGameObject; // = TestGameObject();
		testGameObject.testAll(hw);
		TestLair testLair;
		testLair.testAll(hw);
		TestTower testTower;
		testTower.testAll(hw);
	};
}