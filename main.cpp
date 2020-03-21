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

#define PI 3.14
#define SIZEOFWINDOWED 800
//#define P P_P ->



//sf::WindowHandle

sf::Mouse Mouser;
sf::ContextSettings settings(24, 8, 4 , 3, 1 , sf::ContextSettings::Debug, 0);
sf::RenderWindow RWINdow (sf::VideoMode(800, 600), L"The Restart", sf::Style::Close, settings);
sf::View viewer = RWINdow.getView();
sf::Event Event;
int MouseX;
int MouseY;
sf::Vector2f WindowSizer;
int Counter;
int Counter2;
static MasterAccessor MasterAccess(&viewer, &RWINdow);



//float WindowInfluence::InfluencePercantage = 79.f;
sf::RenderWindow * BaseManager::WINdow = &RWINdow;
sf::View * BaseManager::viewerp = &viewer;
MasterAccessor * Entity::Mptr = &MasterAccess;
MasterAccessor * TextBox::Mptr = &MasterAccess;
MasterAccessor * Ability::Masterptr = &MasterAccess;
WindowInfluence Entity::WInflu;
WindowInfluence * WindowUpdater::Winptr = &Entity::WInflu;


/** < declaring static varibles for BaseManager */
std::vector<sf::Font> BaseManager::Fonts;
ResourceHolder<sf::Texture, Textures::ID> BaseManager::Res_Texture;
///A global ptr to TextBoxes for all NPC's to use
TextBox * NPC::TBptr = NULL;










bool TowerSelected = false;
namespace MouseSpace
{
    bool ExistingTowerSelect = false;
    bool MouseReleased = true;
    bool Fast = true;
}

namespace TowerDefenseUI
{
    enum BoxID
    {
        TowerUI_Background = 0,
        PointDisplay,
        //TowerUpgradeButton,
        //TowerSellButton,
        SpeedUpButton,
        SettingsButton,

    };
}


int Currency = 1000;
int unsigned Round = 0;
int unsigned EnemyRound = Round;







/* --------------------------------------------------------- */


/*
GoalPoint Goaler;
std::vector<GoalPoint> GoalArray;
std::vector <float> X;
std::vector <float> Y;
*/
std::list <Tower> TowerArray;
std::list <Projectile> ProjectileArray;
std::list<Jerber> JerberArray;




/* --------------------------------------------------------- */

//ResourceHolder<sf::Texture, Textures::ID> & R_Texture = BaseManager::Res_Texture;

/** \brief This struct handles various things associated with the mouse*/
struct MouseHandling
{
    MouseHandling() {Dot.setSize(sf::Vector2f(10,10)), Dot.setFillColor(sf::Color::Blue), BoughtIndex = -1;}

    void update(); //{Dot.setPosition(Mouser.getPosition(RWINdow).x ,Mouser.getPosition(RWINdow).y);}
    Tower * SelectedTower;
    bool PlacingMode = false;
    int BoughtIndex;
    sf::RectangleShape Dot;
}MouseHandle;
/*
\brief This struct handles various things associated with the Window*/
/*
class WindowHanlding
{
    public:
    WindowHanlding(): Fullscreen(false), CurrentWindowName("The Restart") {}
    void Update();
    void FixWindowStatus();
    unsigned char StatusOfWindow;
    std::string CurrentWindowName;
    bool Fullscreen;

}WindowHandlier;
*/
/** \brief This Union handles various things associated with Fonts*/
union FontHandling
{
    /** \brief Pairs a Font to a directory
     * \param The Font
     * \param The directory
     * \return Returns nothing but game fails if unable to obtain font
     */
    void Pair(sf::Font & , std::string);
}FontHandle;






