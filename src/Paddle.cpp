#include "Paddle.h"
#include <algorithm>

Paddle::Paddle() : x((WINDOW_WIDTH - PADDLE_W) / 2.f) {}

void Paddle::moveLeft(float dt) {
    x -= PADDLE_SPEED * dt;
    clamp();
}

void Paddle::moveRight(float dt) {
    x += PADDLE_SPEED * dt;
    clamp();
}

void Paddle::clamp() {
    x = std::clamp(x, 0.f, (float)WINDOW_WIDTH - width);
}

void Paddle::resize(float delta) {
    float cx = centerX();
    width = std::clamp(width + delta, PADDLE_MIN_W, PADDLE_MAX_W);
    x = cx - width / 2.f;
    clamp();
}

sf::FloatRect Paddle::bounds() const {
    return sf::FloatRect({x, PADDLE_Y}, {width, PADDLE_H});
}

void Paddle::draw(sf::RenderWindow& win) const {
    sf::RectangleShape shadow({width, PADDLE_H});
    shadow.setPosition({x + PADDLE_SHADOW_OFFSET, PADDLE_Y + PADDLE_SHADOW_OFFSET});
    shadow.setFillColor(sf::Color(0, 0, 0, PADDLE_SHADOW_ALPHA));
    win.draw(shadow);

    sf::RectangleShape shape({width, PADDLE_H});
    shape.setPosition({x, PADDLE_Y});
    shape.setFillColor(sf::Color(PADDLE_COLOR_R, PADDLE_COLOR_G, PADDLE_COLOR_B));
    shape.setOutlineColor(sf::Color(PADDLE_OUTLINE_R, PADDLE_OUTLINE_G, PADDLE_OUTLINE_B));
    shape.setOutlineThickness(PADDLE_OUTLINE);
    win.draw(shape);

    sf::RectangleShape glare({width * PADDLE_GLARE_WIDTH, PADDLE_GLARE_H});
    glare.setPosition({x + width * PADDLE_GLARE_OFFSET, PADDLE_Y + PADDLE_GLARE_Y});
    glare.setFillColor(sf::Color(255, 255, 255, PADDLE_GLARE_ALPHA));
    win.draw(glare);
}
