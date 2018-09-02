#ifndef GAME_H
#define GAME_H

/**
 * Singleton class
 */
class Game {
private:
    static Game *instance;
    Game();
public:
    static Game *getInstance();
};

#endif // GAME_H