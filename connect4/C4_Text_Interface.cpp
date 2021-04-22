#include "C4_Text_Interface.hpp"

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

C4_Text_Interface::C4_Text_Interface() {

    instance = std::make_shared<Connect4>();

    this->firstmover_symbol         = '$';
    this->secondmover_symbol        = '*';
    this->blank_chessboard_symbol   = '-';
}

void C4_Text_Interface::gamemode_firstmover_setting_UI() {
    cout << "# Choose game mode: \n- 1. PvC \n- 2. PvP. " << endl;

    int choice = get_int_choice_between(1,2);

    if (choice == 1) {
        instance->set_game_mode(ChessGame::GAME_MODE::PVC);
        cout << "# Game mode: Player v.s. Computer" << endl;
        cout << "# Who goes first?\n" << endl;
        cout << "- 1. " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER  ) << endl;
        cout << "- 2. " << instance->get_name_tag(ChessGame::SUBJECT::COMPUTER) << endl;

        choice = get_int_choice_between(1,2);

        if (choice == 1) {
            instance->set_firstmover  (ChessGame::SUBJECT::PLAYER  );
            instance->set_secondmover (ChessGame::SUBJECT::COMPUTER);
        }
        else {
            instance->set_firstmover  (ChessGame::SUBJECT::COMPUTER);
            instance->set_secondmover (ChessGame::SUBJECT::PLAYER  );
        }
    }
    else {
        instance->set_game_mode(ChessGame::GAME_MODE::PVP);

        cout<<"# Game mode: Player v.s. Player"<<endl;
        cout<<"# Who goes first?\n"<<endl;
        cout << "- 1. " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER1) << endl;
        cout << "- 2. " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER2) << endl;

        choice = get_int_choice_between(1,2);

        if(choice == 1){
            instance->set_firstmover  (ChessGame::SUBJECT::PLAYER1);
            instance->set_secondmover (ChessGame::SUBJECT::PLAYER2);
        }
        else {
            instance->set_firstmover  (ChessGame::SUBJECT::PLAYER2);
            instance->set_secondmover (ChessGame::SUBJECT::PLAYER1);
        }
    }
}

void C4_Text_Interface::symbols_change_UI() {
    std::string input;

    cout<<"Input a character for each role:\n";

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

auto C4_Text_Interface::get_usr_map_size() {
    cout << "Set the rows and columns you'd like to have:\n";
    cout << "(Input an integer which's between 4 and 15)\n";

    cout << "Rows:    " << instance->get_row() << " -> ";
    int rowNum = get_int_choice_between(4,15);

    cout << "Columns: " << instance->get_col() << " -> ";
    int colNum = get_int_choice_between(4,15);

    return std::pair<int, int>(rowNum, colNum);
}

void C4_Text_Interface::mapsize_change_with_notif(int rowNum, int colNum) {

    instance->resize_to(rowNum, colNum);
    //instance->reset();

    cout << "Current map size: " << endl;
    cout << "Rows:    " << instance->get_row() << endl;
    cout << "Columns: " << instance->get_col() << endl;
}

void C4_Text_Interface::change_tags_UI() {
    std::string input;
    int choice = -1;
    while (choice != 0)
    {
        cout << "# Choose one to edit: " << endl;
        cout << "- 1. Tags for PLAYER  : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER ) << endl;
        cout << "- 2. Tags for PLAYER1 : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER1) << endl;
        cout << "- 3. Tags for PLAYER2 : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER2) << endl;
        cout << "- 0. Exit." << endl;

        choice = get_int_choice_between(0, 3);

        if (choice == 1)
        {
            cout << "Tags for PLAYER  : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER ) << " -> ";
            std::getline(cin, input);
            trim(input);
            if (!input.empty()) instance->set_name_tag(ChessGame::SUBJECT::PLAYER, input);
        }
        if (choice == 2)
        {
            cout << "Tags for PLAYER1 : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER1) << " -> ";
            std::getline(cin, input);
            trim(input);
            if (!input.empty()) instance->set_name_tag(ChessGame::SUBJECT::PLAYER1, input);
        }
        if (choice == 3)
        {
            cout << "Tags for PLAYER2 : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER2) << " -> ";
            std::getline(cin, input);
            trim(input);
            if (!input.empty()) instance->set_name_tag(ChessGame::SUBJECT::PLAYER2, input);
        }
        if (choice == 0) break;
    }
    cout << "Tags have been set as below:\n";
    cout << "Tags for PLAYER  : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER ) << endl;
    cout << "Tags for PLAYER1 : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER1) << endl;
    cout << "Tags for PLAYER2 : " << instance->get_name_tag(ChessGame::SUBJECT::PLAYER2) << endl;
}

void C4_Text_Interface::custom_settings() {
    int choice = -1;
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

        if(choice == 1) {
            auto p = this->get_usr_map_size();
            mapsize_change_with_notif(p.first, p.second);
        }
        else if(choice == 2) symbols_change_UI();
        else if (choice == 3) change_tags_UI();
        else if (choice == 4) {
            // resotre mapsize
            mapsize_change_with_notif(6, 7);
            cout << "Map size has been reset to the default." << endl;

            // restore symbols
            cout << "First mover : " << firstmover_symbol  << " -> $" << endl;
            cout << "Second mover: " << secondmover_symbol << " -> *" << endl;
            firstmover_symbol  = '$';
            secondmover_symbol = '*';
            cout<<"Symbols have been reset to the default."<<endl;

            // restore tags
            cout<<"Tags for PLAYER  : "<< instance->get_name_tag(ChessGame::SUBJECT::PLAYER ) <<" -> "<<"Player"  <<endl; 
            instance->set_name_tag(ChessGame::SUBJECT::PLAYER , "Player"  );
            
            cout<<"Tags for PLAYER1 : "<< instance->get_name_tag(ChessGame::SUBJECT::PLAYER1) <<" -> "<<"Player 1"<<endl; 
            instance->set_name_tag(ChessGame::SUBJECT::PLAYER1, "Player 1");
            
            cout<<"Tags for PLAYER2 : "<< instance->get_name_tag(ChessGame::SUBJECT::PLAYER2) <<" -> "<<"Player 2"<<endl; 
            instance->set_name_tag(ChessGame::SUBJECT::PLAYER2, "Player 2");

            // cout<<"Tags for COMPUTER: "<< instance->get_name_tag(ChessGame::SUBJECT::COMPUTER) <<" -> "<<"Computer"<<endl; 
            // instance->set_name_tag(ChessGame::SUBJECT::COMPUTER, "Computer");

            cout<<"Tags have been reset to the default."<<endl;

            cout<<"# Settings have been rolled back to the default.\n";
        }
    }
    //cout<<"# Settings configured successfully!"<<endl;
}

