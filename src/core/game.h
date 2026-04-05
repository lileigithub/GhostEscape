#pragma once

#include "asset_store.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <random>

class Scene;
struct ImageTexture;

class Game
{
private:
    Scene *current_scene_ = nullptr;
    Scene *next_scene_ = nullptr;
    glm::vec2 screen_size_ = glm::vec2(0);
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    AssetStore *asset_store_ = nullptr;
    bool is_running_ = true;
    Uint64 FPS_ = 60;
    Uint64 frame_time_ = 0; // 每帧的时间间隔, 单位为纳秒
    float dt_ = 0;          // 每帧的时间间隔, 单位为秒
    Uint64 last_time_ns_ = 0;
    int score_ = 0;
    int high_score_ = 0;
    std::mt19937 gen = std::mt19937(std::random_device{}());
    TTF_TextEngine *ttf_engine_ = nullptr; // TTF字体引擎

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
    void setIsRunning(bool is_running) { is_running_ = is_running; }

    TTF_Text *createTTF_Text(const std::string &text, const std::string &fontPath, int fontSize);

    glm::vec2 getMousePos();
    glm::vec2 getMouseScreenPos();
    int getScore() { return score_; }
    void setScore(int score) { score_ = score; if (score > high_score_) high_score_ = score; }
    int getHighScore() { return high_score_; }

    void drawGrid(glm::vec2 left_top, glm::vec2 right_bottom, glm::vec2 cell_size, SDL_FColor color);
    void drawRect(SDL_FRect rect, SDL_FColor color);
    void renderFillCircle(const std::string &texture_name, glm::vec2 pos, glm::vec2 size, float alpha);
    void renderTexture(ImageTexture *imageTexture, glm::vec2 pos, glm::vec2 size, glm::vec2 mask = glm::vec2(1.0f, 1.0f));
    void drawBoundary(const glm::vec2 &top_left, const glm::vec2 &botton_right, float boundary_width, SDL_FColor fcolor);
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen); }
    glm::vec2 randomVec2(glm::vec2 min, glm::vec2 max) { return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y)); }
    bool checkPointInRect(const glm::vec2 &point, const glm::vec2 &top_left, const glm::vec2 &bottom_right);
    void changeScene(Scene *scene) { next_scene_ = scene; }
    std::string loadTextFile(const std::string &path);

    void playMusic(const std::string &music_path, int loop = true) {Mix_PlayMusic(asset_store_->getMusic(music_path), loop ? -1 : 0);};
    void playChunk(const std::string &sound_path) { Mix_PlayChannel(-1, asset_store_->getChunk(sound_path), 0); };
    void stopMusic() { Mix_HaltMusic(); };
    void stopChunk() { Mix_HaltChannel(-1); };
    void pauseMusic() { Mix_PauseMusic(); };
    void resumeMusic() { Mix_ResumeMusic(); };
    void pauseChunk() { Mix_Pause(-1); };
    void resumeChunk() { Mix_Resume(-1); };
};
