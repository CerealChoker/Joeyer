#ifndef BASEMANAGER_H_INCLUDED
#define BASEMANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
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





enum FontStyle
{
    Arial,
    Comic_Sans,
    WTTW_Messy,
    Tehminal_Autismo,
    Dimbo_Regular,
    Dimbo_Italic
};


class LevelType
{
    public:
    LevelType();
    LevelType(const LevelType &);
    LevelType & operator=(const LevelType &);
    ///Contains types for the constructor to use
    enum Types
    {
        ///Contains Falsers, Calculations, Declare, mouse, and Draw
        Default,
        ///Contains every single function
        All,
        ///Contains all that Default has and pause
        DefaultNPause
    };
    LevelType(Types);


    bool Data[5] = {false, false, true, true, true};

    enum DataInfo
    {
        ///States if a level has a pause capability
        HasPause,
        ///Has Mouse Calculation
        HasMouse,
        ///Has Remove Falser's Function
        HasRemoveFalsers,
        ///Has Calculation function or like calculate collision
        HasCalculation,
        ///has Declare Assets function
        HasDeclareAssest,
        ///has Draw function
        HasDraw
    };
};

///Base class for all level states in the game, contains five main functions
class BaseManager
{
    public:
    BaseManager();
    ///The window pointer
    static sf::RenderWindow * WINdow;
    ///the sf::View pointer
    static sf::View * viewerp;
    ///Contains what functions will be used
    LevelType LevelInfo;

    ///Contains all the textures for the game :P
    static ResourceHolder<sf::Texture, Textures::ID> Res_Texture;
    static std::vector<sf::Font> Fonts;


    virtual void DrawEntities() = 0;
    virtual void DeclareAssests()  = 0;
    virtual void MouseCalculation()  = 0;
    virtual void Calculation()  = 0;
    virtual void RemoveFalsers()  = 0;

    //virtual ~BaseManager();



};

enum StateValue
{
    /** Value to input to change the current state value from paused to main value \see ChangeState*/


    SV_LevelTest,
    ///The inside the player conscious
    SV_SubCworld,
    SV_Undefined,
    SV_Introduction,
    SV_BeginningMenu,
    SV_Pause,

    SV_FowlKingDomBegin
};
/** \brief This struct handles the status state of the game*/
struct StateStatusHandler
{
    public:
    StateStatusHandler() {PauseDeclared = false, IsPause = false;}

    ///Contains literally the levels :0
    std::vector <BaseManager *> TheLevels;
    ///iterates to the chosen level
    std::vector<BaseManager *>::const_iterator SelectedLevel;
    ///iterates to the chosen Paused type
    std::vector<BaseManager *>::const_iterator SelectedPause;

    void Draw();
    void Calculate();
    void Declare();
    void ChangeState(int);
    void ChangePausedState(int);


    int * StatusPointer;

    //std::vector <* LevelManager>

    bool IsPause;

    int GameState;
    int PauseState;



    private:
    enum Indexes
    {
        MS,
        CS,
        SS
    };

    void NonPauseDraw();
    int StateValueArray[3] = {0, 0, 0};

    bool SVv_Update;
    bool PauseDeclared;

};







#endif // BASEMANAGER_H_INCLUDED
