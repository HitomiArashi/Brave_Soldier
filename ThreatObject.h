#pragma once
#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"

const int THREAT_FRAME_NUM = 10;
const int THREAT_GRAVITY = 5;
const int THREAT_MAX_SPEED = 20;

class ThreatsObject : public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();

	void set_x_val(const float &x_val){x_val_ = x_val;}
	void set_y_val(const float &y_val){y_val_ = y_val;}

	void set_x_pos(const float &x_pos){x_pos_ = x_pos;}
	void set_y_pos(const float &y_pos) { y_pos_ = y_pos;}

	float get_x_pos() const {return x_pos_;}
	float get_y_pos() const {return y_pos_;}

	void SetMapXY(const int& map_x, const int& map_y) {map_x_ = map_x; map_y_ = map_y;}

	void SetClip();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);

	int get_width_frame() const {return width_frame_;}
	int get_height_frame() const {return height_frame_;}
	void DoPlayer(Map& gMap);
	void CheckColMap(Map& gMap);
private:
	int map_x_;
	int map_y_;

	float x_pos_;
	float y_pos_;

	float x_val_;
	float y_val_;

	bool on_ground_;
	int come_back_time_;

	SDL_Rect frame_clip_[THREAT_FRAME_NUM];

	int width_frame_;
	int height_frame_;

	int frame_;
};

#endif // !THREAT_OBJECT_H_
