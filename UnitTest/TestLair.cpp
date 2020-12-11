#include "MainScene.h"
#include <assert.h>
#include "TestLair.h" 
#include "Buildings/Lair/Lair.h"

namespace unitTest
{
	void TestLair::testAll(game::MainScene* hw)
	{
		constructor1(hw);
	};
	void TestLair::constructor1(game::MainScene* hw)
	{
		game::Lair lair = game::Lair("Isometric Tower defence pack/Sample.png", Point(100, 200), Point(0.5, 0.5));
		assert(lair.getEnemies().size() == 0);
		assert(lair.getHeight() != 0);
		assert(lair.getPosition() == Point(100, 200));
		assert(lair.getWay() == nullptr);
		assert(lair.getWayWithDamage() == nullptr);
	}
}