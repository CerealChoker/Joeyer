#ifndef RPGSEGFUN_H_INCLUDED
#define RPGSEGFUN_H_INCLUDED
#include "BaseManager.h"

class OverWorld : public BaseManager
{
    public:
    OverWorld();//: eventer(0), ready(false), Drink(" R I N K") {}
    /** \brief Here interaction related activities are done here, it takes the define value as parameter
     * \param the DefineValue
     * \param The StatusValue
     */
    void InteractForDefine(int, int);
    /** \brief Here Interaction related activities are done here, it takes the Status State value as parameter
     * \param The StatusValue
     *
     */
    void InteractForStatus(int);

    void DrawEntities();
    void DeclareAssests();
    void MouseCalculation();
    void Calculation();
    void RemoveFalsers();
    void EmptyArrays();
    ///This is for the TextList array, if true the finished first element will be removed
    bool ready;
    ///event handling
    int eventer;
    ///Holds characters to be slowly printed out
    std::string Drink;
    ///Simple tile map accessor for holding a tile sheet
    TextBox BoxText;

    ///The shaker for the game's view
    ScreenShaker SShaker;
    ///Moves the screen up or down
    ScreenRiser SRShaker;
    ///Shakes various objects
    ObjectShaker OSHaker;

    TileMap TMer;
    Player theplayer;
    GroupRiseUp RU[3];

    MasterText MArr[3];
    std::list <MasterText> TextList;

    Box Boxy;
    Box Boxy2;
    Box Boxy3;

    std::vector<Box> BoxArray;
    std::vector<Box> BoxArray2;
    std::vector<Box> BoxArray3;

    std::list<Box> ObjectsArray;

    std::list <NPC> NPCArray;
    std::list <Tower> TowerArray;

    std::list <Projectile> ProjectileArray;

    //selbaward::Sprite3d spriteman;

    sf::Clock Clocker;


   // void BaseMouseCalculation();

};



class Introduction //: public BaseManager
{
    public:
    Introduction() {Statuser = -1, Clocker.restart();}
    //~Introduction() {if (Boxy.Shadepoint) delete Boxy.Shadepoint;}

    WindowUpdater WinUp;

    MasterText texter;
    MasterText texter2;
    MasterText texter3;
    MasterText texter4;
    MasterText texter5;

    MasterText * TextPointer[5] = {&texter, &texter2, &texter3, &texter4, &texter5};

    Box Boxy;
    Box Boxy2;
    Box Boxy3;
    Box Boxy4;
    Box Boxy5;

    Box * BoxPointers[4] = {&Boxy2, &Boxy3, &Boxy4, &Boxy5};

    void DrawEntities();
    void DeclareAssests();
    void MouseCalculation();
    void Calculation();
    void RemoveFalsers();

    sf::Clock Clocker;
    int Statuser;
};

#endif // RPGSEGFUN_H_INCLUDED
