#include "life.h"

char** alloc_board(int w, int h, char fill)
{
    char **b = malloc(h * sizeof(char *));
    if(!b)
        return(NULL);
    for(int i =0; i< h; i++)
    {
        b[i] = malloc(w * sizeof(char *));
        if(!b[i])
        {
            while (i--)
            {
                free(b[i]);
            }
            free(b);
            return(NULL);
            
        }
        for(int j =0; j< w; j++)
        {
            b[i][j] = fill;
        }
    }
    return(b);
}
int init_game(t_game* g, char** av)
{
    g->width = av[1];
    g->heigth = av[2];
    g->iteration = av[3];
    g->i = 0;
    g->j = 0;
    g->draw = 0;
    g->alive = '0';
    g->dead = ' ';
    g->board = alloc_board(g->width, g->heigth, ' ');
    if(!g->board)
        return(-1);
    return(0);
}

void fill_board(t_game* g)
{
    char c;
    int move;

    while(read(0, &c, 1) == 1)
    {
        move = 1;
        if(c == 'w' && g->i >0)
            g->i--;
        else if(c == 's' && g->i < g->heigth -1)
            g->i++;
        else if(c == 'a' && g->j > 0)
            g->j--;
        else if(c == 'd' && g->j < g->width -1)
            g->j++;
        else if(c == 'x')
        {
            g->draw ^= 1;
            move = 0;
        }
        else
            move = 0;
        if(g->draw && move)
            g->board[g->i][g->j] = g->alive;
    }
}
void free_board(t_game* g)
{
    if(!g->board)
        return;
    for(int i = 0; i < g->heigth; i++)
    {
        free(g->board[i]);
    }
    free(g->board);
    g->board = NULL;
}
void print_board(t_game* g)
{
    for(int i = 0; i < g->heigth; i++)
    {
        for(int j =0; j < g->width; j++)
        {
            putchar(g->board[i][j]);
        }
        putchar('\n');
    }

}

int count_neighbors(t_game* g, int i, int j)
{
    int count = 0;
    int ni;
    int nj;

    for(int di = -1; di <= 1; di++)
    {
        for(int dj = -1; dj <= 1; dj++)
        {
            if(!di && !dj)
                continue;
            ni = i + di;
            nj = j + dj;
            if(ni >= 0 && nj >= 0 && ni <g->heigth && nj < g->width)
                count += (g->board[ni][nj] == g->alive);
        }
    }
    return(count);
}
int play(t_game* g)
{
    char **temp;
    int n;
    int alive;

    temp = alloc_board(g->heigth, g->width, g->dead);
    if(!temp)
    {
        return(-1);
    }
    for(int i = 0; i < g->heigth; i++)
    {
        for(int j =0; j < g->width; j++)
        {
            n = count_nrighboars(g, i, j);
            alive = (g->board[i][j] == g->alive);
            if(alive && (n == 2  || n == 3))
                temp[i][j] = g->alive;
            else if(!alive && n == 3)
                temp[i][j] = g->alive;
            else
                temp[i][j] = g->dead;

        }
    }
    free_board(g);
    g->board = temp;
    return(0);
}

int main(int ac, char **av)
{
    t_game g;
    if(ac != 4)
        return(1);
    if(init_game(&g, av) == -1)
        return(1);
    fill_board(&g);
    for(int i =0; i < g.iteration; i++)
    {
        if(play(&g) == -1)
        {
            free_board(&g);
            return(1);
        }
    }
    print_board(&g);
    free_board(&g);
    return(0);
}