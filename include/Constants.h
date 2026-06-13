#pragma once

constexpr int WINDOW_WIDTH  = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int FPS           = 60;

constexpr int BLOCK_COLS     = 12;
constexpr int BLOCK_ROWS     = 6;
constexpr int BLOCK_W        = 58;
constexpr int BLOCK_H        = 22;
constexpr int BLOCK_PAD      = 4;
constexpr int BLOCK_OFFSET_X = 28;
constexpr int BLOCK_OFFSET_Y = 50;

constexpr float PADDLE_W            = 100.f;
constexpr float PADDLE_H            = 14.f;
constexpr float PADDLE_Y            = 560.f;
constexpr float PADDLE_SPEED        = 420.f;
constexpr float PADDLE_MIN_W        = 40.f;
constexpr float PADDLE_MAX_W        = 200.f;
constexpr float PADDLE_SHADOW_OFFSET = 3.f;
constexpr float PADDLE_GLARE_WIDTH  = 0.7f;
constexpr float PADDLE_GLARE_OFFSET = 0.15f;
constexpr float PADDLE_GLARE_Y      = 2.f;
constexpr float PADDLE_OUTLINE      = 1.5f;
constexpr float PADDLE_RESIZE_MISS  = 15.f;

constexpr float BALL_RADIUS     = 8.f;
constexpr float BALL_SPEED_INIT = 280.f;
constexpr float BALL_SPEED_MAX  = 560.f;
constexpr float BALL_SPEED_MIN  = 180.f;

constexpr float BONUS_FALL_SPEED    = 130.f;
constexpr float BONUS_W             = 28.f;
constexpr float BONUS_H             = 14.f;
constexpr float BONUS_PADDLE_GROW   = 30.f;
constexpr float BONUS_PADDLE_SHRINK = 25.f;
constexpr float BONUS_SPEED_DELTA   = 50.f;

constexpr int SCORE_PER_HIT = 1;
constexpr int SCORE_MISS    = -3;
constexpr int MAX_DEFEATS   = 3;

// Фон
constexpr float BG_TOP_R = 10.f, BG_TOP_G = 10.f, BG_TOP_B = 35.f;
constexpr float BG_BOT_R = 15.f, BG_BOT_G = 10.f, BG_BOT_B = 40.f;
constexpr int   STAR_COUNT       = 120;
constexpr float STAR_RADIUS      = 1.f;
constexpr float STAR_BRIGHT_MIN  = 80.f;
constexpr float STAR_BRIGHT_MAX  = 255.f;

// HUD
constexpr float HUD_HEIGHT       = 36.f;
constexpr float HUD_LABEL_SIZE   = 12;
constexpr float HUD_VALUE_SIZE   = 16;
constexpr float HUD_BIG_SIZE     = 24;
constexpr float HUD_GAMEOVER_SIZE= 28;
constexpr float HEART_RADIUS     = 6.f;
constexpr float HEART_SPACING    = 20.f;
constexpr float HEART_X_START    = 140.f;
constexpr float HEART_Y          = 26.f;
constexpr float LIVES_LABEL_X    = 160.f;

// Мяч — начальное направление
constexpr float BALL_INIT_DIR_X  = 0.4f;
constexpr float BALL_INIT_DIR_Y  = -1.f;
constexpr float BALL_SPAWN_GAP   = 2.f;

// Угол отражения от ракетки
constexpr float PADDLE_ANGLE_MAX = 60.f;
constexpr float PI               = 3.14159f;
constexpr float PADDLE_BOUNCE_GAP= 1.f;

// Время
constexpr float DT_CAP          = 0.05f;

// Рандом блоков
constexpr int BLOCK_ROLL_MAX        = 9;
constexpr int BLOCK_ROLL_INDESTR    = 0;
constexpr int BLOCK_ROLL_SPEED      = 1;
constexpr int BLOCK_HP_MAX          = 4;
constexpr int BLOCK_BONUS_CHANCE    = 3;
constexpr int BLOCK_BONUS_TYPES     = 4;

constexpr float BALL_GLOW_STEP   = 3.f;
constexpr int   BALL_GLOW_LAYERS = 3;
constexpr float BALL_GLARE_RATIO = 0.3f;
constexpr float BALL_OUTLINE     = 1.f;
constexpr int BALL_GLOW_ALPHA = 15;

// Блоки — визуал
constexpr int BLOCK_OUTLINE_BOOST = 60;
constexpr int BLOCK_OUTLINE_ALPHA = 140;
constexpr int BLOCK_HP_TEXT_SIZE  = 13;
constexpr int BLOCK_TEXT_ALPHA    = 220;

// Мяч — цвета
constexpr int BALL_COLOR_R       = 240;
constexpr int BALL_COLOR_G       = 240;
constexpr int BALL_COLOR_B       = 255;
constexpr int BALL_OUTLINE_R     = 180;
constexpr int BALL_OUTLINE_G     = 220;
constexpr int BALL_OUTLINE_B     = 255;
constexpr int BALL_GLARE_ALPHA   = 180;

