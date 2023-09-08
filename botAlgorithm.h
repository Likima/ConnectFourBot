#ifndef BOTALGORITHM_H
#define BOTALGORITHM_H
#include "board.h"
#include <random>

//std::vector<std::pair<int, int>> getSurface(PlayingBoard board){
//
//}

//int analyzePosition(PlayingBoard board, int player){
//    
//}
void chooseMove(PlayingBoard &board, int player){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 7);
    int col = distribution(gen);

    if(board.placePiece(col, player).first == -1){
        chooseMove(board, player);
    }
    else{
        std::cout<<"Player "<<player<<" placed a piece in column "<<col<<std::endl;
    }
}

#endif