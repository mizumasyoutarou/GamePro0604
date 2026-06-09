#pragma once

#include "EnemyBullet.h"

class Enemy1
{
public:
    Enemy1();

    void Init(float startX, float startY);
    void update(EnemyBullet bullets[], int bulletCount);
    void draw() const;
    void Damage(int amount);
    bool IsAlive() const;
    float GetX() const;
    float GetY() const;
    int GetSize() const;

private:
    float x;
    float y;
    float moveSpeed;
    int m_Hp;
    int size;
    int fireTimer;
    int* unsafeCounter;

    void shootBullet(EnemyBullet bullets[], int bulletCount);
};
