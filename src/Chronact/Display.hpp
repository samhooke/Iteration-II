#ifndef DISPLAY_HPP_INCLUDED
#define DISPLAY_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#define DISPLAY_WIDTH_MAX 80
#define DISPLAY_HEIGHT_MAX 40

class Display {
private:
    int width;
    int height;
    char tile[DISPLAY_WIDTH_MAX][DISPLAY_HEIGHT_MAX];
    sf::Texture tileSet;
    sf::Sprite testSprite;
public:
    Display(int w, int h);
    ~Display();

    void Render(sf::RenderWindow* window);
};

#endif // DISPLAY_HPP_INCLUDED
