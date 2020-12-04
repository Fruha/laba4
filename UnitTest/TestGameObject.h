#pragma once
#include "MainScene.h"

namespace unitTest
{
	class MainScene;
	class TestGameObject
	{
	public:
		TestGameObject() {};
		void testAll(game::MainScene* hw);
		void constructorDefault(game::MainScene* hw);
		void constructor1(game::MainScene* hw);
		void constructor2(game::MainScene* hw);
		void constructor3(game::MainScene* hw);
		void constructor4(game::MainScene* hw);
		void getersSeters(game::MainScene* hw);
	};
}