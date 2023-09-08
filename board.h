#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

struct piece{
    int color; //red 1 black 2; empty 0
    bool pseudo = true; //for minimax
    //struct in case needed
};

bool checkWin(const std::vector<std::vector<piece>>& board, int player);

class PlayingBoard{
    public:
        PlayingBoard(){
            //std::cout<<"board created"<<std::endl;
            std::vector<piece> row;
            piece empty;
            empty.color = 0;
            
            for(int i = 0; i<6; i++){
                for(int n = 0; n<7; n++){
                    row.emplace_back(empty);
                }
                board.emplace_back(row);
            }
        }

        void printBoard(){
            for(int i = 0; i<6; i++){
                for(int n = 0; n<7; n++){
                    if(board[i][n].color==0){std::cout<<" . ";}
                    else if(board[i][n].color==1){std::cout<<" X ";}
                    else std::cout<<" O ";
                }
                std::cout<<std::endl;
            }
        }

        std::pair<int, int> placePiece(int column, int color){
            for(int i = 0; i<6; i++){
                for(int n = 0; n<7; n++){
                    if(n==column && board[i][n].color==0){
                        if(i != 5 && board[i+1][n].color==0){
                            break;
                        }
                        board[i][n].color = color;
                        board[i][n].pseudo = false;
                        return std::make_pair(i, n);
                    }
                }
            }
            return std::make_pair(-1, -1);
        }

        void fillPseudo(int color){
            for(int i = 0; i<6; i++){
                for(int n = 0; n<7; n++){
                    if(board[i][n].color==0){
                        board[i][n].color = color;
                        board[i][n].pseudo = true;
                    }
                }
            }
        }

        void removePseudo(){
            for(int i = 0; i<6; i++){
                for(int n = 0; n<7; n++){
                    if(board[i][n].pseudo==true){
                        board[i][n].color = 0;
                        board[i][n].pseudo = false;
                    }
                }
            }
        }

        std::vector<std::vector<piece>> getBoard(){
            return board;
        }

        void removePiece(int x, int y){
            board[x][y].color = 0;
        }

    private:
        std::vector<std::vector<piece>> board;
};

#endif