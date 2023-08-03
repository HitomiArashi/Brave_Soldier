#pragma once
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

/**
 * @brief New data type: BulletObject
 * 
 * @note Handle the bullet object
 */
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

	/**
	 * @brief Group of direction of the bullet
	 * 
	 */
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

	/**
	 * @brief Group of type of bullet
	 * 
	 */
	enum BulletType
	{
		SPHERE_BULLET = 50,
		LASER_BULLET = 51,
	};

	/**
	 * @brief Set the x val object
	 * 
	 * @param x_val 
	 */
	void set_x_val(const int& x_val){x_val_ = x_val;}
	/**
	 * @brief Set the y val object
	 * 
	 * @param y_val 
	 */
	void set_y_val(const int& y_val){y_val_ = y_val;}

	/**
	 * @brief Get the x val object
	 * 
	 * @return int 
	 */
	int get_x_val() const {return x_val_;}
	/**
	 * @brief Get the y val object
	 * 
	 * @return int 
	 */
	int get_y_val() const {return y_val_;}

	/**
	 * @brief Set the is move object
	 * 
	 * @param is_move 
	 */
	void set_is_move(const int& is_move){is_move_ = is_move;}
	/**
	 * @brief Get the is move object
	 * 
	 * @return true 
	 * @return false 
	 */
	bool get_is_move() const {return is_move_;}

	/**
	 * @brief Set the bullet dir object
	 * 
	 * @param bulletDir 
	 */
	void set_bullet_dir(const unsigned int& bulletDir){bullet_dir_ = bulletDir;}
	/**
	 * @brief Get the bullet dir object
	 * 
	 * @return const unsigned int 
	 */
	const unsigned int get_bullet_dir() const {return bullet_dir_;}

	/**
	 * @brief Set the bullet type object
	 * 
	 * @param bulletType 
	 */
	void set_bullet_type(const unsigned int& bulletType){bullet_type_ = bulletType;}
	/**
	 * @brief Get the bullet type object
	 * 
	 * @return const unsigned int 
	 */
	const unsigned int get_bullet_type() const {return bullet_type_;}

	void HandleMove(const int& x_border, const int& y_border);
	void LoadImgBullet(SDL_Renderer* des);
};

#endif // !BULLET_OBJECT_H_
