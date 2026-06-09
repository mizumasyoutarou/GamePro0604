#include "GameScene2D.h"

#include "../Input/InputManager.h"
#include "SceneManager.h"

#include <DxLib.h>

static bool IsHit(float ax, float ay, int aw, float bx, float by, int bw)
{
    return ax < bx + bw && ax + aw > bx && ay < by + bw && ay + aw > by;
}

GameScene2D::GameScene2D(SceneManager* sceneManager)
    : BaseScene(sceneManager)
    , score_(0)
    , enemy2HpMirror_(0)
{
}

GameScene2D::~GameScene2D() = default;

void GameScene2D::Init()
{
    score_ = 0;
    enemy2HpMirror_ = 4;

    player_.Init();
    enemy1_.Init(210.0f, 80.0f);
    enemy2_.Init(850.0f, 120.0f);
    enemy2_.SetExternalHp(&enemy2HpMirror_);

    for (int i = 0; i < maxBulletCount; ++i)
    {
        playerBullets_[i].Deactivate();
    }

    for (int i = 0; i < static_cast<int>(enemyBullets_.size()); ++i)
    {
        enemyBullets_[i].Deactivate();
        enemyBullets_[i].SetTarget(player_.GetXAddress());
    }
}

void GameScene2D::Update()
{
    player_.update(playerBullets_.data(), static_cast<int>(playerBullets_.size()));
    enemy1_.update(enemyBullets_.data(), static_cast<int>(enemyBullets_.size()));
    enemy2_.update(enemyBullets_.data(), static_cast<int>(enemyBullets_.size()));

    for (int i = 0; i < static_cast<int>(playerBullets_.size()); ++i)
    {
        playerBullets_[i].update();
    }

    for (int i = 0; i < static_cast<int>(enemyBullets_.size()); ++i)
    {
        enemyBullets_[i].update();
    }

    for (int i = 0; i < static_cast<int>(playerBullets_.size()); ++i)
    {
        if (!playerBullets_[i].IsActive())
        {
            continue;
        }

        if (enemy1_.IsAlive() && IsHit(
            playerBullets_[i].GetX(),
            playerBullets_[i].GetY(),
            playerBullets_[i].GetSize(),
            enemy1_.GetX(),
            enemy1_.GetY(),
            enemy1_.GetSize()))
        {
            enemy1_.Damage(1);
            playerBullets_[i].Deactivate();
            score_ += 10;
        }

        if (enemy2_.IsAlive() && playerBullets_[i].IsActive() && IsHit(
            playerBullets_[i].GetX(),
            playerBullets_[i].GetY(),
            playerBullets_[i].GetSize(),
            enemy2_.GetX(),
            enemy2_.GetY(),
            enemy2_.GetSize()))
        {
            enemy2_.Damage(1);
            playerBullets_[i].Deactivate();
            score_ += 20;
        }
    }

    for (int i = 0; i < static_cast<int>(enemyBullets_.size()); ++i)
    {
        if (enemyBullets_[i].IsActive() && player_.IsAlive() && IsHit(
            enemyBullets_[i].GetX(),
            enemyBullets_[i].GetY(),
            enemyBullets_[i].GetSize(),
            player_.GetX(),
            player_.GetY(),
            player_.GetSize()))
        {
            player_.Damage(1);
            enemyBullets_[i].Deactivate();
        }
    }

    if (InputManager::GetInstance().IsKeyPressed(KEY_INPUT_RETURN))
    {
        sceneManager_->ChangeScene(SceneID::Result);
    }
}

void GameScene2D::Draw()
{
    DrawString(10, 10, "Arrow keys: move  Space/Z: shot  Enter: result", GetColor(255, 255, 255));
    DrawFormatString(10, 58, GetColor(255, 255, 255), "Score: %d", score_);

    enemy1_.draw();
    enemy2_.draw();

    for (int i = 0; i < static_cast<int>(playerBullets_.size()); ++i)
    {
        playerBullets_[i].draw();
    }

    for (int i = 0; i < static_cast<int>(enemyBullets_.size()); ++i)
    {
        enemyBullets_[i].draw();
    }

    player_.draw();

    if (!player_.IsAlive())
    {
        DrawString(560, 350, "PLAYER DOWN", GetColor(255, 64, 64));
    }
}