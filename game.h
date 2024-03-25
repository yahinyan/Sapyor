#ifndef GAME_H
#define GAME_H
#include <iostream>

class Game {
    public:
        Game();
        Game(int size, int mins_count);
        Game(const Game& other);
        Game(Game&& other) noexcept;
        Game& operator=(const Game& other);
        Game& operator=(Game&& other) noexcept;

        void gameOver(int i, int j, int** temp);
        void sinkIsland(int i, int j, int** temp);
        
        bool check(int i, int j, int** temp);
        void win(int** temp);
        bool openElem(int i, int j, int** temp);
        void print();
        size_t get_size() const;
        size_t get_mins_count() const;
        size_t get_open() const;
        ~Game();
    private:
        void countMins();
        int foo(int i, int j);
        
        
        void randomMins();
    private:
        int** m_matrix;
        int m_size;
        int m_mins_count;
        int open;
};
#endif // GAME_H