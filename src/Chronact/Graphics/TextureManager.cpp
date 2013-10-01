#include "TextureManager.hpp"

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

void TextureManager::AddTexture(sf::Texture& tex) {
    textureList.push_back(tex);
}

sf::Texture& TextureManager::GetTexture(int index) {
    return textureList[index];
}
