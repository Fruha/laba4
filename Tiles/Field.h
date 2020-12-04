#pragma once
#include <string>
#include "Tiles/Tile.h"
#include "MainScene.h"

namespace game {
	
	class Field
	{
	private:
		int len;
		int width;
		Point startEnemy;
		Point endEnemy;
		std::vector<std::vector<Tile*>> tiles;
		Point last;
		Point selectedTile;
		bool isSelected = 0;
		Point start;
		Point tile_size;
	public:

		MainScene* hw = nullptr;

		Field();
		Field(int level, MainScene* t_hw);
		
		bool checkPath();
		float mapDistance(Point p1, Point p2);
		void changeTile(MainScene* hw, Tile* tile, int x, int y);
		bool tileInField(Point t_tile);
		void show();

		Point getTileSize() { return tile_size; };
		int getLen() { return len; };
		int getWidth() { return width; };
		Point getLast() { return last; };
		Tile* getTile(Point t_tile) { return tiles[(int)t_tile.x][(int)t_tile.y]; };
		Point getStartEnemy() { return startEnemy; };
		Point getEndEnemy() { return endEnemy; };
		Castle* getCastle() { return tiles[(int)endEnemy.x][(int)endEnemy.y]->getCastle(); };
		Lair* getLair() { return tiles[(int)startEnemy.x][(int)startEnemy.y]->getLair(); };
		Tile* getSelectedTile() { return tiles[(int)selectedTile.x][(int)selectedTile.y]; };
		Point getSelectedTileI1I2() { return selectedTile; };

		void setLast(Point newLast) { last = newLast; };
		void setStartEnemy(Point t_startEnemy) { startEnemy = t_startEnemy; };
		void setEndEnemy(Point t_endEnemy) { endEnemy = t_endEnemy; };
		void setSelectedTileI1I2(Point newSelectedTile) { selectedTile = newSelectedTile; };

		Point findTile(Tile* t_tile);

		void hide(MainScene* hw);
		~Field()
		{
			CCLOG("1234");
		};
	};

}
