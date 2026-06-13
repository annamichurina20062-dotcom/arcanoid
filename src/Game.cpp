#include "Game.h"
#include "GameState.h"
#include "Constants.h"
#include <random>
#include <algorithm>
#include <sstream>

namespace {
    std::mt19937& rng() {
        static std::mt19937 g(std::random_device{}());
        return g;
    }

    int randInt(int lo, int hi) {
        return std::uniform_int_distribution<int>(lo, hi)(rng());
    }

    bool rectOverlap(const sf::FloatRect& a, const sf::FloatRect& b,
                     float& dx, float& dy)
    {
        dx = std::min(a.position.x + a.size.x, b.position.x + b.size.x)
           - std::max(a.position.x, b.position.x);
        dy = std::min(a.position.y + a.size.y, b.position.y + b.size.y)
           - std::max(a.position.y, b.position.y);
        return dx > 0.f && dy > 0.f;
    }
}

Game::Game()
    : window_(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Arkanoid",
              sf::Style::Titlebar | sf::Style::Close)
{
    window_.setFramerateLimit(FPS);
    font_.openFromFile("C:/Windows/Fonts/arial.ttf");


    buildLevel();
    generateStars();
}

void Game::buildLevel() {
    balls_.clear();
    blocks_.clear();
    bonuses_.clear();

    Vec2 ballStart{(float)WINDOW_WIDTH / 2.f, PADDLE_Y - BALL_RADIUS - 2.f};
    balls_.emplace_back(ballStart, Vec2{0.4f, -1.f});

    auto makeFactory = [](int choice) -> NormalBlock::BonusFactory {
        switch (choice) {
            case 0: return [](Vec2 p){ return std::make_unique<BonusPaddleGrow>(p);   };
            case 1: return [](Vec2 p){ return std::make_unique<BonusPaddleShrink>(p); };
            case 2: return [](Vec2 p){ return std::make_unique<BonusSpeedDown>(p);    };
            case 3: return [](Vec2 p){ return std::make_unique<BonusSticky>(p);       };
            case 4: return [](Vec2 p){ return std::make_unique<BonusExtraBall>(p);    };
            default: return nullptr;
        }
    };

    for (int row = 0; row < BLOCK_ROWS; ++row) {
        for (int col = 0; col < BLOCK_COLS; ++col) {
            float bx = BLOCK_OFFSET_X + col * (BLOCK_W + BLOCK_PAD);
            float by = BLOCK_OFFSET_Y + row * (BLOCK_H + BLOCK_PAD);
            Vec2  p{bx, by};

            int roll = randInt(0, 9);
            if (roll == 0) {
                blocks_.push_back(std::make_unique<IndestructibleBlock>(p));
            } else if (roll == 1) {
                blocks_.push_back(std::make_unique<SpeedBlock>(p));
            } else {
                int hp = randInt(1, 4);
                NormalBlock::BonusFactory factory = nullptr;
                if (randInt(0, 3) == 0)
                    factory = makeFactory(randInt(0, 4));
                blocks_.push_back(std::make_unique<NormalBlock>(p, hp, std::move(factory)));
            }
        }
    }
}

void Game::run() {
    sf::Clock clock;
    while (window_.isOpen() && running_) {
        float dt = clock.restart().asSeconds();
        dt = std::min(dt, 0.05f);

        handleEvents();
        if (!paused_) update(dt);
        draw();
    }
}

void Game::handleEvents() {
    while (auto event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window_.close();

        if (const auto* kp = event->getIf<sf::Event::KeyPressed>()) {
            if (kp->code == sf::Keyboard::Key::Escape) running_ = false;
            if (kp->code == sf::Keyboard::Key::P)      paused_  = !paused_;

            if (kp->code == sf::Keyboard::Key::Space) {
                for (auto& b : balls_) {
                    if (b.sticky) {
                        b.sticky = false;
                        b.vel = Vec2{0.4f, -1.f}.normalized() * b.speed;
                    }
                }
            }

            if (kp->code == sf::Keyboard::Key::R && defeats_ >= MAX_DEFEATS) {
                score_   = 0;
                defeats_ = 0;
                paddle_  = Paddle{};
                buildLevel();
            }
        }
    }

    if (!paused_ && defeats_ < MAX_DEFEATS) {
        float dt = 1.f / FPS;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  paddle_.moveLeft(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) paddle_.moveRight(dt);
    }
}

