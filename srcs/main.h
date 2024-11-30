#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <raylib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
#include <sys/time.h>


typedef struct s_window
{
	int screenWidth;
	int screenHeight;
	int sprite_size;
} t_window;

typedef struct s_bombe
{
	int x;
	int y;
	long long time_crea;
	int power;
	Sound sound;
} t_bombe;

typedef struct s_player
{
	float x;
	float y;
	int nbr_bombe;
	int power_bombe;
	t_bombe **bombe;
	Wave bomb_sound;
} t_player;

typedef struct s_map
{
	char **data;
	int size_X;
	int size_Y;
} t_map;

Texture2D ResizeTexture(Texture2D texture, int newWidth, int newHeight);
long long currentTimeMillis();


# endif