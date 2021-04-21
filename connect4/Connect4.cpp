#include "Connect4.hpp"

using std::cin;
using std::cout;
using std::endl;

void trim(std::string &str)
{
    auto beginning = str.find_first_not_of(" \t");
    auto ending = str.find_last_not_of(" \t");
    if (ending != std::string::npos) str = str.substr(0, ending + 1);
    if (beginning != std::string::npos) str = str.substr(beginning);
}

int get_int_choice_between(int a, int b) {
    static std::string err_msg = "Illegal input! Try again!";
    int choice = a - 1;
    std::string input;
    while (choice < a || choice > b) {
        std::getline(cin, input);
        trim(input);
        try {
            choice = std::stoi(input);
        } catch (...) {
            cout << err_msg << endl;
        }
        if (choice < a || choice > b) cout << err_msg << endl;
    }
    return choice;
}

Connect4::Connect4() {
    std::random_device rd;
    random_source = std::mt19937(rd());

    rowNum = 6;
    colNum = 7; // suggestted colNum should be less than 15;

    map = std::vector<std::vector<int>>(rowNum, std::vector<int>(colNum, 0));
    history_moves = std::vector<C4_Move>(rowNum * colNum, {0});
    used = std::vector<int>(colNum, 0);

    firstmover_symbol = '$';
    secondmover_symbol = '*';
    blank_chessboard_symbol = '-';
}

void Connect4::generate_map() {
    map = std::vector<std::vector<int>>(rowNum, std::vector<int>(colNum, 0));
    history_moves = std::vector<C4_Move>(rowNum * colNum, {0});
    used = std::vector<int>(colNum, 0);
}

void Connect4::reset()
{
    for (int i = 0; i < rowNum; i++)
        for (int j = 0; j < colNum; j++) 
            map[i][j] = 0;
    for (int i = 0; i<rowNum * colNum; i++) history_moves[i].col = 0;
    for (int i = 0; i<colNum; i++) used[i] = 0;
    rounds = 1; 
    is_game_over = false;
}

void Connect4::game_settings()
{
    cout << "# Choose game mode: \n- 1. PvC \n- 2. PvP. " << endl;

    int choice = get_int_choice_between(1,2);

    if (choice == 1) {
        gamemode = ChessGame::GAME_MODE::PVC;
        cout << "# Game mode: Player v.s. Computer" << endl;
        cout << "# Who goes first?\n" << endl;
        cout << "- 1. " << name_tags[ChessGame::SUBJECT::PLAYER] << endl;
        cout << "- 2. " << name_tags[ChessGame::SUBJECT::COMPUTER] << endl;

        choice = get_int_choice_between(1,2);

        if (choice == 1) {
            firstmover  = ChessGame::SUBJECT::PLAYER;
            secondmover = ChessGame::SUBJECT::COMPUTER;
        }
        else {
            firstmover  = ChessGame::SUBJECT::COMPUTER;
            secondmover = ChessGame::SUBJECT::PLAYER;
        }
    }
    else {
        gamemode = ChessGame::GAME_MODE::PVP;
        cout<<"# Game mode: Player v.s. Player"<<endl;
        cout<<"# Who goes first?\n"<<endl;
        cout<<"- 1. "<<name_tags[ChessGame::SUBJECT::PLAYER1]<<endl;
        cout<<"- 2. "<<name_tags[ChessGame::SUBJECT::PLAYER2]<<endl;

        choice = get_int_choice_between(1,2);

        if(choice == 1){
            firstmover  = ChessGame::SUBJECT::PLAYER1;
            secondmover = ChessGame::SUBJECT::PLAYER2;
        }
        else {
            firstmover  = ChessGame::SUBJECT::PLAYER2;
            secondmover = ChessGame::SUBJECT::PLAYER1;
        }
    }
}

