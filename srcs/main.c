#include "main.h"

void createBombe(t_player *player, t_map *map)
{
	for (int i = 0; i < player->nbr_bombe; i++)
	{
		if (player->bombe[i] == NULL && map->data[(int)player->x][(int)player->y] == 0)
		{
			printf("Bombe created\n");
			player->bombe[i] = malloc(sizeof(t_bombe));
			player->bombe[i]->x = player->x;
			player->bombe[i]->y = player->y;
			player->bombe[i]->time_crea = currentTimeMillis();
			player->bombe[i]->power = player->power_bombe;
			map->data[(int)player->x][(int)player->y] = 5;
			player->bombe[i]->sound = LoadSoundFromWave(player->bomb_sound);
			break;
		}
	}
}

void manager_input(t_player *player, t_map *map)
{
	if (IsKeyDown(KEY_A))
	{
		if (player->x > 1 && map->data[(int)(player->x - 0.1)][(int)player->y] != 1)
			player->x -= 0.1;
		
	}
	if (IsKeyDown(KEY_D))
	{
		if (player->x < map->size_X - 1 && map->data[(int)(player->x + 0.1)][(int)player->y] != 1)
			player->x += 0.1;
	}
	if (IsKeyDown(KEY_W))
	{
		if (player->y > 1 && map->data[(int)player->x][(int)(player->y - 0.1)] != 1)
			player->y -= 0.1;
	}
	if (IsKeyDown(KEY_S))
	{
		if (player->y < map->size_Y - 1 && map->data[(int)player->x][(int)(player->y + 0.1)] != 1)
			player->y += 0.1;
	}
	if (IsKeyDown(KEY_SPACE))
	{
		createBombe(player, map);
	}
	for (int i = 0; i < player->nbr_bombe; i++)
	{
		clock_t now = clock();

		if (player->bombe[i] != NULL && currentTimeMillis() - player->bombe[i]->time_crea >= 3 * 1000)
		{
			printf("Bombe explo\n");
			PlaySound(player->bombe[i]->sound);
			for (int explo = -player->bombe[i]->power; explo <= player->bombe[i]->power; explo++)
			{
				if (explo == 0)
					continue;
				//check case explo en X
				if (player->bombe[i]->x + explo >= 0 && player->bombe[i]->x + explo < map->size_X)
				{
					if (map->data[player->bombe[i]->x + explo][player->bombe[i]->y] == 1)
						map->data[player->bombe[i]->x + explo][player->bombe[i]->y] = 0;
					if (map->data[player->bombe[i]->x + explo][player->bombe[i]->y] == 5)
					{
						for (int j = 0; j < player->nbr_bombe; j++)
						{
							if (player->bombe[j] != NULL && player->bombe[j]->x == player->bombe[i]->x + explo && player->bombe[j]->y == player->bombe[i]->y)
								{
									printf("Bombe explo + 1\n");
									PlaySound(player->bombe[i]->sound);

									free(player->bombe[j]);
									player->bombe[j] = NULL;
									map->data[player->bombe[i]->x + explo][player->bombe[i]->y] = 6;
									break;
								}
						}
					}

				}
				//check case explo en Y
				if (player->bombe[i]->y + explo >= 0 && player->bombe[i]->y + explo < map->size_Y)
				{
					if (map->data[player->bombe[i]->x][player->bombe[i]->y + explo] == 1)
						map->data[player->bombe[i]->y ][player->bombe[i]->y + explo] = 0;
					if (map->data[player->bombe[i]->x][player->bombe[i]->y + explo] == 5)
					{
						for (int j = 0; j < player->nbr_bombe; j++)
						{
							if (player->bombe[j] != NULL && player->bombe[j]->y == player->bombe[i]->y + explo && player->bombe[j]->x == player->bombe[i]->x)
								{
									printf("Bombe explo - 1\n");
									PlaySound(player->bombe[i]->sound);

									free(player->bombe[j]);
									player->bombe[j] = NULL;
									map->data[player->bombe[i]->x][player->bombe[i]->y + explo] = 6;
									break;
								}
						}
					}
				}
			}
			map->data[player->bombe[i]->x][player->bombe[i]->y] = 6;
			free(player->bombe[i]);

			player->bombe[i] = NULL;
		}
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
	InitAudioDevice();
	
	Font customFont = LoadFont("textures/robot/Robot-Black.ttf");


	//map en brut
	srand(time(0));

	t_map map;
	map.size_X = 1000;
	map.size_Y = 1000;
	map.data = malloc(sizeof(char*) * map.size_X);
	for (int i = 0; i < map.size_X; i++)
	{
		map.data[i] = malloc(sizeof(char) * map.size_Y);
		for (int j = 0; j < map.size_Y; j++)
		{
			if (rand() % 100 < 10)
			{
				map.data[i][j] = 1;
				continue;
			}
				map.data[i][j] = 0;
		}
	}
	
	map.data[map.size_X / 2][map.size_Y / 2] = 0;
    
	//init
	t_player player;
	player.x = map.size_X / 2;
	player.y = map.size_Y / 2;
	player.nbr_bombe = 100;
	player.power_bombe = 10;
	player.bombe = malloc(sizeof(t_bombe) * player.nbr_bombe);
	for (int i = 0; i < 5; i++)
		player.bombe[i] = NULL;
	Wave sound = LoadWave("textures/PAM.wav");
	player.bomb_sound = sound;


	Texture2D base_player_text = LoadTexture("textures/vaisseau.png");
	Texture2D base_wall_text = LoadTexture("textures/wall.jpg");
	Texture2D base_void_text = LoadTexture("textures/dirt.jpeg");
	Texture2D base_feu_text = LoadTexture("textures/feu.jpeg");

	Texture2D player_text = ResizeTexture(base_player_text, window.sprite_size, window.sprite_size);
	Texture2D wall_text = ResizeTexture(base_wall_text, window.sprite_size, window.sprite_size);
	Texture2D void_text = ResizeTexture(base_void_text, window.sprite_size, window.sprite_size);

	Texture2D feu_text_up = ResizeTexture(base_feu_text, window.sprite_size, window.sprite_size * 11);
	Texture2D feu_text_line = ResizeTexture(base_feu_text, window.sprite_size * 11, window.sprite_size);

    SetTargetFPS(60);

	int nbr_text_x = (window.screenWidth / window.sprite_size) + 2;
	int nbr_text_y = (window.screenHeight / window.sprite_size) + 2;

    while (!WindowShouldClose()) {

        // Démarrer le dessin
		ClearBackground(BLACK);
        BeginDrawing();
		manager_input(&player, &map);

		// printf("Player x = %f, y = %f\n", player.x, player.y);

		//on recupere la partie decimale de la pos du player
		float offset_x = -(player.x - (int)player.x);
		float offset_y = -(player.y - (int)player.y);

		int fire_nbr = 0;
		int *fires = malloc(sizeof(int) * (player.nbr_bombe * 2));

		// printf("offset_x = %f, offset_y = %f\n", offset_x, offset_y);
		
		//print map
		// for (int i = 0; i < map.size_Y; i++){
		// 	for (int j = 0; j < map.size_X; j++)
		// 	{
		// 		// printf("%d", map.data[i][j]);
		// 		if (map.data[i][j] == 5)
		// 			printf("bomb found\n");
		// 	}
		// 	// printf("\n");
		// }
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

			if (pos_block_x < 0 || pos_block_x >= map.size_X || pos_block_y < 0 || pos_block_y >= map.size_Y)
				continue;

			int time_fire = 16;

			int type = map.data[pos_block_x][pos_block_y];
			if (type == 0)
				DrawTexture(void_text, text_x, text_y, WHITE);
			else if (type == 1)
				DrawTexture(wall_text, text_x, text_y, WHITE);
			else if (type == 5)
				DrawTexture(player_text, text_x, text_y, WHITE);
			else if (type >= 6 && type <= time_fire)
			{
				DrawTexture(player_text, text_x, text_y, WHITE);
				if (fire_nbr < player.nbr_bombe)
				{
					fires[fire_nbr * 2] = text_x;
					fires[fire_nbr * 2 + 1] = text_y;
					fire_nbr++;
				}
				map.data[pos_block_x][pos_block_y]++;
				if (time_fire <= map.data[pos_block_x][pos_block_y])
					map.data[pos_block_x][pos_block_y] = 0;
			}
			

		}
		}
			// DrawTexture(feu_text_up, window.screenWidth / 2, window.screenHeight / 2, WHITE);
		for (int i = 0; i < fire_nbr * 2; i += 2)
		{
			DrawTexture(feu_text_up, fires[i], fires[i + 1] - 5 * window.sprite_size, WHITE);
			DrawTexture(feu_text_line , fires[i]  - 5 * window.sprite_size, fires[i + 1], WHITE);
		}
		free(fires);
		int size_dot = 15;
		DrawCircle(window.screenWidth / 2, window.screenHeight / 2, size_dot, RED);
		DrawTextEx(customFont, "Move =  WASD\nBomb = SPACE", (Vector2){50, 50}, 60, 3, BLACK);
        EndDrawing(); // Fin du dessin
    }

    CloseWindow();

    return 0;
}


