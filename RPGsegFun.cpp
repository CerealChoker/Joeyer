#include "BaseManager.h"
#include "RPGsegFun.h"
#include <windows.h>



void OverWorld::DrawEntities()
{
    sf::RectangleShape S(sf::Vector2f(20, 20));
    S.setFillColor(sf::Color::Red);
    ///This does not work :/
    WINdow -> draw(S);
    //viewerp->move(.1f,0);
    
}