void Connect4::change_map_size(bool if_to_reset)
{
    if(if_to_reset)
    {
        rowNum = 6;
        colNum = 7; //suggestted colNums should be less than 15;
    }
    else {
        cout<<"Set the rows and columns you'd like to have:\n";
        cout<<"(Input an integer which's between 4 and 15)\n";
        cout<<"Rows:    "<<rowNum<<" -> ";

        rowNum = get_int_choice_between(4,15);

        cout<<"Columns: "<<colNum<<" -> ";

        colNum = get_int_choice_between(4,15);
    }
    cout<<"Current map size: "<<endl;
    cout<<"Rows:    "<<rowNum<<endl;
    cout<<"Columns: "<<colNum<<endl;
    if (if_to_reset) cout<<"Map size has been reset to the default."<<endl;
    generate_map();
    return;
}

void Connect4::change_symbols(bool if_to_reset)
{
    if(if_to_reset)
    {
        cout<<"First mover : "<<firstmover_symbol<<" -> $"<<endl;
        cout<<"Second mover: "<<secondmover_symbol<<" -> *"<<endl;
        firstmover_symbol = '$';
        secondmover_symbol = '*';
        cout<<"Symbols have been reset to the default."<<endl;
        return;
    }
    cout<<"Input a character for each role:\n";
    std::string input;

    cout<<"First mover : "<<firstmover_symbol<<" -> ";
    std::getline(cin, input);
    trim(input);
    if(input[0] != ' ' && input[0] != '\0') firstmover_symbol = input[0];

    while (blank_chessboard_symbol == firstmover_symbol || firstmover_symbol < 0) {
        cout<<"Please choose a different symbol!"<<endl;
        std::getline(cin, input);
        trim(input);
        if(input[0]!=' '&&input[0]!='\0') secondmover_symbol = input[0];
    }

    cout<<"Second mover: "<<secondmover_symbol<<" -> ";
    std::getline(cin, input);
    trim(input);
    if(input[0]!=' '&&input[0]!='\0') secondmover_symbol = input[0];
    while (secondmover_symbol == firstmover_symbol || blank_chessboard_symbol == secondmover_symbol || secondmover_symbol < 0) {
        cout<<"Please choose a different symbol!"<<endl;
        std::getline(cin, input);
        trim(input);
        if(input[0]!=' '&&input[0]!='\0') secondmover_symbol = input[0];
    }

    cout<<"Symbols have been set as below:\n";
    cout<<"First mover : "<<firstmover_symbol<<endl;
    cout<<"Second mover: "<<secondmover_symbol<<endl;
}

void Connect4::change_tags(bool if_to_reset)
{
    if(if_to_reset)
    {
        cout<<"Tags for PLAYER  : "<<name_tags[ChessGame::SUBJECT::PLAYER  ]<<" -> "<<"Player"  <<endl; name_tags[ChessGame::SUBJECT::PLAYER ] = "Player";
        cout<<"Tags for PLAYER1 : "<<name_tags[ChessGame::SUBJECT::PLAYER1 ]<<" -> "<<"Player 1"<<endl; name_tags[ChessGame::SUBJECT::PLAYER1] = "Player 1";
        cout<<"Tags for PLAYER2 : "<<name_tags[ChessGame::SUBJECT::PLAYER2 ]<<" -> "<<"Player 2"<<endl; name_tags[ChessGame::SUBJECT::PLAYER2] = "Player 2";
        //cout<<"Tags for COMPUTER: "<<name_tags[ChessGame::SUBJECT::COMPUTER]<<" -> "<<"COMPUTER"<<endl; name_tags[ChessGame::SUBJECT::PLAYER2] = "Computer";
        cout<<"Tags have been reset to the default."<<endl;
        return;
    }

    std::string input;
    int choice = -1;
    while (choice != 0)
    {
        cout<<"# Choose one to edit: "<<endl;
        cout<<"- 1. Tags for PLAYER  : "<<name_tags[ChessGame::SUBJECT::PLAYER ]<<endl;
        cout<<"- 2. Tags for PLAYER1 : "<<name_tags[ChessGame::SUBJECT::PLAYER1]<<endl;
        cout<<"- 3. Tags for PLAYER2 : "<<name_tags[ChessGame::SUBJECT::PLAYER2]<<endl;
        cout<<"- 0. Exit."<<endl;

        choice = get_int_choice_between(0, 3);

        if (choice == 1)
        {
            cout << "Tags for PLAYER  : " << name_tags[ChessGame::SUBJECT::PLAYER] << " -> ";
            std::getline(cin, input);
            trim(input);
            if (!input.empty()) name_tags[ChessGame::SUBJECT::PLAYER] = input;
        }
        if (choice == 2)
        {
            cout << "Tags for PLAYER1 : " << name_tags[ChessGame::SUBJECT::PLAYER1] << " -> ";
            std::getline(cin, input);
            trim(input);
            if (!input.empty()) name_tags[ChessGame::SUBJECT::PLAYER1] = input;
        }
        if (choice == 3)
        {
            cout << "Tags for PLAYER2 : " << name_tags[ChessGame::SUBJECT::PLAYER2] << " -> ";
            std::getline(cin, input);
            trim(input);
            if (!input.empty()) name_tags[ChessGame::SUBJECT::PLAYER2] = input;
        }
        if (choice == 0) break;
    }
    cout << "Tags have been set as below:\n";
    cout << "Tags for PLAYER  : " << name_tags[ChessGame::SUBJECT::PLAYER ] << endl;
    cout << "Tags for PLAYER1 : " << name_tags[ChessGame::SUBJECT::PLAYER1] << endl;
    cout << "Tags for PLAYER2 : " << name_tags[ChessGame::SUBJECT::PLAYER2] << endl;
}

