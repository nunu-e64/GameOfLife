#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GridReader.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CSLoader* instance = CSLoader::getInstance();
    // Be very careful to do GridReader::getInstance, not GridReader::getInstance() which will crash
    instance->registReaderObject("GridReader", (ObjectFactory::Instance) GridReader::getInstance);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    
    auto leftPanel = rootNode->getChildByName("leftPanel");
    auto rightPanel = rootNode->getChildByName("rightPanel");
    
    grid = rightPanel->getChildByName<Grid*>("gridNode");
    
    auto balloon = leftPanel->getChildByName("balloon");
    generationCount = balloon->getChildByName<cocos2d::ui::Text*>("generationCount");
    populationCount = balloon->getChildByName<cocos2d::ui::Text*>("populationCount");
    
    cocos2d::ui::Button* playButton = leftPanel->getChildByName<cocos2d::ui::Button*>("btnPlay");
    cocos2d::ui::Button* pauseButton = leftPanel->getChildByName<cocos2d::ui::Button*>("btnPause");
    
    playButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::play, this));
    pauseButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::pause, this));

    addChild(rootNode);

    return true;
}

void HelloWorld::play(Ref* pSender, ui::Widget::TouchEventType type)
{
    this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::step), 0.5f);
}

void HelloWorld::pause(Ref* pSender, ui::Widget::TouchEventType type)
{
    this->unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::step));
}

void HelloWorld::step(float dt)
{
    grid->evolveStep();
    
    generationCount->setString(std::to_string(grid->getGenerationCount()));
    populationCount->setString(std::to_string(grid->getPopulationCount()));
}
