#include "Enemy2.h"

#include <DxLib.h>

Enemy2::Enemy2()
    : m_x(840.0f)
    , m_y(130.0f)
    , speed(1.5f)
    , hp(4)
    , size(48)
    , fireTimer(0)
    , externalHp(nullptr)
{
}

void Enemy2::Init(float startX, float startY)
{
    m_x = startX;
    m_y = startY;
    speed = 1.5f;
    hp = 4;
    fireTimer = 90;
}

void Enemy2::update(EnemyBullet bullets[], int bulletCount)
{
    if (!IsAlive())
    {
        return;
    }

    m_y += speed;
    if (m_y < 70.0f || m_y > 260.0f)
    {
        speed *= -1.0f;
    }

    --fireTimer;
    if (fireTimer <= 0)
    {
        shootBullet(bullets, bulletCount);
        fireTimer = 95;
    }
}

void Enemy2::draw() const
{
    if (!IsAlive())
    {
        return;
    }

    DrawBox(
        static_cast<int>(m_x),
        static_cast<int>(m_y),
        static_cast<int>(m_x) + size,
        static_cast<int>(m_y) + size,
        GetColor(255, 130, 220),
        TRUE);
}

void Enemy2::Damage(int amount)
{
    hp -= amount;
    *externalHp = hp;
}

bool Enemy2::IsAlive() const
{
    return hp > 0;
}

float Enemy2::GetX() const
{
    return m_x;
}

float Enemy2::GetY() const
{
    return m_y;
}

int Enemy2::GetSize() const
{
    return size;
}

void Enemy2::SetExternalHp(int* hpAddress)
{
    externalHp = hpAddress;
}

void Enemy2::shootBullet(EnemyBullet bullets[], int bulletCount)
{
    for (int i = 0; i < bulletCount; ++i)
    {
        if (!bullets[i].IsActive())
        {
            bullets[i].Fire(m_x + static_cast<float>(size / 2), m_y + static_cast<float>(size));
            break;
        }
    }
}