// Ракетка — цвета
constexpr int PADDLE_COLOR_R     = 130;
constexpr int PADDLE_COLOR_G     = 80;
constexpr int PADDLE_COLOR_B     = 220;
constexpr int PADDLE_OUTLINE_R   = 200;
constexpr int PADDLE_OUTLINE_G   = 150;
constexpr int PADDLE_OUTLINE_B   = 255;
constexpr int PADDLE_SHADOW_ALPHA= 80;
constexpr int PADDLE_GLARE_ALPHA = 80;
constexpr float PADDLE_GLARE_H   = 3.f;

// HUD — цвета и позиции
constexpr int HUD_BAR_R          = 20;
constexpr int HUD_BAR_G          = 10;
constexpr int HUD_BAR_B          = 50;
constexpr int HUD_BAR_ALPHA      = 180;
constexpr int HUD_TEXT_R         = 220;
constexpr int HUD_TEXT_G         = 180;
constexpr int HUD_TEXT_B         = 255;
constexpr int HUD_LABEL_R        = 180;
constexpr int HUD_LABEL_G        = 130;
constexpr int HUD_LABEL_B        = 255;
constexpr int HEART_ACTIVE_R     = 60;
constexpr int HEART_ACTIVE_G     = 180;
constexpr int HEART_ACTIVE_B     = 255;
constexpr int HEART_DEAD_R       = 60;
constexpr int HEART_DEAD_G       = 60;
constexpr int HEART_DEAD_B       = 80;
constexpr int HEART_OUTLINE_R    = 180;
constexpr int HEART_OUTLINE_G    = 230;
constexpr int HEART_OUTLINE_B    = 255;
constexpr float HEART_OUTLINE_T  = 1.f;
constexpr float HUD_SCORE_X      = 10.f;
constexpr float HUD_SCORE_Y      = 4.f;
constexpr float HUD_VALUE_Y      = 16.f;
constexpr float PAUSED_OFFSET_X  = 110.f;
constexpr float GAMEOVER_OFFSET_X= 140.f;
constexpr float GAMEOVER_OFFSET_Y= 30.f;
constexpr float RESTART_OFFSET_X = 100.f;
constexpr float RESTART_OFFSET_Y = 10.f;
constexpr int HUD_RESTART_SIZE   = 20;

// Блоки — drawRect
constexpr float BLOCK_SHADOW_OFFSET = 2.f;
constexpr float BLOCK_SHADOW_ALPHA  = 60.f;
constexpr float BLOCK_INNER_OFFSET  = 1.f;
constexpr float BLOCK_OUTLINE_DEF_ALPHA = 60;
constexpr float BLOCK_GLARE_RATIO   = 0.6f;
constexpr float BLOCK_GLARE_X_RATIO = 0.2f;
constexpr float BLOCK_GLARE_Y      = 3.f;
constexpr float BLOCK_GLARE_H      = 3.f;
constexpr int   BLOCK_GLARE_ALPHA  = 50;
constexpr int   INDESTR_R = 80,  INDESTR_G = 80,  INDESTR_B = 95;
constexpr int   INDESTR_OUT_R = 150, INDESTR_OUT_G = 150, INDESTR_OUT_B = 170;
constexpr int   INDESTR_OUT_ALPHA = 120;
constexpr int   SPEED_R = 180, SPEED_G = 80,  SPEED_B = 200;
constexpr int   SPEED_OUT_R = 220, SPEED_OUT_G = 150, SPEED_OUT_B = 255;
constexpr int   SPEED_OUT_ALPHA = 120;

// Бонусы — цвета
constexpr int BONUS_OUTLINE_ALPHA  = 160;
constexpr float BONUS_OUTLINE_T    = 1.f;
constexpr float BONUS_GLARE_R      = 2.f;
constexpr float BONUS_GLARE_OFFSET_X = 3.f;
constexpr float BONUS_GLARE_OFFSET_Y = 4.f;
constexpr int   BONUS_GLARE_ALPHA  = 180;
constexpr int   BONUS_GROW_R   = 180, BONUS_GROW_G   = 100, BONUS_GROW_B   = 255;
constexpr int   BONUS_SHRINK_R = 255, BONUS_SHRINK_G = 100, BONUS_SHRINK_B = 180;
constexpr int   BONUS_SUP_R    = 255, BONUS_SUP_G    = 180, BONUS_SUP_B    = 220;
constexpr int   BONUS_SDOWN_R  = 100, BONUS_SDOWN_G  = 149, BONUS_SDOWN_B  = 237;
constexpr int   BONUS_STICKY_R = 130, BONUS_STICKY_G = 80,  BONUS_STICKY_B = 220;
constexpr int   BONUS_EXTRA_R  = 48,  BONUS_EXTRA_G  = 63,  BONUS_EXTRA_B  = 200;
