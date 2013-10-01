#ifndef TILE_HPP_INCLUDED
#define TILE_HPP_INCLUDED

#include <SFML\Graphics.hpp>

class Tile {
private:
    sf::Sprite baseSprite;

public:
    Tile(sf::Texture& texture);
    ~Tile();

    void Draw(int x, int y, sf::RenderWindow* rw);
};

#endif // TILE_HPP_INCLUDED
