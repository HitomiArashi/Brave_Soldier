#include "game_map.h"

/**
 * @brief Read info in the file contain map
 * 
 * @param name 
 * @return true 
 * @return false 
 */
bool GameMap::LoadMap(const char* name)
{
	FILE* fp = NULL; //Point to the file
	fopen_s(&fp, name, "rb"); //Open the file "name"
	if (fp == NULL) //Failed
	{
		return false;
	}

	game_map_.max_x_ = 0;
	game_map_.max_y_ = 0;
	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);
			//Read the data in fp at each pos (i, j) and save in game_map_.tile with the same pos
			int val = game_map_.tile[i][j]; //Take the data saved
			if (val > 0) //Not empty
			{
				if (j > game_map_.max_x_) //Update max_x_
				{
					game_map_.max_x_ = j;
				}

				if (i > game_map_.max_y_) //Update max_y_
				{
					game_map_.max_y_ = i;
				}
			}
		}
	}

	game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE; //Take the end of the part will be shown
	game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

	game_map_.start_x_ = 0; //Place that start to be shown
	game_map_.start_y_ = 0;

	game_map_.file_name_ = name; //Name of the file will be used
	fclose(fp); //Close the file

	return true;
}

/**
 * @brief Load the image of the tile map
 * 
 * @param screen 
 */
void GameMap::LoadTiles(SDL_Renderer *screen)
{
	char file_img[30]; //Image for each index type
	FILE* fp = NULL; //Point to the file

	for (int i = 0; i < MAX_TILES; i++)
	{
		sprintf_s(file_img, "Resources/map good/%d.png", i); //Convert the file_img[i] point to the file

		fopen_s(&fp, file_img, "rb"); //Open file
		if (fp == NULL) //Failed
		{
			continue;
		}

		fclose(fp); //Close file

		tile_mat[i].LoadImg(file_img, screen); //Upload the file
	}
}

/**
 * @brief Fill the image at each tile map
 * 
 * @param screen 
 */
void GameMap::DrawMap(SDL_Renderer *screen)
{
	//Limit to show the img
	int x1 = 0, x2 = 0;
	int y1 = 0, y2 = 0;

	//Size of the map to show the img
	int map_x = 0;
	int map_y = 0;

	//Where to start
	map_x = game_map_.start_x_ / TILE_SIZE;
	x1 = (game_map_.start_x_ % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	map_y = game_map_.start_y_ / TILE_SIZE;
	y1 = (game_map_.start_y_ % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	//Show the tile map on the screen
	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = game_map_.start_x_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int val = game_map_.tile[map_y][map_x]; //Take the type of map
			if (val > 0)
			{
				tile_mat[val].SetRect(j, i); //Set the pos
				tile_mat[val].Render(screen); //Show on screen
			}
			map_x++;
		}
		map_y++;
	}
}