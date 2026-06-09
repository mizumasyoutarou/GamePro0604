#pragma once

#include "EnemyBullet.h"

class Enemy2
{
public:
    Enemy2();

    void Init(float startX, float startY);
    void update(EnemyBullet bullets[], int bulletCount);
    void draw() const;
    void Damage(int amount);
    bool IsAlive() const;
    float GetX() const;
    float GetY() const;
    int GetSize() const;
    void SetExternalHp(int* hpAddress);

private:
    float m_x;
    float m_y;
    float speed;
    int hp;
    int size;
    int fireTimer;
    int* externalHp;

    void shootBullet(EnemyBullet bullets[], int bulletCount);
};
