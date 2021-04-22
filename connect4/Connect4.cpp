#include "Connect4.hpp"

Connect4::Connect4() {
    std::random_device rd;
    random_source = std::mt19937(rd());

    rowNum = 6;
    colNum = 7; // suggestted colNum should be less than 15;

    this->regenerate_map();
}

void Connect4::regenerate_map() {
    map = std::vector<std::vector<int>>(rowNum, std::vector<int>(colNum, 0));
    history_moves = std::vector<C4_Move>(rowNum * colNum, {0});
    used = std::vector<int>(colNum, 0);
}

void Connect4::reset()
{
    this->regenerate_map();
    rounds = 1; 
    is_game_over = false;
}

void Connect4::resize_to(int row, int col) {
    this->rowNum = row;
    this->colNum = col;
    this->reset();
}

C4_Move Connect4::find_win(int check)
{
    C4_Move cmove{-1};
    for(int i = 0; i < rowNum - 3; i++) {
        for(int j = 0; j < colNum - 3; j++) {

            if (map[i][j]     == check &&  //       * 
                map[i+1][j+1] == check &&  //     @ & 
                map[i+2][j+2] == check &&  //   @ & & 
                map[i+3][j+3] == 0     &&  // @ & & & 
                map[i+2][j+3] != 0 ) { return {j + 3}; }

            if (map[i][j]     == check &&  //       @
                map[i+1][j+1] == check &&  //     * & 
                map[i+2][j+2] == 0     &&  //   @ & & 
                map[i+3][j+3] == check &&  // @ & & & 
                map[i+1][j+2] != 0) { return {j + 2}; }

            if (map[i][j]     == check &&  //       @
                map[i+1][j+1] == 0     &&  //     @ &
                map[i+2][j+2] == check &&  //   * & &
                map[i+3][j+3] == check &&  // @ & & &
                map[i][j+1] != 0) { return {j + 1}; }

            if (map[i][j]     == 0     &&  //       @ 
                map[i+1][j+1] == check &&  //     @ & 
                map[i+2][j+2] == check &&  //   @ & & 
                map[i+3][j+3] == check &&  // * & & & 
                (i == 0 || (i >= 1 && map[i-1][j] != 0)) ) { return {j}; }

            if (map[i+3][j]   == 0     &&  // * 
                map[i+2][j+1] == check &&  // & @ 
                map[i+1][j+2] == check &&  // & & @  
                map[i][j+3]   == check &&  // & & & @ 
                map[i+2][j] != 0) { return {j}; }

            if (map[i+3][j]   == check &&  // @ 
                map[i+2][j+1] == 0     &&  // & * 
                map[i+1][j+2] == check &&  // & & @  
                map[i][j+3]   == check &&  // & & & @ 
                map[i+1][j+1] != 0) { return {j + 1}; }

            if (map[i+3][j]   == check &&  // @ 
                map[i+2][j+1] == check &&  // & @ 
                map[i+1][j+2] == 0     &&  // & & *  
                map[i][j+3]   == check &&  // & & & @ 
                map[i][j+2] != 0) { return {j+2}; }

            if (map[i+3][j]   == check &&  // @
                map[i+2][j+1] == check &&  // & @
                map[i+1][j+2] == check &&  // & & @ 
                map[i][j+3]   == 0     &&  // & & & *
                (i == 0 || (i >= 1 && map[i-1][j+3] != 0))) { return {j+3}; }
        }
    }
    for (int i = 0; i < rowNum; i++) {
        for (int j =0; j < colNum -3;j++) {

            if (map[i][j]   == 0     && // * @ @ @
                map[i][j+1] == check && 
                map[i][j+2] == check && 
                map[i][j+3] == check && 
                (i == 0 || (i > 0 && map[i-1][j] != 0))) { return {j}; }

            if (map[i][j]   == check && // @ * @ @
                map[i][j+1] == 0     && 
                map[i][j+2] == check && 
                map[i][j+3] == check && 
                (i == 0 || (i > 0 && map[i-1][j+1] != 0))) { return {j+1}; }

            if (map[i][j]   == check && // @ @ * @
                map[i][j+1] == check && 
                map[i][j+2] == 0     && 
                map[i][j+3] == check && 
                (i == 0 || (i > 0 && map[i-1][j+2] != 0))) { return {j+2}; }

            if (map[i][j]   == check && // @ @ @ *
                map[i][j+1] == check && 
                map[i][j+2] == check && 
                map[i][j+3] == 0     && 
                (i == 0 || (i > 0 && map[i-1][j+3] != 0))) { return {j+3}; }
        }
    }
    for (int i = 0; i < rowNum - 3; i++) {
        for (int j = 0 ; j < colNum ; j++) {
            if (map[i][j]   == check && // * 
                map[i+1][j] == check && // @ 
                map[i+2][j] == check && // @ 
                map[i+3][j] == 0)       // @ 
            {  return {j}; } 
        }
    }
    return {-1};
}

