#include "game.h"
#include <cstdlib>

Game::Game()
    : m_matrix{nullptr}, m_size{}, m_mins_count{}, open{}
{
}

Game::Game(int size, int mins_count)
    : m_size{size}, m_mins_count{mins_count}, open{}
{
    m_matrix = new int *[m_size];
    for (int i = 0; i < m_size; ++i)
    {
        m_matrix[i] = new int[m_size];
    }
    countMins();
}

Game::Game(const Game &other)
    : m_size{other.m_size}, m_mins_count{other.m_mins_count}, open{other.open}
{
    m_matrix = new int *[m_size];
    for (int i = 0; i < m_size; ++i)
    {
        m_matrix[i] = new int[m_size];
    }
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            m_matrix[i][j] = other.m_matrix[i][j];
        }
    }
}

Game::Game(Game &&other) noexcept
    : m_size{std::exchange(other.m_size, 0)}, m_mins_count{std::exchange(other.m_mins_count, 0)}, m_matrix{std::exchange(other.m_matrix, nullptr)}, open{std::exchange(other.open, 0)}
{
}

Game &Game::operator=(const Game &other)
{
    if (this != &other)
    {
        if (m_matrix != nullptr)
        {
            for (int i = 0; i < m_size; ++i)
            {
                delete[] m_matrix[i];
            }
            delete[] m_matrix;
        }

        m_size = other.m_size;
        m_mins_count = other.m_mins_count;

        m_matrix = new int *[m_size];
        for (int i = 0; i < m_size; ++i)
        {
            m_matrix[i] = new int[m_size];
        }
        for (int i = 0; i < m_size; ++i)
        {
            for (int j = 0; j < m_size; ++j)
            {
                m_matrix[i][j] = other.m_matrix[i][j];
            }
        }
    }
    return *this;
}

Game &Game::operator=(Game &&other) noexcept
{
    if (this != &other)
    {
        if (m_matrix != nullptr)
        {
            for (int i = 0; i < m_size; ++i)
            {
                delete[] m_matrix[i];
            }
            delete[] m_matrix;
        }
        m_size = std::exchange(other.m_size, 0);
        m_mins_count = std::exchange(other.m_mins_count, 0);
        m_matrix = std::exchange(other.m_matrix, nullptr);
    }
    return *this;
}

void Game::randomMins()
{
    std::srand(std::time(0));

    for (int i = 0; i < m_mins_count; ++i)
    {
        int rand_row = std::rand() % m_size;
        int rand_col = std::rand() % m_size;

        m_matrix[rand_row][rand_col] = -1;
    }
}

size_t Game::get_open() const
{
    return open;
}
void Game::countMins()
{
    randomMins();
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            if (m_matrix[i][j] == 0)
            {
                int count = foo(i, j);
                m_matrix[i][j] = count;
            }
        }
    }
}

int Game::foo(int i, int j)
{
    int count = 0;

    for (int m = -1; m <= 1; ++m)
    {
        for (int n = -1; n <= 1; ++n)
        {
            if (m == 0 && n == 0)
            {
                continue;
            }
            int mi = i + m;
            int nj = j + n;

            if ((mi >= 0 && mi < m_size) && (nj >= 0 && nj < m_size) && m_matrix[mi][nj] == -1)
            {
                ++count;
            }
        }
    }
    return count;
}

void Game::win(int **temp)
{
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            if (temp[i][j] == 9)
            {
                temp[i][j] = 0;
            }
        }
    }
}
size_t Game::get_size() const
{
    return m_size;
}

size_t Game::get_mins_count() const
{
    return m_mins_count;
}
void Game::gameOver(int i, int j, int **temp)
{
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            if (m_matrix[i][j] == -1)
            {
                temp[i][j] = m_matrix[i][j];
            }
            else
            {
                temp[i][j] = 0;
            }
        }
    }
}
void Game::sinkIsland(int i, int j, int **temp)
{
    if (i < 0 || i >= m_size || j < 0 || j >= m_size)
    {
        return;
    }
    if (m_matrix[i][j] != 0)
    {
        temp[i][j] = m_matrix[i][j];
        return;
    }
    m_matrix[i][j] = 9;
    sinkIsland(i + 1, j, temp);
    sinkIsland(i, j - 1, temp);
    sinkIsland(i - 1, j, temp);
    sinkIsland(i, j + 1, temp);
    sinkIsland(i + 1, j + 1, temp);
    sinkIsland(i + 1, j - 1, temp);
    sinkIsland(i - 1, j + 1, temp);
    sinkIsland(i - 1, j - 1, temp);
    temp[i][j] = m_matrix[i][j];
}

bool Game::openElem(int i, int j, int **temp)
{
    sinkIsland(i, j, temp);
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            if (temp[i][j] == 0)
            {
                ++open;
            }
        }
    }
    if (open == m_mins_count)
    {
        std::cout << "You win!!" << std::endl;
        return false;
    }
    open = 0;
    return true;
}

bool Game::check(int i, int j, int **temp)
{
    if (m_matrix[i][j] == -1)
    {
        std::cout << "Game Over" << std::endl;
        gameOver(i, j, temp);
        return false;
    }
    return openElem(i, j, temp);
}

void Game::print()
{
    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            std::cout << m_matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

Game::~Game()
{
    for (int i = 0; i < m_size; ++i)
    {
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}