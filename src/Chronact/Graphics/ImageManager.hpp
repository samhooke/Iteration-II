#ifndef IMAGEMANAGER_HPP_INCLUDED
#define IMAGEMANAGER_HPP_INCLUDED

#include <vector>
#include <SFML\Graphics.hpp>

class ImageManager {
private:
    std::vector<sf::Image> imageList;

public:
    ImageManager();
    ~ImageManager();

    void AddImage(sf::Image& image);
    sf::Image& GetImage(int index);
};

#endif // IMAGEMANAGER_HPP_INCLUDED
