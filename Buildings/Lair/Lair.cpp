#include "Lair.h"
#include "Tiles/Tile.h"
#include "Tiles/Field.h"
#include <algorithm>
#include "Abstract/ClickableObject.h"

namespace game
{
	Lair::Lair(std::string t_path, Point t_position, Point t_scale) :
		GameObject(t_path, t_position, t_scale)
	{};

	FiniteTimeAction* Lair::createWayOneTile(Point start, Point end, Point tile, Field* field)
	{
		auto dist = [](Point p1, Point p2)->double {return sqrt(((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y))); };
		Point startPoint = field->getTile(tile)->getClickPoligon()[0];
		Point tempVec1 = field->getTileSize() / 2;
		Point tempVec2 = Point(field->getTileSize().x, -field->getTileSize().y) / 2;
		
		if (
			(start == Point(0, 1) && end == Point(1, 0))
			|| (start == Point(1, 0) && end == Point(0, 1))
			|| (start == Point(0, 1) && end == Point(1, 2))
			|| (start == Point(1, 2) && end == Point(0, 1))
			|| (start == Point(1, 2) && end == Point(2, 1))
			|| (start == Point(2, 1) && end == Point(1, 2))
			|| (start == Point(2, 1) && end == Point(1, 0))
			|| (start == Point(1, 0) && end == Point(2, 1))
			)
		{
			ccBezierConfig bezier;
			Point p1, p2, p3;
			p1 = startPoint + start.x * tempVec2 + start.y * tempVec1;
			p2 = startPoint + tempVec2 + tempVec1;
			p3 = startPoint + end.x * tempVec2 + end.y * tempVec1;
			bezier.controlPoint_1 = (p1 + p2) / 2 + Point(0, height);
			bezier.controlPoint_2 = (p2 + p3) / 2 + Point(0, height);
			bezier.endPosition = p3 + Point(0, height);
			return (FiniteTimeAction*)BezierTo::create(3.1415/4/speed, bezier);
		}
		else
		{
			Point p1, p2;
			p1 = startPoint + start.x * tempVec2 + start.y * tempVec1 + Point(0, height);
			p2 = startPoint + end.x * tempVec2 + end.y * tempVec1 + Point(0, height);
			return (FiniteTimeAction*)MoveTo::create(dist(p1, p2)/dist(Point(0,0),tempVec1 * 2)/speed, p2);
		}
	}

	void Lair::createWay(Field* field) 
	{
		std::vector < std::vector <int> > pathLen(field->getLen(), std::vector <int>(field->getWidth()));

		for (int i1 = 0; i1 < field->getLen(); i1 += 1)
		{
			for (int i2 = 0; i2 < field->getWidth(); i2 += 1)
			{
				pathLen[i1][i2] = INT_MAX - 100;
			}
		}
		pathLen[(int)field->getEndEnemy().x][(int)field->getEndEnemy().y] = 0;

		findWay(field->getEndEnemy(), field, pathLen);
		if (pathLen[(int)field->getStartEnemy().x][(int)field->getStartEnemy().y] == INT_MAX - 100) 
		{
			throw("Error way");
		}
		cocos2d::Vector<FiniteTimeAction*> tempWay(pathLen[(int)field->getStartEnemy().x][(int)field->getStartEnemy().y] + 3);
		backWay(field->getStartEnemy(), Point(0, 0), field, pathLen, tempWay);
	}
	void Lair::backWay(Point tile, Point previousStep, Field* field, std::vector < std::vector <int> >& pathLen, cocos2d::Vector<FiniteTimeAction*>& tempWayDamage)
	{
		if (pathLen[(int)tile.x][(int)tile.y] == 0)
		{
			tempWayDamage.insert(tempWayDamage.capacity() - 3, createWayOneTile(Point(1, 1) - previousStep, Point(1, 1), tile, field));
			FiniteTimeAction* giveDamage = CallFunc::create([field]() {
				field->getCastle()->changeLife(field->hw, -1);
				field->getLair()->enemies.pop_front();
			    });
			tempWayDamage.insert(tempWayDamage.capacity() - 2, giveDamage);
			tempWayDamage.insert(tempWayDamage.capacity() - 1, RemoveSelf::create());
			cocos2d::Vector<FiniteTimeAction*> tempWay = tempWayDamage;
			tempWay.popBack();
			tempWay.popBack();
			tempWay.pushBack(RemoveSelf::create());
			//tempWay.back()->retain();
			way = Sequence::create(tempWay);
			way->retain();
			wayWithDamage = Sequence::create(tempWayDamage);
			wayWithDamage->retain();
			return;
		}
		std::vector<Point> tempPoints = { {0,1},{1,0},{0,-1},{-1,0} };
		for (int i1 = 0; i1 < tempPoints.size(); i1 += 1)
		{
			Point tile2;
			tile2 = tile + tempPoints[i1];
			if (field->tileInField(tile2))
			{
				if (pathLen[(int)tile2.x][(int)tile2.y] + 1 == pathLen[(int)tile.x][(int)tile.y])
				{
					tempWayDamage.insert(tempWayDamage.capacity() - pathLen[(int)tile.x][(int)tile.y] - 3, createWayOneTile(Point(1, 1) - previousStep, Point(1, 1) + tempPoints[i1], tile, field));
					tempWayDamage.back()->retain();
					backWay(tile2, tempPoints[i1], field, pathLen, tempWayDamage);
				}
			};
		}
	};

