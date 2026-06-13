#pragma once
#include "Vec2.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

class Paddle;
class Ball;
class GameState;

class Bonus {
public:
    Vec2 pos;
    bool active = true;

    explicit Bonus(Vec2 spawnPos) : pos(spawnPos) {}
    virtual ~Bonus() = default;

    virtual void activate(GameState& gs) = 0;
    virtual sf::Color color() const = 0;

    void update(float dt) { pos.y += BONUS_FALL_SPEED * dt; }

    sf::FloatRect bounds() const {
        return sf::FloatRect(
            {pos.x - BONUS_W / 2.f, pos.y - BONUS_H / 2.f},
            {BONUS_W, BONUS_H}
        );
    }

    void draw(sf::RenderWindow& win) const {
        sf::ConvexShape diamond;
        diamond.setPointCount(4);
        diamond.setPoint(0, {0.f,      -BONUS_H});
        diamond.setPoint(1, {BONUS_W,   0.f});
        diamond.setPoint(2, {0.f,       BONUS_H});
        diamond.setPoint(3, {-BONUS_W,  0.f});
        diamond.setOrigin({0.f, 0.f});
        diamond.setPosition({pos.x, pos.y});
        diamond.setFillColor(color());
        diamond.setOutlineColor(sf::Color(255, 255, 255, BONUS_OUTLINE_ALPHA));
        diamond.setOutlineThickness(BONUS_OUTLINE_T);
        win.draw(diamond);

        sf::CircleShape glare(BONUS_GLARE_R);
        glare.setOrigin({BONUS_GLARE_R, BONUS_GLARE_R});
        glare.setPosition({pos.x - BONUS_GLARE_OFFSET_X, pos.y - BONUS_GLARE_OFFSET_Y});
        glare.setFillColor(sf::Color(255, 255, 255, BONUS_GLARE_ALPHA));
        win.draw(glare);
    }
};

class BonusPaddleGrow final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return sf::Color(BONUS_GROW_R, BONUS_GROW_G, BONUS_GROW_B); }
};

class BonusPaddleShrink final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return sf::Color(BONUS_SHRINK_R, BONUS_SHRINK_G, BONUS_SHRINK_B); }
};

class BonusSpeedUp final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return sf::Color(BONUS_SUP_R, BONUS_SUP_G, BONUS_SUP_B); }
};

class BonusSpeedDown final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return sf::Color(BONUS_SDOWN_R, BONUS_SDOWN_G, BONUS_SDOWN_B); }
};

class BonusSticky final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return sf::Color(BONUS_STICKY_R, BONUS_STICKY_G, BONUS_STICKY_B); }
};

class BonusExtraBall final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return sf::Color(BONUS_EXTRA_R, BONUS_EXTRA_G, BONUS_EXTRA_B); }
};
