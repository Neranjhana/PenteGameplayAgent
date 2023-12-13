#include <iostream>
#include <fstream>
#include <iostream>
#include<string>
#include<fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>
#include <utility>
#include <limits>
#include<tuple>
#include <array>
using namespace std;
#include <list>
#include <climits>

using std::istringstream;
using std::string;
using std::cout;


class game_play{
private:
    string board_convention[19][19];
    string player_string;
    float time_remaining;
    int white_capture, black_capture;
    string next_move_value;
    string input_file_path;
    string output_file_path;
    char player;
    char opponent;
    std::pair<int, int> best_coords;
    std::pair<int, int> player_previous_move;
    std::pair<int, int> opponent_previous_move;
    int border_row_max =0;
    int border_row_min = 18;
    int col_max =0;
    int col_min = 18;
    int number_of_pieces=0;
    int player_capture=0;
    int opponent_capture=0;




    //keeps track of the state score
    int state_score;

    //state capture
    int state_capture;

    bool empty;

public:
    string board[19];
    //Constructor with Initialisation
    game_play(string input_file_path_inp, string output_file_path_inp)
    {
        input_file_path = input_file_path_inp;
        output_file_path = output_file_path_inp;
    }

    void read_input_file()
    {
        string input_line;

        std::ifstream MyReadFile(input_file_path);
        int i=0;
        while (getline(MyReadFile, input_line))
        {
            if(i==0){
                player_string = input_line;

            }
            else if(i==1){
                istringstream time_string(input_line);
                time_string >> time_remaining;

            }
            else if(i==2){
                string tmp_capture;
                istringstream capture_string(input_line);
                getline(capture_string, tmp_capture, ',');
                white_capture = stoi(tmp_capture);
                getline(capture_string, tmp_capture, ',');
                black_capture = stoi(tmp_capture);

            }
            else {
                board[i-3] = input_line;

            }
            i = i + 1;

        }

//        cout<<"Read the file"<<"\n";
//        cout<<"current player is"<<player_string<<"\n";
    };

    void find_border_pieces(){
        for(int i=0;i<19;i++){
            for(int j=0;j<19;j++){
                if(board[i][j]!='.'){
                    number_of_pieces+=1;
                    if(i>border_row_max){
                        border_row_max = i;
                    }
                    if(i<border_row_min){
                        border_row_min=i;
                    }
                    if(j>col_max){
                        col_max=j;
                    }
                    if(j<col_min){
                        col_min=j;
                    }

                }
            }
        }
//        cout<<"row max is"<<border_row_max<<"\n";
//        cout<<"row min is"<<border_row_min<<"\n";
//        cout<<"col max is"<<col_max<<"\n";
//        cout<<"col min is"<<col_min<<"\n";
//        cout<<"number of pieces is"<<number_of_pieces;


    };

    std::tuple<int, int> make_initial_moves(){

        std::tuple<int, int> move;
        if(number_of_pieces==0){
            std::get<0>(move)=9;
            std::get<1>(move)=9;

        }
        else if(number_of_pieces ==1){
            std::get<0>(move)=8;
            std::get<1>(move)=9;
        }
        else if(number_of_pieces ==2){
            if(board[6][12]=='.'){
                std::get<0>(move)=6;
                std::get<1>(move)=12;
            }
            else{
                std::get<0>(move)=9;
                std::get<1>(move)=6;
            }

        }
        return move;

    };


    void find_opponent(){

        if(player_string=="BLACK"){
            player='b';
        }
        else if(player_string=="WHITE"){
            player='w';
        }
        else{
//            cout<<"ERROR IN FILE READ";
        }

        if(player =='b'){
            opponent = 'w';
        }
        else{
            opponent = 'b';
        }

        if(player =='w'){
            player_capture=white_capture;
            opponent_capture=white_capture;
        }
        else if(player =='b'){
            player_capture=black_capture;
            opponent_capture=white_capture;
        }
//        cout<<"player is"<<player<<"\n";
//        cout<<"player capture is"<<player_capture<<"\n";
//        cout<<"opponent capture is"<<opponent_capture<<"\n";

    }

    bool check_if_board_empty(){
        int counter =0;
        empty =0;
        for(int i=0; i<19; i++){
            if(board[i] == "..................."){
                counter = counter +1;
            }
        }
        if(counter == 19){
            empty =1;
        }

//        cout<<"Empty is"<<empty<<"\n";
        return empty;

    }

    //Assign a 2D array of strings to map to board conventions
    int create_board_convention(){

        string letter_values[] = {"A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T"};

        //TESTING FOR NL AI
        // string letter_values[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I","J", "K", "L", "M", "N", "O", "P", "Q", "R", "S"};
        for(int i=0; i<19; i++){
            for(int j=0; j<19; j++){
                board_convention[i][j] = to_string(19 - i) +letter_values[j] ;
            }

        }

//        for(int i=0; i<19; i++){
//            for(int j=0; j<19; j++)
//            {
//                cout<<board_convention[i][j]<<" ";
//
//            }
//            cout<<"\n";
//        }

        return 0;


    }

