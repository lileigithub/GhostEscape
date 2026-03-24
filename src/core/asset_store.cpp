#include "asset_store.h"

void AssetStore::loadImmage(const std::string &path)
{
    SDL_Texture *image = IMG_LoadTexture(renderer_, path.c_str());
    if (image == nullptr)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", SDL_GetError);
        return;
    }
    imageMap_.emplace(path, image);
}

void AssetStore::loadMusic(const std::string &path)
{
    Mix_Music *music = Mix_LoadMUS(path.c_str());
    if (music == nullptr)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s", SDL_GetError);
        return;
    }
    musicMap_.emplace(path, music);
}

void AssetStore::loadChunk(const std::string &path)
{
    Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
    if (chunk == nullptr)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to load chunk: %s", SDL_GetError);
        return;
    }
    chunkMap_.emplace(path, chunk);
}

void AssetStore::loadFont(const std::string &path, float size)
{
    TTF_Font *font = TTF_OpenFont(path.c_str(), size);
    if (font == nullptr)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", SDL_GetError);
        return;
    }
    fontMap_.emplace(path + std::to_string(size), font);
}

SDL_Texture *AssetStore::getImmage(const std::string &path)
{
    auto it = imageMap_.find(path);
    if (it == imageMap_.end())
    {
        loadImmage(path);
        it = imageMap_.find(path);
        if (it == imageMap_.end())
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", SDL_GetError);
            return nullptr;
        }
    }
    return it->second;
}

Mix_Music *AssetStore::getMusic(const std::string &path)
{
    auto it = musicMap_.find(path);
    if (it == musicMap_.end())
    {
        loadMusic(path);
        it = musicMap_.find(path);
        if (it == musicMap_.end())
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to load music: %s", SDL_GetError);
            return nullptr;
        }
    }
    return it->second;
}

Mix_Chunk *AssetStore::getChunk(const std::string &path)
{
    auto it = chunkMap_.find(path);
    if (it == chunkMap_.end())
    {
        loadChunk(path);
        it = chunkMap_.find(path);
        if (it == chunkMap_.end())
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to load chunk: %s", SDL_GetError);
            return nullptr;
        }
    }
    return it->second;
}

TTF_Font *AssetStore::getFont(const std::string &path, float size)
{
    auto it = fontMap_.find(path + std::to_string(size));
    if (it == fontMap_.end())
    {
        loadFont(path, size);
        it = fontMap_.find(path + std::to_string(size));
        if (it == fontMap_.end())
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", SDL_GetError);
            return nullptr;
        }
    }
    return it->second;
}

void AssetStore::clean()
{
    for (auto it : imageMap_)
    {
        SDL_DestroyTexture(it.second);
    }
    imageMap_.clear();

    for (auto it : musicMap_)
    {
        Mix_FreeMusic(it.second);
    }
    musicMap_.clear();

    for (auto it : chunkMap_)
    {
        Mix_FreeChunk(it.second);
    }
    chunkMap_.clear();

    for (auto it : fontMap_)
    {
        TTF_CloseFont(it.second);
    }
    fontMap_.clear();
}
