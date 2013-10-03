#include "TextureManager.hpp"
#include "../Logger.hpp"

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

void TextureManager::Add(sf::Texture& tex) {
    textureList.push_back(tex);
}

sf::Texture& TextureManager::Get(int index) {
    return textureList[index];
}

void TextureManager::Remove(int index) {
    if (index < textureList.size())
        textureList.erase(textureList.begin() + index);
    else
        LogWarning("TextureManager::Remove() Attempted to erase a texture that does not exist.");
}