    string next_move(){
        string next_move_value;
        if(empty ==1 and player_string == "WHITE"){
            next_move_value = "10K";
        }
        else
            next_move_value = "XX";

//        cout<<next_move_value<<"\n";
        return next_move_value;

    }

    int get_valid_moves(){

        return 0;

    }


    //Check if a potential move is legal or not. This includes making sure that the cell is empty

    bool check_legal_move(char current_player, std::array<string,19>tmp_board, int x, int y){

        char current_opponent;
        if(current_player=='w'){
            current_opponent='b';
        }
        else{
            current_opponent='w';
        }


        if(x>=0 && x<19 && y>=0 && y<19) {


            if (tmp_board[x][y] != '.') {
                return 0;

            } else {
                //Horizontal prevent capture
                if (x >= 1 && x < 17) {
                    if (tmp_board[x - 1][y] == current_opponent && tmp_board[x + 1][y] == current_player &&
                        tmp_board[x + 2][y] == current_opponent) {
                        return 0;
                    }
                }
                if (x >= 2 && x < 18) {
                    if (tmp_board[x - 2][y] == current_opponent && tmp_board[x - 1][y] == current_player &&
                        tmp_board[x + 1][y] == current_opponent) {
                        return 0;
                    }
                }

                //Vertical prevent capture
                if (y >= 1 && y < 17) {
                    if (tmp_board[x][y - 1] == current_opponent && tmp_board[x][y + 1] == current_player &&
                        tmp_board[x][y + 2] == current_opponent) {
                        return 0;
                    }
                }
                if (y >= 2 && y < 18) {
                    if (tmp_board[x][y - 2] == current_opponent && tmp_board[x][y - 1] == current_player &&
                        tmp_board[x][y + 1] == current_opponent) {
                        return 0;
                    }
                }

                //Diagnol prevent captures
                if (x >= 1 && x < 17 && y >= 1 && y < 17) {
                    if (tmp_board[x - 1][y - 1] == current_opponent && tmp_board[x + 1][y + 1] == current_player &&
                        tmp_board[x + 2][y + 2] == current_opponent) {
                        return 0;
                    }
                }

                if (x >= 2 && x < 18 && y >= 2 && y < 18) {
                    if (tmp_board[x - 2][y - 2] == current_opponent && board[x - 1][y - 1] == current_player &&
                        board[x + 1][y + 1] == current_opponent) {
                        return 0;
                    }
                }

                if (x >= 2 && x < 18 && y >= 1 && y < 17) {
                    if (tmp_board[x + 1][y - 1] == current_opponent && tmp_board[x - 1][y + 1] == current_player &&
                        tmp_board[x - 2][y + 2] == current_player) {
                        return 0;
                    }
                }
                if (x >= 1 && x < 18 && y - 2 >= 0 && y < 18) {
                    if (tmp_board[x + 2][y - 2] == current_opponent && tmp_board[x + 1][y - 1] == current_player &&
                        tmp_board[x - 1][y + 1] == current_opponent) {
                        return 0;
                    }
                }
                return 1;
            }
        }

        else{
            //the coordinates are outside the board - move is invalid
            return 0;
        }
    }

    //Check if game is over
    //player variable can be either w (white) or b (black)

    bool check_game_over(int piece_capture, char player){
        int score;

        //Should chck whether it is 10 or 12
        if(piece_capture>=10){
            //Game over, player wins
        }
        for(int i=0; i<19; i++){
            for(int j=0; j<19; j++) {


                if (board[i][j] == player) {
                    //Check horizontal
                    if (i + 4 < 19 &&  board[i + 1][j] == player && board[i + 2][j] == player && board[i + 3][j] == player && board[i + 4][j] == player) {
                        //player wins
                        score +=1000;
                        return true;
                    }
                        //Check vertical
                    else if (j + 4 < 19 && board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player && board[i][j + 4] == player) {
                        //player wins
                        score +=1000;
                        return true;
                    }

                        //Chck diag right
                    else if (i + 4 < 19 && j + 4 < 19 && board[i+1][j+1]==player && board[i+2][j+2]==player && board[i+3][j+3]==player && board[i+4][j+4]==player){
                        //player wins
                        score +=1000;
                        return true;
                    }
                        //chck diag left
                    else if(i + 4 < 19 && j - 4 >= 0  && board[i+1][j-1] == player && board[i+2][j-2] == player && board[i+3][j-3] == player && board[i+4][j-4] == player){
                        //player wins
                        score +=1000;
                        return true;

                    }

                }

            }
        }
        //Checking for draw. If full board is filled, then draw
        for(int i=0; i<19; i++){
            for(int j=0;j<19; j++){
                if(board[i][j]=='.')
                    return false;
            }
        }

        //Full board is filled, game is over but it is draw
        return true;



    }


