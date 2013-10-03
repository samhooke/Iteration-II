#ifndef TEXTUREMANAGER_HPP_INCLUDED
#define TEXTUREMANAGER_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

class TextureManager {
private:
    std::vector<sf::Texture> textureList;

public:
    TextureManager();
    ~TextureManager();

    void Add(sf::Texture& tex);
    sf::Texture& Get(int index);
    void Remove(int index);
};

#endif // TEXTUREMANAGER_HPP_INCLUDED