class EnemyQueue
{
public:
    EnemyQueue()
    {
        Spawned = false;
    }
    sf::Vector2f EnemyStartingPos;
    int EnemyDefinerNumber;
    sf::Clock Clock_er;
    bool Spawned;
    int unsigned WaitTimeAfterRound;
    int unsigned OriginalWaitTime;
    int SpawnOrder;
};
class EnemyRoundQueue : public EnemyQueue
{
public:
    EnemyRoundQueue()
    {
        IsRoundContainer = false;
        ContinueSpawning = true;
    }
    bool IsRoundContainer;
    int RoundV;
    bool ContinueSpawning;
    int SpawnEnemy();
    void CheckRoundValue();
};
std::vector <std::vector <EnemyRoundQueue>> EnemySpawnArray;
std::vector <EnemyRoundQueue> EnemyArrayInserter;









/// in case that the monitor's resolution is too big for the game, a black box is drawn so that it doesn't look like shit
struct FullscreenBlackBox : public sf::Drawable
{
    FullscreenBlackBox(): videoposcpy(0), OriginalfullscreenX(0)  {Rcover.setFillColor(sf::Color::Black), Lcover.setFillColor(sf::Color::Black);}

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {if (!isWindowMode()) target.draw(Rcover), target.draw(Lcover);}
    ///Sets the size of the left and right boxes
    void SetSize(sf::Vector2f S) {Rcover.setSize(S), Lcover.setSize(S);}

    void Update()
    {
        if (isWindowMode())
            return;
        WindowInfluence Win = Entity::WInflu;
        float LeftShift = (RWINdow.getSize().x - (RWINdow.getSize().x - Win.NewWindowSize.x ));
        float RightShift = Win.NewWindowSize.x / 2;
        LeftShift /= 2;
        Rcover.setPosition(viewer.getCenter().x + RightShift, viewer.getCenter().y - (RWINdow.getSize().y / 2));
        Lcover.setPosition(viewer.getCenter().x - (LeftShift + (Lcover.getSize().x )), viewer.getCenter().y - (RWINdow.getSize().y / 2)) ;
    }

    ///How much SFML shifts the view to the right
    float videoposcpy;
    ///The length of the Monitor
    float OriginalfullscreenX;
    ///Is the Box used to cover the window in case that the window is too big
    sf::RectangleShape Rcover;
    sf::RectangleShape Lcover;

};

void InputEnemyWave(int Rounder ,int DefineValue,double RoundWaitingTime, sf::Vector2f StartingPos);
void InsertEnemyWave();
void AddGoalPoint(float,float);
void GiveSprite(Entity *, unsigned char);
void GiveSprite(sf::Sprite *, unsigned char, int);
void GiveSprite(sf::Texture *, unsigned char, int);
sf::Vector2f Movey(sf::Vector2f);
void Create(int, int, sf::Vector2f);


LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

//sf::Text Couter("bruh", FontStyle::Dimbo_Regular);
EnemyRoundQueue* ERQ = new EnemyRoundQueue;
/*LevelManager Level1;
PauseMenu Pausing;
Introduction Introer;
BaseOverWorld Overworlder;
*/
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
    /**Load in Fonts */
    /*{
        FontHandle.Pair(FontStyle::Arial, ARIAL);
        FontHandle.Pair(FontStyle::Comic_Sans, COMIC_SANS);
        FontHandle.Pair(FontStyle::WTTW_Messy, WTTW_MESSY);
        FontHandle.Pair(FontStyle::Tehminal_Autismo, TEHMINAL_AUTISMO);
        FontHandle.Pair(FontStyle::Dimbo_Italic, DIMBO_ITALIC);
        FontHandle.Pair(FontStyle::Dimbo_Regular, DIMBO_REGULAR);
    }
    StatusAccessor.ChangeState(StateValue::SV_SubCworld);
    */
    //MasterAccess.Func_ptr = Create;
    MasterAccess.CurrencyPtr = &Currency;
    MasterAccess.MouseDotptr = &MouseHandle.Dot;
    MasterAccess.Winptr = &RWINdow;
    MasterAccess.vPtr = &viewer;
    sf::RenderWindow * p = &RWINdow;

    sf::Clock clock;

    //init();

