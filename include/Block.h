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
    virtual void draw(sf::RenderWindow& win, const sf::Font& font) const = 0;

    sf::FloatRect bounds() const {
        return sf::FloatRect({pos.x, pos.y}, {(float)BLOCK_W, (float)BLOCK_H});
    }

protected:
    void drawRect(sf::RenderWindow& win, sf::Color fill,
                  sf::Color outline = {255, 255, 255, 60},
                  bool glare = true) const {
        sf::RectangleShape shadow({(float)BLOCK_W - 2.f, (float)BLOCK_H - 2.f});
        shadow.setPosition({pos.x + 2.f, pos.y + 2.f});
        shadow.setFillColor({0, 0, 0, 60});
        win.draw(shadow);

        sf::RectangleShape r({(float)BLOCK_W - 2.f, (float)BLOCK_H - 2.f});
        r.setPosition({pos.x + 1.f, pos.y + 1.f});
        r.setFillColor(fill);
        r.setOutlineColor(outline);
        r.setOutlineThickness(1.f);
        win.draw(r);

        if (glare) {
            sf::RectangleShape g({(float)BLOCK_W * 0.6f, 3.f});
            g.setPosition({pos.x + (float)BLOCK_W * 0.2f, pos.y + 3.f});
            g.setFillColor({255, 255, 255, 50});
            win.draw(g);
        }
    }
};

class IndestructibleBlock final : public Block {
public:
    using Block::Block;
    std::unique_ptr<Bonus> hit() override { return nullptr; }
    void draw(sf::RenderWindow& win, const sf::Font& font) const override {
        drawRect(win, {80, 80, 95}, {150, 150, 170, 120}, false);
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
        drawRect(win, {180, 80, 200}, {220, 150, 255, 120}, true);
    }
};