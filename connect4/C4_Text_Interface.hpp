#ifndef C4_TEXT_INTERFACE_HPP
#define C4_TEXT_INTERFACE_HPP

#include "Connect4.hpp"
#include <memory>
#include <iostream>

class C4_Text_Interface 
{
private:
    std::shared_ptr<Connect4> instance;

    char firstmover_symbol;
    char secondmover_symbol;
    char blank_chessboard_symbol;

    void output_map();
    void display_status();

    void gamemode_firstmover_setting_UI();
    void symbols_change_UI();
    void change_tags_UI();
    void custom_settings();

    auto get_usr_map_size();
    void mapsize_change_with_notif(int rowNum, int colNum);
    void get_player_move_input();

    ChessGame::SUBJECT winner;

public:
    C4_Text_Interface();
    void play();
};

void trim(std::string &str);

int get_int_choice_between(int m, int n);

#endif // CONNECT_4_TEXT_INTERFACE_HPP