    //Check the number of captures possible for the player - Function returns a heuristic value of (no of possible
    //captures by player - no of possible captures by opponent)
    int check_number_of_captures(std::array<string,19> tmp_board, char current_player){

        //current_player can either be w or b


        int capture_count=0;
        char current_opponent;
        int opponent_capture_count=0;
        if(current_player=='w'){
            current_opponent='b';
        }
        else{
            current_opponent='w';
        }


        //Check vertical


        for (int i=0; i<16; i++){
            for(int j=0;j<19;j++){

                if(tmp_board[i][j]==current_player && tmp_board[i+1][j]==current_opponent && tmp_board[i+2][j]==current_opponent && tmp_board[i+3][j]==current_player){
//                    cout<<"\npiece capture vertical\n";
                    capture_count +=7;
                    capture_count+=(player_capture*2);

                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]==current_opponent){
//                    cout<<"\nopponent capture vertical\n";
                    opponent_capture_count += 5;
                    opponent_capture_count += (opponent_capture*2);
                }


            }
        }


        //Check horizontal

        for(int i=0; i<19; i++){
            for(int j=0; j<16; j++){
                if(tmp_board[i][j]==current_player && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_player){
//                    cout<<"\npiece capture horizontal\n";
                    capture_count +=7;
                    capture_count+=(player_capture*2);
                }

                else if(tmp_board[i][j]==current_opponent && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]==current_opponent){
                    opponent_capture_count+=5;
                    opponent_capture_count += (opponent_capture*2);
//                    cout<<"\nopponent capture horizontal\n";
                }
            }
        }

        //diagnol \

        for(int i=0; i<16;i++){
            for(int j=0; j<16;j++){
                if(tmp_board[i][j]==current_player && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]==current_player ){
//                    cout<<"\nplayer capture diag1\n";
                    capture_count+=7;
                    capture_count+=(player_capture*2);
                }

                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]==current_opponent){
//                    cout<<"\nopponent capture diag\n";
                    opponent_capture_count+=5;
                    opponent_capture_count += (opponent_capture*2);
                }

            }
        }

        // diagnol /
        for(int i=3; i<19;i++){
            for(int j=0; j<16;j++){
                if(tmp_board[i][j]==current_player && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]==current_player){
//                    cout<<"\nplayer capture diag2\n";
                    capture_count+=7;
                    capture_count+=(player_capture*2);
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]==current_opponent){
//                    cout<<"\nopponent capture diag\n";
                    opponent_capture_count+=5;
                    opponent_capture_count += (opponent_capture*2);
                }
            }
        }

