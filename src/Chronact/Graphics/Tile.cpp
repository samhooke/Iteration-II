#include "Tile.hpp"

Tile::Tile(sf::Texture& tex) {
    baseSprite.setTexture(tex, true);
}

Tile::~Tile() {
}

void Tile::Draw(int x, int y, sf::RenderWindow* rw) {
    baseSprite.setPosition(x, y);
    rw->draw(baseSprite);
}
