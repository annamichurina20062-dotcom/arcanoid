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
        diamond.setOutlineColor({255, 255, 255, 160});
        diamond.setOutlineThickness(1.f);
        win.draw(diamond);

        sf::CircleShape glare(2.f);
        glare.setOrigin({2.f, 2.f});
        glare.setPosition({pos.x - 3.f, pos.y - 4.f});
        glare.setFillColor({255, 255, 255, 180});
        win.draw(glare);
    }
};

class BonusPaddleGrow final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return {180, 100, 255}; }
};

class BonusPaddleShrink final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return {255, 100, 180}; }
};

class BonusSpeedUp final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return {255, 180, 220}; }
};

class BonusSpeedDown final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return {100, 149, 237}; }
};

class BonusSticky final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return {130, 80, 220}; }
};

class BonusExtraBall final : public Bonus {
public:
    using Bonus::Bonus;
    void activate(GameState& gs) override;
    sf::Color color() const override { return {48, 63, 200}; }
};

