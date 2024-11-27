#include "main.h"




int main()
{
    // Initialisation de la fenêtre
    t_window window;
	window.screenWidth = 1920;
	window.screenHeight = 1080;
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
			if ((i + j ) % 2 == 0)
				map.data[i][j] = 0;
			else
				map.data[i][j] = 0;
		}
	}
	
	map.data[50][49] = 1;
    
	//init
	t_player player;
	player.x = 50;
	player.y = 50;


	Texture2D base_player_text = LoadTexture("textures/vaisseau.png");
	Texture2D base_wall_text = LoadTexture("textures/block.png");
	Texture2D base_void_text = LoadTexture("textures/rien.png");

	Texture2D player_text = ResizeTexture(base_player_text, window.sprite_size, window.sprite_size);
	Texture2D wall_text = ResizeTexture(base_wall_text, window.sprite_size, window.sprite_size);
	Texture2D void_text = ResizeTexture(base_void_text, window.sprite_size, window.sprite_size);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Démarrer le dessin
		ClearBackground(RED);
        BeginDrawing();

		int nbr_text_x = window.screenWidth / window.sprite_size + 2;
		int nbr_text_y = window.screenHeight / window.sprite_size + 2;
		

		for (int y = -nbr_text_y; y < -nbr_text_y; y++){
		for (int x = -nbr_text_x; x < -nbr_text_x; x++)
		{
			int draw_x = player.x * window.sprite_size;
			DrawTexture(void_text, x * window.sprite_size, y * window.sprite_size, WHITE);

		}
		}


        EndDrawing(); // Fin du dessin
    }

    // Fermer la fenêtre et nettoyer les ressources
    CloseWindow();

    return 0;
}


