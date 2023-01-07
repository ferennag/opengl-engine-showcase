#ifndef ENGINE_SHOWCASE_TEXTUREMANAGER_H
#define ENGINE_SHOWCASE_TEXTUREMANAGER_H

#include <memory>
#include <map>
#include <string>
#include <string_view>
#include <QOpenGLTexture>


class TextureManager {
public:
    TextureManager(const TextureManager& other) = delete;
    TextureManager& operator=(const TextureManager& other) = delete;
    ~TextureManager() = default;

    static TextureManager& getInstance();

    void loadTexture(std::string_view name, std::string_view path);
    QOpenGLTexture& getTexture(std::string_view name) const;
    void cleanup();
private:
    static std::unique_ptr<TextureManager> s_textureManager;
    std::map<std::string, std::unique_ptr<QOpenGLTexture>> m_cache;

    TextureManager() = default;
};


#endif //ENGINE_SHOWCASE_TEXTUREMANAGER_H
