#ifndef BOTALGORITHM_H
#define BOTALGORITHM_H
#include "board.h"

//int analyzePosition(PlayingBoard board, int player){
//    for(int i)
//}
void chooseMove(PlayingBoard &board, int player){
    std::vector<std::vector<piece>> boardState = board.getBoard();
    std::pair<int, int> reset;
    int bestMove = 0;
    int bestScore = 0;
    for(int i = 0; i<7; i++){
        for(int n = 0; n<6; n++){
            if(boardState[n][i].color == 0){
                reset = board.placePiece(i, player);
                if(reset.first == -1 && reset.second == -1){
                    continue;
                }
                int score = 0;
                if(checkWin(boardState, player)){
                    score = 100;
                }
                else{
                    score = 0;
                }
                if(score > bestScore){
                    bestScore = score;
                    bestMove = i;
                }
                board.removePiece(reset.first, reset.second);
                break;
            }
        }
    }
    board.placePiece(bestMove, player);
}

#endif