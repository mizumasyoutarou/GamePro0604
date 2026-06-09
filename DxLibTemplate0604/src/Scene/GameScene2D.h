#pragma once

#include "BaseScene.h"

#include "../Game/Enemy1.h"
#include "../Game/Enemy2.h"
#include "../Game/EnemyBullet.h"
#include "../Game/Player.h"
#include "../Game/PlayerBullet.h"

#include <array>

/**
 * @brief ゲーム本編を表すシーンクラスです。
 */
class GameScene2D : public BaseScene
{
public:
    /**
     * @brief ゲームシーンを生成します。
     * @param sceneManager シーン遷移を依頼する先のマネージャーです。
     * @return なし。
     */
    explicit GameScene2D(SceneManager* sceneManager);

    /**
     * @brief ゲームシーンを破棄します。
     * @return なし。
     */
    ~GameScene2D() override;

    /**
     * @brief ゲームシーンの初期化を行います。
     * @return なし。
     */
    void Init() override;

    /**
     * @brief ゲームシーンの更新処理を行います。
     * @return なし。
     */
    void Update() override;

    /**
     * @brief ゲームシーンの描画処理を行います。
     * @return なし。
     */
    void Draw() override;

private:
    Player player_;
    Enemy1 enemy1_;
    Enemy2 enemy2_;
    std::array<PlayerBullet, maxBulletCount> playerBullets_;
    std::array<EnemyBullet, 24> enemyBullets_;
    int score_;
    int enemy2HpMirror_;
};