//ID dos objetos
enum IDS{PLAYER, BULLET , ENEMY , EXPLOSION, BACKGROUND};

//JOGADOR
struct Player{
    int ID;
    int x;
    int y;
    int speed;
    int lives;
    int boundx;
    int boundy;
    int score;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    int animationRow;

    ALLEGRO_BITMAP *image;

};

//BALAS
struct Bullet{

    int ID;
    int x;
    int y;
    bool live;
    int speed;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    int animationRow;

    ALLEGRO_BITMAP *image;

};

//INIMIGO
struct Enemy{

    int ID;
    int x;
    int y;
    bool live;
    int speed;
    int boundx;
    int boundy;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    int animationRow;

    ALLEGRO_BITMAP *image;

};

struct Explosion{

    int x;
    int y;
    bool live;

    int maxFrame;
    int curFrame;
    int frameCount;
    int frameDelay;
    int frameWidth;
    int frameHeight;
    int animationColumns;
    int animationDirection;

    int animationRow;

    ALLEGRO_BITMAP *image;


};

struct Background{

    float x;
    float y;
    float velX;
    float velY;
    int dirX;
    int dirY;

    int width;
    int height;

    ALLEGRO_BITMAP *image;

};