//        cout<<"The number of captures is"<<capture_count<<"\n";
//        cout<<"The number of opponent captures is"<<opponent_capture_count<<"\n";
        return capture_count-opponent_capture_count;

    }


    //Check for open triads - having an open triad will likely lead to winning (if opponent already doesnt have a 4 in row)

    int check_for_open_triads(char current_player, std::array<string,19> tmp_board){
        int player_triads=0;
        int opponent_triads=0;
        char current_opponent;
        int opponent_capture_count=0;
//        cout<<"current player is"<<current_player<<"\n";
        if(current_player=='w'){
            current_opponent='b';
        }
        else{
            current_opponent='w';
        }


        //Check horizontal
        for(int i=0; i<19;i++){
            for(int j=0;j<15 ;j++){
                if(tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]==current_player && tmp_board[i][j+4]=='.'){
                    player_triads+=5;

                }
                if(tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_opponent && tmp_board[i][j+4]=='.'){
                    opponent_triads+=7;

                }
                //one side closed triads
                if((tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]==current_player) || (tmp_board[i][j+1]==current_player && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]==current_player && tmp_board[i][j+4]==current_player )){
                    player_triads+=1;
                }
                if((tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_opponent) || (tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_opponent && tmp_board[i][j+4]==current_opponent )){
                    opponent_triads+=2;
                }

                //check for alternate triads (eg .WW.W or WW.W. or W.W.W or WW..W)
                if(tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]=='.' && tmp_board[i][j+4]==current_player){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]=='.' && tmp_board[i][j+3]==current_player && tmp_board[i][j+4]=='.'){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i][j+1]=='.' && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]=='.' && tmp_board[i][j+4]==current_player){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]=='.' && tmp_board[i][j+3]=='.' && tmp_board[i][j+4]==current_player){
                    player_triads+=2;
                }

                //for opponent

                if(tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]=='.' && tmp_board[i][j+4]==current_opponent){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]=='.' && tmp_board[i][j+3]==current_opponent && tmp_board[i][j+4]=='.'){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i][j+1]=='.' && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]=='.' && tmp_board[i][j+4]==current_opponent){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]=='.' && tmp_board[i][j+3]=='.' && tmp_board[i][j+4]==current_opponent){
                    opponent_triads+=3;
                }

            }
        }
        //Check vertical

        for(int i=0;i<15;i++){
            for(int j=0; j<19; j++){
                if( tmp_board[i][j]=='.' && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]==current_player && tmp_board[i+4][j]=='.'){
                    player_triads+=5;
                }
                if( tmp_board[i][j]=='.' && tmp_board[i+1][j]==current_opponent && tmp_board[i+2][j]==current_opponent && tmp_board[i+3][j]==current_opponent && tmp_board[i+4][j]=='.'){
                    opponent_triads+=7;
                }

                //Check for one side close triads
                if((tmp_board[i][j]=='.' && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]==current_player) || (tmp_board[i+1][j]==current_player && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]==current_player && tmp_board[i][j+4]==current_player )){
                    player_triads+=1;
                }
                if((tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_opponent) || (tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_opponent && tmp_board[i][j+3]==current_opponent )){
                    opponent_triads+=2;
                }

                //check for alternate triads (eg .WW.W or WW.W. or W.W.W or WW..W)
                if(tmp_board[i][j]=='.' && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]=='.' && tmp_board[i+4][j]==current_player){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]=='.' && tmp_board[i+3][j]==current_player && tmp_board[i+4][j]=='.'){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i+1][j]=='.' && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]=='.' && tmp_board[i+4][j]==current_player){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]=='.' && tmp_board[i+3][j]=='.' && tmp_board[i+4][j]==current_player){
                    player_triads+=2;
                }

                //for opponent

                if(tmp_board[i][j]=='.' && tmp_board[i+1][j]==current_opponent && tmp_board[i+2][j]==current_opponent && tmp_board[i+3][j]=='.' && tmp_board[i+4][j]==current_opponent){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j]==current_opponent && tmp_board[i+2][j]=='.' && tmp_board[i+3][j]==current_opponent && tmp_board[i+4][j]=='.'){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j]=='.' && tmp_board[i+2][j]==current_opponent && tmp_board[i+3][j]=='.' && tmp_board[i+4][j]==current_opponent){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j]==current_opponent && tmp_board[i+2][j]=='.' && tmp_board[i+3][j]=='.' && tmp_board[i+4][j]==current_opponent){
                    opponent_triads+=3;
                }

            }
        }

        //Check diagnol

        for(int i=0; i<15;i++){
            for(int j=0;j<15;j++){
                if(tmp_board[i][j]=='.' && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]==current_player && tmp_board[i+4][j+4]=='.'){
                    player_triads+=5;
                }
                else if(tmp_board[i][j]=='.' && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]==current_opponent && tmp_board[i+4][j+4]=='.'){
                    opponent_triads+=7;
                }

                //Checking for closed triads
                if((tmp_board[i][j]=='.' && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]==current_player) || ( tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]==current_player && tmp_board[i+4][j+4]=='.' ) ){
                    player_triads+=1;
                }
                else if((tmp_board[i][j]=='.' && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]==current_opponent) || ( tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]==current_opponent && tmp_board[i+4][j+4]=='.' ) ){
                    opponent_triads+=2;
                }

                //alternate triads
                //check for alternate triads (eg .WW.W or WW.W. or W.W.W or WW..W)
                if(tmp_board[i][j]=='.' && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]=='.' && tmp_board[i+4][j+4]==current_player){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]=='.' && tmp_board[i+3][j+3]==current_player && tmp_board[i+4][j+4]=='.'){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i+1][j+1]=='.' && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]=='.' && tmp_board[i+4][j+4]==current_player){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]=='.' && tmp_board[i+3][j+3]=='.' && tmp_board[i+4][j+4]==current_player){
                    player_triads+=2;
                }

                //for opponent

                if(tmp_board[i][j]=='.' && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]=='.' && tmp_board[i+4][j+4]==current_opponent){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]=='.' && tmp_board[i+3][j+3]==current_opponent && tmp_board[i+4][j+4]=='.'){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j+1]=='.' && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]=='.' && tmp_board[i+4][j+4]==current_opponent){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]=='.' && tmp_board[i+3][j+3]=='.' && tmp_board[i+4][j+4]==current_opponent){
                    opponent_triads+=3;
                }
            }
        }

        for(int i=4;i<19;i++){
            for(int j=0;j<15;j++){
                if(tmp_board[i][j]=='.' && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]==current_player && tmp_board[i-4][j+4]=='.'){
                    player_triads+=5;
                }
                else if(tmp_board[i][j]=='.' && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]==current_opponent && tmp_board[i-4][j+4]=='.'){
                    opponent_triads+=7;
                }
                //Checking for closed triads
                if((tmp_board[i][j]=='.' && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]==current_player) || ( tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]==current_player && tmp_board[i-4][j+4]=='.' ) ){
                    player_triads+=1;
                }
                else if((tmp_board[i][j]=='.' && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]==current_opponent) || ( tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]==current_opponent && tmp_board[i-4][j+4]=='.' ) ){
                    opponent_triads+=3;
                }

                //alternate triads
                //check for alternate triads (eg .WW.W or WW.W. or W.W.W or WW..W)
                if(tmp_board[i][j]=='.' && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]=='.' && tmp_board[i-4][j+4]==current_player){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]=='.' && tmp_board[i-3][j+3]==current_player && tmp_board[i-4][j+4]=='.'){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i-1][j+1]=='.' && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]=='.' && tmp_board[i-4][j+4]==current_player){
                    player_triads+=2;
                }
                if(tmp_board[i][j]==current_player && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]=='.' && tmp_board[i-3][j+3]=='.' && tmp_board[i-4][j+4]==current_player){
                    player_triads+=2;
                }

                //for opponent

                if(tmp_board[i][j]=='.' && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]=='.' && tmp_board[i-4][j+4]==current_opponent){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]=='.' && tmp_board[i-3][j+3]==current_opponent && tmp_board[i-4][j+4]=='.'){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i-1][j+1]=='.' && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]=='.' && tmp_board[i-4][j+4]==current_opponent){
                    opponent_triads+=3;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]=='.' && tmp_board[i-3][j+3]=='.' && tmp_board[i-4][j+4]==current_opponent){
                    opponent_triads+=3;
                }

            }
        }

