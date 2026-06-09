#include "EnemyBullet.h"

#include <DxLib.h>

EnemyBullet::EnemyBullet()
    : x(0.0f)
    , y(0.0f)
    , active(false)
    , size(10)
    , targetX(nullptr)
    , state(enemyIdle)
{
}

void EnemyBullet::Fire(float startX, float startY)
{
    x = startX;
    y = startY;
    active = true;
    state = enemyFlying;
}

void EnemyBullet::update()
{
    if (!active)
    {
        return;
    }

    if (targetX != nullptr && *targetX > x)
    {
        x += 0.4f;
    }
    else if (targetX != nullptr && *targetX < x)
    {
        x -= 0.4f;
    }

    y += static_cast<float>(enemy_bullet_speed);
    if (y > 740.0f)
    {
        active = false;
        state = enemyIdle;
    }
}

void EnemyBullet::draw() const
{
    if (!active)
    {
        return;
    }

    DrawCircle(static_cast<int>(x), static_cast<int>(y), size, GetColor(255, 180, 64), TRUE);
}

bool EnemyBullet::IsActive() const
{
    return active;
}

void EnemyBullet::Deactivate()
{
    active = false;
    state = enemyIdle;
}

float EnemyBullet::GetX() const
{
    return x;
}

float EnemyBullet::GetY() const
{
    return y;
}

int EnemyBullet::GetSize() const
{
    return size;
}

void EnemyBullet::SetTarget(float* playerX)
{
    targetX = playerX;
}
