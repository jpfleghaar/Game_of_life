#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_game
{
    int width;
    int heigth;
    int iteration;
    int j;
    int i;
    char alive;
    char dead;
    int draw;
    char** board;

} t_game;

#endif