//        cout<<"player triads is"<<player_triads<<"\n";
//        cout<<"opponent triads is"<<opponent_triads<<"\n";
        return player_triads-opponent_triads;


    }

    int check_for_five_in_row(char current_player, std::array<string,19> tmp_board){
        int player_score=0;
        int opponent_score=0;

        char current_opponent;
//        cout<<"current player is"<<current_player<<"\n";
        if(current_player=='w'){
            current_opponent='b';
        }
        else{
            current_opponent='w';
        }
        //horizontal
        for(int i=0; i<19;i++)
        {
            for(int j=0;j<15;j++){
                int num_matches=0;
                int opp_num_matches=0;
                for(int k=0;k<5;k++){
                    if (tmp_board[i][j+k]==current_player){
                        num_matches=num_matches+1;
                    }
                    else if(tmp_board[i][j+k]!='.'){
                        num_matches=0;
                        break;
                    }

                }
//                cout<<"num matches is"<<num_matches<<"\n";
                for(int k=0;k<5;k++){
                    if (tmp_board[i][j+k]==current_opponent){
                        opp_num_matches=opp_num_matches+1;
                    }
                    else if(tmp_board[i][j+k]!='.'){
                        opp_num_matches=0;
                        break;
                    }

                }

                if(tmp_board[i][j]==current_player && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]==current_player && tmp_board[i][j+4]==current_player){
                    player_score+=30;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_opponent && tmp_board[i][j+4]==current_opponent){
                    opponent_score+=30;
                }
                if(num_matches ==4){
                    player_score+=6;
                }
                if(opp_num_matches==4){
                    opponent_score+=6;
                }

                //Check for 4 in a row
                if(tmp_board[i][j]==current_player && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]==current_player && tmp_board[i][j+4]=='.'){
                    player_score+=10;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_opponent && tmp_board[i][j+4]=='.'){
                    opponent_score+=15;
                }

                //CHANGE HERE! SHOULD INCLUDE .WWWW too
                if(tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_player && tmp_board[i][j+2]==current_player && tmp_board[i][j+3]==current_player && tmp_board[i][j+4]==current_player){
                    player_score+=10;
                }
                if(tmp_board[i][j]=='.' && tmp_board[i][j+1]==current_opponent && tmp_board[i][j+2]==current_opponent && tmp_board[i][j+3]==current_opponent && tmp_board[i][j+4]==current_opponent){
                    opponent_score+=15;
                }

            }
        }


        //Check vertical

        for(int i=0;i<15;i++){
            for(int j=0; j<19; j++){

                int num_matches=0;
                int opp_num_matches=0;


                for(int k=0;k<5;k++){
                    if (tmp_board[i+k][j]==current_player){
                        num_matches=num_matches+1;
                    }
                    else if(tmp_board[i+k][j]!='.'){
                        num_matches=0;
                        break;
                    }

                }
                for(int k=0;k<5;k++){
                    if (tmp_board[i+k][j]==current_opponent){
                        opp_num_matches=opp_num_matches+1;
                    }
                    else if(tmp_board[i+k][j]!='.'){
                        opp_num_matches=0;
                        break;
                    }

                }

                if( tmp_board[i][j]==current_player && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]==current_player && tmp_board[i+4][j]==current_player){
                    player_score+=30;
                }
                if( tmp_board[i][j]==current_opponent && tmp_board[i+1][j]==current_opponent && tmp_board[i+2][j]==current_opponent && tmp_board[i+3][j]==current_opponent && tmp_board[i+4][j]==current_opponent){
                    opponent_score+=30;
                }
                if(num_matches ==4){
                    player_score+=3;
                }
                if(opp_num_matches==4){
                    opponent_score+=6;
                }

                //Check for 4 in a row
                if( tmp_board[i][j]==current_player && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]==current_player && tmp_board[i+4][j]=='.'){
                    player_score+=10;
                }
                if( tmp_board[i][j]==current_opponent && tmp_board[i+1][j]==current_opponent && tmp_board[i+2][j]==current_opponent && tmp_board[i+3][j]==current_opponent && tmp_board[i+4][j]=='.'){
                    opponent_score+=15;
                }
                //CHANGE HERE! SHOULD INCLUDE .WWWW too
                if( tmp_board[i][j]=='.' && tmp_board[i+1][j]==current_player && tmp_board[i+2][j]==current_player && tmp_board[i+3][j]==current_player && tmp_board[i+4][j]==current_player){
                    player_score+=10;
                }
                if( tmp_board[i][j]=='.' && tmp_board[i+1][j]==current_opponent && tmp_board[i+2][j]==current_opponent && tmp_board[i+3][j]==current_opponent && tmp_board[i+4][j]==current_opponent){
                    opponent_score+=15;
                }
            }

        }

        //Check diagnol
        for(int i=0; i<15;i++){
            for(int j=0;j<15;j++){
                int num_matches=0;
                int opp_num_matches=0;
                for(int k=0;k<5;k++){
                    if (tmp_board[i+k][j+k]==current_player){
                        num_matches=num_matches+1;
                    }
                    else if(tmp_board[i+k][j+k]!='.'){
                        num_matches=0;
                        break;
                    }

                }
                for(int k=0;k<5;k++){
                    if (tmp_board[i+k][j+k]==current_opponent){
                        opp_num_matches=opp_num_matches+1;
                    }
                    else if(tmp_board[i+k][j+k]!='.'){
                        opp_num_matches=0;
                        break;
                    }

                }

                if(tmp_board[i][j]==current_player && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]==current_player && tmp_board[i+4][j+4]==current_player){
                    player_score+=30;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]==current_opponent && tmp_board[i+4][j+4]==current_opponent){
                    opponent_score+=30;
                }
                if(num_matches ==4){
                    player_score+=3;
                }
                if(opp_num_matches==4){
                    opponent_score+=6;
                }

                //Check for 4 in a row
                if(tmp_board[i][j]==current_player && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]==current_player && tmp_board[i+4][j+4]=='.'){
                    player_score+=10;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]==current_opponent && tmp_board[i+4][j+4]=='.'){
                    opponent_score+=15;
                }
                //CHANGE HERE! SHOULD INCLUDE .WWWW too
                if(tmp_board[i][j]=='.' && tmp_board[i+1][j+1]==current_player && tmp_board[i+2][j+2]==current_player && tmp_board[i+3][j+3]==current_player && tmp_board[i+4][j+4]==current_player){
                    player_score+=10;
                }
                if(tmp_board[i][j]=='.' && tmp_board[i+1][j+1]==current_opponent && tmp_board[i+2][j+2]==current_opponent && tmp_board[i+3][j+3]==current_opponent && tmp_board[i+4][j+4]==current_opponent){
                    opponent_score+=15;
                }
            }
        }

        for(int i=4;i<19;i++){
            for(int j=0;j<15;j++){

                int num_matches=0;
                int opp_num_matches=0;


                for(int k=0;k<5;k++){
                    if (tmp_board[i-k][j+k]==current_player){
                        num_matches=num_matches+1;
                    }
                    else if(tmp_board[i-k][j+k]!='.'){
                        num_matches=0;
                        break;
                    }


                }

                for(int k=0;k<5;k++){
                    if (tmp_board[i-k][j+k]==current_opponent){
                        opp_num_matches=opp_num_matches+1;
                    }
                    else if(tmp_board[i-k][j+k]!='.'){
                        opp_num_matches=0;
                        break;
                    }

                }

                if(tmp_board[i][j]==current_player && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]==current_player && tmp_board[i-4][j+4]==current_player){
                    player_score+=30;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]==current_opponent && tmp_board[i-4][j+4]==current_opponent){
                    opponent_score+=30;
                }
                if(num_matches ==4){
                    player_score+=3;
                }
                if(opp_num_matches==4){
                    opponent_score+=6;
                }
                //Check 4 in row
                if(tmp_board[i][j]==current_player && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]==current_player && tmp_board[i-4][j+4]=='.'){
                    player_score+=10;
                }
                if(tmp_board[i][j]==current_opponent && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]==current_opponent && tmp_board[i-4][j+4]=='.'){
                    opponent_score+=15;
                }

                //CHANGE HERE! SHOULD INCLUDE .WWWW too
                if(tmp_board[i][j]=='.' && tmp_board[i-1][j+1]==current_player && tmp_board[i-2][j+2]==current_player && tmp_board[i-3][j+3]==current_player && tmp_board[i-4][j+4]==current_player){
                    player_score+=10;
                }
                if(tmp_board[i][j]=='.' && tmp_board[i-1][j+1]==current_opponent && tmp_board[i-2][j+2]==current_opponent && tmp_board[i-3][j+3]==current_opponent && tmp_board[i-4][j+4]==current_opponent){
                    opponent_score+=15;
                }

            }
        }
