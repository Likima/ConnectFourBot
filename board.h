#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

int DEPTH = 7; int bestMove = 0;

struct piece{
    int color; //red 1 black 2; empty 0
    bool pseudo = true; 
};

std::vector<std::pair<int,int>> checkWin(const std::vector<std::vector<piece>>& board, int player);

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
                    else if(board[i][n].color==1){std::cout<<"\033[0;31m"<<" O "<<"\033[0m";}
                    else std::cout<<"\033[0;36m"<<" O "<<"\033[0m";
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

        void removePiece(int col){
            for(int i = 0; i<6; i++){
                for(int n = 0; n<7; n++){
                    if(n==col && board[i][n].color==0){
                        if(i != 5 && board[i+1][n].color==0){
                            break;
                        }
                        board[i][n].color = 0;
                    }
                }
            }            
        }

        void removePiece(int x, int y){
            board[x][y].color = 0;
        }

        void setScore(int player, int score){
            if(player == 1) firstScore = score;
            else secondScore = score;
        }

    private:
        std::vector<std::vector<piece>> board;
        int firstScore = 0;
        int secondScore = 0;
};

#endif