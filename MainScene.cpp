#include <iostream>
#include "MainScene.h"
#include "Tiles/Field.h"
#include "MenuObject/MenuObject.h"
#include "MenuObject/MainMenu.h"
#include <numbers>
#include "ui/CocosGUI.h"
#include "GameInfo.h"
#include "UnitTest/TestsMain.h"

USING_NS_CC;

namespace game 
{
    const Point MainScene::windowSize = Point(WINDOW_LENGTH, WINDOW_WIDTH);

    Scene* MainScene::createScene()
    {
        return MainScene::create();
    }


    bool MainScene::init()
    {
        if (!Scene::init())
        {
            return false;
        }

        unitTest::TestsMain testsMain = unitTest::TestsMain();
        testsMain.testAll(this);

        mainMenu = new MainMenu(Point(1425, 400));
        this->scheduleUpdate();

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(MainScene::OnTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

        auto _mouseListener = EventListenerMouse::create();
        _mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);


        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        field_level1 = new Field(1, this);
        getField()->getTile(Point(7, 0))->buildCastle(this, 10, 10);
        getField()->getTile(Point(1, 9))->buildLair(this);
        field_level1->show();
        field_level1->getLair()->createWay(field_level1);

        addResumeButton();


        return true;
    }

    void MainScene::update(float dt)
    {
        Lair* lair = field_level1->getLair();
        if ((int)(currentTime / lair->getRate()) == (int)((currentTime + dt) / lair->getRate()) - 1)
        {
            lair->addEnemy(this, field_level1, ((int)std::pow(5 * (currentTime / 20 + 1), 1.3)));
        }
        currentTime += dt;
        towersUpdate(dt);
        std::list<Enemy*>tempEnemies(lair->getEnemies());
        std::list<Enemy*>::iterator it;

        for (it = tempEnemies.begin(); it != tempEnemies.end(); it++)
        {
            (*it)->updateEffects(this, dt);
        }
    }