//        cout<<"SCORE IS"<<player_score-opponent_score<<"\n";


        return player_score-opponent_score;


    }

    int heuristic_value(std::array<string,19> tmp_board, char current_player){
        int player_score=0;
//        cout<<"inside heuristic value fn\n";
//        cout<<"the board is\n\n";
//        for(int i=0;i<19;i++)
//            cout<<tmp_board[i]<<"\n";
        player_score+=check_number_of_captures(tmp_board, current_player);
        player_score+= check_for_open_triads(current_player, tmp_board);
        player_score+= check_for_five_in_row(current_player, tmp_board);

//        cout<<"player score is"<<player_score<<"\n";
        return player_score;
    }

    std::array<std::string, 19> copy_board_and_update_move(char current_player, int x, int y, std::array<string,19> tmp_board){

//        cout<<"inside update board\n";
        std::array<std::string, 19> board_update;
        for(int i=0;i<19;i++){
            board_update[i]=tmp_board[i];
        }
        board_update[x][y]=current_player;
//        cout<<"updated board is\n";
//        for(int i=0;i<19;i++){
//            cout<<board_update[i]<<"\n";
//        }
        return board_update;
    }

    std::list<std::pair<std::array<string,19>, std::pair<int, int>>> find_children(char current_player, std::array<string,19>tmp_board){

        //child list contains list of updated board and the move made
        std::list<std::pair<std::array<string,19>, std::pair<int, int>>>  child_list;
        std::array<std::string ,19> placeholder_board;
        std::pair<std::array<std::string,19>, std::pair<int, int>> my_pair;


        for(int i=border_row_min-2;i<border_row_max+2; i++){
            for(int j=col_min-2;j<col_max+2; j++){
                if(check_legal_move(current_player, tmp_board, i,j)==1){
                    my_pair.first = copy_board_and_update_move(current_player, i,j,tmp_board);
                    my_pair.second = std::make_pair(i, j);
                    child_list.push_back(my_pair);
                }
            }
        }
        return child_list;

    }



    std::tuple<int, int> minmax(std::pair<std::array<string,19>, std::pair<int, int>> board_new_tuple, int depth, char player){
        std::tuple<int, std::tuple<int, int>>  inf = make_tuple(INT32_MAX, make_tuple(-1, -1));
        std::tuple<int, std::tuple<int, int>>  neg_inf = make_tuple(INT32_MIN, make_tuple(-1,-1));
        std::tuple<int, std::tuple<int, int>> m;

//        cout<<"inside minimax";
//        cout<<"alpha is"<<std::get<0>(neg_inf)<<"\n";
//        cout<<"beta is"<<std::get<0>(inf)<<"\n";
//        cout<<"player is"<<player<<"\n";

        m = max_value(board_new_tuple.first,board_new_tuple.second,neg_inf, inf, depth,player);
//        cout<<"the predicted move is"<<std::get<0>(std::get<1>(m))<<"\n";
//        cout<<"the predicted move is"<<std::get<1>(std::get<1>(m))<<"\n";
        return std::get<1>(m);

    }

    std::tuple<int, std::tuple<int, int>> min_value(std::array<string,19> tmp_board, std::pair<int, int> coords, std::tuple<int, std::tuple<int, int>> alpha, std::tuple<int, std::tuple<int, int>> beta, int depth, char current_player){
//        cout<<"inside minvalue\n";
//        cout<<"DEPTH IS"<<depth<<"\n";
//        cout<<"alpha is"<<std::get<0>(alpha)<<"\n";
//        cout<<"beta is"<<std::get<0>(beta)<<"\n";
        char current_opponent;
        if(current_player=='b'){
            current_opponent='w';
        }
        else{
            current_opponent='b';
        }

        //Leaf node
        if(depth==0){

            int heuristic_value_int = heuristic_value(tmp_board, current_player);
            if(current_player==player){

                std::tuple<int, std::tuple<int, int>> tmp_tuple(heuristic_value_int, coords);
                return tmp_tuple;
            }
            else{
                //CHANGE HERE REMOVED -1
                std::tuple<int, std::tuple<int, int>> tmp_tuple(heuristic_value_int, coords);
                return tmp_tuple;
            }
        }

        std::tuple<int, std::tuple<int, int>> m;
        //child list contains list of updated board and the move made
        std::list<std::pair<std::array<string,19>, std::pair<int, int>>> child_list = find_children(current_player, tmp_board);

//        cout<<"size is"<<child_list.size()<<"\n";

        for (auto element = child_list.begin(); element != child_list.end(); ++element) {
            m = max_value(element->first,element->second, alpha, beta, depth-1, current_opponent);
            if(std::get<0>(m) < std::get<0>(beta)){
                //BETA UPDATE
                beta=m;
            }
            if(std::get<0>(alpha)  >=  std::get<0>(beta)){
                //PRUNED
                return beta;
            }
        }
        return beta;
    }

    std::tuple<int, std::tuple<int, int>> max_value(std::array<string,19> tmp_board, std::pair<int, int> coords,  std::tuple<int, std::tuple<int, int>> alpha, std::tuple<int, std::tuple<int, int>> beta, int depth, char current_player){

        std::tuple<int, std::tuple<int, int>> m;
        char current_opponent;
        if(current_player=='b'){
            current_opponent='w';
        }
        else{
            current_opponent='b';
        }

        if(depth==0){

            if(current_player==player) {
//                cout << "inside maxvalue depth is 0\n";
                int heuristic_value_int = heuristic_value(tmp_board, current_player);
                std::tuple<int, std::tuple<int, int>> tmp_tuple(heuristic_value_int,coords);
//                cout << "inside maxvalue after fn\n\n";
//                cout << "\n";
                return tmp_tuple;
            }
            else{
                int heuristic_value_int = heuristic_value(tmp_board, current_player);
                //CHANGE HERE
//                std::tuple<int, std::tuple<int, int>> tmp_tuple(heuristic_value_int*-1,coords);
                std::tuple<int, std::tuple<int, int>> tmp_tuple(heuristic_value_int,coords);
//                cout<<"Leaf node coordinate is"<<std::get<0>(coords)<<","<<std::get<1>(coords)<<"; value is"<<heuristic_value(tmp_board, current_player)<<",player is"<<current_player<<"\n";

                return tmp_tuple;
            }
        }

        std::list<std::pair<std::array<string,19>, std::pair<int, int>>> child_list = find_children(current_player, tmp_board);
        for(auto element=child_list.begin(); element!=child_list.end(); ++element){
//            cout<<"INSIDE FOR LOOP OF MAX\n";
//            cout<<"DEPTH IS"<<depth<<"\n";
            m = min_value(element->first,element->second, alpha, beta, depth-1, current_opponent);
//            cout<<"INSIDE MAX VALUE PT2";

            if ( std::get<0>(m) > std::get<0>(alpha)){
                //ALPHA
                alpha=m;
                std::get<0>(std::get<1>(alpha)) = std::get<0>(element->second);
                std::get<1>(std::get<1>(alpha)) = std::get<1>(element->second);
                std::get<0>(best_coords) = std::get<0>(element->second);
                std::get<1>(best_coords) = std::get<1>(element->second);
            }
            if (std::get<0>(alpha) >= std::get<0>(beta)){
                std::get<0>(best_coords) = std::get<0>(element->second);
                std::get<1>(best_coords) = std::get<1>(element->second);
                cout<<"final";
                return alpha;
            }

        }

//        cout<<"BEST COORDINATES"<<std::get<0>(best_coords)<<","<<std::get<1>(best_coords)<<"\n";

        return alpha;

    }


    //Make a move by filling the position in board with player's character
    void make_move(char current_player, int x, int y){
//        cout<<"inside makemove fn\n";
        board[x][y] = current_player;
    }


    void find_next_move(){
        std::tuple<int, int> next_move;

        if(number_of_pieces<=2){
            next_move = make_initial_moves();
        }
        else {
            std::pair<std::array<string, 19>, std::pair<int, int>> board_input;
            std::array<string, 19> board_new;
            for (int i = 0; i < 19; i++) {
                board_new[i] = board[i];
            }
            board_input.first = board_new;
            board_input.second = std::make_pair(std::get<0>(std::make_tuple(-5, -5)), std::get<1>(std::make_tuple(-5, -5)));;
            //PRINTING THE NEXT MOVE - COUT
            next_move = minmax(board_input, 2, player);

        }
        cout<<board_convention[std::get<0>(next_move)][std::get<1>(next_move)];
    }

    int write_to_file(){

        std::ofstream MyOutFile(output_file_path);
        for(int i=0; i<19;i++){
            MyOutFile<<board[i]<<endl;
        }

        MyOutFile.close();

//        cout<<"Written to out"<<"\n";
        return 0;


    };


};



int main() {



    string input_file_path_inp = "/Users/neranjhana/FoundationsOfAI/Assn2/input.txt";
    string output_file_path_inp = "output.txt";

//    std::ofstream outfile ("output.txt");
//    outfile.close();
//    freopen("output.txt","w",stdout);

    game_play obj_gameplay(input_file_path_inp, output_file_path_inp);
    obj_gameplay.read_input_file();
    obj_gameplay.find_opponent();
    obj_gameplay.find_border_pieces();

    obj_gameplay.create_board_convention();
    obj_gameplay.find_next_move();



}