C4_Move Connect4::find_block(int check)
{
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < colNum - 3; j++) {
            if (map[i][j] == 0 && map[i][j+1] == 0 && map[i][j+2] == check && map[i][j+3] == check && (i == 0 || (i > 0 && map[i-1][j] != 0))) {
                return {j+1}; // * * @ @
            }
            if (map[i][j] == check && map[i][j+1] == check && map[i][j+2] == 0 && map[i][j+3] == 0 && (i == 0 || (i > 0 && map[i-1][j+3] != 0))) {
                
                return {j+2}; // @ @ * *
            }
            if (map[i][j] == check && map[i][j+1] == check && map[i][j+2] == 0 && map[i][j+3] == 0 && (i == 0 || (i > 0 && map[i-1][j+1] != 0))) {
                return {j+1}; // @ * @ *
            }
            if (map[i][j] == check && map[i][j+1] == check && map[i][j+2] == 0 && map[i][j+3] == 0 && (i == 0 || (i > 0 && map[i-1][j+3] != 0))) {
                
                return {j+2}; // @ @ * *
            }
            
            //  * @ * @
        }
    }
    for(int i = 0; i < rowNum - 3; i++) {
        for(int j = 0; j < colNum - 3; j++) {

            if (map[i][j]     == check &&  //       *
                map[i+1][j+1] == check &&  //     * &
                map[i+2][j+2] == 0     &&  //   @ & &
                map[i+3][j+3] == 0     &&  // @ & & &
                map[i+1][j+2] != 0 && 
                map[i+2][j+3] != 0) { return {j+2}; }

            if (map[i][j]     == 0     && //       @
                map[i+1][j+1] == 0     && //     @ &
                map[i+2][j+2] == check && //   * & &
                map[i+3][j+3] == check && // * & & &
                map[i][j+1] != 0 && 
                (i==0 || (i>=1 && map[i-1][j] != 0))) { return {j+1}; }

            if (map[i+3][j]   == 0     && // *  
                map[i+2][j+1] == 0     && // & * 
                map[i+1][j+2] == check && // & & @  
                map[i][j+3]   == check && // & & & @ 
                map[i+2][j] != 0 && map[i+1][j+1] != 0) { return {j+1}; }

            if (map[i+3][j]   == check && // @
                map[i+2][j+1] == check && // & @
                map[i+1][j+2] == 0     && // & & * 
                map[i][j+3]   == 0     && // & & & *
                map[i][j+2] != 0 && 
                (i == 0 || (i >= 1 && map[i-1][j+3] != 0))) { return {j+2}; }
        }
    }
    return {-1};
}

bool Connect4::make_move(C4_Move& tmove) {
    if (used[tmove.col] >= rowNum) return false;
    else {
        used[tmove.col]++;
        if (rounds % 2 == 1) map[used[tmove.col]-1][tmove.col] = 1;
        else if (rounds % 2 == 0) map[used[tmove.col]-1][tmove.col] = 2;
        history_moves[rounds-1] = tmove;
        rounds++;
        return true;
    }
}

void Connect4::computer_make_move()
{
    C4_Move cmove;

    int check, oppo_check;
    if (firstmover == ChessGame::SUBJECT::COMPUTER) {check = 1; oppo_check = 2;}
    else {check = 2; oppo_check = 1; }

    // finding 1-to-win place 
    cmove = this->find_win(check);
    if (cmove.col != -1) { this->make_move(cmove); return; }

    // if opponent's 1-to-win, block
    cmove = this->find_win(oppo_check);
    if (cmove.col != -1) { this->make_move(cmove); return; }

    // can block opponent
    cmove = this->find_block(oppo_check);
    if (cmove.col != -1) { this->make_move(cmove); return; }

    // can connect myself
    cmove = this->find_block(check); 
    if (cmove.col != -1) { this->make_move(cmove); return; }

    
    //drop a chess on its own chess
    for (int i = 0; i< colNum ;i++) {
        if((used[i] > 0 && used[i] < rowNum && map[used[i]][i] == check)){
            cmove.col = i;
            this-> make_move(cmove);
            return;
        }
    }

    //drop a chess randomly
    std::uniform_int_distribution<> distrib(0, this->colNum - 1);

    bool flag = false;
    do {
        cmove.col = distrib(random_source) % colNum;
        flag = this->make_move(cmove);
    } while (!flag); // Illegal move

    return;
}

ChessGame::SUBJECT Connect4::win_check()
{
    SUBJECT mover_this_round = this->get_mover_this_round();

    int last_move_col = history_moves[rounds-1].col;
    int last_move_row = used[last_move_col] - 1;

    int check = map[last_move_row][last_move_col]; // mover symbol of this round

    int t, cnt = 0;
    //check horizontally
    t = last_move_col;
    cnt = 0;
    while (t >= 0 && map[last_move_row][t] == check) {cnt++; t--; }
    t = last_move_col + 1;
    while (t < colNum && map[last_move_row][t] == check) {cnt++; t++; }
    if (cnt >= 4) {is_game_over = true; return mover_this_round;}

    //check vertically
    t = last_move_row;
    cnt = 0;
    while (t >= 0 && map[t][last_move_col] == check) {cnt++; t--; }
    t = last_move_row + 1;
    while (t < rowNum && map[t][last_move_col] == check) {cnt++; t++; }
    if (cnt >= 4) {is_game_over = true; return mover_this_round;}
    
    //check diagnolly 1
    int ti = last_move_row;
    int tj = last_move_col;
    cnt = 0;
    while (ti >= 0 && tj >=0 && map[ti][tj] == check) {cnt++; ti--; tj--;}
    ti = last_move_row + 1;
    tj = last_move_col + 1;
    while (ti < rowNum && tj < colNum && map[ti][tj] == check) {cnt++; ti++; tj++; }
    if (cnt >= 4) {is_game_over = true; return mover_this_round;}

    //check diagnolly 2
    ti = last_move_row;
    tj = last_move_col;
    cnt = 0;
    while (ti >= 0 && tj < colNum && map[ti][tj] == check) { cnt++; ti--; tj++;}
    ti = last_move_row + 1;
    tj = last_move_col - 1;
    while (ti < rowNum && tj >= 0 && map[ti][tj] == check) { cnt++; ti++; tj--; }
    if (cnt >= 4) {is_game_over = true; return mover_this_round;}
    
    if (rounds == rowNum * colNum) is_game_over = true;

    return ChessGame::SUBJECT::NEUTRAL;
}


