#include "Bonus.h"
#include "GameState.h"
#include <algorithm>

void BonusPaddleGrow::activate(GameState& gs) {
    gs.paddle.resize(+BONUS_PADDLE_GROW);
}

void BonusPaddleShrink::activate(GameState& gs) {
    gs.paddle.resize(-BONUS_PADDLE_SHRINK);
}

void BonusSpeedUp::activate(GameState& gs) {
    for (auto& b : gs.balls)
        b.setSpeed(b.speed + BONUS_SPEED_DELTA);
}

void BonusSpeedDown::activate(GameState& gs) {
    for (auto& b : gs.balls)
        b.setSpeed(b.speed - BONUS_SPEED_DELTA);
}

void BonusSticky::activate(GameState& gs) {
    for (auto& b : gs.balls)
        b.sticky = true;
}

void BonusExtraBall::activate(GameState& gs) {
    if (gs.balls.empty()) return;
    const Ball& ref = gs.balls.front();
    Vec2 dir{-ref.vel.x, ref.vel.y};
    gs.balls.emplace_back(ref.pos, dir.normalized(), ref.speed);
}