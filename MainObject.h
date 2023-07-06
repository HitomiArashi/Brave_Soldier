#pragma once
#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"

class MainObject : public BaseObject
{
private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	bool on_ground_;

	int width_frame_;
	int height_frame_;

	int map_x_;
	int map_y_;

	SDL_Rect frame_clip_[8];
	Input input_type_;
	int frame_;
	int status_;

public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1
	};

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event even, SDL_Renderer* screen);
	void SetClips();

	void DoPlayer(Map& map_data);
	void CheckColMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y)
	{
		map_x_ = map_x;
		map_y_ = map_y;
	}
	void CenterEntityOnMap(Map& map_data);
};

#endif