void Connect4::custom_settings()
{
    int choice = -1;

    int t_rowNum = rowNum;
    int t_colNum = colNum;
    char t_firstmover_symbol = firstmover_symbol;
    char t_secondmover_symbol = secondmover_symbol;
    while(choice != 0)
    {
        cout<<'\n';
        cout<<"# User settings: \n";
        cout<<"- 1. Change map size;\n";
        cout<<"- 2. Customize chess symbols;\n";
        cout<<"- 3. Customize name tags;\n";
        cout<<"- 4. Return to default settings;\n";
        cout<<"- 0. Exit.\n";

        choice = get_int_choice_between(0,4);

        if(choice == 1) change_map_size();
        else if(choice == 2) change_symbols();
        else if (choice == 3) change_tags();
        else if (choice == 4) {
            change_map_size(true); cout<<endl;
            change_symbols(true); cout<<endl;
            change_tags(true); cout<<endl;
            cout<<"# Settings have been rolled back to the default.\n";
        }
    }
    //cout<<"# Settings configured successfully!"<<endl;
}

void Connect4::play()
{
    int choice = 0;
    while (choice != 1 && choice != 3)
    {
        cout<<"# Welcome to play 'Connect 4' in console!"<<endl;
        cout<<"- 1. Play;\n- 2. Change user prefs;\n- 3. Exit."<<endl;

        choice = get_int_choice_between(1,3);

        if (choice == 2) custom_settings();
        if (choice == 3)
        {
            //release_map();
            return;
        }
    }
    game_settings();

    reset();

    SUBJECT mover_type = firstmover;
    cout<<"# Game starts!"<<endl;
    while(!is_game_over)
    {
        //rounds++;
        display();

        if (rounds % 2 == 1) cout << name_tags[firstmover] << "'s turn: ";
        else cout << name_tags[secondmover] << "'s turn: ";

        if (mover_type == ChessGame::SUBJECT::COMPUTER)
        {
            computer_move();
            mover_type = ChessGame::SUBJECT::PLAYER;
        }
        else 
        {
            player_move();
            if (gamemode == ChessGame::GAME_MODE::PVC) mover_type = ChessGame::SUBJECT::COMPUTER;
            else mover_type = ChessGame::SUBJECT::PLAYER;
        }

        if (rounds == rowNum * colNum) is_game_over = true;
        winner = win_check();
    }

    display();

    cout<<"# Would you like to try again?"<<endl;
    cout<<"- 1. Yes; \n- 2. No. "<<endl;

    choice = get_int_choice_between(1,2);

    if (choice == 1) return play();
    else if (choice == 2) return;
}

