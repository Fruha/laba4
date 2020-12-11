#include "MainScene.h"
#include <assert.h>
#include "TestCastle.h" 
#include "Buildings/Castle/Castle.h"

namespace unitTest
{
	void TestCastle::testAll(game::MainScene* hw)
	{
		constructor1(hw);
		changeGold(hw);
		changeLife(hw);
	};
	void TestCastle::constructor1(game::MainScene* hw)
	{
		game::Castle castle = game::Castle("Isometric Tower defence pack/Sample.png", Point(100, 200), 10, 10);
		assert(castle.getGold() == 10);
		assert(castle.getLife() == 10);
	}
	void TestCastle::changeLife(game::MainScene* hw)
	{
		game::Castle castle = game::Castle("Isometric Tower defence pack/Sample.png", Point(100, 200), 10, 10);
		castle.changeLife(hw, -1);
		assert(castle.getLife() == 9);
	}
	void TestCastle::changeGold(game::MainScene* hw)
	{
		game::Castle castle = game::Castle("Isometric Tower defence pack/Sample.png", Point(100, 200), 10, 10);
		castle.changeGold(2);
		assert(castle.getGold() == 12);
	}
}