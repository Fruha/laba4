#include "MainScene.h"
#include <assert.h>
#include "TestTower.h" 
#include "Buildings/Tower/Tower.h"
#include "GameInfo.h"

namespace unitTest
{
	void TestTower::testAll(game::MainScene* hw)
	{
		constructor1(hw);
		testLevelUp(hw);
		//testPointInArea(hw);
	};
	void TestTower::constructor1(game::MainScene* hw)
	{
		game::Tower tower = game::Tower(Point(0, 0), Point(1, 1), {}, (game::Tower::Type)(0));
		assert(tower.getCircle() == nullptr);
		assert(tower.getEffect() == nullptr);
		assert(tower.getLabel() == nullptr);
		assert(tower.getIsShow() == 0);
		assert(tower.getLevel() == 1);
		assert(tower.getPartOfTower().size() == 0);
		assert(tower.getRange() == CLASSIC_TOWER_START_RANGE);
	}
	void TestTower::testLevelUp(game::MainScene* hw)
	{
		game::Tower tower = game::Tower(Point(0, 0), Point(1, 1), {}, (game::Tower::Type)(0));
		tower.levelUp();
		assert(tower.getLevel() == 2);
	}
	void TestTower::testPointInArea(game::MainScene* hw)
	{
		game::Tower tower = game::Tower(Point(0, 0), Point(1, 1), {}, (game::Tower::Type)(0));
		assert(tower.pointInArea(hw, Point(0, 0)) == 1);
		assert(tower.pointInArea(hw, Point(1000, 1000)) == 0);
	}
}