void Connect4::output_map()
{
    cout<<endl;

    int SPACE_NUM = 10;
    int current_row = 1;

    for (int i = rowNum - 1; i >= 0; i--)
    {
        for (int k = 0; k < SPACE_NUM; k++) cout<<' ';
        
        for (int j = 0; j < colNum; j++) {
            if (map[i][j] == 1) cout << firstmover_symbol << ' ';
            else if (map[i][j] == 2) cout << secondmover_symbol << ' ';
            else cout << blank_chessboard_symbol << ' ';
        }
        if(current_row == 1) cout<<"   "<<firstmover_symbol<<": "<<name_tags[firstmover];
        if(current_row == 2) cout<<"   "<<secondmover_symbol<<": "<<name_tags[secondmover];
        current_row++;
        cout<<endl;
    }
    for (int k = 0; k < SPACE_NUM; k++) cout<<' ';
    
    for (int m = 0; m < colNum - 1; m++) cout<<"--";
    cout<<'-'<<endl;
    
    for (int k = 0; k < SPACE_NUM; k++) cout<<' ';
    
    if (colNum < 10) {
        for (int m = 0; m < colNum; m++) cout<<m+1<<' ';
    }
    else {
        for (int m = 0; m < 9; m++) cout<<m+1<<' ';
        for (int m = 9; m < colNum; m++)cout<<char('A'+m-10+1)<<' ';
    }
    cout<<endl;
}

void Connect4::display()
{
    output_map();
    if (is_game_over) {
        cout << "Game over! ";
        if (winner == firstmover) cout << name_tags[firstmover] << " wins!"<<endl;
        else if (winner == secondmover) cout << name_tags[secondmover] << " wins!"<<endl;
        else if (winner == ChessGame::SUBJECT::NEUTRAL) cout << "Draw!"<<endl;
    }
    if (is_game_over) cout << "Total rounds: " << rounds << endl;
    else cout << "Round: " << rounds << endl;
    cout<<"History: ";
    for (int i = 0; i < rounds - 1; i++) cout<<history_moves[i].col + 1<<' ';
    cout<<endl;
}

