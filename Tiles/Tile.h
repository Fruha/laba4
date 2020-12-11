#pragma once
#include <string>
#include "Abstract/ClickableObject.h"
#include "Abstract/GameObject.h"
#include "cocos2d.h"
#include "Buildings/Tower/Tower.h"
#include "Buildings/Castle/Castle.h"
#include "Buildings/Lair/Lair.h"
#include "Buildings/Trap/Trap.h"
#include "Vector/MyVector.h"

namespace game 
{
	class Tile : public ClickableObject
	{
	private:		
		bool isRoad = 0;
		Tower* tower = nullptr;
		Trap* trap = nullptr;
		Castle* castle = nullptr;
		Lair* lair = nullptr;
	protected:
	public:
		enum State { CANT_BUILD, CAN_BUILD_TOWER, CANT_BUILD_TOWER, CAN_BUILD_TRAP, CANT_BUILD_TRAP};
		State state = CANT_BUILD;



		Tile() :
			ClickableObject()
		{};
		Tile(std::string t_path, Point t_position, MyVector<Point> ClickPoligon_t, Point t_scale) :
			ClickableObject(t_path, t_position, ClickPoligon_t, t_scale)
		{};

		void buildTower(MainScene* hw, Tower::Type type);
		void buildTrap(MainScene* hw, Trap::Type type);
		void buildCastle(MainScene* hw, int life, int gold);
		void buildLair(MainScene* hw);
		void destroyBuilding(MainScene* hw);

		Tower* getTower() { return tower; };
		Trap* getTrap() { return trap; };
		Castle* getCastle() { return castle; };
		Lair* getLair() { return lair; };
		bool getIsRoad() { return isRoad; };

		void setTower(Tower* t_tower) { tower = t_tower; };
		void setTrap(Trap* t_trap) { trap = t_trap; };
		void setCastle(Castle* t_castle) { castle = t_castle; };
		void setLair(Lair* t_lair) { lair = t_lair; };
		void setIsRoad(bool t_isRoad) { isRoad = t_isRoad; };

		void hide(MainScene* hw);
	};
}