/*
    glClearDepth(1.f);


    glEnable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar
    glClearColor(0.f, 0.f, 0.f, 0.f);
*/
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
                return 0;
                case sf::Event::MouseButtonReleased:
                {
                    MouseSpace::MouseReleased = true;
                    break;
                }
                /*
                case sf::Event::MouseButtonPressed:
                {
                    MouseSpace::MouseReleased = false;
                    break;
                }*/
                //case sf::Event::LostFocus:
                {
                    //PauseModeActivate();
                    //StatusAccessor.ChangeState(SV_Pause);
                    //PauseSpace::IsFocusLost = true;
                    break;
                }
                case sf::Event::GainedFocus:
                {
                    //PauseSpace::IsFocusLost = false;
                }
                //case sf::Event::Resized:
                   //WindowHandlier.FixWindowStatus();
               // break;
            }
        }
        //std::cout << "\n sizf " << Event.size.width;
        //std::cout << "  " << Event.size.height;
        //if (!WindowHandlier.Fullscreen)
          //  MasterAccess.WindowCenter = MasterAccess.Winptr->getView().getCenter();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            exit(69);

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::F4) && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) || sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {

            if (isWindowMode())
            {
                sf::Vector2f cen = viewer.getCenter();
                RWINdow.create(sf::VideoMode(0, 0), "The Restart", sf::Style::Fullscreen);
                RWINdow.setVerticalSyncEnabled(true);
                viewer = RWINdow.getDefaultView();
                WindowInfluence & WinFlu = Entity::WInflu;
                WinFlu.NewWindowSize.y = RWINdow.getSize().y;
                //bool toobig = false;
                /**< Creates the games full screen size and resizes so that it fits conditions */
                for (;WinFlu.NewWindowSize.y * 1.333 >= RWINdow.getSize().x /*|| !toobig*/; )
                {
                    WinFlu.NewWindowSize.y -= 1;
                    //toobig = (WinFlu.NewWindowSize.y / 600 <= 1.5);
                }
                WinFlu.StatusValue = Fullscreen;
                WinFlu.NewWindowSize.x = WinFlu.NewWindowSize.y * 1.333;
                WinFlu.influencePercent.x  = WinFlu.NewWindowSize.x / 800;
                WinFlu.influencePercent.y  = WinFlu.NewWindowSize.y / 600;
                std::cout << "\n window influence percentage x" << WinFlu.influencePercent.x;
                std::cout << "\n window influence percentage y" <<  WinFlu.influencePercent.y;
                float FullSizex = RWINdow.getSize().x;
                float FullSizey = RWINdow.getSize().y;
                FullBox.OriginalfullscreenX = FullSizex;
                float videopos =   (  WinFlu.NewWindowSize.x / RWINdow.getSize().x);
                std::cout << "\n video position number " << videopos;
                //float videopos = ( (RWINdow.getSize().x / WinFlu.NewWindowSize.x) < .5 ? .5 : .3);
                //if (videopos == .3)
                //videopos = (video > .4 ? .3 : .0);
                /// contains the percentage of how much the the Black Boxes should be shifted
                float FBvideo = (FullBox.videoposcpy = (1.0 - videopos));
                if (videopos > .95)
                    videopos = 0.f;
                FullBox.SetSize(sf::Vector2f((FullSizex * FBvideo) ,FullSizey));
                float Percentx =   ((FullSizex - (WinFlu.NewWindowSize.x / 2 )) * videopos / FullSizex);
                Percentx = (int)(Percentx * 10) / 10.0;
                viewer.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

                cen.x *= WinFlu.influencePercent.x;
                cen.y *= WinFlu.influencePercent.y;
                viewer.setCenter(cen);
            }
            else
            {
                WindowInfluence & WinFlu = Entity::WInflu;
                /**< Change what the status of the game to windowed mode */
                WinFlu.StatusValue = Windowed;
                sf::Vector2f cen = viewer.getCenter();
                RWINdow.create(sf::VideoMode(800, 600), "peen", sf::Style::Close);
                RWINdow.setVerticalSyncEnabled(false);
                viewer.setViewport(sf::FloatRect(-2.f, 0.f, 1.f, 1.f));
                viewer = RWINdow.getDefaultView();
                cen.x /= WinFlu.influencePercent.x;
                cen.y /= WinFlu.influencePercent.y;
                viewer.setCenter(cen);
            }
            RWINdow.setView(viewer);
            RWINdow.setFramerateLimit(60);
        }
        /*
        //glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);

        //glClear(GL_COLOR_BUFFER_BIT);

        //drawBox();
        RWINdow.clear(sf::Color(0, 0 , 0 , 0));

        //TexFunc();

        /*
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
        float angle = Clocker.getElapsedTime().asSeconds();
		glRotatef(angle * 50, 1.f, 0.f, 0.f);
		glRotatef(angle * 30, 0.f, 1.f, 0.f);
		glRotatef(angle * 90, 0.f, 0.f, 1.f);
        */


		//Draw a cube

        /*glBegin(GL_QUADS);//draw some squares
			glColor3i(0,3,2);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);

			glColor3f(3,0,2);
            glVertex3f(-50.f, -50.f, 50.f);
            glVertex3f(-50.f,  50.f, 50.f);
            glVertex3f( 50.f,  50.f, 50.f);
            glVertex3f( 50.f, -50.f, 50.f);

			glColor3f(1,0,1);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f(-50.f,  50.f,  50.f);
            glVertex3f(-50.f, -50.f,  50.f);

			glColor3f(0,3,0);
            glVertex3f(50.f, -50.f, -50.f);
            glVertex3f(50.f,  50.f, -50.f);
            glVertex3f(50.f,  50.f,  50.f);
            glVertex3f(50.f, -50.f,  50.f);

			glColor3f(1,9,0);
            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f,  50.f);

			glColor3f(3,0,0);
            glVertex3f(-50.f, 50.f,  50.f);
            glVertex3f(-50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f,  50.f);

        glEnd();*/
        {
        //RWINdow.draw(Couter);
        //FullBox.Update();
        //RWINdow.draw(FullBox);
        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
          //  std::cout << MouseHandle.Dot.getPosition().x << "  " << MouseHandle.Dot.getPosition().y << "\n";

        //sf::Time time = clock.getElapsedTime();
        //float fps = 1.f / time.asSeconds();
        //std::cout << fps << "\n";
        //clock.restart();*/
        //std::cout << ObjectsArray.size() << "\n";
        }



        // Apply some transformations for the cube
        //glMatrixMode(GL_MODELVIEW);
        //glLoadIdentity();
        //glTranslatef(0.f, 0.f, -200.f);


		//glRotatef(1.f, 1.f, 0.f, 0.f);
		//glRotatef(30 * 30, 0.f, 1.f, 0.f);
		//glRotatef(30 * 90, 0.f, 0.f, 1.f);



		//Draw a cube
        /*
        glBegin(GL_TRIANGLES);//draw some squares
		{
			glColor3i(0,2,1);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);

		}
        glEnd();*/
        /*
       // RWINdow.pushGLStates();
        //RWINdow.resetGLStates();

        RWINdow.setView(viewer);
        FullBox.Update();


        RWINdow.draw(FullBox);
       // RWINdow.popGLStates();

        */

        //if (GetMessage (&WindowHandlier.message, NULL, 0, 0))
        //{
          //  TranslateMessage(&WindowHandlier.message);
           // DispatchMessage(&WindowHandlier.message);

        //}
        RWINdow.setView(viewer);
        RWINdow.clear(sf::Color(0, 0 , 0 , 0));
        //MouseHandle.update();
        sf::RectangleShape S(sf::Vector2f(20, 20));
        S.setFillColor(sf::Color::Red);
        S.setPosition(300, 300);
        p ->draw(S);
        //RWINdow.draw(MouseHandle.Dot);
        StatusAccessor.Declare();
        StatusAccessor.Calculate();
        StatusAccessor.Draw();
        RWINdow.display();
    }
    return 360;
}



