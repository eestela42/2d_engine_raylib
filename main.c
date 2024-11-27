#include <stdio.h>
#include <raylib.h>
#include <fcntl.h>
#include <stdlib.h>


void manage_input(int *playerX, int *playerY, char **map)
{
	if (IsKeyPressed(KEY_UP))
	{
			map[*playerY][*playerX] = 0;
			*playerY -= 1;
			map[*playerY][*playerX] = 2;
		
	}
	if (IsKeyPressed(KEY_DOWN))
	{
			map[*playerY][*playerX] = 0;
			*playerY += 1;
			map[*playerY][*playerX] = 2;
	}
	if (IsKeyPressed(KEY_LEFT))
	{
			map[*playerY][*playerX] = 0;
			*playerX -= 1;
			map[*playerY][*playerX] = 2;
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
			map[*playerY][*playerX] = 0;
			*playerX += 1;
			map[*playerY][*playerX] = 2;
	}

}

int main()
{
    // Initialisation de la fenêtre
    const int screenWidth = 1800;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "Fenêtre basique avec Raylib");


	char**map = malloc(sizeof(char*) * 100);
	for (int i = 0; i < 100; i++)
	{
		map[i] = malloc(sizeof(char) * 100);
		for (int j = 0; j < 100; j++)
		{
			if ((i + j) % 2 == 0)
				map[i][j] = 1;
			else
				map[i][j] = 0;
			printf("%d", map[i][j]);
		}
	}
	map[50][50] = 2;

    int playerX = 50;
	int playerY = 50;


	Texture2D player_text = LoadTexture("textures/vaisseau.png");
	Texture2D wall_text = LoadTexture("textures/block.png");
	Texture2D void_text = LoadTexture("textures/rien.png");

    SetTargetFPS(60);

    // Boucle principale texture = 200 large
    while (!WindowShouldClose()) {
        // Démarrer le dessin
		ClearBackground(BLACK);
		manage_input(&playerX, &playerY, map);
        BeginDrawing();
		for (int y_t = 0; y_t <  5; y_t++)
		{
			for (int x_t =  0; x_t <  9; x_t++)
			{
				int x = playerX + x_t - 4;
				int y = playerY + y_t - 2;
				if (y < 0 || x < 0 || y >= 100 || x >= 100)
					continue;
				if (map[y][x] == 0)
					DrawTexture(void_text, x_t * 200, y_t * 200, WHITE);
				else if (map[y][x] == 1)
					DrawTexture(wall_text, x_t * 200, y_t * 200, WHITE);
				else if (map[y][x] == 2)
					DrawTexture(player_text, x_t * 200, y_t * 200, WHITE);
			}
		}
	

        EndDrawing(); // Fin du dessin
    }

    // Fermer la fenêtre et nettoyer les ressources
    CloseWindow();

    return 0;
}