bool Connect4::make_move(C4_Move& tmove)
{
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

void Connect4::player_move()
{
    int choice;
    C4_Move usr_move;
    bool flag = false;
    while(!flag)
    {
        choice = get_int_choice_between(1,colNum);

        usr_move = {choice-1};
        flag = make_move(usr_move);
        if (!flag) cout<<"Illegal move! Try again.\n";
    }
}

bool Connect4::find_win(int check, C4_Move& cmove)
{
    for(int i = 0; i < rowNum - 3; i++) {
        for(int j = 0; j < colNum - 3; j++) {
            if (map[i][j] == check && map[i+1][j+1] == check && map[i+2][j+2] == check && map[i+3][j+3] == 0 && map[i+2][j+3] != 0) 
            {                      //       *
                cmove.col = j + 3; //     @ &
                //make_move(cmove);//   @ & &
                return true;       // @ & & &
            }
            if (map[i][j] == check && map[i+1][j+1] == check && map[i+2][j+2] == 0 && map[i+3][j+3] == check && map[i+1][j+2] != 0) 
            {                      //       @
                cmove.col = j + 2; //     * &
                //make_move(cmove);//   @ & &
                return true;       // @ & & &
            }
            if (map[i][j] == check && map[i+1][j+1] == 0 && map[i+2][j+2] == check && map[i+3][j+3] == check && map[i][j+1] != 0) 
            {                      //       @
                cmove.col = j + 1; //     @ &
                //make_move(cmove);//   * & &
                return true;       // @ & & &
            }
            if (map[i][j] == 0  && map[i+1][j+1] == check && map[i+2][j+2] == check && map[i+3][j+3] == check && (i==0 ||( i>=1 && map[i-1][j] != 0))) 
            {                      //       @
                cmove.col = j;     //     @ &
                //make_move(cmove);//   @ & &
                return true;       // * & & &
            }
            if (map[i+3][j] == 0 && map[i+2][j+1] == check && map[i+1][j+2] == check && map[i][j+3] == check && map[i+2][j] != 0) 
            {                      // *
                cmove.col = j;     // & @
                //make_move(cmove);// & & @ 
                return true;       // & & & @
            }
            if (map[i+3][j] == check && map[i+2][j+1] == 0 && map[i+1][j+2] == check && map[i][j+3] == check && map[i+1][j+1] != 0) 
            {                      // @
                cmove.col = j+1;   // & *
                //make_move(cmove);// & & @ 
                return true;       // & & & @
            }
            if (map[i+3][j] == check && map[i+2][j+1] == check && map[i+1][j+2] == 0 && map[i][j+3] == check && map[i][j+2] != 0) 
            {                      // @
                cmove.col = j+2;   // & @
                //make_move(cmove);// & & * 
                return true;       // & & & @
            }
            if (map[i+3][j] == check && map[i+2][j+1] == check && map[i+1][j+2] == check && map[i][j+3] == 0 && (i==0 || (i>=1 && map[i-1][j+3] != 0))) 
            {                      // @
                cmove.col = j+3;   // & @
                //make_move(cmove);// & & @ 
                return true;       // & & & *
            }
        }
    }
    for (int i = 0; i< rowNum ;i++) {
        for (int j =0; j < colNum -3;j++) {
            if(map[i][j] == 0 && map[i][j+1] == check && map[i] [j+2] == check && map[i][j+3] == check && (i == 0 || (i>0 && map[i-1][j] != 0))) {
                // * @ @ @
                cmove.col = j;
                return true;
            }
            if(map[i][j] == check && map[i][j+1] == 0 && map[i][j+2] == check && map[i][j+3] == check && (i == 0 || (i>0 && map[i-1][j+1] != 0))) {
                // @ * @ @
                cmove.col = j+1;
                return true;
            }
            if(map[i][j] == check && map[i][j+1] == check && map[i][j+2] == 0 && map[i][j+3] == check && (i == 0 || (i>0 && map[i-1][j+2] != 0))) {
                // @ @ * @
                cmove.col = j+2;
                return true;
            }
            if(map[i][j] == check && map[i][j+1] == check && map[i] [j+2] == check && map[i][j+3] == 0 && (i == 0 || (i>0 && map[i-1][j+3] != 0))) {
                // @ @ @ *
                cmove.col = j+3;
                return true;
            }
        }
    }
    for (int i = 0; i < rowNum - 3; i++) {
        for (int j = 0 ; j < colNum ; j++) {
            if (map[i][j]==check && map[i+1][j]==check  && map[i+2][j] == check && map[i+3][j] == 0){
                                    // *
                cmove.col = j;      // @
                //make_move(cmove); // @
                return true;        // @
            }
        }
    }
    return false;
}

bool Connect4::find_block(int check, C4_Move& cmove)
{
    //C4_Move cmove;
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < colNum - 3; j++) {
            if (map[i][j] == 0 && map[i][j+1] == 0 && map[i][j+2] == check && map[i][j+3] == check && (i == 0 || (i > 0 && map[i-1][j] != 0))) {
                // * * @ @
                cmove.col = j+1;
                return true;
            }
            if (map[i][j] == check && map[i][j+1] == check && map[i][j+2] == 0 && map[i][j+3] == 0 && (i == 0 || (i > 0 && map[i-1][j+3] != 0))) {
                // @ @ * *
                cmove.col = j+2;
                return true;
            }
            if (map[i][j] == check && map[i][j+1] == check && map[i][j+2] == 0 && map[i][j+3] == 0 && (i == 0 || (i > 0 && map[i-1][j+1] != 0))) {
                // @ * @ *
                cmove.col = j+2;
                return true;
            }
            if (map[i][j] == check && map[i][j+1] == check && map[i][j+2] == 0 && map[i][j+3] == 0 && (i == 0 || (i > 0 && map[i-1][j+3] != 0))) {
                // @ @ * *
                cmove.col = j+2;
                return true;
            }
            
            //  * @ * @
        }
    }
    for(int i = 0; i < rowNum - 3; i++) {
        for(int j = 0; j < colNum - 3; j++) {
            if (map[i][j] == check && map[i+1][j+1] == check && map[i+2][j+2] == 0 && map[i+3][j+3] == 0 && map[i+1][j+2] != 0 && map[i+2][j+3] != 0) 
            {                        //       *
                cmove.col = j+2;     //     * &
                //make_move(cmove);  //   @ & &
                return true;         // @ & & &
            }
            if (map[i][j] == 0  && map[i+1][j+1] == 0 && map[i+2][j+2] == check && map[i+3][j+3] == check && map[i][j+1] != 0 && (i==0 ||( i>=1 && map[i-1][j] != 0))) 
            {                        //       @
                cmove.col = j+1;     //     @ &
                //make_move(cmove);  //   * & &
                return true;         // * & & &
            }
            if (map[i+3][j] == 0 && map[i+2][j+1] == 0 && map[i+1][j+2] == check && map[i][j+3] == check && map[i+2][j] != 0 && map[i+1][j+1] != 0) 
            {                      // *
                cmove.col = j+1;   // & *
                //make_move(cmove);// & & @ 
                return true;       // & & & @
            }
            if (map[i+3][j] == check && map[i+2][j+1] == check && map[i+1][j+2] == 0 && map[i][j+3] == 0 && map[i][j+2] != 0 && (i==0 || (i>=1 && map[i-1][j+3] != 0))) 
            {                      // @
                cmove.col = j+2;   // & @
                //make_move(cmove);// & & * 
                return true;       // & & & *
            }
        }
    }
    return false;
}

