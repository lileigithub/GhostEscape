#include "Game.h"
#include "../SceneMain.h"

void Game::init()
{
    // SDL初始化
    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
        return;
    }
    // SDL_Mixer初始化
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_Init Error: %s", SDL_GetError());
        return;
    }
    if (!Mix_OpenAudio(0, NULL))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s", SDL_GetError());
        return;
    }
    Mix_AllocateChannels(16);            // 设置音频通道数
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音乐音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 4);  // 设置音效音量
    // TTF初始化
    if (!TTF_Init())
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init Error: %s", SDL_GetError);
        return;
    }

    screen_size_ = {800, 600};
    SDL_CreateWindowAndRenderer("GhostEscape", static_cast<int>(screen_size_.x),
                                static_cast<int>(screen_size_.y), SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    if (!window_ || !renderer_)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
        return;
    }
    frame_time_ = 1000000000 / FPS_;

    current_scene_ = new SceneMain();
    current_scene_->init();
}

void Game::clean()
{
    if (renderer_)
    {
        SDL_DestroyRenderer(renderer_);
    }
    if (window_)
    {
        SDL_DestroyWindow(window_);
    }

    TTF_Quit();

    Mix_CloseAudio();
    Mix_Quit();

    SDL_Quit();
}

void Game::run()
{
    while (is_running_)
    {
        auto startTimeNS = SDL_GetTicksNS();

        handleEvents();
        update(dt_);
        render();

        auto diff = SDL_GetTicksNS() - startTimeNS;

        // 控制帧率
        if (diff < frame_time_)
        {
            SDL_DelayNS(frame_time_ - diff);
            dt_ = frame_time_ / 1.0e9f;
        }
        else
        {
            dt_ = diff / 1.0e9f;
        }
    }
}

void Game::handleEvents()
{
    SDL_Event event_;
    if (SDL_PollEvent(&event_))
    {
        switch (event_.type)
        {
        case SDL_EVENT_QUIT:
            is_running_ = false;
            break;
        default:
            current_scene_->handleEvents(event_);
            break;
        }
    }
}

void Game::update(float)
{
    current_scene_->update(dt_);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
    current_scene_->render();
    SDL_RenderPresent(renderer_);
}
