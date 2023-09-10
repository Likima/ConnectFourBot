#ifndef BOTALGORITHM_H
#define BOTALGORITHM_H
#include "board.h"
#include <random>
#include <limits>

std::vector<std::pair<int, int>> getSurface(PlayingBoard board, int color){
    std::vector<std::pair<int, int>> surface;
    board.fillPseudo(color);
    //board.printBoard();
    surface = checkWin(board.getBoard(), color);
    //for(int i = 0; i<surface.size(); i++){
    //    std::cout<<surface[i].first<<" "<<surface[i].second<<std::endl;
    //    //board.getBoard()[surface[i].first][surface[i].second].pseudo = true;
    //}
    board.removePseudo();
    return surface;
}

int analyzePosition(PlayingBoard board){
    //std::vector<std::pair<int, int>> surface = getSurface(board, player);
    //return player == 1 ? getSurface(board, player).size() : -getSurface(board, player).size();
    //if(!checkWin(board.getBoard(), 1).empty()) return INT_MAX;
    //if(!checkWin(board.getBoard(), 2).empty()) return INT_MIN;
    return(getSurface(board,1).size() - getSurface(board,2).size());  
}

int alphaBeta(PlayingBoard &board, int depth, int alpha, int beta, int player){
    if(!checkWin(board.getBoard(), player).empty()){
        //std::cout<<"here"<<std::endl;
        return (player == 1 ? INT_MAX : INT_MIN);
    }
    if(!checkWin(board.getBoard(), player%2+1).empty()){
        //std::cout<<"here"<<std::endl;
        return (player == 1 ? INT_MIN : INT_MAX);
    }
    
    if(depth == 0){
        return analyzePosition(board);
    }

    int maxEval, minEval;
    int value = 0;

    if(player == 1){
        maxEval = INT_MIN;
        for(int i = 0; i<7; i++){
            if(board.placePiece(i, player).first == -1){
                continue;
            }
            value = alphaBeta(board, depth-1, alpha, beta, 2);
            if(value>maxEval){
                maxEval = std::max(maxEval, value);
                if(depth == DEPTH){
                    bestMove = i;
                }
            }
            board.removePiece(i);
            
            if(alpha >= beta){
                break;
            }
            alpha = std::max(alpha, value);
        }
        return maxEval;
    }

    else{
        minEval = INT_MAX;
        for(int i = 0; i<7; i++){
            if(board.placePiece(i, player).first == -1){
                continue;
            }
            value = alphaBeta(board, depth-1, alpha, beta, 1);
            if(value<minEval){
                minEval = std::min(minEval, value);
                if(depth == DEPTH){
                    bestMove = i;
                }
            }
            board.removePiece(i);
            
            if(beta <= alpha){
                break;
            }
            beta = std::min(beta, value);
        }
        return minEval;
    }
}

void chooseMove(PlayingBoard &board, int player){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 7);
    int col = distribution(gen);

    col = alphaBeta(board, DEPTH, INT_MIN, INT_MAX, player);

    if(board.placePiece(bestMove, player).first == -1){
        chooseMove(board, player);
    }
    else{
        //getSurface(board, player);
        //board.placePiece(bestMove, player);
        std::cout<<"Player "<<player<<" placed a piece in column "<<bestMove<<std::endl;
    }
}

#endif