#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos/cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

namespace game {
    class Field;
    class MenuObject;
    class MainMenu;
    class MainScene : public cocos2d::Scene
    {
    private:
        bool isPaused = 0;
        MainMenu* mainMenu = nullptr;
        Field* field_level1 = nullptr;
        cocos2d::ui::Button* resumeButton = nullptr;
    public:
        static const Point windowSize;
        float currentTime = 0;

        static cocos2d::Scene* createScene();

        virtual bool init();
        void menuCloseCallback(cocos2d::Ref* pSender);

        bool OnTouchBegan(Touch* touch, Event* event1);
        void onMouseMove(Event* event);
        void update(float dt);

        Field* getField() { return field_level1; };
        MainMenu* getMainMenu() { return mainMenu; };
        void addResumeButton();
        CREATE_FUNC(MainScene);

        void fieldOnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event1);
        void mainMenuOnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event1);

        void fieldOnMouseMove(Event* event);

        void towersUpdate(float dt);

        void hide();

        ~MainScene()
        {
            hide();
        };
    };

}

#endif // __MAIN_SCENE_H__
