#ifndef CONNECT_4_HPP
#define CONNECT_4_HPP

#include "ChessGame.hpp"
#include <string>
#include <random>
#include <vector>

struct C4_Move
{
    int col;
};

class Connect4 : public ChessGame
{
private:
    int rowNum; // = 6;
    int colNum; // = 7;

    std::vector<std::vector<int>> map; // [6][7];
    std::vector<int> used; // [7];
    std::vector<C4_Move> history_moves; // [6*7]

    std::mt19937 random_source;
    
    C4_Move find_win  (int check);
    C4_Move find_block(int check);

    void regenerate_map();
    bool is_game_over;

public:
    void computer_make_move();
    
    bool make_move(C4_Move& cmove);

    void reset();
    void resize_to(int row, int col);

    auto & get_map() { return map; }
    auto & get_history_moves() { return history_moves; }
    auto get_row() { return this->rowNum; }
    auto get_col() { return this->colNum; }



    ChessGame::SUBJECT win_check();

    bool is_over() { return is_game_over; }

    Connect4();
    virtual ~Connect4() = default;
};

#endif  // CONNECT_4_HPP
