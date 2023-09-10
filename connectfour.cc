#include <iostream>
#include "board.h"
#include "botAlgorithm.h"

bool checkDraw(const std::vector<std::vector<piece>>& board){
    for(int x = 0; x<6; x++){
        for(int y = 0; y<7; y++){
            if(board[x][y].color == 0){
                return false;
            }
        }
    }
    return true;
}

std::vector<std::pair<int,int>> checkWin(const std::vector<std::vector<piece>>& board, int player) {
    // Check rows and columns for a win
    std::vector<std::pair<int,int>> win;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (col + 3 < 7 &&
                //board[row][col].pseudo == false &&
                board[row][col].color == player &&
                board[row][col + 1].color == player &&
                board[row][col + 2].color == player &&
                board[row][col + 3].color == player) {
                    for(int i = 0; i<4; i++){
                        if(board[row][col+i].pseudo == false) win.emplace_back(std::make_pair(row, col+i));
                        // Horizontal win
                    }
            }
            if (row + 3 < 6 &&
                //board[row][col].pseudo == false &&
                board[row][col].color == player &&
                board[row + 1][col].color == player &&
                board[row + 2][col].color == player &&
                board[row + 3][col].color == player) {
                    for(int i = 0; i<4; i++){
                        if(board[row+i][col].pseudo == false) win.emplace_back(std::make_pair(row+i, col));
                        // Horizontal win
                    }
                //return true; // Vertical win
            }
        }
    }

    // Check diagonals for a win
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (col + 3 < 7 && row + 3 < 6 &&
                //board[row][col].pseudo == false &&
                (board[row][col].color == player &&
                 board[row + 1][col + 1].color == player &&
                 board[row + 2][col + 2].color == player &&
                 board[row + 3][col + 3].color == player)) {
                    for(int i = 0; i<4; i++){
                        if(board[row+i][col+i].pseudo == false) win.emplace_back(std::make_pair(row+i, col+i));
                    }                    
            }
            if (col + 3 < 7 && row - 3 >= 0 &&
                //board[row][col].pseudo == false &&
                (board[row][col].color == player &&
                 board[row - 1][col + 1].color == player &&
                 board[row - 2][col + 2].color == player &&
                 board[row - 3][col + 3].color == player)) {
                    for(int i = 0; i<4; i++){
                        if(board[row-i][col+i].pseudo == false) win.emplace_back(std::make_pair(row-i, col+i));
                    }
                //return true; // Diagonal win (top-left to bottom-right)
            }
        }
    }

    return win;
}


int main(){
    PlayingBoard board;
    int column;
    int turn = 2;
    board.printBoard();

    int player;
    std::cout<<"Enter 1 for player 1 or 2 for player 2: ";
    std::cin>>player;
    if(player != 1 && player != 2){
        std::cout<<"Invalid player"<<std::endl;
        return 0;
    }

    while(true){
        if(checkDraw(board.getBoard())){
            std::cout<<"Draw!"<<std::endl;
            break;
        }
        if(turn%2+1 == player){
            std::cout<<"Enter a column: ";
            std::cin>>column;
            if(column < 0 || column > 7){
                std::cout<<"Invalid column"<<std::endl;
                continue;
            }
            if(board.placePiece(column-1, (turn%2)+1) == std::make_pair(-1, -1)){
                std::cout<<"Column is full"<<std::endl;
                continue;
            }
        }

        else{
            //bot
            std::cout<<"Bot's turn"<<std::endl;
            player == 1 ? chooseMove(board, 2) : chooseMove(board, 1);
        }

        board.printBoard();

        //board.removePiece(column-1);
        //for(int x = 0; x<checkWin(board.getBoard(), (turn%2)+1).size(); x++){
        //    std::cout<<"("<<checkWin(board.getBoard(), (turn%2)+1)[x].first<<", "<<checkWin(board.getBoard(), (turn%2)+1)[x].second<<")"<<std::endl;
        //}

        if(!checkWin(board.getBoard(), (turn%2)+1).empty()){
            std::cout<<"Player "<<(turn%2)+1<<" wins!"<<std::endl;
            break;
        }
        turn++;

    }
    return 0;    
}