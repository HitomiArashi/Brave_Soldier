#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	width_frame_ = 0;
	height_frame_ = 0;

	x_val_ = 0;
	y_val_ = 0;

	x_pos_ = 0;
	y_pos_ = 0;

	on_ground_ = 0;
	come_back_time_ = 0;

	frame_ = 0;

	animation_a_ = 0;
	animation_b_ = 0;

	input_type_.left_ = 0;
	type_move_ = STATIC_THREAT;
}

ThreatObject::~ThreatObject()
{
	;
}

void ThreatObject::InitThreats()
{
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 256)
	{
		x_pos_ -= 256;
		animation_a_ -= 256;
		animation_b_ -= 256;
	}
	else
	{
		x_pos_ = 0;
	}
	y_pos_ = 0;
	come_back_time_ = 0;
	input_type_.left_ = 1;
}

void ThreatObject::SetClip()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < FRAMES; i++)
		{
			frame_clip_[i].x = width_frame_ * i;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret)
	{
		width_frame_ = rect_.w / THREAT_FRAME_NUM;
		height_frame_ = rect_.w;
		return true;
	}
	return ret;
}

void ThreatObject::Show(SDL_Renderer* des)
{
	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if (frame_ >= 8)
			frame_ = 0;

		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect rendQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
	}
}

void ThreatObject::HandleMove(Map& gMap)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += THREAT_GRAVITY;
		if (y_val_ >= THREAT_MAX_SPEED)
		{
			y_val_ = THREAT_MAX_SPEED;
		}

		if (input_type_.left_ == 1 && type_move_ == MOVE_IN_SPACE_THREAT)
		{
			x_val_ -= THREAT_SPEED;
		}
		else if (input_type_.right_ == 1 && type_move_ == MOVE_IN_SPACE_THREAT)
		{
			x_val_ += THREAT_SPEED;
		}

		CheckCollid(gMap);
	}
	else if (come_back_time_ > 0)
	{
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			InitThreats();
		}
	}
}

void ThreatObject::CheckCollid(Map& gMap)
{
	int x1 = 0, x2 = 0; //Pos for corner of the part of screen to show
	int y1 = 0, y2 = 0;

	//Check horizontal
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) //Still in range
	{
		if (x_val_ > 0) //Moving to right direct
		{
			int val1 = gMap.tile[y1][x2];
			int val2 = gMap.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_SP) || (val2 != BLANK_TILE && val2 != STATE_SP)) //Collided
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) // Moving to left direct
		{
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y2][x1];
			if ((val1 != BLANK_TILE && val1 != STATE_SP) || (val2 != BLANK_TILE && val2 != STATE_SP)) //Collided
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	//Check vertical
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) //Still in range
	{
		if (y_val_ > 0) //Go down (fall)
		{
			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];
			if ((val1 != BLANK_TILE && val1 != STATE_SP) || (val2 != BLANK_TILE && val2 != STATE_SP)) //Collid
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_frame_ + 1;
				y_val_ = 0;
				on_ground_ = true;
			}
		}
		else if (y_val_ < 0) //Go up (jump)
		{
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y2][x1];
			if ((val1 != BLANK_TILE && val1 != STATE_SP) || (val2 != BLANK_TILE && val2 != STATE_SP)) //Collid
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_frame_ + 1;
				y_val_ = 0;
				on_ground_ = true;
			}
		}
	}

	//Able to move
	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) //Out of range
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > gMap.max_x_)
	{
		x_pos_ = gMap.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > gMap.max_y_) //Fall into chasm
	{
		come_back_time_ = 60;
	}
}

void ThreatObject::ImpMoveType(SDL_Renderer* screen)
{
	if (type_move_ == STATIC_THREAT)
	{
		;
	}
	else
	{
		if (on_ground_ == true)
		{
			if (x_pos_ > animation_b_)
			{
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("Resources//img//threat_left.png", screen);
			}
			else if (x_pos_ < animation_a_)
			{
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				LoadImg("Resources//img//threat_right.png", screen);
			}
		}
		else
		{
			if (input_type_.left_ == 1)
			{
				LoadImg("Resources//img//threat_left.png", screen);
			}
			else
			{
				;//
			}
		}
	}
}