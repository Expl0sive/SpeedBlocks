#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

class textures {
public:
	sf::Texture tileTexture;
	sf::Sprite tile[16];

	sf::Texture fieldBackgroundTexture;
    sf::Sprite fieldBackground;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    sf::Image* icon;

    sf::Font typewriter, printFont;

    sf::String loadTextures();
};

#endif
