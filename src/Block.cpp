#include "Block.h"
#include "Bonus.h"
#include "Constants.h"

std::unique_ptr<Bonus> NormalBlock::hit() {
    --hp_;
    if (hp_ <= 0) {
        alive = false;
        if (factory_) return factory_(pos);
    }
    return nullptr;
}

sf::Color NormalBlock::hpColor() const {
    switch (hp_) {
        case 1:  return {255, 200, 230};
        case 2:  return {220, 130, 220};
        case 3:  return {130, 100, 220};
        default: return {60,  60,  180};
    }
}

void NormalBlock::draw(sf::RenderWindow& win, const sf::Font& font) const {
    sf::Color base = hpColor();
    sf::Color outline{
        (uint8_t)std::min(255, (int)base.r + 60),
        (uint8_t)std::min(255, (int)base.g + 60),
        (uint8_t)std::min(255, (int)base.b + 60),
        140
    };
    drawRect(win, base, outline, true);

    // Цифра HP по центру блока
    sf::Text t(font, std::to_string(hp_), 13);
    t.setFillColor({255, 255, 255, 220});
    sf::FloatRect tb = t.getLocalBounds();
    t.setOrigin({tb.position.x + tb.size.x / 2.f,
                 tb.position.y + tb.size.y / 2.f});
    t.setPosition({pos.x + BLOCK_W / 2.f, pos.y + BLOCK_H / 2.f});
    win.draw(t);
}

std::unique_ptr<Bonus> SpeedBlock::hit() {
    alive = false;
    Vec2 center{pos.x + BLOCK_W / 2.f, pos.y + BLOCK_H / 2.f};
    return std::make_unique<BonusSpeedUp>(center);
}