    bool MainScene::OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event1)
    {
        fieldOnTouchBegan(touch, event1);
        mainMenuOnTouchBegan(touch, event1);
        return true;
    }

    void MainScene::onMouseMove(Event* event)
    {
        fieldOnMouseMove(event);
    }

    void MainScene::hide()
    {
        if (getMainMenu() != nullptr)
        {
            getMainMenu()->hide(this);
            delete(getMainMenu());
        }
        if (getMainMenu() != nullptr)
        {
            getField()->hide(this);
            delete(getField());
        }
    }

    void MainScene::addResumeButton()
    {
        resumeButton = ui::Button::create("Isometric Tower defence pack/Sprites/Menu/resumeButton.png");
        resumeButton->setPosition(Point(WINDOW_LENGTH - 100, 100));
        resumeButton->setScale(0.2, 0.2);
        resumeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (isPaused != 1)
                {
                    Director::getInstance()->pause();
                    isPaused = 1;
                }
                else
                {
                    Director::getInstance()->resume();
                    isPaused = 0;
                }
                break;
            default:
                break;
            }
            });

        this->addChild(resumeButton);
    };

    void MainScene::fieldOnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event1)
    {
        CCLOG("x = %f , y = %f", touch->getLocation().x, touch->getLocation().y);
        for (int i1 = 0; i1 < field_level1->getLen(); i1 += 1)
        {
            for (int i2 = 0; i2 < field_level1->getWidth(); i2 += 1)
            {
                if (field_level1->getTile(Point(i1, i2))->PointInPolygon(touch->getLocation()))
                {
                    if (field_level1->getSelectedTile()->state == Tile::CANT_BUILD_TOWER)
                    {
                        (field_level1->getSelectedTile()->getTower()->hideArea(this));
                    }
                    if (field_level1->getSelectedTileI1I2() != Point(i1, i2) && (field_level1->getTile(Point(i1, i2))->state != Tile::CANT_BUILD))
                    {
                        field_level1->getSelectedTile()->getSprite()->runAction(TintTo::create(0.f, 255.f, 255.f, 255.f));
                        if (field_level1->getSelectedTile()->getTrap() != nullptr)
                        {
                            field_level1->getSelectedTile()->getTrap()->show(this);
                        }
                        field_level1->getTile(Point(i1, i2))->getSprite()->runAction(TintTo::create(0.f, 0.f, 102.f, 255.f));
                        field_level1->setSelectedTileI1I2(Point(i1, i2));
                    }
                    if (field_level1->getTile(Point(i1, i2))->state != Tile::CANT_BUILD && mainMenu->getIsShow() == 1)
                    {
                        mainMenu->hide(field_level1->hw);
                    }
                    if (field_level1->getTile(Point(i1, i2))->state != Tile::CANT_BUILD && mainMenu->getIsShow() == 0)
                    {
                        mainMenu->show(field_level1->hw, (MenuObject::Type)(field_level1->getTile(Point(i1, i2))->state - 1));
                    }
                    if (field_level1->getTile(Point(i1, i2))->state == Tile::CANT_BUILD_TOWER)
                    {
                        (field_level1->getTile(Point(i1, i2))->getTower()->showArea(this, 1));
                    }

                }
            }
        }

    }

    void MainScene::mainMenuOnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event1)
    {
        if (mainMenu->getIsShow() == 1)
        {
            for (int i1 = 0; i1 < mainMenu->getMenu()->getMenuSelections().size(); i1 += 1)
            {
                if (mainMenu->getMenu()->getMenuSelections()[i1].PointInPolygon(touch->getLocation()))
                {
                    mainMenu->getMenu()->getAction()[i1](field_level1->hw, field_level1->getSelectedTile());
                    mainMenu->hide(field_level1->hw);
                    break;
                }
            }
        }
    };

    void MainScene::fieldOnMouseMove(Event* event)
    {
        EventMouse* e = (EventMouse*)event;
        //CCLOG("x = %f , y = %f", e->getCursorX(),900 + e->getCursorY());
        if (!getField()->getTile(getField()->getLast())->PointInPolygon(Point(e->getCursorX(), WINDOW_WIDTH + e->getCursorY()))
            && getField()->getSelectedTileI1I2() != field_level1->getLast())
        {
            if (getField()->getTile(getField()->getLast())->getTrap() == nullptr)
            {
                getField()->getTile(getField()->getLast())->getSprite()->runAction(TintTo::create(0.f, 255.f, 255.f, 255.f));
            }
            else
            {
                getField()->getTile(getField()->getLast())->getTrap()->show(this);
            }

        }
        for (int i1 = 0; i1 < getField()->getLen(); i1 += 1)
        {
            for (int i2 = 0; i2 < getField()->getWidth(); i2 += 1)
            {
                if (getField()->getTile(Point(i1, i2))->PointInPolygon(Point(e->getCursorX(), WINDOW_WIDTH + e->getCursorY())) && getField()->getSelectedTileI1I2() != Point(i1, i2))
                {
                    if (getField()->getTile(Point(i1, i2))->getIsShow() == 1)
                    {
                        if (getField()->getTile(Point(i1, i2))->state != Tile::CANT_BUILD)
                        {
                            getField()->getTile(Point(i1, i2))->getSprite()->runAction(TintTo::create(0.f, 0.f, 255.f, 0.f));
                        }
                        else
                        {
                            getField()->getTile(Point(i1, i2))->getSprite()->runAction(TintTo::create(0.f, 255.f, 51.f, 0.f));
                        }
                    }
                    getField()->setLast(Point(i1, i2));
                }
            }
        }
    }
    
    void MainScene::towersUpdate(float dt) 
    {
        Point tileLair = field_level1->getStartEnemy();
        for (int i1 = 0; i1 < field_level1->getLen(); i1 += 1)
        {
            for (int i2 = 0; i2 < field_level1->getWidth(); i2 += 1)
            {
                if (field_level1->getTile(Point(i1, i2))->getTower() != nullptr)
                {
                    Enemy* temp = field_level1->getTile(Point(i1, i2))->getTower()->findCloseEnemyToCastle(this);
                    field_level1->getTile(Point(i1, i2))->getTower()->fire(this, temp, Color4B::RED);
                }
                if (field_level1->getTile(Point(i1, i2))->getTrap() != nullptr)
                {
                    Enemy* temp = field_level1->getTile(Point(i1, i2))->getTrap()->findCloseEnemyToCastle(this);
                    field_level1->getTile(Point(i1, i2))->getTrap()->fire(this, temp);
                }
            }
        }

    }
    
    void MainScene::menuCloseCallback(Ref* pSender)
    {

        Director::getInstance()->end();
    }
}
