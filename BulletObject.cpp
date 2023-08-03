#include "BulletObject.h"

/**
 * @brief Construct a new Bullet Object:: Bullet Object object
 * 
 */
BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;

	is_move_ = false;

	bullet_type_ = SPHERE_BULLET;
}

/**
 * @brief Destroy the Bullet Object:: Bullet Object object
 * 
 */
BulletObject::~BulletObject()
{

}

/**
 * @brief Upload bullet image
 * 
 * @param des 
 */
void BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	if (bullet_type_ == SPHERE_BULLET)
	{
		LoadImg("Resources//img//sphere.png", des);
	}
	else if (bullet_type_ == LASER_BULLET)
	{
		LoadImg("Resources//img//laser.png", des);
	}
}

/**
 * @brief Handle bullet movement
 * 
 * @param x_border 
 * @param y_border 
 */
void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	if (bullet_dir_ == DIR_RIGHT)
	{
		rect_.x += x_val_;
		if (rect_.x > x_border)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_LEFT)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_UP)
	{
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_UP_LEFT)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_UP_RIGHT)
	{
		rect_.x += x_val_;
		if (rect_.x > x_border)
		{
			is_move_ = false;
		}
		rect_.y -= y_val_;
		if (rect_.y < 0)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_DOWN_LEFT)
	{
		rect_.x -= x_val_;
		if (rect_.x < 0)
		{
			is_move_ = false;
		}
		rect_.y += y_val_;
		if (rect_.y > y_border)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_DOWN_RIGHT)
	{
		rect_.x += x_val_;
		if (rect_.x > x_border)
		{
			is_move_ = false;
		}
		rect_.y += y_val_;
		if (rect_.y > x_border)
		{
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_DOWN)
	{
		rect_.y += y_val_;
		if (rect_.y > y_border)
		{
			is_move_ = false;
		}
	}
}
