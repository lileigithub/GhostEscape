#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include "asset_store.h"

class Scene;
struct ImageTexture;

class Game
{
private:
    Scene *current_scene_ = nullptr;
    glm::vec2 screen_size_ = glm::vec2(0);
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    AssetStore *asset_store_ = nullptr;
    bool is_running_ = true;
    Uint64 FPS_ = 60;
    Uint64 frame_time_ = 0; // 每帧的时间间隔, 单位为纳秒
    float dt_ = 0;          // 每帧的时间间隔, 单位为秒
    Uint64 last_time_ns_ = 0;

    Game() {};

    // 禁止拷贝构造函数
    Game(const Game &) = delete;
    // 禁止赋值操作符
    Game &operator=(const Game &) = delete;
    // 禁止移动构造函数
    Game(Game &&) = delete;
    // 禁止移动赋值操作符
    Game &operator=(Game &&) = delete;

public:
    ~Game() {};
    static Game &getInstance()
    {
        static Game instance;
        return instance;
    }

    void init();
    void run();
    void clean();

    void handleEvents();
    void update(float dt);
    void render();

    Scene *getCurrentScene() const { return current_scene_; }
    glm::vec2 getSceneSize() const { return screen_size_; }
    SDL_Renderer *getRenderer() const { return renderer_; }
    AssetStore *getAssetStore() const { return asset_store_; }

    void drawGrid(glm::vec2 left_top, glm::vec2 right_bottom, glm::vec2 cell_size, SDL_FColor color);
    void drawRect(SDL_FRect rect, SDL_FColor color);
    void renderFillCircle(const std::string &texture_name, glm::vec2 pos, glm::vec2 size, float alpha);
    void renderTexture(ImageTexture * imageTexture, glm::vec2 pos, glm::vec2 size);
};