/** \brief inputs an enemy into the enemy inserter array
 *
 * \param The round the enemy is inputed
 * \param The Defining value for the Enemy
 * \param The Spawn time for the enemy
    (Its in frames by the way)
 * \param Its starting position
 *
 */
void InputEnemyWave(int Rounder, int DefineValue, double RoundWaitingTime, sf::Vector2f StartingPos)
{
    if (Rounder < 0)
    {
        MessageBox(NULL, TEXT("Rounds can't start on 0"), TEXT("Terminating Program"), MB_OK);
        exit(0);
    }
    Rounder++;


    EnemyRoundQueue ERQ;
    ERQ.EnemyDefinerNumber = DefineValue;
    ERQ.WaitTimeAfterRound = ERQ.OriginalWaitTime = RoundWaitingTime;
    ERQ.EnemyStartingPos = StartingPos;
    int SpawnValue = EnemyArrayInserter.size() - 1;
    if (SpawnValue == -1)
        SpawnValue += 2;
    else
        SpawnValue++;
    ERQ.SpawnOrder = SpawnValue;
    EnemyArrayInserter.push_back(ERQ);
}
/** \brief Insert the Enemy inserter array into the EnemySpawnArray
 *
 *
 */
void InsertEnemyWave()
{
    EnemyRoundQueue ERQ;
    ERQ.IsRoundContainer = true;
    ERQ.ContinueSpawning= true;
    std::vector <EnemyRoundQueue> RoundNumberContainer;
    RoundNumberContainer.push_back(ERQ);
    EnemySpawnArray.push_back(RoundNumberContainer);
    EnemySpawnArray.push_back(EnemyArrayInserter);
    EnemyArrayInserter.clear();
}
/** \brief Insert a Goal point Coordinate
 * \param X axis
 * \param  Y axis
 */
