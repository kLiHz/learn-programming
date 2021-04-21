#include "ChessGame.hpp"

ChessGame::ChessGame()
{
    rounds = 1;
    is_game_over = false;
    firstmover = SUBJECT::NEUTRAL;
    gamemode = GAME_MODE::DEFAULT;

    name_tags[SUBJECT::NEUTRAL ] = "NEUTRAL" ;
    name_tags[SUBJECT::PLAYER  ] = "Player"  ;
    name_tags[SUBJECT::PLAYER1 ] = "Player 1";
    name_tags[SUBJECT::PLAYER2 ] = "Player 2";
    name_tags[SUBJECT::COMPUTER] = "Computer";
}
