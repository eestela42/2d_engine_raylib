#include "main.h"


void manager_input(t_player *player, t_map *map)
{
	if (IsKeyDown(KEY_A))
	{
		if (player->x > 1 && map->data[(int)(player->x - 0.1)][(int)player->y] == 0)
			player->x -= 0.1;
		
	}
	if (IsKeyDown(KEY_D))
	{
		if (player->x < 99 && map->data[(int)(player->x + 0.1)][(int)player->y] == 0)
			player->x += 0.1;
	}
	if (IsKeyDown(KEY_W))
	{
		if (player->y > 1 && map->data[(int)player->x][(int)(player->y - 0.1)] == 0)
			player->y -= 0.1;
	}
	if (IsKeyDown(KEY_S))
	{
		if (player->y < 99 && map->data[(int)player->x][(int)(player->y + 0.1)] == 0)
			player->y += 0.1;
	}
}

int main()
{
    // Initialisation de la fenêtre
    t_window window;
	window.screenWidth = 1500;
	window.screenHeight = 720;
	window.sprite_size = 64;

    InitWindow(window.screenWidth, window.screenHeight, "BOMBAMAN");



	//map en brut
	srand(time(0));

	t_map map;
	map.size_X = 100;
	map.size_Y = 100;
	map.data = malloc(sizeof(char*) * 100);
	for (int i = 0; i < 100; i++)
	{
		map.data[i] = malloc(sizeof(char) * 100);
		for (int j = 0; j < 100; j++)
		{
			if (rand() % 100 < 10)
			{
				map.data[i][j] = 1;
				continue;
			}
				map.data[i][j] = 0;
		}
	}
	
	map.data[50][50] = 0;
    
	//init
	t_player player;
	player.x = 50;
	player.y = 50;


	Texture2D base_player_text = LoadTexture("textures/vaisseau.png");
	Texture2D base_wall_text = LoadTexture("textures/wall.jpg");
	Texture2D base_void_text = LoadTexture("textures/dirt.jpeg");

	Texture2D player_text = ResizeTexture(base_player_text, window.sprite_size, window.sprite_size);
	Texture2D wall_text = ResizeTexture(base_wall_text, window.sprite_size, window.sprite_size);
	Texture2D void_text = ResizeTexture(base_void_text, window.sprite_size, window.sprite_size);

    SetTargetFPS(60);

	int nbr_text_x = (window.screenWidth / window.sprite_size) + 2;
	int nbr_text_y = (window.screenHeight / window.sprite_size) + 2;

    while (!WindowShouldClose()) {

        // Démarrer le dessin
		ClearBackground(BLACK);
        BeginDrawing();
		manager_input(&player, &map);

		printf("Player x = %f, y = %f\n", player.x, player.y);

		//on recupere la partie decimale de la pos du player
		float offset_x = -(player.x - (int)player.x);
		float offset_y = -(player.y - (int)player.y);

		// printf("offset_x = %f, offset_y = %f\n", offset_x, offset_y);
		
		for (int y = 0; y <= nbr_text_x; y++){
		for (int x = 0; x <= nbr_text_x; x++)
		{
			//on recupere la pos du centre de l'ecran
			int text_x = window.screenWidth / 2;
			int text_y = window.screenHeight / 2;

			//et on calcule la pos du sprite (par rapport au centre de l'ecran (au dessus)) 																					j'suis pas sur de ce systeme pour le long terme mais ca marche pour l'instant donc chill #chill
			text_x += //distance sprite <=> player
				(x - nbr_text_x / 2 + offset_x) * window.sprite_size;

			text_y += //distance sprite <=> player
				(y - nbr_text_y / 2 + offset_y) * window.sprite_size;
			
			//on recupere la pos du block dans la map (char**)
			int pos_block_x = (int)player.x + x - nbr_text_x / 2;
			int pos_block_y = (int)player.y + y - nbr_text_y / 2;

			if (pos_block_x < 0 || pos_block_x > map.size_X || pos_block_y < 0 || pos_block_y > map.size_Y)
				continue;
			
			int type = map.data[pos_block_x][pos_block_y];

			if (type == 0)
				DrawTexture(void_text, text_x, text_y, WHITE);
			else 
				DrawTexture(wall_text, text_x, text_y, WHITE);
			int size_dot = 15;
			DrawCircle(window.screenWidth / 2, window.screenHeight / 2, size_dot, RED);
		}
		}


        EndDrawing(); // Fin du dessin
    }

    CloseWindow();

    return 0;
}