// void Connect4::redo()
// {
//     int recent_col = history_moves[rounds-1].col;
//     map[used[recent_col]][recent_col] = 0;
//     rounds--;
// }

void Connect4::computer_move()
{
    C4_Move cmove;

    int check, oppo_check;
    if (firstmover == ChessGame::SUBJECT::COMPUTER) {check = 1; oppo_check = 2;}
    else {check = 2; oppo_check = 1; }

    //finding 1-to-win place 
    if(find_win(check,cmove)) {make_move(cmove); cout<<history_moves[rounds-1].col<<endl; return;}
    //if opponent's 1-to-win
    if(find_win(oppo_check,cmove)) {make_move(cmove); cout<<history_moves[rounds-1].col<<endl; return;}

    if(find_block(check,cmove)) {make_move(cmove); cout<<history_moves[rounds-1].col<<endl; return;}
    if(find_block(oppo_check,cmove)) {make_move(cmove); cout<<history_moves[rounds-1].col<<endl; return;}
    
    //drop a chess on its own chess
    for (int i = 0; i< colNum ;i++) {
        if((used[i] > 0 && used[i]<rowNum && map[used[i]][i] == check)){
            cmove.col = i;
            make_move(cmove);
            cout<<cmove.col<<endl;
            return;
        }
    }

    //drop a chess randomly
    
    std::uniform_int_distribution<> distrib(0, this->colNum - 1);

    int choice = distrib(random_source) % colNum;
    cmove = {choice};
    bool flag = make_move(cmove);
    while(!flag)
    {
        //cout<<"Illegal move! Try again. ";
        choice = distrib(random_source) % colNum;
        cmove = {choice};
        flag = make_move(cmove);
    }
    cout<<cmove.col<<endl;

    return;
}

ChessGame::SUBJECT Connect4::win_check()
{
    SUBJECT mover_this_round;
    if (rounds % 2 == 1) {
        mover_this_round = firstmover;
    }
    else {
        mover_this_round = secondmover;
    }

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
    
    return ChessGame::SUBJECT::NEUTRAL;
}
