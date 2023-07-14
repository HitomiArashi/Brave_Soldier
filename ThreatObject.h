#pragma once
#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "CommonFunction.h"
#include "BaseObject.h"

#define THREAT_FRAME_NUM 8

class ThreatObject : public BaseObject
{
private:
	int frame_;
	
	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[THREAT_FRAME_NUM];

	bool on_ground_;
	int come_back_time_;

	float x_pos_;
	float y_pos_;

	float x_val_;
	float y_val_;

	int map_x_;
	int map_y_;

	int type_move_;
	int animation_a_;
	int animation_b_;
	Input input_type_;

public:
	ThreatObject();
	~ThreatObject();

	enum TypeMove
	{
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
	};

	void InitThreats();

	void set_x_val(const float& x_val)
	{
		x_val_ = x_val;
	}
	void set_y_val(const float& y_val)
	{
		y_val_ = y_val;
	}
	
	void set_x_pos(const float& xp)
	{
		x_pos_ = xp;
	}
	void set_y_pos(const float& yp)
	{
		y_pos_ = yp;
	}

	float get_x_pos() const
	{
		return x_pos_;
	}
	float get_y_pos() const
	{
		return y_pos_;
	}

	void SetMapXY(const int& mp_x, const int& mp_y)
	{
		map_x_ = mp_x;
		map_y_ = mp_y;
	}

	void SetClip();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int get_width_frame() const
	{
		return width_frame_;
	}
	int get_height_frame() const
	{
		return height_frame_;
	}

	void HandleMove(Map& gMap);
	void CheckCollid(Map& gMap);

	void set_type_move(const int& type_move)
	{
		type_move_ = type_move;
	}
	void set_animationPos(const int& pos_a, const int& pos_b)
	{
		animation_a_ = pos_a;
		animation_b_ = pos_b;
	}
	void set_input_left(const int& ipleft)
	{
		input_type_.left_ = ipleft;
	}
	void ImpMoveType(SDL_Renderer* screen);
};

#endif // !THREAT_OBJECT_H_