/*void AddGoalPoint(float x,float y)
{
     GoalPoint GInsert;
     GInsert.E_Rect.setPosition(x, y);
     GoalArray.push_back(GInsert);
}*/
/** \brief Function which saves a bit of code by passing a sprite to an object
 *
 * \param The address of object
 * \param The Objects Type
 */
/*void GiveSprite(Entity * object, unsigned char type)
{
    sf::Sprite spriter(R_Texture.get(static_cast<Textures::ID>(Spritefinder(type, object -> DefinerValue))));
    object -> E_Sprite = spriter;
}
/** \brief Function which saves a bit of code by passing a sprite to an object (but for Sprite parameter)
 *
 * \param The address of sf::Sprite
 * \param The Objects Type
 * \param define value
 */
/*void GiveSprite(sf::Sprite * object, unsigned char type, int definevalue)
{
    sf::Sprite spriter(R_Texture.get(static_cast<Textures::ID>(Spritefinder(type, definevalue))));
    *object = spriter;
}
/** \brief Function which saves a bit of code by passing a sprite to an object (but for Sprite parameter)
 *
 * \param The address of sf::Textures
 * \param The Objects Type
 * \param define value
 */
/*void GiveSprite(sf::Texture * object, unsigned char type, int definevalue)
{
    *object = (R_Texture.get(static_cast<Textures::ID>(Spritefinder(type, definevalue))));
}
 \brief The create function allow classes declared in different scopes to create entities
* \param Entity object type
* \param Entity objects names ID
* \param the entities position on the window
*/
/*void Create(int type, int DefineValue, sf::Vector2f pos)
{
    /**< Checks if the game is already in full screen mode, so the position coords aren't accidentally doubled
    WindowUpdater Wup;
    if (Wup.GetStatus() != -1)
        pos.x /= WindowUpdater::Winptr->influencePercent.x, pos.y /= WindowUpdater::Winptr->influencePercent.y;
    switch (type)
    {
    case ObjectTypes::Enemy:
        switch (DefineValue)
        {

        }
        break;
    case ObjectTypes::Tower:
        switch (DefineValue)
        {
            //case TowerNames::Pointduck:
                //return Textures::PointDuckSheet;
        }
        break;
    case ObjectTypes::Projectile:
        switch (DefineValue)
        {

        }
        break;
    case ObjectTypes::Miscellaneous:
        switch (DefineValue)
        {
            case MiscellaneousNames::WaterBucket:
            {
                ObjectsArray.push_front(ObjBox);
                auto It = ObjectsArray.begin();
                (*It).E_Rect.setPosition(pos);
                (*It).E_Rect.setSize(sf::Vector2f(10, 10));
                (*It).TypeValue = handleValues::Unique;
                (*It).AbilPtr = new objbucket((*It), BoxArray3[TowerDefenseUI::PointDisplay].E_Rect.getPosition());
                //(*It).pairPtrs();
            }
        }
    }
}*/


















