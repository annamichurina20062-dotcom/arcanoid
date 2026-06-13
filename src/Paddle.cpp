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
    //тень
    sf::RectangleShape shadow({width, PADDLE_H});
    shadow.setPosition({x + 3.f, PADDLE_Y + 3.f});
    shadow.setFillColor({0, 0, 0, 80});
    win.draw(shadow);

    //основное тело
    sf::RectangleShape shape({width, PADDLE_H});
    shape.setPosition({x, PADDLE_Y});
    shape.setFillColor({130, 80, 220});
    shape.setOutlineColor({200, 150, 255});
    shape.setOutlineThickness(1.5f);
    win.draw(shape);

    //блик сверху
    sf::RectangleShape glare({width * 0.7f, 3.f});
    glare.setPosition({x + width * 0.15f, PADDLE_Y + 2.f});
    glare.setFillColor({255, 255, 255, 80});
    win.draw(glare);
}



