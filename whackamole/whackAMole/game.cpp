//
// Created by sqasim on 4/24/23.
//
#include "game.h"
int Game::score = 0;
int Game::bestScore = 0;

void Game::resetScore(){
    if(Game::score > Game::bestScore){
        Game::bestScore = Game::score;
    }
	Game::score = 0;
}