void EnemyRoundQueue::CheckRoundValue()
{
    int ArrSize = EnemySpawnArray.size() / 2 ;
    if (ArrSize >= (signed int)Round)
        EnemyRound = Round;
    else
        ContinueSpawning = false;
}
int EnemyRoundQueue::SpawnEnemy()
{
    if (EnemyRound != Round)
        CheckRoundValue();
    int RoundStorgeNumber = EnemyRound;
    int EnemyNumContainer = RoundStorgeNumber + 1;
    int RoundSize = EnemySpawnArray[EnemyNumContainer].size();

    if (!EnemySpawnArray[RoundStorgeNumber][0].ContinueSpawning)
        return 37695;
    Counter = 0;
    bool AllSpawned = false;
    for (int I = 0; I < RoundSize; I++)
    {
        if (EnemySpawnArray[EnemyNumContainer][Counter].Spawned)
        {
            AllSpawned = true;
            Counter++;
            continue;
        }
        AllSpawned = false;
        EnemySpawnArray[EnemyNumContainer][Counter].WaitTimeAfterRound--;
        if (EnemySpawnArray[EnemyNumContainer][Counter].WaitTimeAfterRound == 0)
        {
            Jerber JInserter;
            JerberArray.push_front(JInserter);
            auto JIt = JerberArray.begin();
            EnemySpawnArray[EnemyNumContainer][Counter].Spawned = true;
            (*JIt).DefinerValue = EnemySpawnArray[EnemyNumContainer][Counter].EnemyDefinerNumber;
            (*JIt).E_Rect.setPosition(EnemySpawnArray[EnemyNumContainer][Counter].EnemyStartingPos);
            //JInserter.InsertCordinates(X,Y);
            (*JIt).Define();
            (*JIt).VaildCord.push_back(true);


            //std::cout << EnemySpawnArray[EnemyNumContainer][Counter].EnemyDefinerNumber << "\n";
            switch ((*JIt).DefinerValue)
            {
            case EnemyNames::Frog:
                (*JIt).AbilPtr = new Frog(.99, .88, 100, (*JIt));
                break;
            }

        }
        Counter++;
    }
    if (AllSpawned && JerberArray.size() == 0)
    {
        EnemySpawnArray[RoundStorgeNumber][0].ContinueSpawning = false;
        Round += 2;
    }
    return 0;
}

















void FontHandling::Pair(sf::Font & F, std::string S)
{
    if (!F.loadFromFile(S))
    {
        std::cout << "A font was failed to be loaded  lol";
        exit(0);
    }
}

void MouseHandling::update()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(RWINdow);
    sf::Vector2f worldPos = RWINdow.mapPixelToCoords(pixelPos);
    Dot.setPosition(worldPos);
}

/*
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_GETMINMAXINFO:
    {
        std::cout << "cock";
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        lpMMI->ptMinTrackSize.x = 300;
        lpMMI->ptMinTrackSize.y = 300;
    }
    break;

        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
*/