void Game::update(float dt) {
    if (defeats_ >= MAX_DEFEATS) return;

    updateBalls(dt);
    updateBonuses(dt);

    for (auto& b : balls_) {
        if (b.sticky)
            b.pos.x = paddle_.centerX();
    }

    blocks_.erase(
        std::remove_if(blocks_.begin(), blocks_.end(),
                       [](const auto& b){ return !b->alive; }),
        blocks_.end());

    if (allBlocksCleared()) buildLevel();
}

void Game::updateBalls(float dt) {
    for (auto& ball : balls_) {
        ball.update(dt);
        resolveBallVsWalls(ball);
        resolveBallVsPaddle(ball);
        score_ += resolveBallVsBlocks(ball);

        if (ball.pos.y > WINDOW_HEIGHT + BALL_RADIUS)
            ball.active = false;
    }

    resolveBallVsBalls();

    balls_.erase(
        std::remove_if(balls_.begin(), balls_.end(),
                       [](const Ball& b){ return !b.active; }),
        balls_.end());

    if (balls_.empty()) onMiss();
}

void Game::updateBonuses(float dt) {
    for (auto& bon : bonuses_) {
        if (!bon->active) continue;
        bon->update(dt);

        if (bon->bounds().findIntersection(paddle_.bounds())) {
            applyBonus(*bon);
            bon->active = false;
        }

        if (bon->pos.y > WINDOW_HEIGHT) bon->active = false;
    }

    bonuses_.erase(
        std::remove_if(bonuses_.begin(), bonuses_.end(),
                       [](const auto& b){ return !b->active; }),
        bonuses_.end());
}

void Game::resolveBallVsWalls(Ball& ball) {
    if (ball.pos.x - BALL_RADIUS < 0) {
        ball.pos.x = BALL_RADIUS;
        ball.reflectX();
    } else if (ball.pos.x + BALL_RADIUS > WINDOW_WIDTH) {
        ball.pos.x = WINDOW_WIDTH - BALL_RADIUS;
        ball.reflectX();
    }
    if (ball.pos.y - BALL_RADIUS < 0) {
        ball.pos.y = BALL_RADIUS;
        ball.reflectY();
    }
}

void Game::resolveBallVsPaddle(Ball& ball) {
    if (ball.sticky) return;
    auto pb = paddle_.bounds();
    auto bb = ball.bounds();
    float dx, dy;
    if (!rectOverlap(pb, bb, dx, dy)) return;
    if (ball.vel.y < 0) return;

    float offset = (ball.pos.x - paddle_.centerX()) / (paddle_.width / 2.f);
    float angle  = offset * 60.f * (3.14159f / 180.f);
    Vec2  dir{ std::sin(angle), -std::cos(angle) };
    ball.vel = dir.normalized() * ball.speed;
    ball.pos.y = PADDLE_Y - BALL_RADIUS - 1.f;
}

int Game::resolveBallVsBlocks(Ball& ball) {
    int gained = 0;
    sf::FloatRect bb = ball.bounds();

    for (auto& block : blocks_) {
        if (!block->alive) continue;
        float dx, dy;
        if (!rectOverlap(block->bounds(), bb, dx, dy)) continue;

        if (dx < dy) ball.reflectX();
        else         ball.reflectY();

        auto bonus = block->hit();
        gained += SCORE_PER_HIT;

        if (bonus) {
            Vec2 spawnPos{block->bounds().position.x + BLOCK_W / 2.f,
                          block->bounds().position.y + BLOCK_H / 2.f};
            bonus->pos = spawnPos;
            bonuses_.push_back(std::move(bonus));
        }
        break;
    }
    return gained;
}

void Game::resolveBallVsBalls() {
    for (std::size_t i = 0; i < balls_.size(); ++i) {
        for (std::size_t j = i + 1; j < balls_.size(); ++j) {
            Vec2 diff{balls_[j].pos.x - balls_[i].pos.x,
                      balls_[j].pos.y - balls_[i].pos.y};
            float dist = diff.length();
            if (dist < BALL_RADIUS * 2.f && dist > 0.f) {
                Vec2 n = diff.normalized();
                float d1 = balls_[i].vel.x * n.x + balls_[i].vel.y * n.y;
                float d2 = balls_[j].vel.x * n.x + balls_[j].vel.y * n.y;
                balls_[i].vel.x += (d2 - d1) * n.x;
                balls_[i].vel.y += (d2 - d1) * n.y;
                balls_[j].vel.x += (d1 - d2) * n.x;
                balls_[j].vel.y += (d1 - d2) * n.y;
                balls_[i].setSpeed(balls_[i].speed);
                balls_[j].setSpeed(balls_[j].speed);
            }
        }
    }
}

