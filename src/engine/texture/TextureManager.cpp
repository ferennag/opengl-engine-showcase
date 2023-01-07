#include <memory>
#include <string>
#include <QImage>
#include <QOpenGLTexture>
#include "TextureManager.h"

std::unique_ptr<TextureManager> TextureManager::s_textureManager = nullptr;

TextureManager &TextureManager::getInstance() {
    if(!s_textureManager) {
        s_textureManager = std::unique_ptr<TextureManager>(new TextureManager());
    }

    return *s_textureManager;
}

void TextureManager::loadTexture(std::string_view name, std::string_view path) {
    auto image = QImage(path.data());
    auto texture = std::make_unique<QOpenGLTexture>(image.mirrored());
    texture->generateMipMaps();
    m_cache[name.data()] = std::move(texture);
}

QOpenGLTexture &TextureManager::getTexture(std::string_view name) const {
    return *(m_cache.find(name.data())->second);
}

void TextureManager::cleanup() {
    m_cache.clear();
}

