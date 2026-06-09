#pragma once

enum enemyState
{
    enemyIdle,
    enemyFlying
};

const int enemy_bullet_speed = 5;

class EnemyBullet
{
public:
    EnemyBullet();

    void Fire(float startX, float startY);
    void update();
    void draw() const;
    bool IsActive() const;
    void Deactivate();
    float GetX() const;
    float GetY() const;
    int GetSize() const;
    void SetTarget(float* playerX);

private:
    float x;
    float y;
    bool active;
    int size;
    float* targetX;
    enemyState state;
};