void Game::applyBonus(Bonus& b) {
    GameState gs{paddle_, balls_, score_};
    b.activate(gs);
}

void Game::onMiss() {
    score_ += SCORE_MISS;
    ++defeats_;
    paddle_.resize(-15.f);

    if (defeats_ < MAX_DEFEATS) {
        Vec2 start{paddle_.centerX(), PADDLE_Y - BALL_RADIUS - 2.f};
        balls_.emplace_back(start, Vec2{0.4f, -1.f});
    }
}

void Game::draw() {
    window_.clear({10, 10, 35});
    drawBackground();

    for (const auto& bl : blocks_)  bl->draw(window_, font_); 
    for (const auto& bo : bonuses_) bo->draw(window_);
    for (const auto& b  : balls_)   b.draw(window_);
    paddle_.draw(window_);

    drawHUD();
    window_.display();
}

void Game::generateStars() {
    stars_.resize(120);
    std::uniform_real_distribution<float> rx(0, WINDOW_WIDTH);
    std::uniform_real_distribution<float> ry(0, WINDOW_HEIGHT);
    std::uniform_real_distribution<float> rb(80, 255);
    for (auto& s : stars_) {
        s.x = rx(rng());
        s.y = ry(rng());
        s.brightness = rb(rng());
    }
}

void Game::drawBackground() {
    sf::RectangleShape top({(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT / 2});
    top.setPosition({0, 0});
    top.setFillColor({10, 10, 35});
    window_.draw(top);

    sf::RectangleShape bot({(float)WINDOW_WIDTH, (float)WINDOW_HEIGHT / 2});
    bot.setPosition({0, (float)WINDOW_HEIGHT / 2});
    bot.setFillColor({15, 10, 40});
    window_.draw(bot);

    for (const auto& s : stars_) {
        sf::CircleShape star(1.f);
        star.setPosition({s.x, s.y});
        uint8_t b = (uint8_t)s.brightness;
        star.setFillColor({b, b, b, b});
        window_.draw(star);
    }
}

void Game::drawHUD() {
    sf::RectangleShape bar({(float)WINDOW_WIDTH, 36.f});
    bar.setFillColor({20, 10, 50, 180});
    window_.draw(bar);

    auto makeText = [&](const std::string& s, float x, float y, unsigned sz = 18,
                        sf::Color col = {220, 180, 255}) {
        sf::Text t(font_, s, sz);
        t.setPosition({x, y});
        t.setFillColor(col);
        window_.draw(t);
    };

    makeText("SCORE", 10.f, 4.f, 12, {180, 130, 255});
    makeText(std::to_string(score_), 10.f, 16.f, 16);


    makeText("LIVES", WINDOW_WIDTH - 160.f, 4.f, 12, {180, 130, 255});
    for (int i = 0; i < MAX_DEFEATS; ++i) {
        sf::CircleShape heart(6.f);
        heart.setOrigin({6.f, 6.f});
        heart.setPosition({(float)(WINDOW_WIDTH - 140 + i * 20), 26.f});
        if (i < MAX_DEFEATS - defeats_)
            heart.setFillColor({60, 180, 255});
        else
            heart.setFillColor({60, 60, 80});
        heart.setOutlineColor({180, 230, 255});
        heart.setOutlineThickness(1.f);
        window_.draw(heart);
    }

    if (paused_)
        makeText("PAUSED  (P to resume)",
                 WINDOW_WIDTH / 2.f - 110.f, WINDOW_HEIGHT / 2.f, 24,
                 {200, 220, 255});

    if (defeats_ >= MAX_DEFEATS) {
    makeText("G A M E   O V E R",
             WINDOW_WIDTH / 2.f - 140.f, WINDOW_HEIGHT / 2.f - 30.f, 28,
             {255, 150, 200});
    makeText("Press R to restart",
             WINDOW_WIDTH / 2.f - 100.f, WINDOW_HEIGHT / 2.f + 10.f, 20,
             {180, 150, 255});
}
}


bool Game::allBlocksCleared() const {
    for (const auto& b : blocks_)
        if (b->alive && dynamic_cast<IndestructibleBlock*>(b.get()) == nullptr)
            return false;
    return true;
}



