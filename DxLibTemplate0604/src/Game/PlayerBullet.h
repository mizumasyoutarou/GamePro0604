#pragma once

struct bulletData
{
    float x;
    float y;
    bool active;
};

const int maxBulletCount = 16;

class PlayerBullet
{
public:
    PlayerBullet();

    void Fire(float startX, float startY);
    void update();
    void draw() const;
    bool IsActive() const;
    void Deactivate();
    float GetX() const;
    float GetY() const;
    int GetSize() const;

private:
    bulletData data;
    int size;
};
