#include "life2.h"
int w;
int h;

int** calloc_map()
{
    int** map = calloc(h, sizeof(int*));
    for(int i =0; i <h; i++)
    {
        map[i] = calloc(w, sizeof(int));
    }
    return(map);
}
void read_input(int** map)
{
    int x =0;
    int y = 0;
    int draw = 0;
    char buf;
    while (read(0, &buf, 1) == 1)
    {
        if(buf == 'x')
        {
            draw ^= 1;
            if(draw)
                map[y][x] = 1;
        }
        else if(buf == 'w' && y > 0)
            y--;
        else if(buf == 's' && y < h -1)
            y++;
        else if(buf == 'a' && x >  0)
            x--;
        else if(buf == 'd' && x < w - 1)
            x++;
        if(draw)
            map[y][x] = 1;
    }
    return;
}
int neighbours(int** map, int y, int x)
{
    int n = 0;
    for(int dy = -1; dy <= 1; dy++)
    {
        for(int dx = -1; dx <= 1; dx++)
        {
            if(y+dy >= 0 && y+dy < h && x+dx >=0 && x+dx < w)
                n+=map[y+dy][x+dx];
        }
    }
    return(n - map[y][x]);

}
int** nextgen(int** curr, int** next)
{
    for(int y = 0; y < h; y++)
    {
        for(int x =0; x< w; x++)
        {
            int n = neighbours(curr, y, x);
            next[y][x] = (n == 3 || curr[y][x] && n == 2);
        }
    }
    return(next);
}
void free_map(int** map)
{
    for(int i =0; i < h; i++)
        free(map[i]);
    free(map);
}

int main(int ac, char **av)
{
    if(ac != 4)
        return(1);
    w = atoi(av[1]);
    h = atoi(av[2]);
    int iter = atoi(av[3]);
    int** curr = calloc_map();
    int** next = calloc_map();
    read_input(curr);
    for(int i = 0; i < iter; i++)
    {
        int ** temp = curr;
        curr = nextgen(curr, next);
        next = temp;
    }
    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            curr[y][x] ? putchar('O') : putchar(' ');
        }
        putchar('\n');
    }
    free_map(curr);
    free_map(next);
    return(0);
}