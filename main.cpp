#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/OpenGL.hpp>
//#include <SFML/RWINdow.hpp>

#include <GL/glu.h>
#include <GL/gl.h>
//#include <GL/glut.h>





//#include "Resource.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include <thread>
#include <sstream>
#include <deque>
#include <list>
#include <new>
#include <algorithm>
#include <typeinfo>
#include <tuple>

#include "Sprite3d.hpp"

//#include "EnemyIncluder.h"
#include "ENTITY.H"
#include "Enemy.h"
#include "Jerber-Enemy-1.h"
#include "Tower.h"
#include "Projectile.h"
#include "Box.h"
#include "FunEffect.h"
#include "NPC.h"
#include "GoalPoint.h"
#include "FileFun.h"
#include "PLAYER.h"
#include "ResourceManagment.h"
#include "BaseManager.h"
#include "LevelFun.h"
#include "RPGsegFun.h"



#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif



sf::ContextSettings settings(24, 8, 4 , 3, 1 , sf::ContextSettings::Debug, 0);
sf::RenderWindow RWINdow (sf::VideoMode(800, 600), L"Bruh", sf::Style::Close, settings);
sf::View viewer = RWINdow.getView();
sf::Event Event;

static MasterAccessor MasterAccess(&viewer, &RWINdow);



//float WindowInfluence::InfluencePercantage = 79.f;
sf::RenderWindow * BaseManager::WINdow = &RWINdow;
sf::View * BaseManager::viewerp = &viewer;

/** < declaring static variables for BaseManager */
std::vector<sf::Font> BaseManager::Fonts;
ResourceHolder<sf::Texture, Textures::ID> BaseManager::Res_Texture;









LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);


int WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
    BaseManager::WINdow = &RWINdow;
    FileFun F;
    StateStatusHandler StatusAccessor;
    StatusAccessor.TheLevels.push_back(new TowerDefenseTest);
    StatusAccessor.TheLevels.push_back(new OverWorld);
    StatusAccessor.ChangeState(StateValue::SV_SubCworld);
    /**Set icon for game application*/
    {
        WNDCLASSEX * wincl = new WNDCLASSEX;
        wincl -> hInstance = hThisInstance;
        wincl -> style = CS_SAVEBITS;
        wincl -> hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 128,128,0);
        //WindowHandlier.HWNDer = RWINdow.getSystemHandle();
    }
    /**Set Icon to game window */
    {
        sf::Image AppIcon;
        AppIcon.loadFromFile(ICONDIR);
        RWINdow.setIcon(150, 150, AppIcon.getPixelsPtr());
    }


    RWINdow.setFramerateLimit(60);
    RWINdow.setKeyRepeatEnabled(false);
    FullscreenBlackBox FullBox;
    sf::Clock Clocker;

    MasterAccess.CurrencyPtr = &Currency;
    MasterAccess.MouseDotptr = &MouseHandle.Dot;
    MasterAccess.Winptr = &RWINdow;
    MasterAccess.vPtr = &viewer;
    sf::RenderWindow * p = &RWINdow;

    sf::Clock clock;

    std::cout << "RWINdow " << &RWINdow << " RWINdow pointer " << BaseManager::WINdow;
    //sf::Clipboard c;
    //std::cout << static_cast<std::string>(c.getString());
    while (RWINdow.isOpen())
    {
        WindowSizer.x = RWINdow.getSize().x;
        WindowSizer.y = RWINdow.getSize().y;
        while (RWINdow.pollEvent(Event))
        {
            switch ((int)Event.type)
            {
                case sf::Event::Closed:
                    exit(0);
                //return 0;
                //case sf::Event::GainedFocus:
            }
	}

        RWINdow.setView(viewer);
        RWINdow.clear(sf::Color(0, 0 , 0 , 0));
        //MouseHandle.update();
        sf::RectangleShape S(sf::Vector2f(20, 20));
        S.setFillColor(sf::Color::Red);
        S.setPosition(300, 300);
        //RWINdow.draw(MouseHandle.Dot);
        StatusAccessor.Declare();
        StatusAccessor.Calculate();
        StatusAccessor.Draw();
        RWINdow.display();
    }
    return 360;
}















void MouseHandling::update()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(RWINdow);
    sf::Vector2f worldPos = RWINdow.mapPixelToCoords(pixelPos);
    Dot.setPosition(worldPos);
}


















