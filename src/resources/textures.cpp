#include "textures.h"
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#ifdef __APPLE__
#include "ResourcePath.hpp"
#else
#include "EmptyResourcePath.h"
#endif

sf::String textures::loadTextures() {
    if (!tileTexture.loadFromFile(resourcePath() + "media/tile.png"))
        return "media/tile.png";
    tileTexture.setSmooth(true);

    tile[0].setTexture(tileTexture); tile[0].setColor(sf::Color(255,0,0));
    tile[1].setTexture(tileTexture); tile[1].setColor(sf::Color(0,255,0));
    tile[2].setTexture(tileTexture); tile[2].setColor(sf::Color(115,145,255));
    tile[3].setTexture(tileTexture); tile[3].setColor(sf::Color(255,0,255));
    tile[4].setTexture(tileTexture); tile[4].setColor(sf::Color(0,255,255));
    tile[5].setTexture(tileTexture); tile[5].setColor(sf::Color(255,255,0));
    tile[6].setTexture(tileTexture); tile[6].setColor(sf::Color(255,255,255));
    tile[7].setTexture(tileTexture); tile[7].setColor(sf::Color(170,170,170));

    tile[8].setTexture(tileTexture); tile[8].setColor(sf::Color(255,0,0,120));
    tile[9].setTexture(tileTexture); tile[9].setColor(sf::Color(0,255,0,120));
    tile[10].setTexture(tileTexture); tile[10].setColor(sf::Color(115,145,255,120));
    tile[11].setTexture(tileTexture); tile[11].setColor(sf::Color(255,0,255,120));
    tile[12].setTexture(tileTexture); tile[12].setColor(sf::Color(0,255,255,120));
    tile[13].setTexture(tileTexture); tile[13].setColor(sf::Color(255,255,0,120));
    tile[14].setTexture(tileTexture); tile[14].setColor(sf::Color(255,255,255,120));
    tile[15].setTexture(tileTexture); tile[15].setColor(sf::Color(170,170,170,120));

    if (!fieldBackgroundTexture.loadFromFile(resourcePath() + "media/fieldback.png"))
        return "media/fieldback.png";
    fieldBackgroundTexture.setSmooth(true);

    fieldBackground.setTexture(fieldBackgroundTexture);

    if (!backgroundTexture.loadFromFile(resourcePath() + "media/background.png"))
        return "media/background.png";
    background.setTexture(backgroundTexture);

    if (!typewriter.loadFromFile(resourcePath() + "media/Kingthings Trypewriter 2.ttf"))
        return "media/Kingthings Trypewriter 2.ttf";
    if (!printFont.loadFromFile(resourcePath() + "media/F25_Bank_Printer.ttf"))
        return "media/F25_Bank_Printer.ttf";

    /*themeTG = tgui::Theme::create(resourcePath() + "media/TransparentGrey.txt");
    tgui::Label::Ptr test;
    try {
        test = themeTG->load("Label");
    } catch (tgui::Exception) {
        return "media/TransparentGrey.txt";
    }
    themeBB = tgui::Theme::create(resourcePath() + "media/BabyBlue.txt");
    try {
        test = themeBB->load("Label");
    } catch (tgui::Exception) {
        return "media/BabyBlue.txt";
    }*/
    
    return "OK";
}