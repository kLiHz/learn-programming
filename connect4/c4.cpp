#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

//struct ChessMove;

class ChessGame
{
protected:
    int rounds;
    bool is_game_over;
public:
    enum SUBJECT {NEUTRAL, PLAYER1, PLAYER2, COMPUTER};
    enum GAME_MODE {DEFAULT, PVP, PVC};
    
    SUBJECT firstmover, next_mover;
    GAME_MODE gamemode;

    ChessGame();
    int get_int_choice(int a, int b);

    virtual ~ChessGame();
    virtual SUBJECT play() = 0;
};
ChessGame::ChessGame()
{
    rounds = 0;
    is_game_over = false;
}
ChessGame::~ChessGame()
{
}
int ChessGame::get_int_choice(int a, int b)
{
    int choice = a - 1;
    char input[32];
    while (choice < a || choice > b)
    {
        cin.getline(input,30);
        choice = atoi(input);
        if (choice < a || choice > b) cout<<"Illegal input! Try again!"<<endl;
    }
    return choice;
}

struct C4_Move
{
    int col;
};

class Connect4 : public ChessGame
{
private:
    int rowNum;// = 6;
    int colNum;// = 7;

    //int map[6][7];
    int **map;
    //int used[7];
    int *used;
    //C4_Move history_moves[6*7];
    C4_Move* history_moves;

    void player_move();
    bool c_find_1_to_win(int check);
    void computer_move();
    bool make_move(C4_Move&);

