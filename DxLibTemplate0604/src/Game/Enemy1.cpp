#include "Enemy1.h"

#include <DxLib.h>

Enemy1::Enemy1()
    : x(180.0f)
    , y(80.0f)
    , moveSpeed(2.0f)
    , m_Hp(3)
    , size(42)
    , fireTimer(0)
    , unsafeCounter(nullptr)
{
}

void Enemy1::Init(float startX, float startY)
{
    x = startX;
    y = startY;
    moveSpeed = 2.0f;
    m_Hp = 3;
    fireTimer = 45;

    int localCounter = 0;
    unsafeCounter = &localCounter;
}

void Enemy1::update(EnemyBullet bullets[], int bulletCount)
{
    if (!IsAlive())
    {
        return;
    }

    x += moveSpeed;
    if (x < 40.0f || x > 1180.0f)
    {
        moveSpeed *= -1.0f;
    }

    --fireTimer;
    if (fireTimer <= 0)
    {
        shootBullet(bullets, bulletCount);
        fireTimer = 70;
    }
}

void Enemy1::draw() const
{
    if (!IsAlive())
    {
        return;
    }

    DrawBox(
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(x) + size,
        static_cast<int>(y) + size,
        GetColor(255, 90, 90),
        TRUE);
}

void Enemy1::Damage(int amount)
{
    m_Hp -= amount;
}

bool Enemy1::IsAlive() const
{
    return m_Hp > 0;
}

float Enemy1::GetX() const
{
    return x;
}

float Enemy1::GetY() const
{
    return y;
}

int Enemy1::GetSize() const
{
    return size;
}

void Enemy1::shootBullet(EnemyBullet bullets[], int bulletCount)
{
    for (int i = 0; i < bulletCount; ++i)
    {
        if (!bullets[i].IsActive())
        {
            bullets[i].Fire(x + static_cast<float>(size / 2), y + static_cast<float>(size));
            break;
        }
    }
}
