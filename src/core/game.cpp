#include "game.h"
#include "../affiliates/sprite.h"
#include "../scene_main.h"

void Game::init()
{
    screen_size_ = {1280, 720};
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

    SDL_CreateWindowAndRenderer("GhostEscape", static_cast<int>(screen_size_.x),
                                static_cast<int>(screen_size_.y), SDL_WINDOW_RESIZABLE, &window_, &renderer_);
    SDL_HideCursor();
    
    if (!window_ || !renderer_)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
        return;
    }
    SDL_SetRenderLogicalPresentation(renderer_, static_cast<int>(screen_size_.x), static_cast<int>(screen_size_.y), SDL_LOGICAL_PRESENTATION_LETTERBOX);

    asset_store_ = new AssetStore(renderer_);

    frame_time_ = 1000000000 / FPS_;

    current_scene_ = new SceneMain();
    current_scene_->init();
}

void Game::clean()
{
    asset_store_->clean();
    delete asset_store_;
    current_scene_->clean();
    delete current_scene_;
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
        last_time_ns_ = SDL_GetTicksNS();

        handleEvents();
        update(dt_);
        render();

        auto diff = SDL_GetTicksNS() - last_time_ns_;
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
        if (dt_ > 0.1f)
        {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Warning: Large dt detected: %f seconds.", dt_);
            dt_ = 0.1f; // 防止dt过大导致游戏逻辑异常，比如玩家瞬移等
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
        case SDL_EVENT_WINDOW_EXPOSED:
        case SDL_EVENT_WINDOW_MOVED:
            last_time_ns_ = SDL_GetTicksNS();
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

void Game::drawGrid(const glm::vec2 left_top_pos, const glm::vec2 right_bottom_pos, glm::vec2 cell_size, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    for (float x = left_top_pos.x; x <= right_bottom_pos.x; x += cell_size.x)
    {
        if (x >= 0 && x <= screen_size_.x) // 只画屏幕内的线
        {
            SDL_RenderLine(renderer_, x, (left_top_pos.y < 0 ? 0 : left_top_pos.y),
                           x, (screen_size_.y < right_bottom_pos.y ? screen_size_.y : right_bottom_pos.y));
        }
    }
    for (float y = left_top_pos.y; y <= right_bottom_pos.y; y += cell_size.y)
    {
        if (y >= 0 && y <= screen_size_.y)
        {
            SDL_RenderLine(renderer_, (right_bottom_pos.x < 0 ? 0 : left_top_pos.x),
                           y, (screen_size_.x < right_bottom_pos.x ? screen_size_.x : right_bottom_pos.x), y);
        }
    }
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f);
}

void Game::drawRect(SDL_FRect rect, SDL_FColor color)
{
    SDL_SetRenderDrawColorFloat(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer_, &rect);
    SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 0, 1.0f);
}

void Game::renderFillCircle(const std::string &path, glm::vec2 pos, glm::vec2 size, float alpha)
{
    auto texture = Game::getInstance().getAssetStore()->getImmage(path);
    SDL_FRect dest_rect{pos.x, pos.y, size.x, size.y};
    SDL_SetTextureAlphaModFloat(texture, alpha);
    SDL_RenderTexture(Game::getInstance().getRenderer(), texture, NULL, &dest_rect);
}

void Game::renderTexture(ImageTexture *imageTexture, glm::vec2 pos, glm::vec2 size)
{
    SDL_FRect dstrect{pos.x, pos.y, size.x, size.y};
    SDL_RenderTextureRotated(renderer_, imageTexture->texture, &imageTexture->src_rect,
                             &dstrect, imageTexture->angle, nullptr, imageTexture->flip_);
}
