#include "life2.h"

//globals, read input, allocate map (map[i]), neighbours, nextgen, main (incl. printout and gen loop)
int H;
int W;

void read_input(int** map)
{
	int x = 0, y = 0;
	int pen = 0;
	char buf[4096];
	int n = read(0, buf, sizeof(buf));
	for (int i = 0; i < n; i++)
	{
		if (buf[i] == 'x')
		{
			pen = !pen;
			if (pen)
				map[y][x] = 1;
		}
		if (buf[i] == 'w' && y > 0)
			y--;
		if (buf[i] == 'a' && x > 0)
			x--;
		if (buf[i] == 's' && y < H - 1)
			y++;
		if (buf[i] == 'd' && x < W - 1)
			x++;
		if (pen && buf[i] != 'x')
			map[y][x] = 1;
	}
	return ;
}

int** calloc_map()
{
	int** map = calloc(H, sizeof(int*));
	for (int i = 0; i < H; i++)
		map[i] = calloc(W, sizeof(int));
	return map;
}

int neighbours(int** map, int y, int x)
{
	int n = 0;
	for (int dy = -1; dy <= 1; dy++)
		for (int dx = -1; dx <= 1; dx++)
			if (y+dy >= 0 && y+dy < H && x+dx >= 0 && x+dx < W)
				n += map[y+dy][x+dx];
	return (n - map[y][x]);
}

int** nextgen(int** current, int** next)
{
	for (int y = 0; y < H; y++)
		for (int x = 0; x < W; x++)
		{
			int n = neighbours(current, y, x);
			next[y][x] = (n == 3 || (current[y][x] && n == 2));
		}
	return next;
}

int main(int argc, char** argv)
{
	if (argc != 4)
		return 2;
	W = atoi(argv[1]);
	H = atoi(argv[2]);
	int gen = atoi(argv[3]);
	int** current = calloc_map();
	int** next = calloc_map();
	read_input(current);
	for (int i = 0; i < gen; i++)
	{
		int** temp = current;
		current = nextgen(current, next);
		next = temp;
	}
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			current[y][x] ? putchar('O') : putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}