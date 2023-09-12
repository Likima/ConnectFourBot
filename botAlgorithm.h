#ifndef BOTALGORITHM_H
#define BOTALGORITHM_H
#include "board.h"
#include <limits>

std::vector<std::pair<int, int>> getSurface(PlayingBoard board, int color){
    std::vector<std::pair<int, int>> surface;
    board.fillPseudo(color);
    surface = checkWin(board.getBoard(), color);
    board.removePseudo();
    return surface;
}

int analyzePosition(PlayingBoard board){
    return(getSurface(board,1).size() - getSurface(board,2).size());  
}

int alphaBeta(PlayingBoard &board, int depth, int alpha, int beta, int player){

    if(!checkWin(board.getBoard(), player).empty()){
        return (player == 1 ? INT_MIN : INT_MAX);
    }
    if(!checkWin(board.getBoard(), player%2+1).empty()){
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
            
            if(beta <= alpha){
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

    int adder=0;
    for(int i = 0; i<7; i++){
        if(board.getBoard()[0][i].color != 0) adder++;
    }
    DEPTH = 8+((int)adder/2);

    int col = alphaBeta(board, DEPTH, INT_MIN, INT_MAX, player);
    
    if(board.placePiece(bestMove, player).first == -1){
        chooseMove(board, player);
    }
    else{
        std::cout<<"Player "<<player<<" placed a piece in column "<<bestMove+1<<std::endl;
    }
}

#endif