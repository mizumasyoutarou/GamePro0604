#include "PlayerBullet.h"

#include <DxLib.h>

const int PLAYER_BULLET_SPEED = 12;

PlayerBullet::PlayerBullet()
    : data{0.0f, 0.0f, false}
    , size(8)
{
}

void PlayerBullet::Fire(float startX, float startY)
{
    data.x = startX;
    data.y = startY;
    data.active = true;
}

void PlayerBullet::update()
{
    if (!data.active)
    {
        return;
    }

    data.y -= static_cast<float>(PLAYER_BULLET_SPEED);
    if (data.y < -static_cast<float>(size))
    {
        data.active = false;
    }
}

void PlayerBullet::draw() const
{
    if (!data.active)
    {
        return;
    }

    DrawCircle(static_cast<int>(data.x), static_cast<int>(data.y), size, GetColor(64, 220, 255), TRUE);
}

bool PlayerBullet::IsActive() const
{
    return data.active;
}

void PlayerBullet::Deactivate()
{
    data.active = false;
}

float PlayerBullet::GetX() const
{
    return data.x;
}

float PlayerBullet::GetY() const
{
    return data.y;
}

int PlayerBullet::GetSize() const
{
    return size;
}
