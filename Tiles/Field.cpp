#include <string>
#include "Tiles/Field.h"

namespace game {

	Field::Field() {

	}
	Field::Field(int level, MainScene* t_hw)
	{
		hw = t_hw;
		if (level == 1) 
		{
			start = Point(100.f, 400.f);
			tile_size = Point(59.f, 34.f);
			std::vector<std::vector<std::string>> level1 =
			{{"Enviroument tiles/ground.png", "Road tiles/road(13).png"     , "Enviroument tiles/ground.png", "River tiles/river(9).png"    , "River tiles/river(10).png"   , "River tiles/river(10).png"   , "River tiles/river(8).png"             , "Enviroument tiles/ground.png"         , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Road tiles/road(2).png"      , "Road tiles/roads on water/road(4).png", "Road tiles/road(14).png"              , "Road tiles/road(4).png"      , "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "River tiles/river(11).png"            , "Enviroument tiles/ground.png"         , "Road tiles/road(15).png"     , "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Road tiles/road(3).png"      , "Road tiles/road(14).png"     , "Road tiles/road(14).png"     , "Road tiles/road(14).png"     , "Road tiles/road(5).png"      , "River tiles/river(9).png"             , "River tiles/river(8).png"             , "Road tiles/road(15).png"     , "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"         , "River tiles/river(11).png"            , "Road tiles/road(15).png"     , "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Road tiles/road(2).png"      , "Road tiles/road(14).png"     , "Road tiles/road(14).png"     , "Road tiles/road(14).png"     , "Road tiles/road(14).png"              , "Road tiles/roads on water/road(4).png", "Road tiles/road(5).png"      , "Enviroument tiles/ground.png"},
			 {"River tiles/river(8).png"    , "Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"         , "River tiles/river(9).png"             , "River tiles/river(10).png"   , "River tiles/river(8).png"},
			 {"River tiles/river(11).png"   , "Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "Enviroument tiles/ground.png", "Road tiles/road(2).png"      , "Road tiles/road(14).png"     , "Road tiles/road(14).png"              , "Road tiles/road(4).png"               , "Enviroument tiles/ground.png", "River tiles/river(9).png"},
			 {"River tiles/river(11).png"   , "Enviroument tiles/ground.png", "Road tiles/road(3).png"      , "Road tiles/road(14).png"     , "Road tiles/road(5).png"      , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"         , "Road tiles/road(15).png"              , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"},
			 {"River tiles/river(9).png"    , "River tiles/river(8).png"    , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"         , "Road tiles/road(11).png"              , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"}};
			len = level1.size();
			width = level1[0].size();
			tiles.resize(level1.size());
			for (int i1 = 0; i1 < len; i1 += 1)
            {
				tiles[i1].resize(level1[0].size());
                for (int i2 = 0; i2 < width; i2 += 1)
                {
					Tile* temp = new Tile("Isometric Tower defence pack/Sprites/" + level1[len - i2 - 1][i1],
						Point(start.x + (i1 + i2) * tile_size.x, start.y + tile_size.y * (i2 - i1)), 
						{{start.x + tile_size.x * (i1 + i2 - 1),start.y + 24.f + tile_size.y * (i2 - i1)},
						 {start.x + tile_size.x * (i1 + i2)    ,start.y + 24.f + tile_size.y * (i2 - i1 + 1)},
						 {start.x + tile_size.x * (i1 + i2 + 1),start.y + 24.f + tile_size.y * (i2 - i1)},
						 {start.x + tile_size.x * (i1 + i2)    ,start.y + 24.f + tile_size.y * (i2 - i1 - 1)}},
						{ 0.1,0.1 }
						);
					if (temp->getPath().find("road") != -1) 
					{
						temp->setIsRoad(1);
					}
					if (temp->getPath() == "Isometric Tower defence pack/Sprites/Enviroument tiles/ground.png") 
					{
						temp->state = Tile::CAN_BUILD_TOWER;
					}
					if (temp->getPath().find("Road tiles/road") != -1 && temp->getPath().find("water") == -1)
					{
						temp->state = Tile::CAN_BUILD_TRAP;
					}
					for (int i = 10; i < 14; i += 1) 
					{
						if (temp->getPath() == ("Isometric Tower defence pack/Sprites/Road tiles/road(" + std::to_string(i) + ").png")) 
						{
							temp->state = Tile::CANT_BUILD;
						}
					}
					changeTile(hw, temp, i1, i2);
                }
            }
		}
	}
	void Field::show()
	{
		for (int i1 = 0; i1 < len; i1 += 1)
		{
			for (int i2 = 0; i2 < width; i2 += 1)
			{
				if (tiles[i1][i2]->getSprite() != nullptr) 
				{
					tiles[i1][i2]->show(hw, -i2);
				}
			}
		}
	}

	void Field::changeTile(MainScene* hw, Tile* tile, int x, int y)
	{
		if (x < 0 || x >= len)
		{
			throw("Invalid x");
		}
		if (y < 0 || y >= width)
		{
			throw("Invalid y");
		}
		if (tiles[x][y] != nullptr)
		{
			tiles[x][y]->hide(hw);
			delete(tiles[x][y]);
			tiles[x][y] = nullptr;
		}
		tiles[x][y] = tile;
	}
	bool Field::tileInField (Point t_tile)
	{
		return ((int)t_tile.x >= 0 && (int)t_tile.x < len && (int)t_tile.y >= 0 && (int)t_tile.y < width);
	};
	float Field::mapDistance(Point p1, Point p2)
	{
		Point temp = p2 - p1;
		return (Point(temp.x, temp.y / Field::tile_size.y * Field::tile_size.x).length());
	}
	Point Field::findTile(Tile* t_tile) 
	{
		for (int i1 = 0; i1 < len; i1 += 1)
		{
			for (int i2 = 0; i2 < width; i2 += 1)
			{
				if (t_tile == tiles[i1][i2])
				{
					return Point(i1, i2);
				}
			}
		}
	}
	bool Field::checkPath() 
	{
		if (getCastle() == nullptr || getLair() == nullptr)
		{
			return 0;
		}
		Lair* lair = getLair();
		try 
		{
			lair->createWay(this);
		}
		catch (const char*)
		{
			return 0;
		}
		return 1;
	}
	void Field::hide(MainScene* hw)
	{
		for (int i1 = 0; i1 < this->getLen(); i1 += 1)
		{
			for (int i2 = 0; i2 < this->getWidth(); i2 += 1) 
			{
				tiles[i1][i2]->hide(hw);
				delete(tiles[i1][i2]);
				tiles[i1][i2] = nullptr;
			}
		}
	}
}