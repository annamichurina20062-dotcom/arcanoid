#include "Ball.h"
#include <algorithm>

Ball::Ball(Vec2 startPos, Vec2 direction, float spd)
    : pos(startPos), speed(spd)
{
    applyDirection(direction);
}

void Ball::applyDirection(Vec2 dir) {
    vel = dir.normalized() * speed;
}

void Ball::setSpeed(float s) {
    speed = std::clamp(s, BALL_SPEED_MIN, BALL_SPEED_MAX);
    vel   = vel.normalized() * speed;
}

void Ball::update(float dt) {
    if (!sticky) pos += vel * dt;
}

sf::FloatRect Ball::bounds() const {
    return sf::FloatRect(
        {pos.x - BALL_RADIUS, pos.y - BALL_RADIUS},
        {BALL_RADIUS * 2.f,   BALL_RADIUS * 2.f}
    );
}

void Ball::draw(sf::RenderWindow& win) const {
    // Ореол
    for (int i = 3; i >= 1; --i) {
        sf::CircleShape glow(BALL_RADIUS + i * 3.f);
        glow.setOrigin({BALL_RADIUS + i * 3.f, BALL_RADIUS + i * 3.f});
        glow.setPosition({pos.x, pos.y});
        glow.setFillColor({255, 255, 255, (uint8_t)(15 * i)});
        win.draw(glow);
    }

    // Основной мяч
    sf::CircleShape c(BALL_RADIUS);
    c.setOrigin({BALL_RADIUS, BALL_RADIUS});
    c.setPosition({pos.x, pos.y});
    c.setFillColor({240, 240, 255});
    c.setOutlineColor({180, 220, 255});
    c.setOutlineThickness(1.f);
    win.draw(c);

    // Блик
    sf::CircleShape glare(BALL_RADIUS * 0.3f);
    glare.setOrigin({BALL_RADIUS * 0.3f, BALL_RADIUS * 0.3f});
    glare.setPosition({pos.x - BALL_RADIUS * 0.3f, pos.y - BALL_RADIUS * 0.3f});
    glare.setFillColor({255, 255, 255, 180});
    win.draw(glare);
}

