#include "main.h"


void manager_input(t_player *player, t_map *map)
{
	if (IsKeyDown(KEY_A))
	{
		if (map->data[(int)(player->x - 0.2)][(int)player->y] == 0)
			player->x -= 0.1;
		
	}
	if (IsKeyDown(KEY_D))
	{
		if (map->data[(int)(player->x + 0.1)][(int)player->y] == 0)
			player->x += 0.1;
	}
	if (IsKeyDown(KEY_W))
	{
		if (map->data[(int)player->x][(int)(player->y - 0.2)] == 0)
			player->y -= 0.1;
	}
	if (IsKeyDown(KEY_S))
	{
		if (map->data[(int)player->x][(int)(player->y + 0.1)] == 0)
		player->y += 0.1;
	}
}

int main()
{
    // Initialisation de la fenêtre
    t_window window;
	window.screenWidth = 500;
	window.screenHeight = 500;
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
	player.x = 50.1;
	player.y = 50.5;


	Texture2D base_player_text = LoadTexture("textures/vaisseau.png");
	Texture2D base_wall_text = LoadTexture("textures/block.png");
	Texture2D base_void_text = LoadTexture("textures/rien.png");

	Texture2D player_text = ResizeTexture(base_player_text, window.sprite_size, window.sprite_size);
	Texture2D wall_text = ResizeTexture(base_wall_text, window.sprite_size, window.sprite_size);
	Texture2D void_text = ResizeTexture(base_void_text, window.sprite_size, window.sprite_size);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Démarrer le dessin
		ClearBackground(BLACK);
        BeginDrawing();
		manager_input(&player, &map);

		int nbr_text_x = (window.screenWidth / window.sprite_size) / 2;
		int nbr_text_y = (window.screenHeight / window.sprite_size) / 2;
		

		float offset_x = -(player.x - (int)player.x);
		float offset_y = -(player.y - (int)player.y);
		

		// printf("number of text_x = %d, number of text_y = %d\n", nbr_text_x, nbr_text_y);
		for (int y = -nbr_text_y - 2; y <= nbr_text_y + 2; y++){
		for (int x = -nbr_text_x - 2; x <= nbr_text_x + 2; x++)
		{
			
			int text_x = (offset_x + x + nbr_text_x + 1) * window.sprite_size;
			int text_y = (offset_y + y + nbr_text_y + 1) * window.sprite_size;
			// printf("x = %d, y = %d\n", text_x, text_y);
			// if ( text_x < 0 || text_x > window.screenWidth || text_y < 0 || text_y > window.screenHeight)
			// 	continue;
			int type = map.data[(int)player.x + x ][(int)player.y + y];

			if (type == 0)
				DrawTexture(void_text, text_x, text_y, WHITE);
			else 
				DrawTexture(wall_text, text_x, text_y, WHITE);
			int size_dot = 8;
			DrawCircle(window.screenWidth / 2 + size_dot/2, window.screenHeight / 2 + size_dot/2, size_dot, RED);
		}
		}


        EndDrawing(); // Fin du dessin
    }

    // Fermer la fenêtre et nettoyer les ressources
    CloseWindow();

    return 0;
}


