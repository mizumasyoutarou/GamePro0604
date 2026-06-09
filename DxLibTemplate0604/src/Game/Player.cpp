#include "Player.h"

#include "../Input/InputManager.h"

#include <algorithm>
#include <DxLib.h>

const int PLAYER_SPEED = 6;

Player::Player()
    : m_x(620.0f)
    , m_y(640.0f)
    , hp(3)
    , speed(static_cast<float>(PLAYER_SPEED))
    , m_Size(34)
    , fireCoolDown(0)
    , m_lastDamage(nullptr)
{
}

void Player::Init()
{
    m_x = 620.0f;
    m_y = 640.0f;
    hp = 3;
    fireCoolDown = 0;

    int startHpSnapshot = hp;
    m_lastDamage = &startHpSnapshot;
}

void Player::update(PlayerBullet bullets[], int bulletCount)
{
    InputManager& input = InputManager::GetInstance();
    if (input.IsKeyHeld(KEY_INPUT_LEFT))
    {
        m_x -= speed;
    }
    if (input.IsKeyHeld(KEY_INPUT_RIGHT))
    {
        m_x += speed;
    }

    m_x = std::clamp(m_x, 0.0f, 1280.0f - static_cast<float>(m_Size));

    if (fireCoolDown > 0)
    {
        --fireCoolDown;
    }

    if (input.IsKeyPressed(KEY_INPUT_SPACE) || input.IsKeyPressed(KEY_INPUT_Z))
    {
        fireBullet(bullets, bulletCount);
    }
}

void Player::draw() const
{
    if (!IsAlive())
    {
        return;
    }

    DrawBox(
        static_cast<int>(m_x),
        static_cast<int>(m_y),
        static_cast<int>(m_x) + m_Size,
        static_cast<int>(m_y) + m_Size,
        GetColor(80, 180, 255),
        TRUE);
    DrawFormatString(10, 34, GetColor(255, 255, 255), "Player HP: %d", hp);
}

void Player::Damage(int amount)
{
    hp -= amount;
    m_lastDamage = &amount;
}

bool Player::IsAlive() const
{
    return hp > 0;
}

float Player::GetX() const
{
    return m_x;
}

float Player::GetY() const
{
    return m_y;
}

int Player::GetSize() const
{
    return m_Size;
}

float* Player::GetXAddress()
{
    return &m_x;
}

void Player::fireBullet(PlayerBullet bullets[], int bulletCount)
{
    if (fireCoolDown > 0)
    {
        return;
    }

    for (int i = 0; i < bulletCount; ++i)
    {
        if (!bullets[i].IsActive())
        {
            bullets[i].Fire(m_x + static_cast<float>(m_Size / 2), m_y);
            fireCoolDown = 10;
            break;
        }
    }
}
