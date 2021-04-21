#ifndef CONNECT_4_HPP
#define CONNECT_4_HPP

#include "ChessGame.hpp"
#include <iostream>
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
    char firstmover_symbol;
    char secondmover_symbol;
    char blank_chessboard_symbol;

    std::vector<std::vector<int>> map; // [6][7];
    std::vector<int> used; // [7];
    std::vector<C4_Move> history_moves; // [6*7]

    void player_move();

    bool find_win(int check, C4_Move& cmove);
    bool find_block(int check, C4_Move& cmove);
    // int computer_search();

    void computer_move();
    bool make_move(C4_Move&);
    // void redo();

    void output_map();
    void display();
    void custom_settings();
    void game_settings();
    void generate_map();
    void reset();
    SUBJECT win_check();

    void change_map_size(bool if_to_reset = false);
    void change_symbols(bool if_to_reset = false);
    void change_tags(bool if_to_reset = false);
    std::mt19937 random_source;
public:
    Connect4();
    virtual ~Connect4() = default;
    virtual void play();
};

void trim(std::string &str);

int get_int_choice_between(int m, int n);

#endif  // CONNECT_4_HPP