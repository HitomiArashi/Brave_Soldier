#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>

const std::string NAME_OF_THE_APP = "Brave Soldier"; //Name of the app

static SDL_Window* g_window = NULL;     //Console of the app
static SDL_Renderer* g_screen = NULL;   //Background of the app
static SDL_Event g_event;			    //Action in the app

/**
 * @brief Some static information about screen
 * 
 */
enum Screen
{
	FRAME_PER_SECOND = 35, //FPS

	SCREEN_WIDTH = 1280, //Width of the screen
	SCREEN_HEIGHT = 640, //Height of the screen
	SCREEN_BPP = 32,	 //BPP (Bit per pixel) of the screen

	RENDER_DRAW_COLOR = 0xFF, //Background color when upload

	COLOR_KEY_R = 167,	//Red gamma of the object's background
	COLOR_KEY_G = 175,	//Green gamma of the object's background
	COLOR_KEY_B = 180,	//Blue gamma of the object's background
};

/**
 * @brief Some static information about tile map
 * 
 */
enum Tile_map
{
	TILE_SIZE = 64,
	MAX_MAP_X = 400,
	MAX_MAP_Y = 10,
	BLANK_TILE = 0,
};

/**
 * @brief Some static information about main object
 * 
 */
enum Main
{
	JUMP_VAL = 45,
	GRAVITY = 5,
	MAX_SPEED = 10,
	MOVING_SPEED = 10,
	FRAMES = 8,
};

/**
 * @brief Some static information about support stuff
 * 
 */
enum Support
{
	STATE_SP = 4,
};

/**
 * @brief Variable will be used to handle input
 * 
 */
typedef struct Input
{
	int left_;
	int right_;

	int up_;
	int down_;
	
	int jump_;
};

/**
 * @brief Variable will be used for tile map
 * 
 */
typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	std::string file_name_;
};

#endif // !COMMON_FUNCTION_H_
