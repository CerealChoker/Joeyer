//#include "EnemyIncluder.h"
#include "BaseManager.h"

BaseManager::BaseManager()
{
    Fonts.push_back(sf::Font());
    Fonts.push_back(sf::Font());
    Fonts.push_back(sf::Font());
    Fonts.push_back(sf::Font());
    Fonts.push_back(sf::Font());
    Fonts.push_back(sf::Font());
    FontPair(Fonts[0], ARIAL);
    FontPair(Fonts[1], COMIC_SANS);
    FontPair(Fonts[2], WTTW_MESSY);
    FontPair(Fonts[3], TEHMINAL_AUTISMO);
    FontPair(Fonts[4], DIMBO_ITALIC);
    FontPair(Fonts[5], DIMBO_ITALIC);
}

LevelType::LevelType()
{

}
LevelType::LevelType(const LevelType & Right)
{
    for (int i = 0; i < 5; i++)
        Data[i] = Right.Data[i];
}
LevelType::LevelType(Types T)
{
    for (int i = 0; i < 5; i++)
        Data[i] = false;
    switch (T)
    {
    case Types::All:
        for (int i = 0; i < 5; i++)
            Data[i] = true;
        break;
    case Types::Default:
        Data[DataInfo::HasRemoveFalsers] = true;
        Data[DataInfo::HasCalculation] = true;
        Data[DataInfo::HasDeclareAssest] = true;
        Data[DataInfo::HasDraw] = true;
        Data[DataInfo::HasMouse] = true;
        break;
    case Types::DefaultNPause:
        Data[DataInfo::HasRemoveFalsers] = true;
        Data[DataInfo::HasCalculation] = true;
        Data[DataInfo::HasDeclareAssest] = true;
        Data[DataInfo::HasDraw] = true;
        Data[DataInfo::HasPause] = true;
        break;
    }
}
LevelType & LevelType::operator=(const LevelType & Right)
{
    for (int i = 0; i < 5; i++)
        Data[i] = Right.Data[i];
}


void StateStatusHandler::Calculate()
{
    ///Contains the direct LevelType variable, to make things easier
    LevelType & LI = (*SelectedLevel) -> LevelInfo;
    if (LI.Data[LevelType::HasRemoveFalsers])
        (*SelectedLevel) -> RemoveFalsers();
    if (LI.Data[LevelType::HasCalculation])
        (*SelectedLevel) -> Calculation();
    if (LI.Data[LevelType::HasMouse])
        (*SelectedLevel) -> MouseCalculation();
    if (LI.Data[LevelType::HasRemoveFalsers])
        (*SelectedLevel) -> RemoveFalsers();
}
void StateStatusHandler::Declare()
{
    if (SVv_Update)
    {
        StatusPointer = &StateValueArray[CS];
        ///Contains the direct LevelType variable, to make things easier
        LevelType & LI = (*SelectedLevel) -> LevelInfo;
        SVv_Update = false;
        if (LI.Data[LevelType::HasDeclareAssest])
            (*SelectedLevel) ->DeclareAssests();
    }
}
void StateStatusHandler::Draw()
{
    ///Contains the direct LevelType variable, to make things easier
    LevelType & LI = (*SelectedLevel) -> LevelInfo;
    if (IsPause)
    {
        if (LI.Data[LevelType::HasDraw])
        {
            (*SelectedLevel) -> DrawEntities();
            (*SelectedPause) -> DrawEntities();
        }
        return;
    }
    if (LI.Data[LevelType::HasDraw])
        (*SelectedLevel) -> DrawEntities();
}
void StateStatusHandler::ChangePausedState(int State)
{
    PauseState = State;
    int counter = 0;
    for (auto It = TheLevels.begin(); It != TheLevels.end(); It++)
    {
        if (counter == GameState)
        {
            SelectedPause = It;
            break;
        }
        counter++;
    }

}
void StateStatusHandler::ChangeState(int State)
{

    if (State == SV_Pause)
    {
        SVv_Update = (!PauseDeclared ? true : false);
        IsPause = (!IsPause ? true : false);
        return;
    }
    /** Changes the current state of the game*/
    SVv_Update = true;
    GameState = State;
    int counter = 0;
    for (auto It = TheLevels.begin(); It != TheLevels.end(); It++)
    {
        if (counter == GameState)
        {
            SelectedLevel = It;
            break;
        }
        counter++;
    }


}
