#pragma once

#include <unordered_map>
#include <string>
#include <texture.h>

class AssetManager {
    public:
    static AssetManager& getInstance() {
        static AssetManager instance;
        return instance;
    }
    void loadTexture(const std::string& name, const char *filepath,
                     GLenum texType = GL_TEXTURE_2D,
                     GLenum slot = GL_TEXTURE0,
                     GLenum format = GL_RGB,
                     GLenum pixelType = GL_UNSIGNED_BYTE) {
        if (m_textures.find(name) != m_textures.end()) {
            return;
        }
        Texture texture(filepath, texType, slot, format, pixelType);
        m_textures.emplace(name, std::move(texture));
    }

    Texture& getTexture(const std::string& name) {
        auto it = m_textures.find(name);
        if (it == m_textures.end()) {
            throw std::runtime_error("Texture not found: " + name);
        }
        return it->second;
    }
    void clear() {
        for (auto& pair : m_textures) {
            pair.second.clear();
        }
        m_textures.clear();
    }

    private:
    AssetManager() = default;
    ~AssetManager() = default;
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    std::unordered_map<std::string, Texture> m_textures;
};