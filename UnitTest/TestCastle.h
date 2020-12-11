#pragma once
#include "MainScene.h"

namespace unitTest
{
	class MainScene;
	class TestCastle
	{
	public:
		TestCastle() {};
		void testAll(game::MainScene* hw);
		void constructor1(game::MainScene* hw);
		void changeGold(game::MainScene* hw);
		void changeLife(game::MainScene* hw);
	};
}