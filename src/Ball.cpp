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
    for (int i = BALL_GLOW_LAYERS; i >= 1; --i) {
        float r = BALL_RADIUS + i * BALL_GLOW_STEP;
        sf::CircleShape glow(r);
        glow.setOrigin({r, r});
        glow.setPosition({pos.x, pos.y});
        glow.setFillColor(sf::Color(255, 255, 255, (uint8_t)(BALL_GLOW_ALPHA * i)));
        win.draw(glow);
    }

    sf::CircleShape c(BALL_RADIUS);
    c.setOrigin({BALL_RADIUS, BALL_RADIUS});
    c.setPosition({pos.x, pos.y});
    c.setFillColor(sf::Color(BALL_COLOR_R, BALL_COLOR_G, BALL_COLOR_B));
    c.setOutlineColor(sf::Color(BALL_OUTLINE_R, BALL_OUTLINE_G, BALL_OUTLINE_B));
    c.setOutlineThickness(BALL_OUTLINE);
    win.draw(c);

    float gr = BALL_RADIUS * BALL_GLARE_RATIO;
    sf::CircleShape glare(gr);
    glare.setOrigin({gr, gr});
    glare.setPosition({pos.x - gr, pos.y - gr});
    glare.setFillColor(sf::Color(255, 255, 255, BALL_GLARE_ALPHA));
    win.draw(glare);
}