	void Lair::minWay(Point tile, Field* field, std::vector < std::vector <int> >& pathLen)
	{
		if (field->tileInField(tile))
		{
			if (field->getTile(tile)->getIsRoad() == 1)
			{
				std::vector<Point> tempPoints = { {0,1},{1,0},{0,-1},{-1,0} };
				for (int i1 = 0; i1 < tempPoints.size(); i1 += 1)
				{
					Point tile2;
					tile2 = tile + tempPoints[i1];
					if (field->tileInField(tile2) && field->getTile(tile2)->getIsRoad() == 1)
					{
						pathLen[(int)tile.x][(int)tile.y] = std::min(pathLen[(int)(tile2.x)][(int)(tile2.y)] + 1, pathLen[(int)tile.x][(int)tile.y]);
					}
				}
			}
		}


	};
	void Lair::findWay(Point tile, Field* field, std::vector < std::vector <int> >& pathLen)
	{
		if (field->tileInField(tile))
		{
			std::vector<Point> tempPoints = { {0,1},{1,0},{0,-1},{-1,0} };
			for (int i1 = 0; i1 < tempPoints.size(); i1 += 1)
			{
				Point tile2;
				tile2 = tile + tempPoints[i1];
				if (field->tileInField(tile2))
				{
					if ((pathLen[(int)tile.x][(int)tile.y] < pathLen[(int)tile2.x][(int)tile2.y] - 1) && (field->getTile(tile2)->getIsRoad() == 1))
					{
						minWay(tile2, field, pathLen);
						findWay(tile2, field, pathLen);
					}
				};
			}


		}
	};
	void Lair::addEnemy(MainScene* hw, Field* field, int t_life) {
		Enemy* enemy = new Enemy(
			"Isometric Tower defence pack/Sprites/UFO/red ufo.png",
			Point(field->getTile(field->getStartEnemy())->getSprite()->getPosition() + Point(0, 24.f) + Point(0, 15.f)),
			way,
			wayWithDamage,
			t_life,
			{ 0.15,0.15 }
		);
		enemy->show(hw, 1);
		enemy->moveAllPath();
		enemy->getLifeObject()->getLabel()->retain();
		enemy->getSprite()->retain();
		enemies.push_back(enemy);
	};
	void Lair::hide(MainScene* hw)
	{
		if (getIsShow() == 1)
		{
			((GameObject*)this)->hide(hw);
			if (way != nullptr)
			{
				way->release();
				way = nullptr;
			}
			if (wayWithDamage != nullptr)
			{
				wayWithDamage->release();
				wayWithDamage = nullptr;
			}
			std::list<Enemy*>::iterator it;
			for (it = enemies.begin(); it != enemies.end(); it++)
			{
				(*it)->hide(hw);
				delete(*it);
			}
		}

	}
}