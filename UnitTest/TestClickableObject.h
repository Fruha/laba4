#pragma once
#include "MainScene.h"

namespace unitTest
{
	class MainScene;
	class TestClickableObject
	{
	public:
		TestClickableObject() {};
		void testAll(game::MainScene* hw);
		void constructorDefault(game::MainScene* hw);
		void constructor1(game::MainScene* hw);
		void constructor2(game::MainScene* hw);
		void PointInPoligon(game::MainScene* hw);
	};
}