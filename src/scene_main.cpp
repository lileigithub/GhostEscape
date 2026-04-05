#include "scene_main.h"
#include "Enemy.h"
#include "player.h"
#include "scene_title.h"
#include "screen/ui_mouse.h"
#include "spawner.h"
#include "world/effect.h"
#include "world/spell.h"
void SceneMain::init()
{
    Scene::init();
    setWordSize(game_.getSceneSize() * 3.0f);

    button_pause_ = HUDButton::createHUDButtonAddChild(this, game_.getSceneSize() - glm::vec2(250.0f, 30.0f),
                                                       "assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    button_restart_ = HUDButton::createHUDButtonAddChild(this, game_.getSceneSize() - glm::vec2(150.0f, 30.0f),
                                                         "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    button_back_ = HUDButton::createHUDButtonAddChild(this, game_.getSceneSize() - glm::vec2(50.0f, 30.0f),
                                                      "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    player_ = new Player();
    player_->init();
    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setPlayer(player_);
    addChild(spawner_);
    addChild(player_); // 让玩家比敌人后渲染
    player_stats_hud_bar_ = HUDStats::createHUDStatsAddChild(this, player_, {30, 30});

    auto scorePos = glm::vec2{game_.getSceneSize().x - 120.0f, 30.0f};
    score_hud_text_ = HUDText::createHUDTextAddChild(this, "Score: 0", scorePos, glm::vec2(200.0f, 50.0f));

    ui_mouse_ = UI_Mouse::createUiMouseAddChild(this, "assets/UI/29.png", "assets/UI/30.png");
    game_.playMusic("assets/bgm/OhMyGhost.ogg", true);
}

bool SceneMain::handleEvents(SDL_Event &event)
{
    return Scene::handleEvents(event);
}

void SceneMain::update(float dt)
{
    // 摄像机跟随玩家，玩家位置在摄像机中心
    setCameraPos(player_->getPosition() - game_.getSceneSize() / 2.0f);
    Scene::update(dt);
    updateScoreText();
    updateButtonTriggers();
}

void SceneMain::render()
{
    drawBackground();
    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
    // 加入child里的，都由Scene清理了，这里不用管了
}

void SceneMain::drawBackground()
{
    // 世界坐标系下的物体 渲染在窗口中的坐标 = 世界坐标 - 摄像机坐标
    glm::vec2 word_left_top_pos_in_screen = -getCameraPos();
    glm::vec2 word_right_bottom_pos_screen = getWordSize() - getCameraPos();
    game_.drawGrid(word_left_top_pos_in_screen, word_right_bottom_pos_screen, {80, 80}, {0.5f, 0.5f, 0.5f, 1.0f});
}

void SceneMain::updateScoreText()
{
    score_hud_text_->setText("Score: " + std::to_string(game_.getScore()));
}

void SceneMain::updateButtonTriggers()
{
    if (button_pause_->getResetTrigger())
    {
        setIsPause(!getIsPause());
    }
    else if (button_restart_->getResetTrigger())
    {
        game_.changeScene(new SceneMain());
    }
    else if (button_back_->getResetTrigger())
    {
        game_.changeScene(new SceneTitle());
    }
}
