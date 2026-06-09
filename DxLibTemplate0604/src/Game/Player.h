#pragma once

#include "PlayerBullet.h"

class Player
{
public:
    Player();

    void Init();
    void update(PlayerBullet bullets[], int bulletCount);
    void draw() const;
    void Damage(int amount);
    bool IsAlive() const;
    float GetX() const;
    float GetY() const;
    int GetSize() const;
    float* GetXAddress();

private:
    float m_x;
    float m_y;
    int hp;
    float speed;
    int m_Size;
    int fireCoolDown;
    int* m_lastDamage;

    void fireBullet(PlayerBullet bullets[], int bulletCount);
};