    void output_map();
    void display();
    void reset();
    SUBJECT win_check(SUBJECT last_mover);

public:
    virtual SUBJECT play();
    Connect4();
    virtual ~Connect4();
};
Connect4::Connect4() {
    //memset(map, 0, sizeof(map));
    //memset(used, 0, sizeof(used));
    firstmover = NEUTRAL;
    gamemode = DEFAULT;
    map = NULL;
    history_moves = NULL;
}
Connect4::~Connect4()
{
}
void Connect4::reset()
{
    for (int i = 0; i< rowNum; i++)
    {
        for (int j = 0;j<colNum; j++)
        {
            map[i][j] = 0;
        }
    }
    for (int i = 0; i<rowNum * colNum; i++)
    {
        history_moves[i].col = 0;
    }
    for (int i = 0; i<colNum; i++)
    {
        used[i] = 0;
    }
}
ChessGame::SUBJECT Connect4::play()
{
    cout<<"Welcome to the game 'Connect 4' in console!"<<endl;
    cout<<"Chose the game mode: \n- 1. PvC \n- 2. PvP. "<<endl;
    int choice = get_int_choice(1,2);
    if (choice == 1) {
        gamemode = PVC;
        cout<<"Game mode: Player v.s. Computer"<<endl;
        cout<<"Who goes first? \n- 1. Player \n- 2. Computer"<<endl;
        choice = get_int_choice(1,2);
        if (choice == 1) {
            firstmover = PLAYER1;
        }
        else firstmover = COMPUTER;
    }
    else {
        gamemode = PVP;
        cout<<"Game mode: Player v.s. Player"<<endl;
        cout<<"Who goes first? \n- 1. Player1 \n- 2. Player2"<<endl;
        choice = get_int_choice(1,2);
        if(choice == 1){
            firstmover = PLAYER1;
        }
        else firstmover = PLAYER2;
    }

    rowNum = 6;
    colNum = 7; //suggestted colNums should be less than 15;

    map = new int* [rowNum];
    for (int i= 0; i<rowNum;i++){
        map[i] = new int [colNum];
    }
    history_moves = new C4_Move [rowNum * colNum];
    used = new int [colNum];

    reset();

    next_mover = firstmover;
    SUBJECT winner;
    cout<<"Game starts!"<<endl;
    while(!is_game_over)
    {
        rounds++;
        display();
        SUBJECT last_mover = next_mover;
        if (next_mover == PLAYER1)
        {
            if (gamemode == PVC) {
                cout<<"Player's turn: "; 
                player_move();
                next_mover = COMPUTER;
            }
            else if (gamemode == PVP) {
                cout<<"Player 1's turn: ";
                player_move();
                next_mover = PLAYER2;
            }
        }
        else if (next_mover == PLAYER2)
        {
            cout<<"Player 2's turn: ";
            player_move();
            next_mover = PLAYER1;
        }
        else if (next_mover == COMPUTER)
        {
            cout<<"Computer's turn: ";
            computer_move();
            next_mover = PLAYER1;
        }
        winner = win_check(last_mover);
        if (rounds == rowNum * colNum) is_game_over = true;
    }
    display();

    for (int i = 0; i< rowNum;i++)
    {
        delete[] map[i];
    }
    delete[] map;
    delete[] history_moves;

    return winner;
}
void Connect4::output_map()
{
    cout<<endl;

    int SPACE_NUM = 10;
    int current_row = 1;

    //@,1 for firstmover
    for (int i = rowNum - 1; i >= 0; i--)
    {
        for (int k = 0; k < SPACE_NUM; k++) cout<<' ';
        for (int j = 0; j < colNum; j++) {
            if (map[i][j] == 1) cout << '@' << ' ';
            else if (map[i][j] == 2) cout << '$' << ' ';
            else cout << '.' << ' ';
        }
        if(current_row == 1) {
            cout<<"   @: ";
            if (gamemode == PVP)
            {
                if (firstmover == PLAYER1) cout<<"Player 1";
                else if (firstmover == PLAYER2) cout<<"Player 2";
            }
            else if (gamemode == PVC)
            {
                if (firstmover == PLAYER1) cout<<"Player";
                else if (firstmover == COMPUTER) cout<<"Computer";
            }
        }
        if(current_row == 2){
            cout<<"   $: ";
            if (gamemode == PVP)
            {
                if (firstmover == PLAYER1) cout<<"Player 2";
                else if (firstmover == PLAYER2) cout<<"Player 1";
            }
            else if (gamemode == PVC)
            {
                if (firstmover == PLAYER1) cout<<"Computer";
                else if (firstmover == COMPUTER) cout<<"Player";
            }
        }
        current_row++;
        cout<<endl;
    }
    for (int k = 0; k < SPACE_NUM; k++) cout<<' ';
    for (int m = 0; m < colNum - 1; m++) cout<<"--";
    cout<<'-';
    cout<<endl;
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
    cout<<"Round: "<< rounds<<endl;
    cout<<"History: ";
    for (int i = 0; i < rounds - 1; i++) cout<<history_moves[i].col + 1<<' ';
    cout<<endl;
}
bool Connect4::make_move(C4_Move& tmove)
{
    if (used[tmove.col] >= rowNum) return false;
    else {
        if (next_mover == firstmover) map[used[tmove.col]++][tmove.col] = 1;
        else map[used[tmove.col]++][tmove.col] = 2;
        history_moves[rounds-1] = tmove;
        return true;
    }
}
void Connect4::player_move()
{
    int choice = get_int_choice(1,colNum);
    C4_Move usr_move = {choice-1};
    bool flag = make_move(usr_move);
    while(!flag)
    {
        cout<<"Illegal move! Try again. ";
        choice = get_int_choice(1,colNum);
        usr_move = {choice-1};
        flag = make_move(usr_move);
    }
}
bool Connect4::c_find_1_to_win(int check)
{
    C4_Move cmove;
    /*
    for (int i = 0; i < rowNum; i++)
    {
        for (int j = 0; j < colNum; i++)
        {
            if (map[i][j]==check)
            {
                int ti = i, tj = j;

                int cnt = 0;
                
                //check vertically
                while(ti >= 0 && map[ti][j]==check) {ti--; cnt++;}
                ti = i+1;
                while(ti < rowNum && map[ti][j] == check) {ti++; cnt++;}
                if (cnt == 3 && ti < rowNum && map[i][ti] == 0) { cmove.col = j; make_move(cmove); return true;}
                
                //check diagnally 1
                cnt = 0;
                ti = i; tj= j;
                while (ti >= 0 && tj >= 0 && map[ti][tj] == check) {ti--;tj--;cnt++;}
                int bl_i = ti, bl_j = tj; 
                ti = i+1; tj = j+1;
                while (ti < rowNum && tj < colNum && map[ti][tj] == check) {ti++; tj++; cnt++; }
                int tr_i = ti, tr_j = tj;
                if (cnt == 3) {
                    if (bl_i >= 0 && bl_j >= 0 && map[bl_i][bl_j] == 0 && (bl_i == 0 || (bl_i-1 >= 0 && map[bl_i-1][bl_j] != 0))) {cmove.col = bl_j; make_move(cmove); return true;}
                    if (tr_i < rowNum && tr_j < colNum && map[tr_i][tr_j] == 0 && tr_i-1 > 0 && map[tr_i-1][tr_j] != 0) {cmove.col = tr_j; make_move(cmove); return true;}
                }
                if (cnt == 2)
                {
                    if(bl_i-1 >= 0 && bl_j-1 >= 0 && map[bl_i][bl_j] == 0 && map[bl_i-1][bl_j] != 0 && map [bl_i-1][bl_j-1] == check) {cmove.col = bl_j; make_move(cmove); return true;}
                    if(tr_i+1 < rowNum && tr_j+1 < colNum && map[tr_i][tr_j] == 0 && map[tr_i-1][tr_j] != 0 && map[tr_i+1][tr_j+1] == check) {cmove.col = tr_j; make_move(cmove); return true;}
                }
                //check diagnally 2
                cnt = 0;
                ti = i; tj = j;
                while(map[ti][tj] == check && ti >= 0 && tj < colNum) {ti--;tj++;cnt++;}
                int br_i = ti, br_j = tj; 

                ti = i+1; tj = j-1;
                while(map[ti][tj] == check && ti < rowNum && tj >= 0 ) {ti++; tj--; cnt++; }
                int tl_i = ti, tl_j = tj;

                if (cnt == 3) {
                    if (br_i-1 >= 0 && br_j < colNum && map[br_i][br_j] == 0 && map[br_i-1][br_j] != 0) { cmove.col = br_j; make_move(cmove); return true;}
                    if (tl_i < rowNum && tl_j >= 0 && map[tl_i][tl_j] == 0 && map[tl_i-1][tl_j] != 0) { cmove.col = tl_j; make_move(cmove); return true;}
                }
                if (cnt == 2) {
                    if (br_i-1 >= 0 && br_j+1 < colNum && map[br_i][br_j] == 0 && map[br_i-1][br_j] != 0 && map[br_i-1][br_j+1] == check) {cmove.col = br_j; make_move(cmove); return true;}
                    if (tl_i+1 < rowNum && tl_j-1 >= 0 && map[tl_i][tl_j] == 0 && map[tl_i-1][tl_j] != 0 && map[tl_i+1][tl_j-1] == check) {cmove.col = tl_j; make_move(cmove); return true;}
                }
                //check horizontally
                cnt = 0;
                tj = j;
                while(map[i][tj] == check && tj < colNum){tj++; cnt++; }
                int ttj = tj;
                tj = j-1;
                while(map[i][tj] == check && tj >= 0) {tj--; cnt++;}
                if (cnt == 3)
                {
                    if(ttj < colNum && map[i][ttj] == 0 && (i == 0 || i-1>=0 && map[i-1][ttj] != 0) ) { cmove.col = ttj; make_move(cmove); return true;}
                    if(tj >= 0 && map[i][tj] == 0 && (i == 0 || i-1>=0 && map [i-1][tj] != 0)) { cmove.col = tj; make_move(cmove); return true;}
                }
                if(cnt == 2)
                {
                    if(ttj + 1 < colNum && map[i][ttj] == 0 && (i == 0 || i-1>=0 && map[i-1][ttj] != 0) && map[i][ttj+1] == check) { cmove.col = ttj; make_move(cmove); return true;}
                    if(tj - 1 >= 0 && map[i][tj] == 0 && (i == 0 || i-1>=0 && map[i-1][ttj] != 0) && map[i][tj-1] == check) { cmove.col = tj; make_move(cmove); return true;}
                }
            }
        }
    }*/
    for(int i = 0; i < rowNum - 3; i++)
    {
        for(int j = 0; j < colNum - 3; j++)
        {
            if (map[i][j] == check && map[i+1][j+1] == check && map[i+2][j+2] == check && map[i+3][j+3] == 0 && map[i+2][j+3] != 0) 
            {                      //       *
                cmove.col = j + 3; //     @ &
                make_move(cmove);  //   @ & &
                return true;       // @ & & &
            }
            if (map[i][j] == check && map[i+1][j+1] == check && map[i+2][j+2] == 0 && map[i+3][j+3] == check && map[i+1][j+2] != 0) 
            {                      //       @
                cmove.col = j + 2; //     * &
                make_move(cmove);  //   @ & &
                return true;       // @ & & &
            }
            if (map[i][j] == check && map[i+1][j+1] == 0 && map[i+2][j+2] == check && map[i+3][j+3] == check && map[i][j+1] != 0) 
            {                      //       @
                cmove.col = j + 1; //     @ &
                make_move(cmove);  //   * & &
                return true;       // @ & & &
            }
            if (map[i][j] == 0  && map[i+1][j+1] == check && map[i+2][j+2] == check && map[i+3][j+3] == check && (i==0 ||( i>=1 && map[i-1][j] != 0))) 
            {                      //       @
                cmove.col = j + 3; //     @ &
                make_move(cmove);  //   @ & &
                return true;       // * & & &
            }
            if (map[i+3][j] == 0 && map[i+2][j+1] == check && map[i+1][j+2] == check && map[i][j+3] == check && map[i+2][j] != 0) 
            {                      // *
                cmove.col = j;     // & @
                make_move(cmove);  // & & @ 
                return true;       // & & & @
            }
            if (map[i+3][j] == check && map[i+2][j+1] == 0 && map[i+1][j+2] == check && map[i][j+3] == check && map[i+1][j+1] != 0) 
            {                      // @
                cmove.col = j+1;   // & *
                make_move(cmove);  // & & @ 
                return true;       // & & & @
            }
            if (map[i+3][j] == check && map[i+2][j+1] == check && map[i+1][j+2] == 0 && map[i][j+3] == check && map[i][j+2] != 0) 
            {                      // @
                cmove.col = j+2;   // & @
                make_move(cmove);  // & & * 
                return true;       // & & & @
            }
            if (map[i+3][j] == check && map[i+2][j+1] == check && map[i+1][j+2] == check && map[i][j+3] == 0 && (i==0 || (i>=1 && map[i-1][j+3] != 0))) 
            {                      // @
                cmove.col = j;     // & @
                make_move(cmove);  // & & @ 
                return true;       // & & & *
            }
        }
    }
    for (int i = 0; i< rowNum ;i++) {
        for (int j =0; j < colNum -3;j++) {
            if(map[i][j] == 0 && map[i][j+1] == check && map[i] [j+2] == check && map[i][j+3] == check && (i == 0 || (i>0 && map[i-1][j] != 0))) {
                // * @ @ @
                cmove.col = j;
                make_move(cmove);
                return true;
            }
            if(map[i][j] == check && map[i][j+1] == 0 && map[i][j+2] == check && map[i][j+3] == check && (i == 0 || (i>0 && map[i-1][j+1] != 0))) {
                // @ * @ @
                cmove.col = j+1;
                make_move(cmove);
                return true;
            }
            if(map[i][j] == check && map[i][j+1] == check && map[i][j+2] == 0 && map[i][j+3] == check && (i == 0 || (i>0 && map[i-1][j+2] != 0))) {
                // @ @ * @
                cmove.col = j+2;
                make_move(cmove);
                return true;
            }
            if(map[i][j] == check && map[i][j+1] == check && map[i] [j+2] == check && map[i][j+3] == 0 && (i == 0 || (i>0 && map[i-1][j+3] != 0))) {
                // @ @ @ *
                cmove.col = j+3;
                make_move(cmove);
                return true;
            }
        }
    }
    for (int i = 0; i < rowNum - 3; i++)
    {
        for (int j = 0 ; j < colNum ; j++)
        {
            if (map[i][j]==check && map[i+1][j]==check  && map[i+2][j] == check && map[i+3][j] == 0){
                cmove.col = j;
                make_move(cmove);
                return true;
            }
        }
    }
    return false;
}
void Connect4::computer_move()
{
    C4_Move cmove;

    int check, oppo_check;
    if (firstmover == COMPUTER) {check = 1; oppo_check = 2;}
    else {check = 2; oppo_check = 1; }

    //finding 1-to-win place 
    if(c_find_1_to_win(check)) {cout<<history_moves[rounds-1].col<<endl; return;}
    //if opponent's 1-to-win
    if(c_find_1_to_win(oppo_check)) {cout<<history_moves[rounds-1].col<<endl; return;}
    
    for (int i = 0; i< colNum ;i++)
    {
        if(used[i] > 0 && used[i]<rowNum && map[used[i]][i] == check || used[i] == 0 ){
            cmove.col = i;
            make_move(cmove);
            cout<<cmove.col<<endl;
            return;
        }
    }

    int choice = rand() % colNum;
    cmove = {choice};
    bool flag = make_move(cmove);
    while(!flag)
    {
        //cout<<"Illegal move! Try again. ";
        choice = rand() % colNum;
        cmove = {choice};
        flag = make_move(cmove);
    }
    cout<<cmove.col<<endl;

    return;
}
ChessGame::SUBJECT Connect4::win_check(SUBJECT last_mover)
{
    int last_move_col = history_moves[rounds-1].col;
    int last_move_row = used[last_move_col] - 1;

    int check = map[last_move_row][last_move_col];

    int t, cnt = 0;
    //check horizontally
    t = last_move_col;
    cnt = 0;
    while (t >= 0 && map[last_move_row][t] == check) {cnt++; t--; }
    t = last_move_col + 1;
    while (t < colNum && map[last_move_row][t] == check) {cnt++; t++; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}

    //check vertically
    t = last_move_row;
    cnt = 0;
    while (t >= 0 && map[t][last_move_col] == check) {cnt++; t--; }
    t = last_move_row + 1;
    while (t < rowNum && map[t][last_move_col] == check) {cnt++; t++; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}
    
    //check diagnolly 1
    int ti = last_move_row;
    int tj = last_move_col;
    cnt = 0;
    while (ti >= 0 && tj >=0 && map[ti][tj] == check) {cnt++; ti--; tj--;}
    ti = last_move_row + 1;
    tj = last_move_col + 1;
    while (ti < rowNum && tj < colNum && map[ti][tj] == check) {cnt++; ti++; tj++; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}

    //check diagnolly 2
    ti = last_move_row;
    tj = last_move_col;
    cnt = 0;
    while (ti >= 0 && tj < colNum && map[ti][tj] == check) { cnt++; ti--; tj++;}
    ti = last_move_row + 1;
    tj = last_move_col - 1;
    while (ti < rowNum && tj >= 0 && map[ti][tj] == check) { cnt++; ti++; tj--; }
    if (cnt >= 4) {is_game_over = true; return last_mover;}
    return NEUTRAL;
}
int main()
{
    srand((unsigned int)(time(NULL)));
    Connect4 instance;
    ChessGame::SUBJECT winner = instance.play();
    if (instance.gamemode == ChessGame::PVC)
    {
        if (winner == ChessGame::PLAYER1) cout<<"Player wins!"<<endl;
        else if (winner == ChessGame::COMPUTER) cout<<"Computer wins!"<<endl;
        else if (winner == ChessGame::NEUTRAL) cout<<"Draw!"<<endl;
    }
    else if (instance.gamemode == ChessGame::PVP){
        if (winner == ChessGame::PLAYER1) cout<<"Player 1 wins!"<<endl;
        else if (winner == ChessGame::PLAYER2) cout<<"Player 2 wins!"<<endl;
        else if (winner == ChessGame::NEUTRAL) cout<<"Draw!"<<endl;
    }
    return 0;
}
