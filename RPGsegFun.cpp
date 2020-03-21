#include "BaseManager.h"
#include "RPGsegFun.h"
#include <windows.h>


OverWorld::OverWorld()
{
    LevelInfo = LevelType(LevelType::Types::Default);
    LevelInfo.Data[LevelType::HasMouse] = false;
}
void OverWorld::DeclareAssests()
{
    try
    {
        Res_Texture.load(Textures::PlaceHolderTile, PLACEHOLDERTILE);
        Res_Texture.load(Textures::InMindTile, INMINDTILE);
        Res_Texture.load(Textures::Player, PLAYER);
        Res_Texture.load(Textures::PerseveranceSymbol, PERSEVERANCE_SYMBOL);
        Res_Texture.load(Textures::SubCDoor, SUB_CDOOR);
        Res_Texture.load(Textures::SubCTable, SUB_CTABLE);
    }
    catch(std::runtime_error& Shawn_E)
    {
        std::cout << "Exception: " << Shawn_E.what() << std::endl;
        exit(0);
        system("pause");
    }
    TMer.m_tileset = Res_Texture.get(Textures::InMindTile);

    const int level[] =
    {
        3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2,
        5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6,
        0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1
    };
    /**< The PLayer stuff  */
    theplayer.E_Sprite.setTexture(Res_Texture.get(Textures::Player));
    theplayer.E_Rect.setPosition(sf::Vector2f(900, 300));
    theplayer.isControled = true;
    theplayer.GrabCenter = true;
    theplayer.E_Sprite.setTextureRect(sf::IntRect(0 , 0 , 160, 160));
    theplayer.SAHCharacter.SetAnimation(Player::aniID::Sleeping);
    theplayer.SAHCharacter.Play();
    theplayer.TBptr = &BoxText;
    //theplayer.Wptr = &WalkingSpace;
    /**< the tile mape stuff */
    TMer.load(sf::Vector2u(64, 64), level, 17, 3);
    TMer.setPosition(sf::Vector2f(-50, 278));
    TMer.setScale(sf::Vector2f(1, 1));
    /**< The Text box */
    BoxText.WaitforInput = true;
    BoxText.FontPtr = &Fonts[FontStyle::Dimbo_Regular];
    BoxText.boxOfText.setPosition(sf::Vector2f(550, 50));

    /**< The Box class stuff */
    sf::Sprite SS(Res_Texture.get(Textures::PerseveranceSymbol));
    SS.setScale(sf::Vector2f(.5, .5));
    Boxy.E_Sprite = SS;
    Boxy.E_Rect.setSize(sf::Vector2f(100, 10));
    Boxy.E_Rect.setOrigin(sf::Vector2f(-20, -30));
    Boxy2.E_Sprite = SS;
    Boxy3.E_Sprite = SS;


    //spriteman.setTexture(Res_Texture.get(Textures::PerseveranceSymbol));
    //spriteman.setBackTexture(Res_Texture.get(Textures::PerseveranceSymbol));
    //spriteman.setOrigin(sf::Vector3f(80, 80, 80));
    //spriteman.setPosition(sf::Vector2f(100, 100));
    sf::Sprite S(Res_Texture.get(Textures::InMindTile));
    sf::Vector2f pos = theplayer.E_Rect.getPosition();
    /**< The MasterText class stuff  */
    MArr[0].SetText("this", 1, 20);
    MArr[0].MT_Texter.setPosition(sf::Vector2f(pos.x - 50, pos.y - 20 ));
    MArr[0].setSlide(10, MasterText::N, 100);
    MArr[1].SetText("is", 1, 20);
    MArr[1].setSlide(10, MasterText::N, 100);
    MArr[1].MT_Texter.setPosition(sf::Vector2f(pos.x + 20, pos.y - 30));
    MArr[2].SetText("you", 1, 20);
    MArr[2].setSlide(10, MasterText::N, 100);
    MArr[2].MT_Texter.setPosition(sf::Vector2f(pos.x + 70, pos.y - 20));

    for (int i = 0; i < 3; i++)
    {
        MArr[i].MT_Texter.setFont(Fonts[FontStyle::Dimbo_Regular]);
        MArr[i].MT_Texter.setFillColor(sf::Color(sf::Color::White));
        MArr[i].MT_Texter.setCharacterSize(32);
    }

    /**< RiserUper class stuff */
    SpriteAnimation inserter;
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(64 * 3 , 64 , 64, 64)));
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(64 * 3 , 0 , 64, 64)));
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(64 * 2 , 0 , 64, 64)));
    RU[0].spriter = S;
    RU[0].SetValues(inserter, RiserUper(S, 3, 1.1, .9, 10), 18, (int)GroupRiseUp::SizeTypes::EndsandChunk, 1);
    inserter.Animation.clear();
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(0 , 64 , 64, 64)));
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(64 , 64 , 64, 64)));
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(64 * 2 , 64 , 64, 64)));
    RU[1].spriter = S;
    RU[1].SetValues(inserter, RiserUper(S, 3, 1.1, .9, 10), 18, (int)GroupRiseUp::SizeTypes::EndsandChunk, 1);
    inserter.Animation.clear();
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(0 , 64 * 2 , 64, 64)));
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(0, 0 , 64, 64)));
    inserter.Animation.push_back(SpriteFrame(0, sf::IntRect(64 , 0 , 64, 64)));
    RU[2].spriter = S;
    RU[2].SetValues(inserter, RiserUper(S, 3, 1.1, .9, 10), 18, (int)GroupRiseUp::SizeTypes::EndsandChunk, 1);
    for (int i = 0; i < 3; i++)
    {
        RU[i].XSize = 64;
        RU[i].SetSpeed(5);
        RU[i].changePos(sf::Vector2f(-50, 300 + (i * 63)));
    }
    /**< The NPC stuff */
    {NPC c;NPCArray.push_front(c);}
    ///NPC Iterator
    auto NPCIt = NPCArray.begin();
    (*NPCIt).E_Rect.setPosition(sf::Vector2f(100 , 215));
    (*NPCIt).TBptr = &BoxText;
    (*NPCIt).Define(NPCNames::TheSubDoor);
    (*NPCIt).E_Sprite.setTexture(Res_Texture.get(Textures::SubCDoor));
    sf::Color C = (*NPCIt).E_Sprite.getColor();
    C.a = 0;
    (*NPCIt).E_Sprite.setColor(C);

    {NPC c;NPCArray.push_back(c);}
    NPCIt = NPCArray.end();
    NPCIt--;
    (*NPCIt).E_Rect.setPosition(sf::Vector2f(-300 , 315));
    (*NPCIt).TBptr = &BoxText;
    (*NPCIt).Define(NPCNames::MilkTable);
    (*NPCIt).E_Sprite.setTexture(Res_Texture.get(Textures::SubCTable));
    //sf::Color C = (*NPCIt).E_Sprite.getColor();
    //C.a = 0;
    //(*NPCIt).E_Sprite.setColor(C);

    theplayer.NonWalkSpace.NotWalk.push_back((*NPCIt).E_Rect.getGlobalBounds());
    theplayer.WalkSpace.BoxList.push_back(sf::FloatRect(sf::Vector2f(-685, 270), sf::Vector2f(1720, 170)));

    SRShaker.Setvalues( 10, 1.1, 7, 10);


}
void OverWorld::MouseCalculation()
{
    Drink = "gay";
}
void OverWorld::DrawEntities()
{
    sf::RectangleShape S(sf::Vector2f(20, 20));
    S.setFillColor(sf::Color::Red);
    WINdow -> draw(S);
    viewerp->move(.1f,0);
    //WINdow ->clear();

//    bool restartF = false;
//    SShaker.Update();
//    //static int j = 30;
//    //std::cout << "\n is player controlled? " << theplayer.GrabCenter;
//    /**< This Switch is specifically for calculation and drawings for only one event */
//    switch (eventer)
//    {
//        /**< The tiles rise up */
//    case 0:
//        {
//
//            static int f = 0;
//            if (f > 30)
//                f = 30;
//            for (int i = 0; i < f / 10; i++)
//            RU[i].Update(), WINdow ->draw(RU[i]);
//            f++;
//            if (RU[2].allDone)
//                eventer++;
//        }
//        break;
//    case 1:
//
//        if (Timing( 2 ,&Clocker))
//            eventer++;
//        break;
//    case 2:
//
//        if (Timing( 5 ,&Clocker))
//            eventer++;
//        viewerp ->move(Movey(sf::Vector2f(1,0)));
//        break;
//    case 3:
//        //SShaker.UndoShake();
//        if (MArr[2].StringFinished)
//            eventer++,Clocker.restart();
//        break;
//    case 4:
//        if (Timing( .5 ,&Clocker))
//        {
//            for (int i = 0; i < 3; i++)
//                MArr[i].setOutFade(2, 50);
//            eventer++;
//        }
//        break;
//    case 5:
//        if (Timing( 2.0, &Clocker))
//        {
//            for (int i = 0; i < 3; i++)
//                MArr[i].Restart();
//            MArr[0].SetText("you must", 1, 10);
//            MArr[0].MT_Texter.move(-60, 0);
//            MArr[1].SetText("wake", 1, 10);
//            MArr[1].MT_Texter.move(-20, -20);
//            MArr[2].SetText("up", 1, 10);
//            MArr[2].MT_Texter.move(25, 0);
//            restartF = true;
//            eventer++;
//        }
//        break;
//    case 6:
//        {
//            if (Clocker.getElapsedTime().asSeconds() > 2.5)
//            {
//                /**< Slowly set the color to red*/
//                sf::Color C = MArr[1].MT_Texter.getFillColor();
//                if (C.b == 160)
//                    SShaker.setFreqen(sf::Vector2i(200,200), 120);
//                if (C.b != 0)
//                    C.b -= 1;
//                if (C.g != 0)
//                    C.g -= 1;
//                MArr[1].MT_Texter.setFillColor(C);
//                //Clocker.restart();
//            }
//            if (Timing( 5.5 ,&Clocker))
//                eventer++;
//        }
//        break;
//    case 7:
//        {
//            //if (Timing( 1.5 ,&Clocker))
//            {
//               // MArr[1].MT_Texter.setFillColor(sf::Color::Transparent);
//                SShaker.UndoShake();
//
//                //for (int i = 0; i < 3; i++)
//                MArr[1].setOutFade(8, 50);
//                Boxy.E_Rect.setPosition(MArr[1].MT_Texter.getPosition());
//                eventer++;
//                Clocker.restart();
//            }
//        }
//        break;
//    case 8:
//        {
//            Boxy.E_Rect.move(Movey(sf::Vector2f(0,-2)));
//            SShaker.UndoShake();
//            if (Timing(.5, &Clocker))
//            {
//                auto NPCIt = NPCArray.begin();
//                    sf::Color c = (*NPCIt).E_Sprite.getColor();
//                    c.a = 255;
//                    (*NPCIt).E_Sprite.setColor(c);
//                eventer++;
//            }
//        }
//        break;
//    case 9:
//        {
//            Boxy.E_Rect.move(sf::Vector2f(0, ( std::sin(clock() * (.001)))));
//            if (Timing(.5, &Clocker))
//            {
//                eventer++;
//            }
//        }
//        break;
//    case 10:
//        {
//            Boxy.E_Rect.move(sf::Vector2f(0, ( std::sin(clock() * (.001)))));
//            sf::Vector2f BoxVec = Boxy.E_Rect.getPosition();
//
//            sf::Vector2f MT2 = MArr[2].MT_Texter.getPosition();
//            sf::Vector2f MT0 = MArr[0].MT_Texter.getPosition();
//            if (!Boxy.E_Rect.getGlobalBounds().intersects(MArr[2].MT_Texter.getGlobalBounds()))
//            {
//                sf::Vector2f AimDir = BoxVec - MT2;
//                AimDir.x /= sqrt(pow(AimDir.x , 2) + pow(AimDir.y , 2));
//                AimDir.y /= sqrt(pow(AimDir.x , 2) + pow(AimDir.y, 2));
//                AimDir = sf::Vector2f(AimDir.x * 3, AimDir.y * 3);
//                MArr[2].MT_Texter.setRotation(MArr[2].MT_Texter.getRotation() + 1);
//                MArr[2].MT_Texter.scale(.98, .98);
//                MArr[2].MT_Texter.move(Movey(AimDir));
//            }
//            else
//                MArr[2].setOutFade(15, 50);
//            if (!Boxy.E_Rect.getGlobalBounds().intersects(MArr[0].MT_Texter.getGlobalBounds()))
//            {
//                sf::Vector2f AimDir = BoxVec - MT0 ;
//                AimDir.x += 20;
//                AimDir.x /= sqrt(pow(AimDir.x , 2) + pow(AimDir.y , 2));
//                AimDir.y /= sqrt(pow(AimDir.x , 2) + pow(AimDir.y, 2));
//                AimDir = sf::Vector2f(AimDir.x * 3, AimDir.y * 3);
//                MArr[0].MT_Texter.move(Movey(AimDir));
//                MArr[0].MT_Texter.setRotation(MArr[0].MT_Texter.getRotation() + 1);
//                MArr[0].MT_Texter.scale(.98, .98);
//            }
//            else
//                MArr[0].setOutFade(15, 50);
//            if (Timing(4.5, &Clocker))
//                eventer++;
//
//        }
//        break;
//    case 11:
//        {
//            Boxy.E_Rect.move(Movey(sf::Vector2f(0, 9)));
//            //Boxy.E_Sprite.rotate(1.0);
//
//            //Boxy2.E_Rect.move(sf::Vector2f(0, ( std::sin(clock() * (.001)))));
//            //Boxy.E_Rect.getGlobalBounds().intersects(theplayer.E_Sprite);
//            if (Boxy.E_Rect.getGlobalBounds().intersects(theplayer.E_Sprite.getGlobalBounds()))
//            {
//                eventer++;
//                Boxy2.E_Rect.setFillColor(sf::Color::White);
//                sf::Color C = Boxy2.E_Rect.getFillColor();
//                C.a = 0;
//                Boxy2.E_Rect.setFillColor(C);
//                Boxy2.E_Rect.setSize(Movey(sf::Vector2f(1100, 700)));
//                Boxy2.E_Rect.setPosition(Movey(sf::Vector2f(200, -50)));
//
//            }
//        }
//        break;
//    case 12:
//        {
//            sf::Color C = Boxy2.E_Rect.getFillColor();
//            if (C.a < 250)
//            C.a = (C.a + 10);
//            Boxy2.E_Rect.setFillColor(C);
//            //theplayer.isControled = true;
//        }
//        if (FadeOut(&Boxy,5, 10))
//        {
//            SShaker.setFreqen(sf::Vector2i(1000,1000), 10);
//            eventer++;
//        }
//        break;
//    case 13:
//        {
//            Boxy.E_Rect.move(Movey(sf::Vector2f(0, ( std::sin(clock() * (.001))))));
//            if (Timing(.5, &Clocker))
//                eventer++;
//        }
//        break;
//    case 14:
//        {
//            sf::Color C = Boxy2.E_Rect.getFillColor();
//            if (C.a < 250)
//                C.a = (C.a + 10);
//            else
//                C.a = 255;
//            Boxy2.E_Rect.setFillColor(C);
//
//            if (Timing(1.f, &Clocker))
//            {
//                theplayer.GrabCenter = true;
//                //theplayer.isControled = true;
//                const int level[] =
//                {
//                    3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2,
//                    5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6,
//                    0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1
//                };
//                TMer.load(sf::Vector2u(64, 64), level, 27, 3);
//                TMer.move(Movey(sf::Vector2f(-635, 0)));
//                eventer++;
//            }
//        }
//        break;
//    case 15:
//        {
//            sf::Color C = Boxy2.E_Rect.getFillColor();
//            if (C.a > 10)
//            C.a = (C.a - 10);
//            else
//            {
//                C.a = 0;
//                if (Timing(1.f, &Clocker))
//                {
//                    eventer++;
//                    theplayer.SAHCharacter.SetAnimation(Player::WakeUp);
//                    theplayer.SAHCharacter.Play();
//                }
//
//            }
//            Boxy2.E_Rect.setFillColor(C);
//        }
//        break;
//    case 16:
//        {
//            if (Timing( .7, &Clocker))
//            {
//                for (int i = 0; i < 3; i++)
//                {
//                    MArr[i].Restart();
//                    MArr[i].MT_Texter.setFillColor(sf::Color(sf::Color::White));
//                    MArr[i].MT_Texter.setCharacterSize(Movey(sf::Vector2f(32, 0)).x);
//                    MArr[i].MT_Texter.setRotation(0.f);
//                    MArr[i].MT_Texter.setScale(1,1);
//                }
//                MArr[0].SetText("Move with W A S D", 1, 4);
//                MArr[0].setSlide(9, MasterText::W, 2000);
//                MArr[0].MT_Texter.setPosition(Movey(sf::Vector2f(600 , 100)));
//                MArr[2].MT_Texter.setPosition(Movey(sf::Vector2f(635 , 150)));
//
//                MArr[2].SetText("Interact with  Z", 1, 4);
//                MArr[2].setSlide(9, MasterText::W, 2000);
//                restartF = true;
//
//                theplayer.isControled = true;
//                eventer++;
//            }
//
//        }
//        break;
//    case 17:
//        {
//            if (Timing(8.7, &Clocker))
//            {
//                for (int i = 0; i < 3; i++)
//                    MArr[i].setOutFade(2, 50);
//                eventer++;
//
//
//            }
//            break;
//
//        }
//    }
//    /**< The event handling for the Door of subconsciousness */
//    switch (eventer)
//    {
//    case 19:
//        SRShaker.Update();
//        if (SRShaker.isDone)
//        {
//            for (int i = 0; i < 3; i++)
//            {
//                MArr[i].Restart();
//                MArr[i].MT_Texter.setCharacterSize(Movey(sf::Vector2f(32, 0)).x);
//                MArr[i].MT_Texter.setRotation(0.f);
//                MArr[i].MT_Texter.setScale(1,1);
//            }
//            MArr[1].MT_Texter.setPosition(Movey(sf::Vector2f(-180 , 60)));
//            //MArr[2].MT_Texter.setPosition(Movey(sf::Vector2f(300 , 150)));
//            MArr[1].SetText("Here lies the Door of Subconsciousness, Where all mental\nmemories lie hidden. Beyond it contains complete mental \nprowess", 1, 2);
//            MArr[1].setSlide(5, MasterText::N, 1000);
//            Clocker.restart();
//            eventer++;
//        }
//        break;
//    case 20:
//        if (MArr[1].StringFinished && Timing(5.5, &Clocker))
//        {
//            MArr[2].MT_Texter.setPosition(Movey(sf::Vector2f(155 , -100)));
//            MArr[2].SetText("No, you can not open it", 1, 7);
//
//            MArr[2].MT_Texter.setFillColor(sf::Color(sf::Color::Red));
//
//            MArr[2].setSlide(9, MasterText::W, 1000);
//
//            eventer++;
//        }
//
//        break;
//    case 21:
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
//        {
//            if (MArr[2].StringFinished )
//            {
//                MArr[1].setOutFade(2, 70);
//                SRShaker.Setvalues( 10, 1.1, 7, 10);
//                SRShaker.moveUp = false;
//                eventer++;
//            }
//
//        }
//        if (MArr[2].StringFinished)
//            MArr[2].setOutFade(2, 70);
//        break;
//    case 22:
//        SRShaker.Update();
//        if (SRShaker.isDone)
//        {
//            theplayer.GrabCenter = true;
//            theplayer.isControled = true;
//            eventer++;
//        }
//        break;
//    }
//    switch (eventer)
//    {
//    case 30:
//        {
//            for (int i = 0; i < 3; i++)
//            {
//                MArr[i].Restart();
//                MArr[i].MT_Texter.setCharacterSize(Movey(sf::Vector2f(32, 0)).x);
//                MArr[i].MT_Texter.setRotation(0.f);
//                MArr[i].MT_Texter.setScale(1,1);
//            }
//            {
//                MasterText m;
//                TextList.push_front(m);
//            }
//            auto MTIt = TextList.begin();
//
//            (*MTIt).MT_Texter.setPosition(sf::Vector2f(-480 , 230));
//            //MArr[2].MT_Texter.setPosition(Movey(sf::Vector2f(300 , 150)));
//            (*MTIt).SetText("The Milk of Life       ", 1, 5);
//            (*MTIt).MT_Texter.setCharacterSize(32);
//            (*MTIt).MT_Texter.setFont(Fonts[FontStyle::Dimbo_Regular]);
//            (*MTIt).MT_Texter.setFillColor(sf::Color(sf::Color::White));
//            (*MTIt).setSlide(1, MasterText::N, 300);
//            eventer++;
//        }
//        break;
//    case 31:
//        {
//            auto MTItC = TextList.begin();
//            if ((*MTItC).StringFinished)
//            {
//                TextList.push_front(MasterText());
//                auto MTIt = TextList.begin();
//
//                (*MTIt).MT_Texter.setPosition(sf::Vector2f(-250 , 200));
//                (*MTIt).MT_Texter.setCharacterSize(32);
//                //MArr[2].MT_Texter.setPosition(Movey(sf::Vector2f(300 , 150)));
//                (*MTIt).SetText("Gifted by the\n    Bovidae Family     ", 1, 5);
//                (*MTIt).MT_Texter.setFont(Fonts[FontStyle::Dimbo_Regular]);
//                (*MTIt).MT_Texter.setFillColor(sf::Color(sf::Color::White));
//                (*MTIt).setSlide(3, MasterText::N, 300);
//                eventer++;
//            }
//            break;
//        }
//    case 32:
//        {
//            auto MTItC = TextList.begin();
//            if ((*MTItC).StringFinished)
//            {
//                TextList.push_front(MasterText());
//                auto MTIt = TextList.begin();
//
//                (*MTIt).MT_Texter.setPosition(sf::Vector2f(-350 , 430));
//                (*MTIt).MT_Texter.setCharacterSize(32);
//                //MArr[2].MT_Texter.setPosition(Movey(sf::Vector2f(300 , 150)));
//                (*MTIt).SetText("It'll surely awaken you    ", 1, 5);
//                (*MTIt).MT_Texter.setFont(Fonts[FontStyle::Dimbo_Regular]);
//                (*MTIt).MT_Texter.setFillColor(sf::Color(sf::Color::White));
//                (*MTIt).setSlide(3, MasterText::N, 300);
//                eventer++;
//            }
//            break;
//        }
//    case 33:
//        {
//            auto MTItC = TextList.begin();
//            if ((*MTItC).StringFinished)
//            {
//                for (auto It = TextList.begin(); It != TextList.end(); It++)
//                    (*It).setOutFade(2, 70);
//                TextList.push_front(MasterText());
//                auto MTIt = TextList.begin();
//                (*MTIt).MT_Texter.setCharacterSize(100);
//                (*MTIt).MT_Texter.setPosition(sf::Vector2f(-410 , 100));
//                //MArr[2].MT_Texter.setPosition(Movey(sf::Vector2f(300 , 150)));
//                (*MTIt).SetText("D", 1, 25);
//                (*MTIt).MT_Texter.setFont(Fonts[FontStyle::Dimbo_Regular]);
//                (*MTIt).MT_Texter.setFillColor(sf::Color(sf::Color::White));
//                OSHaker.UndoShake();
//                OSHaker.ShakeList.push_back(ShakeObj(&(*MTIt).MT_Texter, (*MTIt).MT_Texter.getPosition()));
//                OSHaker.setFreqen(sf::Vector2i(200, 200), 3000);
//                eventer++;
//
//            }
//        }
//        break;
//    case 34:
//        {
//            auto MTIt = TextList.begin();
//            if ((*MTIt).StringFinished)
//            {
//                if ((*MTIt).StringFinished && !Drink.empty())
//                {
//                    TextList.push_front(MasterText());
//                    auto MTIt = TextList.begin();
//
//                    (*MTIt).MT_Texter.setCharacterSize(100);
//                    ///Determines the placement of each letter
//                    int pos = (9 - Drink.size());
//                    (*MTIt).MT_Texter.setPosition(sf::Vector2f(-410 + (40 * pos), 100));
//
//                    std::string setter = "";
//                    setter += Drink[0];
//                    if (setter != " ")
//                        OSHaker.ShakeList.push_back(ShakeObj(&(*MTIt).MT_Texter, (*MTIt).MT_Texter.getPosition())), SShaker.setFreqen(sf::Vector2i(1000,1000), 10);
//                    (*MTIt).SetText(setter, 1, 13);
//                    Drink.erase(Drink.begin());
//                    (*MTIt).MT_Texter.setFont(Fonts[FontStyle::Dimbo_Regular]);
//                    (*MTIt).MT_Texter.setFillColor(sf::Color(sf::Color::White));
//                }
//
//
//            }
//            if (Drink.empty())
//                eventer++, Clocker.restart();
//            break;
//        }
//    case 35:
//        {
//            if (Timing(0.1f, &Clocker))
//            {
//                Projectile P;
//                ProjectileArray.push_front(P);
//                auto  ItP = ProjectileArray.begin();
//                Projectile & Pro = (*ItP);
//                Pro.DefinerValue = ProjectileNames::TheLarginingZ;
//                Pro.Define();
//                Pro.E_Radius.setPosition(sf::Vector2f(-300, 120));
//                Pro.E_Text.setFont(Fonts[FontStyle::Dimbo_Regular]);
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
//                eventer++;
//            break;
//        }
//    case 36:
//        {
//            for (auto It = TextList.begin(); It != TextList.end(); It++)
//                (*It).setOutFade(rand() % 3 + 1, 900);
//            Clocker.restart();
//            eventer++;
//            break;
//        }
//    case 37:
//        {
//            if (Timing(2.5, &Clocker))
//            {
//                theplayer.SAHCharacter.SetAnimation(Player::DrinkMilk);
//                theplayer.AnimateID = Player::DrinkMilk;
//                theplayer.SAHCharacter.Play();
//                auto NPCIt = NPCArray.end();
//                NPCIt--;
//                NPC & N = (*NPCIt);
//                N.E_Sprite.setTextureRect(sf::IntRect(0 , 0 , 60, 60));
//                eventer++;
//            }
//            break;
//
//        }
//    case 38:
//        {
//            if (Timing(2.5, &Clocker))
//            {
//                TextList.clear();
//                SShaker.setFreqen(sf::Vector2i(1000, 1000), 900);
//                TextList.push_front(MasterText());
//                auto MTIt = TextList.begin();
//                (*MTIt).MT_Texter.setCharacterSize(32);
//                (*MTIt).MT_Texter.setPosition(sf::Vector2f(-550 , 320));
//                //MArr[2].MT_Texter.setPosition(Movey(sf::Vector2f(300 , 150)));
//                (*MTIt).SetText("Perfect", 1, 29);
//                (*MTIt).MT_Texter.setFont(Fonts[FontStyle::Dimbo_Regular]);
//                (*MTIt).MT_Texter.setFillColor(sf::Color(sf::Color::White));
//                eventer++;
//            }
//        }
//    case 39:
//        {
//            if (Timing(2.5, &Clocker))
//            {
//                EmptyArrays();
//                //StatusAccessor.ChangeState(StateValue::SV_FowlKingDomBegin);
//            }
//        }
//    }
//    switch (eventer)
//    {
//    case 0:
//        break;
//    case 1:
//    case 2:
//        TMer.Update();
//        WINdow ->draw(TMer);
//        break;
//    case 3:
//    case 4:
//    case 5:
//    case 6:
//    case 7:
//    case 8:
//    case 9:
//    case 10:
//    default:
//        OSHaker.Update();
//        TMer.Update();
//        WINdow ->draw(TMer);
//        static int ff = 0;
//        if (restartF)
//            ff = 0, restartF = false;
//        if (ff > 270)
//            ff = 270;
//        for (int i = 0; i < ff / 90; i++)
//        {
//            MArr[i].Update();
//            WINdow ->draw(MArr[i]);
//        }
//        for (auto It = TextList.begin(); It != TextList.end(); It++)
//        {
//            (*It).Update();
//            WINdow ->draw((*It));
//        }
//        Boxy.Update();
//        WINdow ->draw(Boxy);
//        ff++;
//        break;
//    }
//    for (auto It = NPCArray.begin(); It != NPCArray.end(); It++)
//    {
//        (*It).Update();
//        WINdow ->draw((*It));
//    }
//
//    theplayer.Update();
//    WINdow ->draw(theplayer);
//    WINdow ->draw(theplayer.E_Rect);
//    if (theplayer.GrabCenter)
//        viewerp ->setCenter(theplayer.E_Sprite.getPosition());
//
//
//    BoxText.Update();
//    WINdow ->draw(BoxText);
//
//    //static int i = 0;
//    //spriteman.setYaw(i++);
//    //spriteman.move(sf::Vector2f(0, .1));
//    //spriteman.set
//    //spriteman.setOrigin3d(sf::Vector3f(80, 60, 80));
//
//    //WINdow ->draw(spriteman);
//
//    ///Draw all Projectiles
//    for (auto It = ProjectileArray.begin(); It != ProjectileArray.end(); It++)
//    {
//        /**< Update projectiles when the text is doing that spiraling thing */
//        if (eventer == 35)
//            (*It).Update(), (*It).UpdateMovement();
//        WINdow ->draw((*It).E_Text);
//    }
//    Boxy2.Update();
//    WINdow ->draw(Boxy2.E_Rect);
//   //WINdow ->display();
//    //if (!BoxText.TextBoxActive)
}
void OverWorld::Calculation()
{
    ///if a collision is defined the object that is collided with, it's define and its current status it obtained
    int define = -9696;
    int StatusValue = -1;

    bool success = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        for (auto It = NPCArray.begin(); It != NPCArray.end(); It++)
            if (theplayer.CanInteract((*It).E_Rect.getGlobalBounds()))
            {
                define = (*It).DefinerValue;
                StatusValue = (*It).Interacted();
                success = true;

                if (StatusValue == -1)
                    success = false;
                break;
            }

    }
    if (success)
        InteractForDefine(define, StatusValue);

}
void OverWorld::InteractForDefine(int def, int S)
{
    switch (def)
    {
    case NPCNames::TheSubDoor:
    case NPCNames::MilkTable:
        InteractForStatus(S);
        break;
    }
}
void OverWorld::InteractForStatus(int S)
{
    switch (S)
    {
    case SubconDoor::hasbeeeninteracted:
        for (int i = 0; i < 3; i++)
            MArr[i].setOutFade(2, 50);
        theplayer.isControled = false;
        theplayer.GrabCenter = false;
        eventer = 19;
        break;
    case SubconTable::hasbeeeninteracted:
        eventer = 30;
        theplayer.isControled = false;
        theplayer.GrabCenter = false;
        break;

    }
}
void OverWorld::RemoveFalsers()
{
    for (auto It = ProjectileArray.begin(); It != ProjectileArray.end(); It++)
    {
        if (!(*It).Exist)
        {
            ProjectileArray.erase(It);
            break;

        }
    }
}
void OverWorld::EmptyArrays()
{
    ProjectileArray.clear();
    NPCArray.clear();
    TextList.clear();

}


