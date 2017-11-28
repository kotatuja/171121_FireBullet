#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)               HW16A075  小梶 希望
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)                   HW16A076  小谷 将豊
// TODO: 砲台を青い壁に沿って上下に動かす。(C)                                     HW16A076  小谷 将豊
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)         HW16A005  有村 泉弥
// TODO: スコアのサイズを大きくする。(E)                                          HW16A005  有村 泉弥
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)                  　HW16A005  有村 泉弥
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)                                HW16A075  小梶 希望
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)    HW16A075  小梶 希望


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
float   vx_cloud = 30;
float   vy_cannon = 3;


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-300, -150);
    targetRect = Rect(270, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (( bulletPos.x >320 || bulletPos.x <= -999)  && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_system43.mp3");
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 50 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_explosion03.mp3");
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);
    
    // 雲の移動（HW16A076 小谷　将豊）
    cloudPos.x += 500 * Time::deltaTime;
        if(cloudPos.x > 320){
            cloudPos.x = -540;
        }

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    cannonPos.y += vy_cannon*5;
    if ( cannonPos.y > -60 ) {
        cannonPos.y = -60;
        vy_cannon *= -1;
    }
    if ( cannonPos.y < -150 ) {
        cannonPos.y = -150;
        vy_cannon *= -1;
    }

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 150.0f);
    DrawText(FormatString("%05d", score), Vector2(-319, 119), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-320, 120), Color::white);
}

