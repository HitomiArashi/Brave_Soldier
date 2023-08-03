#pragma once
#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunction.h"
#include "BaseObject.h"

#define MAX_TILES 20

/**
 * @brief New data type: TileMat
 * 
 * @note Take the LoadImg and Render from BaseObject only
 */
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

/**
 * @brief New data type: GameMap
 * 
 * @note Map for all gameplay
 */
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

	/**
	 * @brief Set the Map object
	 * 
	 * @param map_data 
	 */
	void SetMap(Map& map_data) {
		game_map_ = map_data;
	};
	/**
	 * @brief Get the Map object
	 * 
	 * @return Map 
	 */
	Map getMap() const {
		return game_map_;
	};
};

#endif