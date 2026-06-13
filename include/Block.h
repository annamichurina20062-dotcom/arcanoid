#pragma once
#include "Constants.h"
#include "Vec2.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class Bonus;

class Block {
public:
    Vec2 pos;
    bool alive = true;

    Block(Vec2 p) : pos(p) {}
    virtual ~Block() = default;

    virtual std::unique_ptr<Bonus> hit() = 0;
    virtual bool solid() const { return true; }
    virtual bool isDestructible() const { return true; }
    virtual void draw(sf::RenderWindow& win, const sf::Font& font) const = 0;

    sf::FloatRect bounds() const {
        return sf::FloatRect({pos.x, pos.y}, {(float)BLOCK_W, (float)BLOCK_H});
    }

protected:
    void drawRect(sf::RenderWindow& win, sf::Color fill,
                  sf::Color outline = sf::Color(255, 255, 255, BLOCK_OUTLINE_DEF_ALPHA),
                  bool glare = true) const {
        sf::RectangleShape shadow({(float)BLOCK_W - BLOCK_INNER_OFFSET, (float)BLOCK_H - BLOCK_INNER_OFFSET});
        shadow.setPosition({pos.x + BLOCK_SHADOW_OFFSET, pos.y + BLOCK_SHADOW_OFFSET});
        shadow.setFillColor(sf::Color(0, 0, 0, BLOCK_SHADOW_ALPHA));
        win.draw(shadow);

        sf::RectangleShape r({(float)BLOCK_W - BLOCK_INNER_OFFSET, (float)BLOCK_H - BLOCK_INNER_OFFSET});
        r.setPosition({pos.x + BLOCK_INNER_OFFSET, pos.y + BLOCK_INNER_OFFSET});
        r.setFillColor(fill);
        r.setOutlineColor(outline);
        r.setOutlineThickness(BALL_OUTLINE);
        win.draw(r);

        if (glare) {
            sf::RectangleShape g({(float)BLOCK_W * BLOCK_GLARE_RATIO, BLOCK_GLARE_H});
            g.setPosition({pos.x + (float)BLOCK_W * BLOCK_GLARE_X_RATIO, pos.y + BLOCK_GLARE_Y});
            g.setFillColor(sf::Color(255, 255, 255, BLOCK_GLARE_ALPHA));
            win.draw(g);
        }
    }
};

class IndestructibleBlock final : public Block {
public:
    using Block::Block;
    std::unique_ptr<Bonus> hit() override { return nullptr; }
    bool isDestructible() const override { return false; }
    void draw(sf::RenderWindow& win, const sf::Font& font) const override {
        drawRect(win,
            sf::Color(INDESTR_R, INDESTR_G, INDESTR_B),
            sf::Color(INDESTR_OUT_R, INDESTR_OUT_G, INDESTR_OUT_B, INDESTR_OUT_ALPHA),
            false);
    }
};

class NormalBlock : public Block {
public:
    using BonusFactory = std::function<std::unique_ptr<Bonus>(Vec2)>;

    NormalBlock(Vec2 p, int hp, BonusFactory factory = nullptr)
        : Block(p), hp_(hp), factory_(std::move(factory)) {}

    std::unique_ptr<Bonus> hit() override;
    void draw(sf::RenderWindow& win, const sf::Font& font) const override;

private:
    int          hp_;
    BonusFactory factory_;
    sf::Color hpColor() const;
};

class SpeedBlock final : public Block {
public:
    using Block::Block;
    std::unique_ptr<Bonus> hit() override;
    void draw(sf::RenderWindow& win, const sf::Font& font) const override {
        drawRect(win,
            sf::Color(SPEED_R, SPEED_G, SPEED_B),
            sf::Color(SPEED_OUT_R, SPEED_OUT_G, SPEED_OUT_B, SPEED_OUT_ALPHA),
            true);
    }
};
