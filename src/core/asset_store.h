#pragma once

#include <unordered_map>
#include <string>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

class AssetStore {
    SDL_Renderer* renderer_ = nullptr;
public:
    AssetStore(SDL_Renderer* renderer) : renderer_(renderer) {}
    ~AssetStore() = default;
    AssetStore(const AssetStore&) = delete;
    AssetStore& operator=(const AssetStore&) = delete;


    std::unordered_map<std::string, SDL_Texture*> imageMap_;
    std::unordered_map<std::string, Mix_Music*> musicMap_;
    std::unordered_map<std::string, Mix_Chunk*> chunkMap_;
    std::unordered_map<std::string, TTF_Font*> fontMap_;

    void loadImmage(const std::string& path);
    void loadMusic(const std::string& path);
    void loadChunk(const std::string& path);
    void loadFont(const std::string& path, float size);

    SDL_Texture* getImmage(const std::string& path);
    Mix_Music* getMusic(const std::string& path);
    Mix_Chunk* getChunk(const std::string& path);
    TTF_Font* getFont(const std::string& path, float size);

    void clean();
};