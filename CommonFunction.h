#pragma once
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H

#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>

#define NAME_OF_THE_APP "Brave Soldier" //Name of the app

static SDL_Window* g_window = NULL;     //Console of the app
static SDL_Renderer* g_screen = NULL;   //Background of the app
static SDL_Event g_event;			    //Action in the app

//Screen
const int SCREEN_WIDTH = 1280; //Width of the screen
const int SCREEN_HEIGHT = 640; //Height of the screen
const int SCREEN_BPP = 32;     //BPP (Bit per pixel) of the screen

const int RENDER_DRAW_COLOR = 0xFF; //Background color when upload

const int COLOR_KEY_R = 167;   //Red gamma of the object's background
const int COLOR_KEY_G = 175;   //Green gamma of the object's background
const int COLOR_KEY_B = 180;   //Blue gamma of the object's background

//Tile map index
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define BLANK_TILE 0

//Main object
#define GRAVITY 0.1
#define MAX_SPEED 1
#define MOVING_SPEED 1
#define FRAMES 8

//Variable will be used to handle input
typedef struct Input
{
	int left_;
	int right_;

	int up_;
	int down_;
	
	int jump_;
};

//Variable will be used for tile map
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
