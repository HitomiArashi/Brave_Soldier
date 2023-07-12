#pragma once
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

class BulletObject : public BaseObject
{
private:
	int x_val_;
	int y_val_;

	int x_pos_;
	int y_pos_;

	bool is_move_;

	unsigned int bullet_dir_;

	unsigned int bullet_type_;

public:
	BulletObject();
	~BulletObject();

	enum BulletDir
	{
		DIR_UP = 20,
		DIR_LEFT = 21,
		DIR_RIGHT = 22,
		DIR_UP_LEFT = 23,
		DIR_UP_RIGHT = 24,
		DIR_DOWN_LEFT = 25,
		DIR_DOWN_RIGHT = 26,
		DIR_DOWN = 27
	};

	enum BulletType
	{
		SPHERE_BULLET = 50,
		LASER_BULLET = 51,
	};

	void Set_x_val(const int& x_val)
	{
		x_val_ = x_val;
	}
	void Set_y_val(const int& y_val)
	{
		y_val_ = y_val;
	}

	int Get_x_val() const
	{
		return x_val_;
	}
	int Get_y_val() const
	{
		return y_val_;
	}

	void Set_is_move(const int& is_move)
	{
		is_move_ = is_move;
	}
	bool Get_is_move() const
	{
		return is_move_;
	}

	void Set_bullet_dir(const unsigned int& bulletDir)
	{
		bullet_dir_ = bulletDir;
	}
	const unsigned int Get_bullet_dir() const
	{
		return bullet_dir_;
	}

	void Set_bullet_type(const unsigned int& bulletType)
	{
		bullet_type_ = bulletType;
	}
	const unsigned int Get_bullet_type() const
	{
		return bullet_type_;
	}

	void HandleMove(const int& x_border, const int& y_border);
	void LoadImgBullet(SDL_Renderer* des);
};

#endif // !BULLET_OBJECT_H_
