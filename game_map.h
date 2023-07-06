#pragma once
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunction.h"
#include "BaseObject.h"

#define MAX_TILES 20

//Take the LoadImg and Render from BaseObject only
class TileMat : public BaseObject
{
public:
	TileMat()
	{
		;
	}
	~TileMat()
	{
		;
	}
};

//Map for all gameplay
class GameMap
{
private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
public:
	GameMap()
	{
		;
	}
	~GameMap()
	{
		;
	}

	bool LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	void SetMap(Map& map_data) {
		game_map_ = map_data;
	};
	Map getMap() const {
		return game_map_;
	};
};

#endif