void C4_Text_Interface::output_map() {
    cout<<endl;

    auto map = instance->get_map();
    auto rowNum = instance->get_row();
    auto colNum = instance->get_col();

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
        if(current_row == 1) cout << "   " << firstmover_symbol  << ": " << instance->get_name_tag(instance->get_firstmover ());
        if(current_row == 2) cout << "   " << secondmover_symbol << ": " << instance->get_name_tag(instance->get_secondmover());
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

void C4_Text_Interface::display_status() {
    // print map
    output_map();
    // print info
    auto current_rounds = instance->get_rounds();
    if (instance->is_over()) {
        cout << "Game over! ";
        if (winner == ChessGame::SUBJECT::NEUTRAL) { cout << "Draw!"<<endl; }
        else {
            std::cout << instance->get_name_tag(winner) << " wins!"<<endl;
        }
        cout << "Total rounds: " << current_rounds << endl;
    }
    else { cout << "Round: " << current_rounds << endl; }
    cout << "History: ";
    for (int i = 0; i < current_rounds - 1; i++) cout << instance->get_history_moves()[i].col + 1 <<' ';
    cout<<endl;
}

void C4_Text_Interface::get_player_move_input() {
    int choice;
    C4_Move usr_move;
    bool flag = false;
    while(!flag)
    {
        choice = get_int_choice_between(1, instance->get_col());

        usr_move = {choice-1};
        flag = instance->make_move(usr_move);
        if (!flag) cout<<"Illegal move! Try again.\n";
    }
}

void C4_Text_Interface::play() {
    int choice = 0;
    while (choice != 1 && choice != 3)
    {
        cout<<"# Welcome to play 'Connect 4' in console!"<<endl;
        cout<<"- 1. Play;\n- 2. Change user prefs;\n- 3. Exit."<<endl;

        choice = get_int_choice_between(1,3);

        if (choice == 2) this->custom_settings();
        if (choice == 3) { return; }
    }

    this->gamemode_firstmover_setting_UI();

    instance->reset();

    cout<<"# Game starts!"<<endl;

    while(!instance->is_over())
    {
        //rounds++;
        display_status();

        auto mover_this_round = instance->get_mover_this_round();

        std::cout << instance->get_name_tag(mover_this_round) << "'s turn: ";

        if (mover_this_round == ChessGame::SUBJECT::COMPUTER)
        {
            instance->computer_make_move();
        }
        else 
        {
            get_player_move_input();
        }

        winner = instance->win_check();
    }

    display_status();

    cout<<"# Would you like to try again?"<<endl;
    cout<<"- 1. Yes; \n- 2. No. "<<endl;

    choice = get_int_choice_between(1,2);

    if (choice == 1) return play();
    else if (choice == 2) return;
}
