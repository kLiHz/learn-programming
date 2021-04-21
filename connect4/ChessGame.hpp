#ifndef CHESS_GAME_HPP
#define CHESS_GAME_HPP

#include <string>
#include <map>

class ChessGame
{
private:
public:
    enum class SUBJECT {NEUTRAL, PLAYER, PLAYER1, PLAYER2, COMPUTER};
    enum class GAME_MODE {DEFAULT, PVP, PVC};

    ChessGame();
    virtual ~ChessGame()  = default;
    virtual void play() = 0;
protected:
    int rounds;
    bool is_game_over;
    std::map<SUBJECT, std::string> name_tags;
    SUBJECT firstmover, secondmover, winner;
    GAME_MODE gamemode;
};

#endif // CHESS_GAME_HPP
