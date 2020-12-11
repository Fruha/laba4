#pragma once
#include "MainScene.h"

namespace unitTest
{
	class MainScene;
	class TestTower
	{
	public:
		TestTower() {};
		void testAll(game::MainScene* hw);
		void constructor1(game::MainScene* hw);
		void testLevelUp(game::MainScene* hw);
		void testPointInArea(game::MainScene* hw);
	};
}