////////////////////////////////////////////Introduction'
//
//void Introduction::DeclareAssests()
//{
//    try
//    {
//        Res_Texture.load(Textures::GameTitle, GAMETITLE);
//        Res_Texture.load(Textures::Introduction1, INTRODUCTION1);
//        Res_Texture.load(Textures::Introduction2, INTRODUCTION2);
//        Res_Texture.load(Textures::Introduction3, INTRODUCTION3);
//        Res_Texture.load(Textures::Introduction4, INTRODUCTION4);
//        Res_Texture.load(Textures::Introduction5, INTRODUCTION5);
//        Res_Texture.load(Textures::Introduction6, INTRODUCTION6);
//        Res_Texture.load(Textures::Introduction7, INTRODUCTION7);
//        Res_Texture.load(Textures::Introduction8, INTRODUCTION8);
//
//    }
//    catch(std::runtime_error& Shawn_E)
//    {
//        std::cout << "Exception: " << Shawn_E.what() << std::endl;
//        exit(0);
//        system("pause");
//    }
//    /*TextPointer[0] = &texter;
//    TextPointer[1] = &texter2;
//    TextPointer[2] = &texter3;
//    TextPointer[3] = &texter4;
//    TextPointer[4] = &texter5;*/
//    for (auto & TextPoint : TextPointer)
//    {
//        TextPoint -> setFrameWait(1);
//        TextPoint -> MT_Texter.setCharacterSize(30);
//        TextPoint -> MT_Texter.setFont(Fonts[FontStyle::Dimbo_Regular]);
//    }
//    for (auto & BoxPoint : BoxPointers)
//    {
//        BoxPoint -> E_Sprite.setColor(sf::Color(255, 255, 255, 0));
//        BoxPoint -> E_Rect.setSize(sf::Vector2f(20, 20));
//    }
//    /*
//    texter.MT_Texter.setCharacterSize(30);
//    texter2.MT_Texter.setCharacterSize(30);
//    texter3.MT_Texter.setCharacterSize(30);
//    texter4.MT_Texter.setCharacterSize(30);
//    texter.MT_Texter.setFont(FontStyle::Dimbo_Regular);
//    texter2.MT_Texter.setFont(FontStyle::Dimbo_Regular);
//    texter3.MT_Texter.setFont(FontStyle::Dimbo_Regular);
//    texter4.MT_Texter.setFont(FontStyle::Dimbo_Regular);
//    */
//    {
//        sf::Sprite joey((Res_Texture.get(Textures::GameTitle)));
//        Boxy.E_Sprite = joey;
//        sf::Color color(Boxy.E_Sprite.getColor());
//        Boxy.E_Sprite.setColor(sf::Color(color.r, color.b, color.g, 0));
//        Boxy.E_Rect.setSize(sf::Vector2f(20, 20));
//        Boxy.E_Rect.setFillColor(sf::Color::Red);
//        Boxy.E_Rect.setSize(sf::Vector2f(20, 20));
//        Boxy.E_Rect.setPosition(106,  50);
//        Boxy.E_Sprite.setPosition(106,  50);
//        //Boxy.LockedHitbox = false;
//        //std::cout << "\n" << Boxy.E_Rect.getPosition().x << "  " << Boxy.E_Rect.getPosition().y;
//        Boxy.Shadepoint = new WaveyShade;
//    }
//}
//void Introduction::DrawEntities()
//{
//    /*
//    texter.Update();
//    WINdow ->draw(texter.MT_Texter);
//    texter2.Update();
//    WINdow ->draw(texter2.MT_Texter);*/
//    for (auto & TextPoint : TextPointer)
//    {
//        TextPoint -> Update();
//        WINdow ->draw(*TextPoint);
//    }
//    for (auto & BoxPoint : BoxPointers)
//    {
//        BoxPoint -> Update();
//        WINdow ->draw(*BoxPoint);
//        //WINdow ->draw((*BoxPoint).E_Rect);
//    }
//    Boxy.Update();
//    WINdow ->draw(Boxy);
//    //WINdow ->draw(Boxy.E_Rect);
//}
//void Introduction::Calculation()
//{
//    /*
//    {
//        < Checks the Games window status and changes the Wavey shader's value to fit game status /
//        int test = WinUp.GetStatus();
//        if (test != -1)
//            WaveyShade * ptr = dynamic_cast<WaveyShade *>(Boxy.Shadepoint), ptr->mover = Movey(ptr->mover);
//    }
//    */
//   // std::cout << "\n pos " << texter.MT_Texter.getPosition().x << "  " << Boxy.E_Rect.getPosition().y;
//   // std::cout << "\n pos " << Boxy.LockedHitbox;
//    //std::stringstream streamer;
//      //  streamer << Boxy.LockedHitbox;
//
//    //Couter.setString(streamer.str());
//
//    if (10 > Statuser)
//    {
//
//        if (Statuser > 5)
//            Boxy.E_Rect.setPosition(Movey(sf::Vector2f(200, 50)));
//            //Boxy.E_Sprite.setPosition(Movey(sf::Vector2f(200, 50)));
//        else
//            Boxy.E_Rect.setPosition(Movey(sf::Vector2f(106, 50)));
//
//
//        texter.MT_Texter.setPosition(Movey(sf::Vector2f(150, 390)));
//    }
//    if (29 < Statuser && 35 >= Statuser)
//        Boxy4.E_Rect.setPosition(sf::Vector2f(275, 80 * ( std::sin(clock() * (.001)))));
//    switch (Statuser)
//    {
//    /** Game waits*/
//    case -1:
//            if (Clocker.getElapsedTime().asSeconds() > 2)
//                Statuser++;
//        break;
//    /** Games title is slowly displayed  */
//    case 0:
//        {
//            if (FadeIn(&Boxy , 240, 1))
//                Statuser++,Clocker.restart();
//        }
//        break;
//        /** Game waits 2 secs*/
//    case 1:
//        if (Clocker.getElapsedTime().asSeconds() > 4)
//                Statuser++;
//        break;
//        /** Title fades out */
//    case 2:
//        {
//            if (FadeOut(&Boxy ,5 , .8))
//                Statuser++,Clocker.restart();
//        }
//        break;
//    case 3:
//            if (Clocker.getElapsedTime().asSeconds() > 2)
//                Statuser++, Boxy.Shadepoint -> ActiveShade = false;
//                break;
//    case 4:
//        {
//            sf::Sprite joey((Res_Texture.get(Textures::Introduction1)));
//            joey.setPosition(Boxy.E_Rect.getPosition());
//            joey.setScale(Movey(sf::Vector2f(1, 1)));
//            Boxy.E_Sprite = joey;
//            sf::Color color(Boxy.E_Sprite.getColor());
//            Boxy.E_Sprite.setColor(sf::Color(color.r, color.b, color.g, 0));
//            Statuser++;
//        }
//        break;
//    case 5:
//        {
//            texter.MT_Texter.setPosition(Movey(sf::Vector2f(56, 390)));
//            texter2.MT_Texter.setPosition(Movey(sf::Vector2f(6, 150)));
//            texter.setFrameWait(1);
//
//
//            //texter.setSlide(10, 2,300);
//            texter.SetText("It was 20XX and the human race had remained the \nhighest among this world", 1 , 3);
//            Statuser++, Clocker.restart();
//        }
//        break;
//    case 6:
//        if (Clocker.getElapsedTime().asSeconds() > .7)
//            Statuser++;
//            break;
//    case 7:
//        {
//            FadeIn(&Boxy, 240, .9);
//            if (texter.StringFinished)
//              Statuser++,Sleep(1750),texter.setOutFade(1, 125);
//        }
//        break;
//    case 8:
//        {
//            if (FadeOut(&Boxy ,5 ,.8))
//                Statuser++,Clocker.restart();
//        }
//        break;
//    case 9:
//        if (Clocker.getElapsedTime().asSeconds() > 1)
//            Statuser++;
//        break;
//    case 10:
//        {
//            sf::Sprite joey((Res_Texture.get(Textures::Introduction2)));
//            joey.setScale(Movey(sf::Vector2f(1, 1)));
//            Boxy.E_Sprite = joey;
//            sf::Color color(Boxy.E_Sprite.getColor());
//            Boxy.E_Sprite.setColor(sf::Color(color.r, color.b, color.g, 0));
//            Statuser++;
//            texter.Restart();
//            Clocker.restart();
//        }
//        break;
//    case 11:
//        {
//            texter.setFrameWait(1);
//            texter.SetText("But suddenly one day had fallen to nuclear war, \ntearing the world apart", 1 , 3);
//            Statuser++;
//        }
//        break;
//    case 12:
//        {
//            FadeIn(&Boxy, 240, 4);
//            if (Clocker.getElapsedTime().asSeconds() > 2)
//              Statuser++;
//        }
//        break;
//    case 13:
//        {
//            if (FadeOut(&Boxy ,20 ,4))
//                Statuser++,Clocker.restart();
//        }
//        break;
//    case 14:
//        {
//            sf::Sprite joey((Res_Texture.get(Textures::Introduction3)));
//            joey.setScale(Movey(sf::Vector2f(1, 1)));
//            Boxy.E_Sprite = joey;
//            sf::Color color(Boxy.E_Sprite.getColor());
//            Boxy.E_Sprite.setColor(sf::Color(color.r, color.b, color.g, 0));
//            Statuser++;
//            Clocker.restart();
//        }
//        break;
//    case 15:
//        {
//            FadeIn(&Boxy ,240 , 3);
//            if (texter.StringFinished)
//                Statuser++,Sleep(1750),texter.setOutFade(1, 125);
//        }
//        break;
//    case 16:
//        {
//            if (FadeOut(&Boxy ,5 , .8))
//                Statuser++,Clocker.restart();
//        }
//        break;
//    case 17:
//        {
//            texter.Restart();
//            texter.SetText("Hundreds of thousand humans and animals had fallen\nto the radiation, hope had began to dim in the world", 1 , 3);
//            Statuser++;
//        }
//        break;
//    case 18:
//        {
//            sf::Sprite joey((Res_Texture.get(Textures::Introduction4)));
//            joey.setScale(Movey(sf::Vector2f(1, 1)));
//            Boxy.E_Sprite = joey;
//            sf::Color color(Boxy.E_Sprite.getColor());
//            Boxy.E_Sprite.setColor(sf::Color(color.r, color.b, color.g, 0));
//            //Boxy.E_Sprite.setTextureRect(sf::IntRect(0 , 0 , 250 , 190));
//            Statuser++;
//            Clocker.restart();
//        }
//        break;
//    case 19:
//        {
//            FadeIn(&Boxy ,240 ,3);
//            if (texter.StringFinished)
//                Statuser++, texter.setOutFade(1, 125), Sleep(1750);
//        }
//        break;
//    case 20:
//        {
//            if (!FadeOut(&Boxy ,5 , .8))
//                break;
//            sf::Sprite joey((Res_Texture.get(Textures::Introduction5)));
//            joey.setScale(Movey(sf::Vector2f(1, 1)));
//            Boxy.E_Sprite = joey;
//            Boxy2.E_Sprite = joey;
//            Boxy3.E_Sprite = joey;
//            //sf::Vector2f Pos = Boxy.E_Rect.getPosition();
//            Boxy2.E_Rect.setPosition(Movey(sf::Vector2f(150, 0)));
//            Boxy3.E_Rect.setPosition(Movey(sf::Vector2f(250, 0)));
//
//
//            for (auto & BoxPoint : BoxPointers)
//                BoxPoint -> E_Sprite.setColor(sf::Color(255, 255, 255, 0));
//            Boxy.E_Sprite.setColor(sf::Color(255, 255, 255, 0));
//            Statuser++;
//            Clocker.restart();
//        }
//        break;
//    case 21:
//        {
//
//            if (Clocker.getElapsedTime().asSeconds() > 5)
//              Statuser++, texter.Restart();
//        }
//        break;
//    case 22:
//        {
//            bool pass = true;
//            bool unpass = false;
//            FadeIn(&Boxy ,250 , 5);
//            for (auto & BoxPoint : BoxPointers)
//            {
//                pass = FadeIn(BoxPoint ,250 , 5);
//                if (!pass)
//                    unpass = true;
//            }
//            if (pass && !unpass)
//                Statuser++;
//        }
//        break;
//    case 23:
//        {
//            for (auto & BoxPoint : BoxPointers)
//                BoxPoint -> E_Sprite.setColor(sf::Color(255, 255, 255, 255));
//            texter.setFrameWait(1);
//            texter.setSlide(20, MasterText::E,100);
//            texter.SetText("As the last few humans roamed", 1 , 3);
//            Statuser++, Clocker.restart();
//        }
//        break;
//    case 24:
//        FadeOut(&Boxy3 ,5 , .8);
//        if (Clocker.getElapsedTime().asSeconds() > 1.8)
//            Statuser++;
//            break;
//    case 25:
//        {
//
//            texter2.MT_Texter.setPosition(Movey(sf::Vector2f(40, 90)));
//
//            texter2.setSlide(20, MasterText::S, 160);
//            texter2.SetText("it seemed as if \nthey were all\nfated to die", 1, 3);
//            Clocker.restart();
//            Statuser++;
//        }
//        break;
//    case 26:
//        FadeOut(&Boxy3 ,5 , .8);
//        FadeOut(&Boxy2 ,5 , .8);
//        if (Clocker.getElapsedTime().asSeconds() > 2.7)
//            Statuser++;
//            break;
//    case 27:
//        {
//            Boxy3.E_Sprite.setColor(sf::Color::Transparent);
//            Boxy2.E_Sprite.setColor(sf::Color::Transparent);
//            texter3.MT_Texter.setPosition(Movey(sf::Vector2f(545, 250)));
//
//            texter3.setSlide(20, MasterText::S, 100);
//            texter3.SetText("but as hope begin \nfalter, a ", 1, 3);
//            Clocker.restart();
//            Statuser++;
//        }
//        break;
//    case 28:
//        FadeOut(&Boxy ,5 , .9);
//        if (Clocker.getElapsedTime().asSeconds() > 1.65)
//            Statuser++;
//            break;
//    case 29:
//        {
//            sf::Sprite joey((Res_Texture.get(Textures::Introduction6)));
//            joey.setScale(Movey(sf::Vector2f(1, 1)));
//            Boxy4.E_Sprite = joey;
//            Boxy4.E_Sprite.setColor(sf::Color(255, 255, 255, 0));
//            sf::Vector2f CharPos = texter3.MT_Texter.findCharacterPos(30);
//            //CharPos.y += 160;
//            texter4.MT_Texter.setPosition(CharPos);
//            //texter4.setSlide(20, MasterText::S, 160);
//            texter4.setFrameWait(3);
//            texter4.MT_Texter.setFillColor(sf::Color::Red);
//            texter4.SetText("Special Entity", 1, 3);
//            Clocker.restart();
//            Statuser++;
//        }
//        break;
//    case 30:
//        FadeIn(&Boxy4 ,250 ,3);
//
//        FadeOut(&Boxy ,4 ,.6);
//        if (Clocker.getElapsedTime().asSeconds() > 2.5)
//            Statuser++;
//            break;
//    case 31:
//        {
//            Boxy.E_Sprite.setColor(sf::Color::Transparent);
//            sf::Vector2f CharPos = texter3.MT_Texter.findCharacterPos(19);
//            //CharPos.y += 160;
//            texter5.MT_Texter.setPosition(CharPos);
//            texter4.setFrameWait(1);
//            texter5.MT_Texter.setFillColor(sf::Color::White);
//            texter5.SetText("\nwas found", 1, 3);
//            Clocker.restart();
//            Statuser++;
//            ///sf::tex
//        }
//        break;
//    case 32:
//        if (Clocker.getElapsedTime().asSeconds() > 1.4)
//            Statuser++;
//        break;
//
//    case 33:
//        {
//            sf::Color color(Boxy.E_Sprite.getColor());
//            for (auto & PointText : TextPointer)
//                PointText -> setOutFade(1, 125);
//            for (auto & PointBox : BoxPointers)
//                FadeOut(PointBox , 6 ,.6);
//            Statuser++;
//            Clocker.restart();
//        }
//        break;
//    case 34:
//        {
//            FadeOut(&Boxy4 , 6 ,.9);
//            if (Clocker.getElapsedTime().asSeconds() > 3.4)
//                Statuser++;
//            break;
//        }
//    case 35:
//        {
//            sf::Sprite joey((Res_Texture.get(Textures::Introduction7)));
//            joey.setScale(Movey(sf::Vector2f(1, 1)));
//            Boxy.E_Sprite = joey;
//            for (auto & PointText : TextPointer)
//                PointText ->Restart();
//            for (auto & BoxPoint : BoxPointers)
//            {
//                BoxPoint -> E_Sprite = joey;
//                BoxPoint -> E_Sprite.setColor(sf::Color(255, 255, 255, 0));
//            }
//            Boxy.E_Sprite.setColor(sf::Color(255, 255, 255, 0));
//            Boxy3.E_Sprite.setTextureRect(sf::IntRect( 2 , 92, 222, 154));
//            Boxy4.E_Sprite.setTextureRect(sf::IntRect( 223 , 100, 150, 99));
//            Boxy.E_Sprite.setTextureRect(sf::IntRect( 0 , 251, 293, 83));
//            Boxy2.E_Sprite.setTextureRect(sf::IntRect( 0 , 0, 384, 100));
//
//            Boxy3.E_Rect.setPosition(Movey(sf::Vector2f(289, 200)));
//            Boxy4.E_Rect.setPosition(Movey(sf::Vector2f(325, 150)));
//            Boxy.E_Rect.setPosition(Movey(sf::Vector2f(254, 120)));
//            Boxy2.E_Rect.setPosition(Movey(sf::Vector2f(208, 62)));
//            Statuser++;
//            break;
//        }
//    case 36:
//        {
//            texter.Restart();
//            texter.SetText("And through the aid of the entity, the last few \nhumans will able to persist and repopulate", 1 , 3);
//            Clocker.restart();
//            Statuser++;
//            break;
//        }
//    case 37:
//        {
//
//            if (Clocker.getElapsedTime().asSeconds() > 1.2)
//            {
//                Statuser++;
//                Clocker.restart();
//            }
//            break;
//        }
//    case 38:
//        {
//            FadeIn(&Boxy3 , 250 ,4);
//            if (Clocker.getElapsedTime().asSeconds() > .6)
//            {
//                Statuser++;
//                Clocker.restart();
//            }
//            break;
//        }
//    case 39:
//        {
//            FadeIn(&Boxy4 , 250 ,2);
//            if (Clocker.getElapsedTime().asSeconds() > 1.2)
//            {
//                Statuser++;
//                Clocker.restart();
//            }
//            break;
//        }
//    case 40:
//        {
//            FadeIn(&Boxy , 250 ,2);
//            if (Clocker.getElapsedTime().asSeconds() > 1.2)
//            {
//                Statuser++;
//                Clocker.restart();
//            }
//            break;
//        }
//    case 41:
//        {
//            FadeIn(&Boxy2 , 250 ,2);
//            if (Clocker.getElapsedTime().asSeconds() > 1.2)
//            {
//                Statuser++;
//                Clocker.restart();
//                texter.setOutFade(1, 125);
//            }
//            break;
//        }
//    case 42:
//        {
//            sf::Color color(Boxy.E_Sprite.getColor());
//
//            bool pass = true;
//            bool unpass = false;
//            FadeOut(&Boxy ,2 , 1);
//            for (auto & BoxPoint : BoxPointers)
//            {
//                pass = FadeOut(BoxPoint ,2 , 1);
//                if (!pass)
//                    unpass = true;
//            }
//            if (pass && !unpass)
//            {
//                for (auto & BoxPoint : BoxPointers)
//                    BoxPoint -> E_Sprite.setColor(sf::Color(255, 255 , 255, 0));
//                Statuser++;
//            }
//            break;
//        }
//    case 43:
//        {
//            sf::Sprite joey((Res_Texture.get(Textures::Introduction8)));
//            joey.setScale(Movey(sf::Vector2f(1, 1)));
//            Boxy.E_Sprite = joey;
//            Boxy.E_Sprite.setColor(sf::Color(255, 255 , 255, 0));
//            Boxy.E_Rect.setPosition(Movey(sf::Vector2f(200, 50)));
//        }
//    case 44:
//        {
//            texter.Restart();
//            texter.SetText("The humans were returning to their normal status \nand their future became brighter each day", 1 , 3);
//            Clocker.restart();
//            Statuser++;
//            break;
//        }
//    case 45:
//        {
//            FadeIn(&Boxy , 250 ,2);
//            if (texter.StringFinished)
//            {
//                Statuser++;
//                Clocker.restart();
//            }
//            break;
//        }
//    case 46:
//        {
//            if (Clocker.getElapsedTime().asSeconds() > 1.2)
//            {
//                Statuser++;
//                Clocker.restart();
//                texter.setOutFade(1, 125);
//            }
//            break;
//        }
//    case 47:
//        {
//            if (FadeOut(&Boxy ,2 , 1))
//            {
//                Statuser++;
//                Clocker.restart();
//            }
//            break;
//        }
//    case 48:
//        {
//            texter.Restart();
//            Boxy.E_Sprite.setColor(sf::Color(255, 255, 255, 0));
//            sf::Color colorer = texter.MT_Texter.getFillColor();
//
//            colorer.b -= 75;
//            colorer.g -= 75;
//
//            texter.MT_Texter.setFillColor(colorer);
//            texter.SetText("Until one day,  they all disappeared without a trace", 1 , 6);
//            Statuser++;
//            break;
//        }
//    case 49:
//        {
//        }
//    }
//}
//void Introduction::MouseCalculation()
//{0;}
//void Introduction::RemoveFalsers()
//{0;}
//
